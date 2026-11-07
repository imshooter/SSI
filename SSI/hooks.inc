#include <SSI\unique>

#if defined _INC_y_hooks
    #error SSI\hooks is not compatible with y_hooks
#endif

#if defined _INC_SSI_HOOKS
    #endinput
#endif
#define _INC_SSI_HOOKS

#include <SSI\amx>

/**
 * Hooks, as in y_hooks: any number of functions for one callback, and hooks
 * that replace a native or a function. Every file that hooks includes this
 * last, after its other includes. Each include moves on to new names, so a file
 * hooks the same callback once, or more often with a suffix written after the
 * name of the callback: `hook OnPlayerConnect@1(playerid)`.
 *
 *     #include <SSI\hooks>
 *
 *     hook OnPlayerConnect(playerid) {
 *         SendClientMessage(playerid, -1, "Welcome.");
 *
 *         return 1;
 *     }
 *
 * The hooks of a callback run in the order they were declared, from the first
 * include to the last, and the public of the callback, if the script has one,
 * runs last. The callback returns what they all returned, joined with `&` when
 * its default return is `1` and with `|` when it is `0`. A hook that returns
 * `~0` or `~1` ends the chain there: the callback returns `0` or `1` and nothing
 * after that hook runs. A hook can be written for a state, as a public can:
 * `hook OnPlayerSpawn(playerid) <round:running>`. In a state it does not name,
 * the hook does nothing.
 *
 * The callbacks of open.mp and of the streamer, Pawn.CMD, Pawn.RakNet,
 * crashdetect and sscanf return `1` by default, as in y_hooks, apart from
 * `OnPlayerCommandText` and `OnRconCommand`. Every other callback, as the events
 * a script calls with `CallLocalFunction`, returns `0` by default, so a hook
 * returning `1` makes the callback return `1`. A callback that needs another
 * default sets it with `DEFINE_HOOK_RETURN__(callback, value);`, outside any
 * function.
 *
 * `hook native` replaces a native, and `hook function` or `hook stock` a
 * function of the script. The hook declared last runs first. Inside a hook, a
 * call to the native or function it replaces calls the hook declared before
 * it, and in the first hook it calls the native or the function:
 *
 *     hook native SetPlayerHealth(playerid, Float:health) {
 *         return SetPlayerHealth(playerid, health > 100.0 ? 100.0 : health);
 *     }
 *
 * An include holds any number of these hooks. A native or function hooked
 * twice in one include takes a suffix on the second, as a callback does:
 * `hook native SetPlayerHealth@1(playerid, Float:health)`. Only the calls made
 * by this script are hooked.
 *
 * The chains are built the first time `OnGameModeInit` or `OnFilterScriptInit`
 * runs. Each chain is a few cells of code, written over a function of `nop`s
 * kept for them, which calls the hooks and the public one after another with
 * the arguments copied once, so a hook costs a call and one or two
 * instructions. The public of a callback is turned into its chain. A callback
 * with hooks and no public gets a public named after it, so the server and the
 * plugins find it as if it had been written. A public that only returns `0`,
 * as `event` writes one, in a callback whose default is `0`, is left out of its
 * chain and jumps to it, so calling it as a function runs the hooks. The hooks
 * see `-1` from `numargs`, the same as in y_hooks. Every call to a hooked
 * native or function is pointed at the hook declared last, and the call inside
 * a hook at the one declared before it, so these hooks cost a call each. When
 * the code of the script cannot be read, the script stops at start up with an
 * index out of bounds error.
 */

/**
 * # Header
 */

#if !defined SSI_HOOKS_CODE
    #define SSI_HOOKS_CODE (8192)
#endif

#if !defined SSI_HOOKS_FUNCTIONS
    #define SSI_HOOKS_FUNCTIONS (64)
#endif

/**
 * # Functions
 */

/**
 * @brief      Declare a hook of a callback, with `native` a hook of a native,
 *             or with `function` or `stock` a hook of a function of the
 *             script.
 *
 *     hook OnPlayerDisconnect(playerid, reason) {
 *         return 1;
 *     }
 */
#define hook%0(%1) forward SSI_UNIQUE<@H_%0@...>(%1);SSI_UNIQUE<@H_%0@...>(%1)

/**
 * @brief      Set the default return of a callback: `1` joins the returns of its
 *             hooks with `&`, `0` with `|`.
 *
 *     DEFINE_HOOK_RETURN__(OnPlayerReachGoal, 1);
 */
#define DEFINE_HOOK_RETURN__(%0,%1) forward @Hr_%0();@Hr_%0(){return(%1);}forward @Hr_%0()

/**
 * @brief      Declare an event: a callback the script raises itself by calling
 *             it as a function, which runs its hooks.
 *
 *     event OnPlayerReachGoal(playerid, goal);
 *
 *     ReachGoal(playerid, goal) {
 *         return call OnPlayerReachGoal(playerid, goal);
 *     }
 *
 * The event is a public that returns `0`, so it answers `0` until a hook
 * answers. Raising it costs about 1.8 us less than `CallLocalFunction`, keeps
 * the tags of its arguments, passes strings by reference and is checked by the
 * compiler. The script answers it with hooks, never with a public.
 */
#define event%0(%1) forward%0(%1);public%0(%1){return 0;}forward%0(%1)

/**
 * @brief      Raise an event declared with `event`: its hooks run, and it
 *             answers what they joined. A plain call does the same, and `call`
 *             marks the call as an event.
 *
 *     call OnPlayerReachGoal(playerid, goal);
 *
 * The event's name starts with `On`, as callbacks do.
 */
#define call%0\32;On%1(%2) On%1(%2)

