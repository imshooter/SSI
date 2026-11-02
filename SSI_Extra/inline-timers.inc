#if defined _INC_SSI_EXTRA_INLINE_TIMERS
    #endinput
#endif
#define _INC_SSI_EXTRA_INLINE_TIMERS

#include <open.mp>
#include <SSI\inline>
#include <SSI\collection>

/**
 * Timers that call an inline:
 *
 *     #include <SSI_Extra\inline-timers>
 *
 *     Remind(playerid) {
 *         new
 *             calls = 0
 *         ;
 *
 *         inline OnTick() {
 *             SendClientMessage(playerid, -1, "call %d", ++calls);
 *         }
 *
 *         new const
 *             Timer:timer = Timer_StartInline(using inline OnTick, 1000, 5)
 *         ;
 *     }
 *
 * - A timer takes the inline and frees it when it ends: after its last call,
 *   or when it is stopped.
 * - A count of `0` calls it until the timer is stopped. Any other count calls
 *   it that many times.
 * - The first call comes after `delay`, the same as `interval` when it is not
 *   given.
 * - An inline can stop its own timer. Stopping a timer that ended, or was
 *   never made, does nothing.
 */

/**
 * # Header
 */

#if !defined SSI_TIMERS
    #define SSI_TIMERS (TimerSlot:256)
#endif

#define INVALID_TIMER_ID (Timer:-1)
#define INVALID_TIMER_SLOT (TimerSlot:-1)

static enum E_TIMER_DATA {
    Inline:E_TIMER_INLINE,
    E_TIMER_ID,
    E_TIMER_LEFT,
    E_TIMER_INTERVAL,
    bool:E_TIMER_REPEATING
};

static stock
    Collection<Generation>:TimerSlot<SSI_TIMERS>
;

static stock
    SSI@timer[SSI_TIMERS][E_TIMER_DATA]
;

/**
 * # Functions
 */

/**
 * @brief      Call an inline on a timer.
 *
 * The timer takes the inline, and frees it even when it cannot start. The
 * inline takes no parameters.
 *
 * @param      callback  The inline, as `using inline Name`.
 * @param      interval  Milliseconds between calls.
 * @param      count     Calls to make, or `0` until it is stopped.
 * @param      delay     Milliseconds before the first call, or `-1` for
 *                       `interval`.
 *
 * @return     - the timer
 *             - `INVALID_TIMER_ID` when:
 *                 + the inline could not be captured
 *                 + `interval` is `0` or less, or `count` is below `0`
 *                 + `SSI_TIMERS` timers are running
 */
forward Timer:Timer_StartInline(Inline:callback<>, interval, count = 0, delay = -1);

/**
 * @brief      Stop a timer and free its inline.
 *
 * @param      timer  The timer.
 *
 * @return     - `true` it is stopped
 *             - `false` it ended already, or was never made
 */
forward bool:Timer_Stop(Timer:timer);

/**
 * @brief      Whether a timer is still running.
 *
 * @param      timer  The timer.
 *
 * @return     - `true` it is
 *             - `false` it ended, was stopped, or was never made
 */
forward bool:Timer_IsRunning(Timer:timer);

/**
 * # Internal
 */

forward @SSI_TimerFire(ticket);

#define SSI_Timer_Slot(%0) Collection_Redeem(TimerSlot, _:(%0))

static stock SSI_TimerEndInternal(TimerSlot:slot) {
    if (SSI@timer[slot][E_TIMER_ID] != 0) {
        KillTimer(SSI@timer[slot][E_TIMER_ID]);
    }

    Inline_Free(SSI@timer[slot][E_TIMER_INLINE]);
    Collection_Remove(TimerSlot, slot);
}

/**
 * # Timer
 */

stock Timer:Timer_StartInline(Inline:callback<>, interval, count = 0, delay = -1) {
    new const
        Inline:closure = callback
    ;

    if (!Inline_IsValid(closure)) {
        return INVALID_TIMER_ID;
    }

    if (interval <= 0) {
        Inline_Free(closure);

        return INVALID_TIMER_ID;
    }

    if (count < 0) {
        Inline_Free(closure);

        return INVALID_TIMER_ID;
    }

    new const
        TimerSlot:slot = Collection_Alloc(TimerSlot)
    ;

    if (slot == INVALID_TIMER_SLOT) {
        Inline_Free(closure);

        return INVALID_TIMER_ID;
    }

    new const
        ticket = Collection_Ticket(TimerSlot, slot),
        first = (delay < 0) ? interval : delay,
        bool:repeating = (first == interval && count != 1)
    ;

    SSI@timer[slot][E_TIMER_INLINE] = closure;
    SSI@timer[slot][E_TIMER_LEFT] = count;
    SSI@timer[slot][E_TIMER_INTERVAL] = interval;
    SSI@timer[slot][E_TIMER_REPEATING] = repeating;
    SSI@timer[slot][E_TIMER_ID] = SetTimerEx("@SSI_TimerFire", first, repeating, "i", ticket);

    return Timer:ticket;
}

stock bool:Timer_Stop(Timer:timer) {
    new const
        TimerSlot:slot = SSI_Timer_Slot(timer)
    ;

    if (slot == INVALID_TIMER_SLOT) {
        return false;
    }

    SSI_TimerEndInternal(slot);

    return true;
}

stock bool:Timer_IsRunning(Timer:timer) {
    return SSI_Timer_Slot(timer) != INVALID_TIMER_SLOT;
}

/**
 * # Calls
 */

public @SSI_TimerFire(ticket) {
    new const
        TimerSlot:slot = Collection_Redeem(TimerSlot, ticket)
    ;

    if (slot == INVALID_TIMER_SLOT) {
        return 0;
    }

    if (!SSI@timer[slot][E_TIMER_REPEATING]) {
        SSI@timer[slot][E_TIMER_ID] = 0;

        if (SSI@timer[slot][E_TIMER_LEFT] != 1) {
            SSI@timer[slot][E_TIMER_REPEATING] = true;
            SSI@timer[slot][E_TIMER_ID] = SetTimerEx("@SSI_TimerFire", SSI@timer[slot][E_TIMER_INTERVAL], true, "i", ticket);
        }
    }

    Inline_Call(SSI@timer[slot][E_TIMER_INLINE]);

    if (Collection_Redeem(TimerSlot, ticket) == INVALID_TIMER_SLOT) {
        return 0;
    }

    if (SSI@timer[slot][E_TIMER_LEFT] == 0) {
        return 0;
    }

    if (--SSI@timer[slot][E_TIMER_LEFT] != 0) {
        return 0;
    }

    SSI_TimerEndInternal(slot);

    return 0;
}
