#if defined _INC_SSI_PLAYER_FPS
    #endinput
#endif
#define _INC_SSI_PLAYER_FPS

/**
 * Frames per second of each player's game. The game lowers the drunk level by
 * one each frame, so the level is set high enough to count from and read
 * again each second. Levels under 2000 are not drawn as drunk.
 *
 * A script that already has a `GetPlayerFPS` keeps its own: this library
 * then adds nothing, and the libraries that read the frame rate use that one.
 * The check also looks for this library's own mark, a function: functions
 * stay known from one compiler pass to the next, so `defined GetPlayerFPS`
 * alone would find this very library on the second pass and drop it there.
 */
#if defined GetPlayerFPS && !defined SSI@PlayerFps_Mark
    #endinput
#endif

#include <open.mp>

#include <SSI\task>
#include <SSI\hooks>

/**
 * # Header
 */

#if !defined PLAYER_FPS_STEP
    #define PLAYER_FPS_STEP (1000)
#endif

#if !defined PLAYER_FPS_DRUNK_START
    #define PLAYER_FPS_DRUNK_START (2000)
#endif

#if !defined PLAYER_FPS_DRUNK_FLOOR
    #define PLAYER_FPS_DRUNK_FLOOR (100)
#endif

#if !defined PLAYER_FPS_MAX
    #define PLAYER_FPS_MAX (300)
#endif

static enum _:E_PLAYER_FPS_DATA {
    E_PLAYER_FPS_RATE,
    E_PLAYER_FPS_LEVEL,
    E_PLAYER_FPS_READ
};

static
    gPlayerFps[MAX_PLAYERS][E_PLAYER_FPS_DATA]
;

/**
 * # Functions
 */

/**
 * @brief      The frames per second of a player's game, measured over the last
 *             second.
 *
 * @param      playerid  Player to read.
 *
 * @return     - the frames per second
 *             - `0` until a second was measured, or for bots
 */
forward GetPlayerFPS(playerid);

/**
 * # Internal
 */

stock SSI@PlayerFps_Mark() {
}

static stock MeasureFpsInternal(playerid) {
    new const
        level = GetPlayerDrunkLevel(playerid),
        now = GetTickCount()
    ;

    if (level < PLAYER_FPS_DRUNK_FLOOR) {
        SetPlayerDrunkLevel(playerid, PLAYER_FPS_DRUNK_START);

        gPlayerFps[playerid][E_PLAYER_FPS_LEVEL] = 0;

        return;
    }

    new const
        frames = gPlayerFps[playerid][E_PLAYER_FPS_LEVEL] - level,
        elapsed = now - gPlayerFps[playerid][E_PLAYER_FPS_READ]
    ;

    if (gPlayerFps[playerid][E_PLAYER_FPS_LEVEL] != 0 && frames > 0 && elapsed > 0 && frames * 1000 / elapsed <= PLAYER_FPS_MAX) {
        gPlayerFps[playerid][E_PLAYER_FPS_RATE] = frames * 1000 / elapsed;
    }

    gPlayerFps[playerid][E_PLAYER_FPS_LEVEL] = level;
    gPlayerFps[playerid][E_PLAYER_FPS_READ] = now;
}

/**
 * # External
 */

stock GetPlayerFPS(playerid) {
    if (!(0 <= playerid < MAX_PLAYERS)) {
        return 0;
    }

    return gPlayerFps[playerid][E_PLAYER_FPS_RATE];
}

/**
 * # Calls
 */

ptask PlayerFpsStep[PLAYER_FPS_STEP](playerid) {
    if (!IsPlayerNPC(playerid)) {
        MeasureFpsInternal(playerid);
    }
}

hook OnPlayerConnect(playerid) {
    gPlayerFps[playerid][E_PLAYER_FPS_RATE] = 0;
    gPlayerFps[playerid][E_PLAYER_FPS_LEVEL] = 0;
    gPlayerFps[playerid][E_PLAYER_FPS_READ] = 0;

    return 1;
}