#define @H_%0\32; @H_
#define @H_native%0@%1(%2);%3>(%4) SSI@HT%0:A:B:;(N)(%1)(%2)
#define @H_function%0@%1(%2);%3>(%4) SSI@HT%0:A:B:;(F)(%1)(%2)
#define @H_stock%0@%1(%2);%3>(%4) SSI@HT%0:A:B:;(F)(%1)(%2)
#define SSI@HT%9\32;%0:%1:%2:%3;(%4)(%5)(%6) SSI@H%4%2(%1)(%0)(%5)(%6)
#define SSI@HNA(%0)(%1)(%2)(%3) %1:%0@Hn@%2(%3);forward @Hi@%0@%2();@Hi@%0@%2(){__emit(sysreq.c %0,call %0@Hn@%2);}%1:%0@Hn@%2(%3)
#define SSI@HNB(%0)(%1)(%2)(%3) %1@Hn@%2(%3);forward @Hi@%1@%2();@Hi@%1@%2(){__emit(sysreq.c %1,call %1@Hn@%2);}%1@Hn@%2(%3)
#define SSI@HFA(%0)(%1)(%2)(%3) %1:%0@Hn@%2(%3);forward @Hi@%0@%2();@Hi@%0@%2(){__emit(call %0,call %0@Hn@%2);}%1:%0@Hn@%2(%3)
#define SSI@HFB(%0)(%1)(%2)(%3) %1@Hn@%2(%3);forward @Hi@%1@%2();@Hi@%1@%2(){__emit(call %1,call %1@Hn@%2);}%1@Hn@%2(%3)

/**
 * # Internal
 */

static enum {
    SSI_OP_LOAD_PRI = 1,
    SSI_OP_LOAD_S_PRI = 3,
    SSI_OP_LOAD_S_ALT = 4,
    SSI_OP_CONST_PRI = 11,
    SSI_OP_CONST_ALT = 12,
    SSI_OP_STOR_PRI = 15,
    SSI_OP_STOR_S_PRI = 17,
    SSI_OP_LCTRL = 31,
    SSI_OP_SCTRL = 32,
    SSI_OP_MOVE_PRI = 33,
    SSI_OP_MOVE_ALT = 34,
    SSI_OP_XCHG = 35,
    SSI_OP_PUSH_C = 39,
    SSI_OP_POP_PRI = 42,
    SSI_OP_STACK = 44,
    SSI_OP_PROC = 46,
    SSI_OP_RETN = 48,
    SSI_OP_CALL = 49,
    SSI_OP_JUMP = 51,
    SSI_OP_JZER = 53,
    SSI_OP_JEQ = 55,
    SSI_OP_JSLESS = 61,
    SSI_OP_SUB = 79,
    SSI_OP_AND = 81,
    SSI_OP_OR = 82,
    SSI_OP_INVERT = 86,
    SSI_OP_ADD_C = 87,
    SSI_OP_ZERO_PRI = 89,
    SSI_OP_ZERO_ALT = 90,
    SSI_OP_MOVS = 117,
    SSI_OP_HALT = 120,
    SSI_OP_SYSREQ_C = 123,
    SSI_OP_SWITCH = 129,
    SSI_OP_CASETBL = 130,
    SSI_OP_NOP = 134,
    SSI_OP_BREAK = 137
}

static enum E_SSI_HOOK_FUNCTION {
    E_SSI_HOOK_TARGET,
    bool:E_SSI_HOOK_NATIVE,
    E_SSI_HOOK_BODY,
    E_SSI_HOOK_NEXT,
    E_SSI_HOOK_HEAD
}

static stock
    SSI@hookAt,
    SSI@hookCapacity,
    bool:SSI@hookCounting,
    SSI@hookStart,
    SSI@hookCopy,
    SSI@hookRareAnd,
    SSI@hookRareOr,
    SSI@hookTail,
    SSI@hookNeutral[2],
    SSI@hookPublics,
    SSI@hookCount,
    SSI@hookSize,
    SSI@hookGameModeInit,
    SSI@hookFilterScriptInit,
    bool:SSI@hookPlain,
    SSI@hookSwitch,
    SSI@hookCasetbl,
    SSI@hookCells[160][2],
    SSI@hookCellCount,
    SSI@hookFunction[SSI_HOOKS_FUNCTIONS][E_SSI_HOOK_FUNCTION],
    SSI@hookFunctions,
    bool:SSI@hookReady
;

