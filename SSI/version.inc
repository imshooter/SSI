#if defined _INC_SSI_VERSION
    #endinput
#endif
#define _INC_SSI_VERSION

/**
 * The version shared by the SSI libraries and their startup banner. Define
 * `SSI_NO_BANNER` before including SSI to keep the version without the banner.
 *
 * JIT detection uses `OnJITCompile`, as the legacy JIT plugin reports it.
 * Components that do not raise that callback are shown as `not reported`.
 */

#define SSI_VERSION_MAJOR 0
#define SSI_VERSION_MINOR 2
#define SSI_VERSION_PATCH 0
#define SSI_VERSION #SSI_VERSION_MAJOR "." #SSI_VERSION_MINOR "." #SSI_VERSION_PATCH

#if defined SSI_NO_BANNER
    #endinput
#endif

#include <open.mp>

static
    bool:SSI@versionShown,
    bool:SSI@versionJit
;

/**
 * # Internal
 */

static stock SSI@Version_Show() {
    if (SSI@versionShown) {
        return;
    }

    SSI@versionShown = true;

    new const
        padding[] = "                                        "
    ;

    print("");
    print("  +----------------------------------------------------+");
    print("  |                                                    |");
    print("  |                _____   _____   ___                 |");
    print("  |               / ____| / ____| |_ _|                |");
    print("  |              | (___  | (___    | |                 |");
    print("  |               \\___ \\  \\___ \\   | |                 |");
    print("  |               ____) | ____) | _| |_                |");
    print("  |              |_____/ |_____/ |_____|               |");
    print("  |                                                    |");
    print("  |             Pawn libraries for open.mp             |");
    print("  |                                                    |");
    printf("  | Version : %s%s |", SSI_VERSION, padding[strlen(SSI_VERSION)]);
    print("  | GitHub  : https://github.com/imshooter/SSI         |");
    if (SSI@versionJit) {
        print("  | JIT     : detected                                 |");
    } else {
        print("  | JIT     : not reported                             |");
    }
    print("  |                                                    |");
    print("  +----------------------------------------------------+");
    print("");
}

/**
 * # Calls
 */

#if !defined _ALS_OnJITCompile
    forward OnJITCompile();
#endif

public OnJITCompile() {
    #if defined SSI@Version_OnJITCompile
        SSI@versionJit = bool:SSI@Version_OnJITCompile();
    #else
        SSI@versionJit = true;
    #endif

    return _:SSI@versionJit;
}

#if defined _ALS_OnJITCompile
    #undef OnJITCompile
#else
    #define _ALS_OnJITCompile
#endif
#define OnJITCompile SSI@Version_OnJITCompile

#if defined SSI@Version_OnJITCompile
    forward SSI@Version_OnJITCompile();
#endif

public OnGameModeInit() {
    SSI@Version_Show();

    #if defined SSI@Version_OnGameModeInit
        return SSI@Version_OnGameModeInit();
    #else
        return 1;
    #endif
}

#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit SSI@Version_OnGameModeInit

#if defined SSI@Version_OnGameModeInit
    forward SSI@Version_OnGameModeInit();
#endif

public OnFilterScriptInit() {
    SSI@Version_Show();

    #if defined SSI@Version_OnFilterScriptInit
        return SSI@Version_OnFilterScriptInit();
    #else
        return 1;
    #endif
}

#if defined _ALS_OnFilterScriptInit
    #undef OnFilterScriptInit
#else
    #define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit SSI@Version_OnFilterScriptInit

#if defined SSI@Version_OnFilterScriptInit
    forward SSI@Version_OnFilterScriptInit();
#endif
