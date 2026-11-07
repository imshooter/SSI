#if defined _INC_SSI_TASK
    #endinput
#endif
#define _INC_SSI_TASK

#include <open.mp>
#include <SSI\iterator>

/**
 * Functions that run on their own every so many milliseconds, as the tasks of
 * y_timers. A `task` runs from `OnGameModeInit` while the script lives. A
 * `ptask` runs for each player from the moment they connect until they leave.
 *
 *     #include <SSI\task>
 *     #include <SSI\hooks>
 *
 *     task SaveWorld[60000]() {
 *         SaveHouses();
 *     }
 *
 *     ptask Hunger[30000](playerid) {
 *         new
 *             Float:health
 *         ;
 *
 *         GetPlayerHealth(playerid, health);
 *         SetPlayerHealth(playerid, health - 1.0);
 *     }
 *
 *     Task_Pause(SaveWorld);
 *     PTask_PausePlayer(Hunger, playerid);
 *
 * - The name is a public of the script, so it can also be called as any
 *   function, and two tasks cannot share it.
 * - The interval is read in `OnGameModeInit`, so it can be any expression.
 * - Tasks whose intervals are equal, or one a multiple of the other, start
 *   spread over the interval, as in y_timers: three tasks of a second run at
 *   0, 333 and 666 milliseconds into it, not in the same tick.
 * - Each task is a native repeating timer started by a hook, so a file that
 *   declares one includes `SSI\hooks` last, as for any hook.
 * - Bots connect as players do, so a `ptask` runs for them too.
 */

/**
 * # Header
 */

#if !defined SSI_TASKS
    #define SSI_TASKS (TimerTask:64)
#endif

#define SSI_TASK_NAME (32)

#define INVALID_TIMER_TASK (TimerTask:-1)

static enum E_TASK_DATA {
    E_TASK_NAME[SSI_TASK_NAME],
    E_TASK_INTERVAL,
    E_TASK_TIMER,
    bool:E_TASK_PER_PLAYER,
    bool:E_TASK_PAUSED
};

static stock
    SSI@task[SSI_TASKS][E_TASK_DATA],
    TimerTask:SSI@taskCount
;

/**
 * # Functions
 */

/**
 * @brief      Declare a function that runs every `interval` milliseconds from
 *             `OnGameModeInit`.
 *
 *     task SaveWorld[60000]() {
 *     }
 */
#define task%9\32;%0[%1]() stock TimerTask:SSI@Tk_%0=INVALID_TIMER_TASK;hook OnGameModeInit@%0(){SSI@Tk_%0=SSI@Task_Add(#%0,(%1),false);return 1;}forward %0();public %0()

/**
 * @brief      Declare a function that runs every `interval` milliseconds for
 *             each player, from `OnPlayerConnect` to `OnPlayerDisconnect`.
 *
 *     ptask Hunger[30000](playerid) {
 *     }
 */
#define ptask%9\32;%0[%1](%2) stock TimerTask:SSI@Tk_%0=INVALID_TIMER_TASK,SSI@Tp_%0[MAX_PLAYERS];hook OnGameModeInit@%0(){SSI@Tk_%0=SSI@Task_Add(#%0,(%1),true);return 1;}hook OnPlayerConnect@%0(playerid){SSI@PTask_Start(SSI@Tk_%0,SSI@Tp_%0,playerid);return 1;}hook OnPlayerDisconnect@%0(playerid,reason){SSI@PTask_Stop(SSI@Tp_%0,playerid);return 1;}forward %0(%2);public %0(%2)

/**
 * @brief      Stop a `task` until `Task_Resume`.
 *
 * @param      name  The task.
 *
 * @return     - `true` it was paused
 *             - `false` it was paused already, or is not a `task`
 */
forward bool:Task_Pause(name);
#define Task_Pause(%0) SSI@Task_Pause(SSI@Tk_%0)