static stock const SSI@hookCallbacks[][] = {
    !"OnActorStreamIn",
    !"OnActorStreamOut",
    !"OnCachedInit",
    !"OnClientCheckResponse",
    !"OnDialogResponse",
    !"OnDynamicActorStreamIn",
    !"OnDynamicActorStreamOut",
    !"OnDynamicObjectMoved",
    !"OnEnterExitModShop",
    !"OnFilterScriptExit",
    !"OnFilterScriptInit",
    !"OnGameModeExit",
    !"OnGameModeInit",
    !"OnIncomingConnection",
    !"OnIncomingPacket",
    !"OnIncomingRPC",
    !"OnNPCChangeNode",
    !"OnNPCCreate",
    !"OnNPCDeath",
    !"OnNPCDestroy",
    !"OnNPCFinishMove",
    !"OnNPCFinishMovePath",
    !"OnNPCFinishMovePathPoint",
    !"OnNPCFinishNode",
    !"OnNPCFinishNodePoint",
    !"OnNPCGiveDamage",
    !"OnNPCPlaybackEnd",
    !"OnNPCPlaybackStart",
    !"OnNPCRespawn",
    !"OnNPCSpawn",
    !"OnNPCTakeDamage",
    !"OnNPCWeaponShot",
    !"OnNPCWeaponStateChange",
    !"OnObjectMoved",
    !"OnOutcomingPacket",
    !"OnOutcomingRPC",
    !"OnOutgoingPacket",
    !"OnOutgoingRPC",
    !"OnPickupStreamIn",
    !"OnPickupStreamOut",
    !"OnPlayerClickGangZone",
    !"OnPlayerClickMap",
    !"OnPlayerClickPlayer",
    !"OnPlayerClickPlayerGangZone",
    !"OnPlayerClickPlayerTextDraw",
    !"OnPlayerClickTextDraw",
    !"OnPlayerCommandPerformed",
    !"OnPlayerCommandReceived",
    !"OnPlayerConnect",
    !"OnPlayerDeath",
    !"OnPlayerDisconnect",
    !"OnPlayerEditAttachedObject",
    !"OnPlayerEditDynamicObject",
    !"OnPlayerEditObject",
    !"OnPlayerEnterCheckpoint",
    !"OnPlayerEnterDynamicArea",
    !"OnPlayerEnterDynamicCP",
    !"OnPlayerEnterDynamicRaceCP",
    !"OnPlayerEnterGangZone",
    !"OnPlayerEnterPlayerGangZone",
    !"OnPlayerEnterRaceCheckpoint",
    !"OnPlayerEnterVehicle",
    !"OnPlayerExitVehicle",
    !"OnPlayerExitedMenu",
    !"OnPlayerFinishedDownloading",
    !"OnPlayerGiveDamage",
    !"OnPlayerGiveDamageActor",
    !"OnPlayerGiveDamageDynamicActor",
    !"OnPlayerInteriorChange",
    !"OnPlayerKeyStateChange",
    !"OnPlayerLeaveCheckpoint",
    !"OnPlayerLeaveDynamicArea",
    !"OnPlayerLeaveDynamicCP",
    !"OnPlayerLeaveDynamicRaceCP",
    !"OnPlayerLeaveGangZone",
    !"OnPlayerLeavePlayerGangZone",
    !"OnPlayerLeaveRaceCheckpoint",
    !"OnPlayerObjectMoved",
    !"OnPlayerPickUpDynamicPickup",
    !"OnPlayerPickUpPickup",
    !"OnPlayerPickUpPlayerPickup",
    !"OnPlayerPickupStreamIn",
    !"OnPlayerPickupStreamOut",
    !"OnPlayerRequestClass",
    !"OnPlayerRequestDownload",
    !"OnPlayerRequestSpawn",
    !"OnPlayerSelectDynamicObject",
    !"OnPlayerSelectObject",
    !"OnPlayerSelectedMenuRow",
    !"OnPlayerShootDynamicObject",
    !"OnPlayerSpawn",
    !"OnPlayerStateChange",
    !"OnPlayerStreamIn",
    !"OnPlayerStreamOut",
    !"OnPlayerTakeDamage",
    !"OnPlayerText",
    !"OnPlayerUpdate",
    !"OnPlayerWeaponShot",
    !"OnRconLoginAttempt",
    !"OnRuntimeError",
    !"OnScriptLoadPlayer",
    !"OnScriptUnloadPlayer",
    !"OnTrailerUpdate",
    !"OnUnoccupiedVehicleUpdate",
    !"OnVehicleDamageStatusUpdate",
    !"OnVehicleDeath",
    !"OnVehicleMod",
    !"OnVehiclePaintjob",
    !"OnVehicleRespray",
    !"OnVehicleSirenStateChange",
    !"OnVehicleSpawn",
    !"OnVehicleStreamIn",
    !"OnVehicleStreamOut",
    !"Streamer_OnItemStreamIn",
    !"Streamer_OnItemStreamOut",
    !"Streamer_OnPluginError"
};

#define SSI@NOP8 nop, nop, nop, nop, nop, nop, nop, nop
#define SSI@NOP64 SSI@NOP8, SSI@NOP8, SSI@NOP8, SSI@NOP8, SSI@NOP8, SSI@NOP8, SSI@NOP8, SSI@NOP8
#define SSI@NOP512 SSI@NOP64, SSI@NOP64, SSI@NOP64, SSI@NOP64, SSI@NOP64, SSI@NOP64, SSI@NOP64, SSI@NOP64

static stock SSI_HooksSpaceInternal() {
    __emit(SSI@NOP512);
    __emit(SSI@NOP512);
    __emit(SSI@NOP512);
    __emit(SSI@NOP512);

    #if SSI_HOOKS_CODE > 2048
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
    #endif

    #if SSI_HOOKS_CODE > 4096
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
    #endif

    #if SSI_HOOKS_CODE > 6144
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
    #endif

    #if SSI_HOOKS_CODE > 8192
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
    #endif

    #if SSI_HOOKS_CODE > 10240
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
    #endif

    #if SSI_HOOKS_CODE > 12288
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
    #endif

    #if SSI_HOOKS_CODE > 14336
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
        __emit(SSI@NOP512);
    #endif
}

static stock SSI_HooksSwitchInternal(value) {
    switch (value) {
        case 0: {
            return 1;
        }
    }

    return 0;
}

static stock SSI_HooksFullInternal(needed) {
    new
        space[1]
    ;

    return space[needed];
}

static stock SSI_HooksTooManyInternal(count) {
    new
        functions[SSI_HOOKS_FUNCTIONS]
    ;

    return functions[count];
}

static stock SSI_HooksUnknownInternal(address) {
    new
        opcode[1]
    ;

    return opcode[address];
}

static stock SSI_HooksCallInternal(address) {
    if (address == 0) {
        return 1;
    }

    __emit(
        push.c 0,
        lctrl 6,
        add.c 28,
        push.pri,
        load.s.pri address,
        sctrl 6,
        retn
    );

    return 0;
}

static stock SSI_HooksPatchInternal(index, value) {
    if (SSI@hookCounting) {
        return;
    }

    SSI@Amx_Write(SSI@amxCode + SSI@hookStart + index * 4, value);
}

static stock SSI_HooksEmitInternal(value) {
    SSI_HooksPatchInternal(SSI@hookAt++, value);
}

