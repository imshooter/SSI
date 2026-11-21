#if defined _INC_SSI_PLAYER_ANIMATION_PRELOAD
    #endinput
#endif
#define _INC_SSI_PLAYER_ANIMATION_PRELOAD

#include <open.mp>

#include <SSI\hooks>

/**
 * Animation libraries loaded ahead. The game loads an animation library the
 * first time one of its animations is played, and that first animation does
 * not play. The libraries given to `PreloadAnimationLibrary` are loaded on the
 * first spawn of each player, so the first animation a script plays shows like
 * the others. Bots of the server are left out.
 *
 * Give only the libraries the scripts play: every library is read from disk
 * by the game on spawn, and all of them at once stall it for seconds and can
 * crash it. PED is always loaded.
 */

/**
 * # Header
 */

#if !defined MAX_PRELOADED_ANIMATION_LIBRARIES
    #define MAX_PRELOADED_ANIMATION_LIBRARIES (32)
#endif

#define MAX_ANIMATION_LIBRARY_NAME (16)

static
    gPreloadedLibrary[MAX_PRELOADED_ANIMATION_LIBRARIES][MAX_ANIMATION_LIBRARY_NAME],
    gPreloadedLibraries,
    bool:gPlayerAnimationsLoaded[MAX_PLAYERS]
;

/**
 * # Functions
 */

/**
 * @brief      Load an animation library for every player on their first
 *             spawn.
 *
 * @param      library  The library, such as `"GYMNASIUM"`.
 *
 * @return     - `true` it is loaded from now on, or was already
 *             - `false` there are `MAX_PRELOADED_ANIMATION_LIBRARIES` already
 */
forward bool:PreloadAnimationLibrary(const library[]);

/**
 * # External
 */

stock bool:PreloadAnimationLibrary(const library[]) {
    for (new i; i != gPreloadedLibraries; ++i) {
        if (strequal(gPreloadedLibrary[i], library, true)) {
            return true;
        }
    }

    if (gPreloadedLibraries == MAX_PRELOADED_ANIMATION_LIBRARIES) {
        return false;
    }

    strcopy(gPreloadedLibrary[gPreloadedLibraries++], library);

    return true;
}

/**
 * # Calls
 */

hook OnPlayerConnect(playerid) {
    gPlayerAnimationsLoaded[playerid] = false;

    return 1;
}

hook OnPlayerSpawn(playerid) {
    if (gPlayerAnimationsLoaded[playerid]) {
        return 1;
    }

    if (IsPlayerNPC(playerid)) {
        return 1;
    }

    gPlayerAnimationsLoaded[playerid] = true;

    for (new i; i != gPreloadedLibraries; ++i) {
        ApplyAnimation(playerid, gPreloadedLibrary[i], "null", 4.1, false, false, false, false, 0, SYNC_NONE);
    }

    return 1;
}