/**
 * @brief      Run a paused `task` again. It runs one interval after this.
 *
 * @param      name  The task.
 *
 * @return     - `true` it runs again
 *             - `false` it was not paused, or is not a `task`
 */
forward bool:Task_Resume(name);
#define Task_Resume(%0) SSI@Task_Resume(SSI@Tk_%0)

/**
 * @brief      Stop a `ptask` for every player, and for those who connect,
 *             until `PTask_Resume`.
 *
 * @param      name  The task.
 *
 * @return     - `true` it was paused
 *             - `false` it was paused already, or is not a `ptask`
 */
forward bool:PTask_Pause(name);
#define PTask_Pause(%0) SSI@PTask_Pause(SSI@Tk_%0,SSI@Tp_%0)

/**
 * @brief      Run a paused `ptask` again for every player.
 *
 * @param      name  The task.
 *
 * @return     - `true` it runs again
 *             - `false` it was not paused, or is not a `ptask`
 */
forward bool:PTask_Resume(name);
#define PTask_Resume(%0) SSI@PTask_Resume(SSI@Tk_%0,SSI@Tp_%0)

/**
 * @brief      Stop a `ptask` for one player. It starts again when they
 *             reconnect, or with `PTask_ResumePlayer`.
 *
 * @param      name      The task.
 * @param      playerid  The player.
 *
 * @return     - `true` it was stopped
 *             - `false` it was not running for them
 */
forward bool:PTask_PausePlayer(name, playerid);
#define PTask_PausePlayer(%0,%1) SSI@PTask_Stop(SSI@Tp_%0,(%1))

/**
 * @brief      Run a `ptask` again for one player.
 *
 * @param      name      The task.
 * @param      playerid  The player.
 *
 * @return     - `true` it runs again
 *             - `false` it was running, the player is not connected, or the
 *               task is paused for everyone
 */
forward bool:PTask_ResumePlayer(name, playerid);
#define PTask_ResumePlayer(%0,%1) SSI@PTask_Start(SSI@Tk_%0,SSI@Tp_%0,(%1))

/**
 * # Internal
 */

forward @SSI_TaskSpread();
forward @SSI_TaskFirst(TimerTask:slot);

static stock bool:SSI_TaskIsGlobalInternal(TimerTask:slot) {
    return slot >= TimerTask:0 && slot < SSI@taskCount && !SSI@task[slot][E_TASK_PER_PLAYER];
}

static stock bool:SSI_TaskIsPerPlayerInternal(TimerTask:slot) {
    return slot >= TimerTask:0 && slot < SSI@taskCount && SSI@task[slot][E_TASK_PER_PLAYER];
}

static stock SSI_TaskStartInternal(TimerTask:slot, delay) {
    SSI@task[slot][E_TASK_TIMER] = (delay == 0) ? SetTimer(SSI@task[slot][E_TASK_NAME], SSI@task[slot][E_TASK_INTERVAL], true) : SetTimerEx("@SSI_TaskFirst", delay, false, "i", _:slot);
}

/**
 * # Task
 */

stock TimerTask:SSI@Task_Add(const name[], interval, bool:perPlayer) {
    if (interval <= 0) {
        printf("[task] %s has an interval of %i ms and does not run", name, interval);

        return INVALID_TIMER_TASK;
    }

    if (SSI@taskCount == SSI_TASKS) {
        printf("[task] %s does not run, SSI_TASKS are declared already", name);

        return INVALID_TIMER_TASK;
    }

    new const
        TimerTask:slot = SSI@taskCount++
    ;

    strcopy(SSI@task[slot][E_TASK_NAME], name, SSI_TASK_NAME);
    SSI@task[slot][E_TASK_INTERVAL] = interval;
    SSI@task[slot][E_TASK_PER_PLAYER] = perPlayer;

    if (slot == TimerTask:0) {
        SetTimer("@SSI_TaskSpread", 0, false);
    }

    return slot;
}