static stock SSI_HooksOpInternal(opcode) {
    SSI_HooksPatchInternal(SSI@hookAt++, SSI@amxOpcode[opcode]);
}

static stock SSI_HooksHereInternal(index) {
    return SSI@hookStart + index * 4 + SSI@amxDelta;
}

static stock SSI_HooksEntryInternal(index) {
    return SSI@amxBase + SSI@hookPublics + index * SSI@hookSize;
}

static stock SSI_HooksByteInternal(index, offset) {
    return SSI@Amx_ReadByte(SSI@amxBase + SSI@Amx_Read(SSI_HooksEntryInternal(index) + 4) + offset);
}

static stock SSI_HooksCompareInternal(left, right) {
    new const
        a = SSI@amxBase + SSI@Amx_Read(SSI_HooksEntryInternal(left) + 4),
        b = SSI@amxBase + SSI@Amx_Read(SSI_HooksEntryInternal(right) + 4)
    ;

    for (new i; i != 64; ++i) {
        new const
            x = SSI@Amx_ReadByte(a + i),
            y = SSI@Amx_ReadByte(b + i)
        ;

        if (x != y) {
            return x - y;
        }

        if (x == 0) {
            return 0;
        }
    }

    return 0;
}

static stock SSI_HooksMatchInternal(index, const name[]) {
    for (new i; i != 64; ++i) {
        new const
            x = SSI_HooksByteInternal(index, i)
        ;

        if (x != name[i]) {
            return name[i] - x;
        }

        if (x == 0) {
            return 0;
        }
    }

    return 0;
}

static stock SSI_HooksFindInternal(const name[]) {
    new
        low,
        high = SSI@hookCount - 1
    ;

    while (low <= high) {
        new const
            middle = (low + high) >>> 1,
            order = SSI_HooksMatchInternal(middle, name)
        ;

        if (order == 0) {
            return middle;
        }

        if (order < 0) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }

    return -1;
}

static stock bool:SSI_HooksPrefixInternal(index, const prefix[]) {
    for (new i; prefix[i] != EOS; ++i) {
        if (SSI_HooksByteInternal(index, i) != prefix[i]) {
            return false;
        }
    }

    return true;
}

static stock bool:SSI_HooksServerInternal(const callback[]) {
    new
        low,
        high = sizeof SSI@hookCallbacks - 1
    ;

    while (low <= high) {
        new const
            middle = (low + high) >>> 1,
            order = strcmp(callback, SSI@hookCallbacks[middle])
        ;

        if (order == 0) {
            return true;
        }

        if (order < 0) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }

    return false;
}

static stock SSI_HooksOpcodesInternal() {
    SSI@hookPlain = true;

    for (new i; i != sizeof SSI@amxOpcode; ++i) {
        if (SSI@amxOpcode[i] != -1 && SSI@amxOpcode[i] != i) {
            SSI@hookPlain = false;
        }
    }

    new const
        sample = SSI@Amx_Entry(__addressof(SSI_HooksSwitchInternal)) + SSI@amxCode
    ;

    if (SSI@Amx_Read(sample) != SSI@amxOpcode[SSI_OP_LOAD_S_PRI]) {
        return;
    }

    SSI@hookSwitch = SSI@Amx_Read(sample + 8);
    SSI@hookCasetbl = SSI@Amx_Read(SSI@Amx_Read(sample + 12) - SSI@amxDelta + SSI@amxCode);

    if (SSI@hookSwitch != SSI_OP_SWITCH || SSI@hookCasetbl != SSI_OP_CASETBL) {
        SSI@hookPlain = false;
    }

    if (SSI@hookPlain) {
        return;
    }

    for (new i; i != sizeof SSI@amxOpcode; ++i) {
        if (SSI@amxOpcode[i] == -1) {
            continue;
        }

        if (i == SSI_OP_SWITCH) {
            continue;
        }

        if (i == SSI_OP_CASETBL) {
            continue;
        }

        SSI@hookCells[SSI@hookCellCount][0] = SSI@amxOpcode[i];
        SSI@hookCells[SSI@hookCellCount++][1] = i;
    }

    SSI@hookCells[SSI@hookCellCount][0] = SSI@hookSwitch;
    SSI@hookCells[SSI@hookCellCount++][1] = SSI_OP_SWITCH;
    SSI@hookCells[SSI@hookCellCount][0] = SSI@hookCasetbl;
    SSI@hookCells[SSI@hookCellCount++][1] = SSI_OP_CASETBL;

    for (new i = 1; i < SSI@hookCellCount; ++i) {
        new const
            cell = SSI@hookCells[i][0],
            opcode = SSI@hookCells[i][1]
        ;

        new
            j = i
        ;

        while (j != 0 && SSI@hookCells[j - 1][0] > cell) {
            SSI@hookCells[j][0] = SSI@hookCells[j - 1][0];
            SSI@hookCells[j][1] = SSI@hookCells[j - 1][1];
            --j;
        }

        SSI@hookCells[j][0] = cell;
        SSI@hookCells[j][1] = opcode;
    }
}

static stock SSI_HooksDecodeInternal(cell) {
    if (SSI@hookPlain) {
        return cell;
    }

    new
        low,
        high = SSI@hookCellCount - 1
    ;

    while (low <= high) {
        new const
            middle = (low + high) >>> 1,
            value = SSI@hookCells[middle][0]
        ;

        if (value == cell) {
            return SSI@hookCells[middle][1];
        }

        if (value < cell) {
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }

    return -1;
}

static stock SSI_HooksLengthInternal(opcode, address) {
    switch (opcode) {
        case SSI_OP_CASETBL: {
            return 3 + 2 * SSI@Amx_Read(address + 4);
        }
        case SSI_OP_SWITCH: {
            return 2;
        }
    }

    if (!(0 < opcode < sizeof SSI@amxOperands)) {
        return 0;
    }

    if (SSI@amxOperands[opcode] == -1) {
        return 0;
    }

    return 1 + SSI@amxOperands[opcode];
}

static stock SSI_HooksSharedInternal() {
    SSI@hookCopy = SSI@hookAt;
    SSI_HooksOpInternal(SSI_OP_LOAD_S_PRI);
    SSI_HooksEmitInternal(8);
    SSI_HooksOpInternal(SSI_OP_JZER);

    new const
        skip = SSI@hookAt++
    ;

    SSI_HooksOpInternal(SSI_OP_MOVE_ALT);
    SSI_HooksOpInternal(SSI_OP_LCTRL);
    SSI_HooksEmitInternal(4);
    SSI_HooksOpInternal(SSI_OP_SUB);
    SSI_HooksOpInternal(SSI_OP_SCTRL);
    SSI_HooksEmitInternal(4);
    SSI_HooksOpInternal(SSI_OP_XCHG);
    SSI_HooksOpInternal(SSI_OP_STOR_PRI);

    new const
        patch = SSI@hookAt++
    ;

    SSI_HooksOpInternal(SSI_OP_LCTRL);
    SSI_HooksEmitInternal(5);
    SSI_HooksOpInternal(SSI_OP_ADD_C);
    SSI_HooksEmitInternal(12);
    SSI_HooksOpInternal(SSI_OP_MOVS);
    SSI_HooksPatchInternal(patch, SSI@amxCode + SSI@hookStart + SSI@hookAt * 4);
    SSI_HooksEmitInternal(0);
    SSI_HooksPatchInternal(skip, SSI_HooksHereInternal(SSI@hookAt));
    SSI_HooksOpInternal(SSI_OP_PUSH_C);
    SSI_HooksEmitInternal(-4);
    SSI_HooksOpInternal(SSI_OP_LOAD_S_PRI);
    SSI_HooksEmitInternal(-8);
    SSI_HooksOpInternal(SSI_OP_SCTRL);
    SSI_HooksEmitInternal(6);

    new
        rare[2]
    ;

    for (new mode; mode != 2; ++mode) {
        if (mode == 0) {
            SSI@hookRareOr = SSI@hookAt;
        } else {
            SSI@hookRareAnd = SSI@hookAt;
        }

        SSI_HooksOpInternal(SSI_OP_ZERO_ALT);
        SSI_HooksOpInternal(SSI_OP_JSLESS);
        rare[mode] = SSI@hookAt++;
        SSI_HooksOpInternal(SSI_OP_LOAD_S_ALT);
        SSI_HooksEmitInternal(-4);
        SSI_HooksOpInternal(mode == 0 ? SSI_OP_OR : SSI_OP_AND);
        SSI_HooksOpInternal(SSI_OP_STOR_S_PRI);
        SSI_HooksEmitInternal(-4);
        SSI_HooksOpInternal(SSI_OP_POP_PRI);
        SSI_HooksOpInternal(SSI_OP_SCTRL);
        SSI_HooksEmitInternal(6);
    }

    SSI_HooksPatchInternal(rare[0], SSI_HooksHereInternal(SSI@hookAt));
    SSI_HooksPatchInternal(rare[1], SSI_HooksHereInternal(SSI@hookAt));
    SSI_HooksOpInternal(SSI_OP_INVERT);
    SSI@hookTail = SSI@hookAt;
    SSI_HooksOpInternal(SSI_OP_MOVE_ALT);
    SSI_HooksOpInternal(SSI_OP_LCTRL);
    SSI_HooksEmitInternal(5);
    SSI_HooksOpInternal(SSI_OP_SCTRL);
    SSI_HooksEmitInternal(4);
    SSI_HooksOpInternal(SSI_OP_MOVE_PRI);
    SSI_HooksOpInternal(SSI_OP_RETN);
    SSI@hookNeutral[0] = SSI@hookAt;
    SSI_HooksOpInternal(SSI_OP_PROC);
    SSI_HooksOpInternal(SSI_OP_ZERO_PRI);
    SSI_HooksOpInternal(SSI_OP_RETN);
    SSI@hookNeutral[1] = SSI@hookAt;
    SSI_HooksOpInternal(SSI_OP_PROC);
    SSI_HooksOpInternal(SSI_OP_CONST_PRI);
    SSI_HooksEmitInternal(1);
    SSI_HooksOpInternal(SSI_OP_RETN);
}

static stock SSI_HooksStateInternal(address, neutral) {
    if (SSI@hookSwitch == 0) {
        return;
    }

    new
        code = address + SSI@amxCode
    ;

    while (SSI@Amx_Read(code) == SSI@amxOpcode[SSI_OP_BREAK]) {
        code += 4;
    }

    if (SSI@Amx_Read(code) != SSI@amxOpcode[SSI_OP_LOAD_PRI]) {
        return;
    }

    if (SSI@Amx_Read(code + 8) != SSI@hookSwitch) {
        return;
    }

    new const
        table = SSI@Amx_Read(code + 12) - SSI@amxDelta + SSI@amxCode
    ;

    if (SSI@Amx_Read(table) != SSI@hookCasetbl) {
        return;
    }

    new const
        fallback = SSI@Amx_Read(table + 8) - SSI@amxDelta + SSI@amxCode
    ;

    if (SSI@Amx_Read(fallback) != SSI@amxOpcode[SSI_OP_HALT]) {
        return;
    }

    if (SSI@Amx_Read(fallback + 4) != 13) {
        return;
    }

    SSI@Amx_Write(table + 8, SSI_HooksHereInternal(SSI@hookNeutral[neutral]));
}

static stock SSI_HooksCallTargetInternal(address, bool:joinAnd) {
    SSI_HooksOpInternal(SSI_OP_CALL);
    SSI_HooksEmitInternal(address + SSI@amxDelta);

    if (joinAnd) {
        SSI_HooksOpInternal(SSI_OP_CONST_ALT);
        SSI_HooksEmitInternal(1);
        SSI_HooksOpInternal(SSI_OP_JEQ);
        SSI_HooksEmitInternal(SSI_HooksHereInternal(SSI@hookAt + 3));
        SSI_HooksOpInternal(SSI_OP_CALL);
        SSI_HooksEmitInternal(SSI_HooksHereInternal(SSI@hookRareAnd));
    } else {
        SSI_HooksOpInternal(SSI_OP_JZER);
        SSI_HooksEmitInternal(SSI_HooksHereInternal(SSI@hookAt + 3));
        SSI_HooksOpInternal(SSI_OP_CALL);
        SSI_HooksEmitInternal(SSI_HooksHereInternal(SSI@hookRareOr));
    }
}

static stock SSI_HooksChainInternal(first, last, original, defaultReturn) {
    new const
        start = SSI@hookAt,
        bool:joinAnd = defaultReturn == 1
    ;

    SSI_HooksOpInternal(SSI_OP_PROC);
    SSI_HooksOpInternal(SSI_OP_PUSH_C);
    SSI_HooksEmitInternal(joinAnd ? 1 : 0);
    SSI_HooksOpInternal(SSI_OP_CALL);
    SSI_HooksEmitInternal(SSI_HooksHereInternal(SSI@hookCopy));

    new
        previous = -1
    ;

    for (new emitted = first; emitted != last; ++emitted) {
        new
            address = cellmax
        ;

        for (new i = first; i != last; ++i) {
            new const
                here = SSI@Amx_Read(SSI_HooksEntryInternal(i))
            ;

            if (here > previous && here < address) {
                address = here;
            }
        }

        previous = address;

        if (!SSI@hookCounting) {
            SSI_HooksStateInternal(address, joinAnd ? 1 : 0);
        }

        SSI_HooksCallTargetInternal(address, joinAnd);
    }

    if (original != -1) {
        SSI_HooksCallTargetInternal(SSI@Amx_Read(SSI_HooksEntryInternal(original)), joinAnd);
    }

    SSI_HooksOpInternal(SSI_OP_LOAD_S_PRI);
    SSI_HooksEmitInternal(-4);
    SSI_HooksOpInternal(SSI_OP_JUMP);
    SSI_HooksEmitInternal(SSI_HooksHereInternal(SSI@hookTail));

    return SSI@hookStart + start * 4;
}

static stock SSI_HooksCallbackInternal(index, name[], size = sizeof name) {
    new
        length
    ;

    while (length != size - 1) {
        new const
            c = SSI_HooksByteInternal(index, 3 + length)
        ;

        if (c == '@') {
            break;
        }

        if (c == 0) {
            break;
        }

        name[length++] = c;
    }

    name[length] = EOS;

    return length;
}

static stock bool:SSI_HooksSameInternal(index, const name[], length) {
    if (!SSI_HooksPrefixInternal(index, "@H_")) {
        return false;
    }

    for (new i; i != length; ++i) {
        if (SSI_HooksByteInternal(index, 3 + i) != name[i]) {
            return false;
        }
    }

    return SSI_HooksByteInternal(index, 3 + length) == '@';
}

static stock SSI_HooksSortInternal() {
    for (new i = 1; i < SSI@hookCount; ++i) {
        if (SSI_HooksCompareInternal(i - 1, i) <= 0) {
            continue;
        }

        new const
            address = SSI@Amx_Read(SSI_HooksEntryInternal(i)),
            name = SSI@Amx_Read(SSI_HooksEntryInternal(i) + 4)
        ;

        new
            j = i
        ;

        while (j != 0) {
            new const
                before = SSI_HooksEntryInternal(j - 1),
                a = SSI@amxBase + SSI@Amx_Read(before + 4),
                b = SSI@amxBase + name
            ;

            new
                order
            ;

            for (new k; ; ++k) {
                new const
                    x = SSI@Amx_ReadByte(a + k),
                    y = SSI@Amx_ReadByte(b + k)
                ;

                order = x - y;

                if (order != 0) {
                    break;
                }

                if (x == 0) {
                    break;
                }
            }

            if (order <= 0) {
                break;
            }

            SSI@Amx_Write(SSI_HooksEntryInternal(j), SSI@Amx_Read(before));
            SSI@Amx_Write(SSI_HooksEntryInternal(j) + 4, SSI@Amx_Read(before + 4));
            --j;
        }

        SSI@Amx_Write(SSI_HooksEntryInternal(j), address);
        SSI@Amx_Write(SSI_HooksEntryInternal(j) + 4, name);
    }
}

static stock SSI_HooksBlankInternal() {
    return 0;
}

static stock bool:SSI_HooksSilentInternal(address) {
    new
        blank = __addressof(SSI_HooksBlankInternal) + SSI@amxCode,
        code = address + SSI@amxCode
    ;

    for (new i; i != 8; ++i) {
        new const
            cell = SSI@Amx_Read(blank)
        ;

        if (SSI@Amx_Read(code) != cell) {
            return false;
        }

        if (SSI_HooksDecodeInternal(cell) == SSI_OP_RETN) {
            return true;
        }

        blank += 4;
        code += 4;
    }

    return false;
}

static stock SSI_HooksBuildInternal(bool:apply) {
    new
        callback[64],
        name[72],
        bool:renamed
    ;

    for (new first; first < SSI@hookCount; ) {
        if (!SSI_HooksPrefixInternal(first, "@H_")) {
            ++first;
            continue;
        }

        new const
            length = SSI_HooksCallbackInternal(first, callback)
        ;

        new
            last = first + 1,
            defaultReturn = _:SSI_HooksServerInternal(callback)
        ;

        while (last < SSI@hookCount && SSI_HooksSameInternal(last, callback, length)) {
            ++last;
        }

        format(name, sizeof name, "@Hr_%s", callback);

        new const
            setter = SSI_HooksFindInternal(name),
            bool:init = strequal(callback, "OnGameModeInit") || strequal(callback, "OnFilterScriptInit")
        ;

        if (setter != -1) {
            defaultReturn = _:(SSI_HooksCallInternal(SSI@Amx_Read(SSI_HooksEntryInternal(setter))) == 1);
        }

        if (init) {
            format(name, sizeof name, "SSI@H_%s", callback);
        } else {
            format(name, sizeof name, "%s", callback);
        }

        new const
            original = SSI_HooksFindInternal(name),
            entry = (original == -1) ? 0 : SSI@Amx_Read(SSI_HooksEntryInternal(original)),
            bool:silent = !init && original != -1 && defaultReturn == 0 && SSI_HooksSilentInternal(entry),
            chain = SSI_HooksChainInternal(first, last, silent ? -1 : original, defaultReturn)
        ;

        if (!apply) {
            first = last;
            continue;
        }

        if (init) {
            if (callback[2] == 'G') {
                SSI@hookGameModeInit = chain;
            } else {
                SSI@hookFilterScriptInit = chain;
            }
        } else if (original != -1) {
            SSI@Amx_Write(SSI_HooksEntryInternal(original), chain);

            if (silent) {
                SSI@Amx_Write(SSI@amxCode + entry, SSI@amxOpcode[SSI_OP_JUMP]);
                SSI@Amx_Write(SSI@amxCode + entry + 4, chain + SSI@amxDelta);
            }
        } else {
            SSI@Amx_Write(SSI_HooksEntryInternal(first), chain);
            renamed = true;
        }

        first = last;
    }

    if (!apply) {
        return;
    }

    if (SSI@hookGameModeInit == 0) {
        new const
            original = SSI_HooksFindInternal("SSI@H_OnGameModeInit")
        ;

        if (original != -1) {
            SSI@hookGameModeInit = SSI@Amx_Read(SSI_HooksEntryInternal(original));
        }
    }

    if (SSI@hookFilterScriptInit == 0) {
        new const
            original = SSI_HooksFindInternal("SSI@H_OnFilterScriptInit")
        ;

        if (original != -1) {
            SSI@hookFilterScriptInit = SSI@Amx_Read(SSI_HooksEntryInternal(original));
        }
    }

    if (!renamed) {
        return;
    }

    new const
        low = SSI@hookStart,
        high = SSI@hookStart + SSI@hookCapacity * 4
    ;

    for (new i; i != SSI@hookCount; ++i) {
        new const
            address = SSI@Amx_Read(SSI_HooksEntryInternal(i))
        ;

        if (!(low <= address < high)) {
            continue;
        }

        if (!SSI_HooksPrefixInternal(i, "@H_")) {
            continue;
        }

        new const
            nameOffset = SSI@Amx_Read(SSI_HooksEntryInternal(i) + 4),
            length = SSI_HooksCallbackInternal(i, callback)
        ;

        SSI@Amx_WriteByte(SSI@amxBase + nameOffset + 3 + length, 0);
        SSI@Amx_Write(SSI_HooksEntryInternal(i) + 4, nameOffset + 3);
    }

    SSI_HooksSortInternal();
}

static stock bool:SSI_HooksSameTargetInternal(left, right) {
    if (SSI@hookFunction[left][E_SSI_HOOK_NATIVE] != SSI@hookFunction[right][E_SSI_HOOK_NATIVE]) {
        return false;
    }

    return SSI@hookFunction[left][E_SSI_HOOK_TARGET] == SSI@hookFunction[right][E_SSI_HOOK_TARGET];
}

static stock bool:SSI_HooksCollectInternal() {
    for (new i; i != SSI@hookCount; ++i) {
        if (!SSI_HooksPrefixInternal(i, "@Hi@")) {
            continue;
        }

        if (SSI@hookFunctions == SSI_HOOKS_FUNCTIONS) {
            SSI_HooksTooManyInternal(SSI@hookFunctions + 1);

            return false;
        }

        new const
            code = SSI@Amx_Entry(SSI@Amx_Read(SSI_HooksEntryInternal(i))) + SSI@amxCode,
            kind = SSI_HooksDecodeInternal(SSI@Amx_Read(code)),
            body = SSI@Amx_Read(code + 12) - SSI@amxDelta
        ;

        if (SSI_HooksDecodeInternal(SSI@Amx_Read(code + 8)) != SSI_OP_CALL) {
            continue;
        }

        new
            k = SSI@hookFunctions++
        ;

        while (k != 0 && SSI@hookFunction[k - 1][E_SSI_HOOK_BODY] > body) {
            SSI@hookFunction[k] = SSI@hookFunction[k - 1];
            --k;
        }

        SSI@hookFunction[k][E_SSI_HOOK_TARGET] = SSI@Amx_Read(code + 4);
        SSI@hookFunction[k][E_SSI_HOOK_NATIVE] = kind == SSI_OP_SYSREQ_C;
        SSI@hookFunction[k][E_SSI_HOOK_BODY] = body;
    }

    for (new k; k != SSI@hookFunctions; ++k) {
        SSI@hookFunction[k][E_SSI_HOOK_NEXT] = -1;
        SSI@hookFunction[k][E_SSI_HOOK_HEAD] = SSI@hookFunction[k][E_SSI_HOOK_BODY];

        for (new j = k - 1; j >= 0; --j) {
            if (SSI_HooksSameTargetInternal(j, k)) {
                SSI@hookFunction[k][E_SSI_HOOK_NEXT] = SSI@hookFunction[j][E_SSI_HOOK_BODY];
                break;
            }
        }

        for (new j = SSI@hookFunctions - 1; j > k; --j) {
            if (SSI_HooksSameTargetInternal(j, k)) {
                SSI@hookFunction[k][E_SSI_HOOK_HEAD] = SSI@hookFunction[j][E_SSI_HOOK_BODY];
                break;
            }
        }
    }

    return SSI@hookFunctions != 0;
}

static stock SSI_HooksTargetInternal(bool:isNative, target, current) {
    if (current != -1 && SSI@hookFunction[current][E_SSI_HOOK_NATIVE] == isNative && SSI@hookFunction[current][E_SSI_HOOK_TARGET] == target) {
        return SSI@hookFunction[current][E_SSI_HOOK_NEXT];
    }

    for (new k; k != SSI@hookFunctions; ++k) {
        if (SSI@hookFunction[k][E_SSI_HOOK_NATIVE] == isNative && SSI@hookFunction[k][E_SSI_HOOK_TARGET] == target) {
            return SSI@hookFunction[k][E_SSI_HOOK_HEAD];
        }
    }

    return -1;
}

static stock SSI_HooksSysreqInternal(previous, address, current) {
    new const
        target = SSI_HooksTargetInternal(true, SSI@Amx_Read(address + 4), current)
    ;

    if (target == -1) {
        return;
    }

    if (SSI_HooksDecodeInternal(SSI@Amx_Read(previous)) != SSI_OP_PUSH_C) {
        return;
    }

    if (SSI_HooksDecodeInternal(SSI@Amx_Read(address + 8)) != SSI_OP_STACK) {
        return;
    }

    SSI@Amx_Write(address, SSI@amxOpcode[SSI_OP_CALL]);
    SSI@Amx_Write(address + 4, target + SSI@amxDelta);
    SSI@Amx_Write(address + 12, SSI@Amx_Read(address + 12) - SSI@Amx_Read(previous + 4) - 4);
}

static stock SSI_HooksRedirectInternal(address, current) {
    new const
        target = SSI_HooksTargetInternal(false, SSI@Amx_Read(address + 4), current)
    ;

    if (target != -1) {
        SSI@Amx_Write(address + 4, target + SSI@amxDelta);
    }
}

static stock SSI_HooksWalkInternal() {
    new const
        end = SSI@amxCode + SSI@Amx_Header(16) - SSI@Amx_Header(12)
    ;

    new
        address = SSI@amxCode,
        previous = SSI@amxCode,
        current = -1,
        next
    ;

    while (address < end) {
        new const
            opcode = SSI_HooksDecodeInternal(SSI@Amx_Read(address)),
            length = SSI_HooksLengthInternal(opcode, address)
        ;

        if (length == 0) {
            SSI_HooksUnknownInternal(address - SSI@amxCode);

            return;
        }

        switch (opcode) {
            case SSI_OP_PROC: {
                while (next != SSI@hookFunctions && SSI@hookFunction[next][E_SSI_HOOK_BODY] < address - SSI@amxCode) {
                    ++next;
                }

                current = (next != SSI@hookFunctions && SSI@hookFunction[next][E_SSI_HOOK_BODY] == address - SSI@amxCode) ? next : -1;
            }
            case SSI_OP_SYSREQ_C: {
                SSI_HooksSysreqInternal(previous, address, current);
            }
            case SSI_OP_CALL: {
                SSI_HooksRedirectInternal(address, current);
            }
        }

        previous = address;
        address += length * 4;
    }
}

static stock SSI_HooksReadyInternal() {
    if (SSI@hookReady) {
        return;
    }

    SSI@hookReady = true;

    if (!SSI@Amx_Ready()) {
        SSI_HooksUnknownInternal(-1);

        return;
    }

    SSI@hookPublics = SSI@Amx_Header(32);
    SSI@hookSize = (SSI@Amx_Header(8) >>> 16) & 0xFFFF;
    SSI@hookCount = (SSI@Amx_Header(36) - SSI@hookPublics) / SSI@hookSize;
    SSI_HooksOpcodesInternal();

    new
        address = __addressof(SSI_HooksSpaceInternal) + SSI@amxCode
    ;

    while (SSI@Amx_Read(address) != SSI@amxOpcode[SSI_OP_NOP]) {
        address += 4;
    }

    new
        end = address
    ;

    while (SSI@Amx_Read(end) == SSI@amxOpcode[SSI_OP_NOP] || SSI@Amx_Read(end) == SSI@amxOpcode[SSI_OP_BREAK]) {
        end += 4;
    }

    SSI@hookStart = address - SSI@amxCode;
    SSI@hookCapacity = (end - address) / 4;
    SSI@hookCounting = true;
    SSI_HooksSharedInternal();
    SSI_HooksBuildInternal(false);

    if (SSI@hookAt > SSI@hookCapacity) {
        SSI_HooksFullInternal(SSI@hookAt);

        return;
    }

    SSI@hookCounting = false;
    SSI@hookAt = 0;
    SSI_HooksSharedInternal();
    SSI_HooksBuildInternal(true);

    if (SSI_HooksCollectInternal()) {
        SSI_HooksWalkInternal();
    }
}

/**
 * # Calls
 */

public OnGameModeInit() {
    SSI_HooksReadyInternal();

    return SSI_HooksCallInternal(SSI@hookGameModeInit);
}

#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit SSI@H_OnGameModeInit

forward SSI@H_OnGameModeInit();

public OnFilterScriptInit() {
    SSI_HooksReadyInternal();

    return SSI_HooksCallInternal(SSI@hookFilterScriptInit);
}

#if defined _ALS_OnFilterScriptInit
    #undef OnFilterScriptInit
#else
    #define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit SSI@H_OnFilterScriptInit

forward SSI@H_OnFilterScriptInit();