stock bool:SSI@Task_Pause(TimerTask:slot) {
    if (!SSI_TaskIsGlobalInternal(slot)) {
        return false;
    }

    if (SSI@task[slot][E_TASK_PAUSED]) {
        return false;
    }

    SSI@task[slot][E_TASK_PAUSED] = true;

    if (SSI@task[slot][E_TASK_TIMER] != 0) {
        KillTimer(SSI@task[slot][E_TASK_TIMER]);
        SSI@task[slot][E_TASK_TIMER] = 0;
    }

    return true;
}

stock bool:SSI@Task_Resume(TimerTask:slot) {
    if (!SSI_TaskIsGlobalInternal(slot)) {
        return false;
    }

    if (!SSI@task[slot][E_TASK_PAUSED]) {
        return false;
    }

    SSI@task[slot][E_TASK_PAUSED] = false;
    SSI_TaskStartInternal(slot, 0);

    return true;
}

/**
 * # Player Task
 */

stock bool:SSI@PTask_Start(TimerTask:slot, timers[MAX_PLAYERS], playerid) {
    if (!SSI_TaskIsPerPlayerInternal(slot)) {
        return false;
    }

    if (SSI@task[slot][E_TASK_PAUSED]) {
        return false;
    }

    if (!IsPlayerConnected(playerid)) {
        return false;
    }

    if (timers[playerid] != 0) {
        return false;
    }

    timers[playerid] = SetTimerEx(SSI@task[slot][E_TASK_NAME], SSI@task[slot][E_TASK_INTERVAL], true, "i", playerid);

    return true;
}

stock bool:SSI@PTask_Stop(timers[MAX_PLAYERS], playerid) {
    if (playerid < 0 || playerid >= MAX_PLAYERS) {
        return false;
    }

    if (timers[playerid] == 0) {
        return false;
    }

    KillTimer(timers[playerid]);
    timers[playerid] = 0;

    return true;
}

stock bool:SSI@PTask_Pause(TimerTask:slot, timers[MAX_PLAYERS]) {
    if (!SSI_TaskIsPerPlayerInternal(slot)) {
        return false;
    }

    if (SSI@task[slot][E_TASK_PAUSED]) {
        return false;
    }

    SSI@task[slot][E_TASK_PAUSED] = true;

    foreach (new playerid : Character) {
        SSI@PTask_Stop(timers, playerid);
    }

    return true;
}

stock bool:SSI@PTask_Resume(TimerTask:slot, timers[MAX_PLAYERS]) {
    if (!SSI_TaskIsPerPlayerInternal(slot)) {
        return false;
    }

    if (!SSI@task[slot][E_TASK_PAUSED]) {
        return false;
    }

    SSI@task[slot][E_TASK_PAUSED] = false;

    foreach (new playerid : Character) {
        SSI@PTask_Start(slot, timers, playerid);
    }

    return true;
}

/**
 * # Calls
 */

public @SSI_TaskSpread() {
    for (new TimerTask:slot; slot != SSI@taskCount; ++slot) {
        if (SSI@task[slot][E_TASK_PER_PLAYER] || SSI@task[slot][E_TASK_PAUSED]) {
            continue;
        }

        new const
            interval = SSI@task[slot][E_TASK_INTERVAL]
        ;

        new
            total,
            before
        ;

        for (new TimerTask:other; other != SSI@taskCount; ++other) {
            if (SSI@task[other][E_TASK_PER_PLAYER]) {
                continue;
            }

            new const
                otherInterval = SSI@task[other][E_TASK_INTERVAL]
            ;

            if (interval % otherInterval != 0 && otherInterval % interval != 0) {
                continue;
            }

            ++total;

            if (other < slot) {
                ++before;
            }
        }

        SSI_TaskStartInternal(slot, interval * before / total);
    }

    return 1;
}

public @SSI_TaskFirst(TimerTask:slot) {
    SSI@task[slot][E_TASK_TIMER] = SetTimer(SSI@task[slot][E_TASK_NAME], SSI@task[slot][E_TASK_INTERVAL], true);

    return 1;
}
