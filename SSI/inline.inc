#if defined _INC_SSI_INLINE
    #endinput
#endif
#define _INC_SSI_INLINE

#include <open.mp>
#include <SSI\amx>
#include <SSI\collection>
#include <SSI\hooks>

/**
 * Inline functions: a function written inside another, that reads and changes
 * the arguments of the outer function and the locals it had where the inline
 * is written, and can be called after the outer function returned, as by a
 * timer:
 *
 *     #include <SSI\inline>
 *
 *     Remind(playerid) {
 *         new
 *             minutes = 0
 *         ;
 *
 *         inline OnTick() {
 *             ++minutes;
 *             SendClientMessage(playerid, -1, "%d minutes", minutes);
 *         }
 *
 *         Timer_StartInline(using inline OnTick, 60000);
 *     }
 *
 * - `using inline Name` captures it: a copy of the arguments of the outer
 *   function and of its locals written before the inline. A function that
 *   takes an `Inline:` captures it on the call, so `using inline` only makes
 *   the call easier to read.
 * - `@.closure(...)` calls it. A call runs on the copy and keeps what the
 *   inline changed for the next call. The outer function never sees the
 *   changes. `@once.closure(...)`, or `@@.closure(...)`, calls it once and
 *   frees it.
 * - Parameters are cells of any tag, or arrays of a given size, which take a
 *   string: `inline OnAnswer(response, text[64])`. A parameter the call leaves
 *   out is `0`, or an empty string. References are not allowed.
 * - `return` belongs to the outer function, so it returns a value of its type.
 *   `@return value;` returns any value, and `@return;` only ends the call.
 *   `break` and `continue` end it too.
 * - Arguments passed by reference, and arrays passed as arguments, point to
 *   memory of whoever called the outer function: an inline called after the
 *   outer function returned must not use them.
 * - A capture holds at most `SSI_INLINE_CELLS` cells, counting the arguments
 *   and the locals it copies. A larger capture gives `INVALID_INLINE`. The
 *   parameters of the inline are written on the stack at each call, so they do
 *   not count.
 *
 * A function that takes an inline:
 *
 *     static
 *         Inline:gDialog[MAX_PLAYERS] = { INVALID_INLINE, ... }
 *     ;
 *
 *     stock Dialog_ShowInline(playerid, Inline:callback<iis>, style, const title[], const body[], const button1[], const button2[] = "") {
 *         Inline_Free(gDialog[playerid]);
 *         gDialog[playerid] = callback;
 *
 *         return ShowPlayerDialog(playerid, DIALOG_ID, style, title, body, button1, button2);
 *     }
 *
 *     hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
 *         new const
 *             Inline:callback = gDialog[playerid]
 *         ;
 *
 *         gDialog[playerid] = INVALID_INLINE;
 *         @once.callback(response, listitem, inputtext);
 *
 *         return 1;
 *     }
 *
 * - Whoever takes an `Inline:` owns it, and ends it with `Inline_CallOnce`,
 *   `@once.` or `@@.`, which call and free it, or with `Inline_Free`. They do
 *   nothing with a handle freed or never made, so `INVALID_INLINE` needs no
 *   check.
 * - `Inline:callback<iis>` takes only an inline with those parameters: `i` a
 *   cell, `f` a float, `s` a string. Another shape stops with a run time error
 *   at the capture, naming the inline. A float and a cell look the same there.
 * - A handle of one shape does not go where another is wanted, and any of them
 *   goes into an `Inline:`.
 * - `Inline_Count` tells how many captures are alive, which a test can check
 *   for leaks.
 *
 * An inline can belong to something, as with y_ebc. It is freed when that
 * thing goes, so an answer that comes later, as from the database, never runs,
 * even when something else took its id by then:
 *
 *     MySQL_ThreadedQueryInline(gDatabase, EBC(playerid, using inline OnFound), "SELECT ...");
 *
 * The tag of the owner tells what it is. Without one it is a player, freed when
 * they leave. `Vehicle:`, `Object:` and `Pickup:` are freed by `DestroyVehicle`,
 * `DestroyObject` and `DestroyPickup`, so a vehicle is written
 * `EBC(Vehicle:vehicleid, using inline OnFound)`. A library with a tag of its
 * own frees those with `Inline_FreeOwned` when it destroys one.
 */

/**
 * # Header
 */

#if !defined SSI_INLINE_SITES
    #define SSI_INLINE_SITES (InlineSite:256)
#endif

#if !defined SSI_INLINE_CLOSURES
    #define SSI_INLINE_CLOSURES (InlineClosure:256)
#endif

#if !defined SSI_INLINE_CELLS
    #define SSI_INLINE_CELLS (64)
#endif

#if !defined SSI_INLINE_PARAMS
    #define SSI_INLINE_PARAMS (8)
#endif

#define INVALID_INLINE (Inline:-1)
#define INVALID_INLINE_SITE (InlineSite:-1)
#define INVALID_INLINE_CLOSURE (InlineClosure:-1)

/**
 * Declares an inline inside a function. The body after it never runs where it
 * is written.
 *
 *     inline OnTick() {
 *     }
 */
#define inline%0(%1) static InlineSite:%0 = INVALID_INLINE_SITE; while (SSI@Inline_None:SSI@Inline_Start(%0,#%0))for(SSI@Inline_Params:%1|;SSI@Inline_Loop();)
#define SSI@Inline_None:SSI@Inline_Start(%0))for(SSI@Inline_Params:| SSI@Inline_Start(%0))for(
#define SSI@Inline_Params:%0| new %0

/**
 * Marks an argument as an inline. The capture is done by the `Inline:` it is
 * passed as.
 *
 *     Timer_StartInline(using inline OnTick, 1000);
 */
#define using%0inline

/**
 * Ends the call of an inline with a value of any tag, whatever the outer
 * function returns, or with `0` when no value is given.
 *
 *     @return listitem;
 *     @return;
 */
#define @return%0; SSI@Inline_Return(SSI@Inline_Nothing:SSI@Inline_Value:(%0));
#define inline_return%0; SSI@Inline_Return(SSI@Inline_Nothing:SSI@Inline_Value:(%0));
#define SSI@Inline_Nothing:SSI@Inline_Value:() 0
#define SSI@Inline_Value:(%0) _:(%0)

/**
 * Calls an inline with its parameters, the same as `Inline_Call`.
 *
 *     @.callback(response, listitem, inputtext);
 */
#define @.%0(%1) Inline_Call(SSI@Inline_Callee:%0,SSI@Inline_Args:(%1))
#define SSI@Inline_Callee:%0,SSI@Inline_Args:() SSI@Inline_Callee:%0
#define SSI@Inline_Args:(%0) %0

/**
 * Calls an inline once with its parameters and frees it, the same as
 * `Inline_CallOnce`. `@@.` is the short form. PawnPlus also defines `@@` when
 * `PP_SYNTAX_@@` is set, so that syntax cannot be used together with this one.
 *
 *     @once.callback(response, listitem, inputtext);
 *     @@.callback(response, listitem, inputtext);
 */
#define @once.%0(%1) Inline_CallOnce(SSI@Inline_Callee:%0,SSI@Inline_Args:(%1))
#define @@.%0(%1) Inline_CallOnce(SSI@Inline_Callee:%0,SSI@Inline_Args:(%1))

/**
 * @brief      Give an inline to an owner, as y_ebc does: it is freed, and never
 *             called again, when the owner goes.
 *
 *     MySQL_ThreadedQueryInline(gDatabase, EBC(playerid, using inline OnFound), "SELECT ...");
 *     Timer_StartInline(EBC(Vehicle:vehicleid, using inline OnTick), 1000);
 *
 * The owner is a variable, whose tag tells what it is, or an id written with
 * its tag, as `Vehicle:vehicleid`. It goes to the capture made by the `Inline:`
 * it is passed as.
 *
 * @param      owner     The owner.
 * @param      callback  The inline, as `using inline Name`.
 */
forward InlineSite:EBC(owner, InlineSite:callback);
#define EBC(%0,%1) SSI@Inline_Own(_:(%0),tagof(%0),%1)
#define SSI@Inline_Own(_:(%0:%1),%2,%3) SSI@Inline_Own(_:%0:(%1),tagof(%0:),%3)

/**
 * An inline that takes the parameters written between `<` and `>`: `i` a
 * cell, `f` a float, `s` a string.
 *
 *     stock Dialog_ShowInline(playerid, Inline:callback<iis>)
 */
#define Inline:%0<%1> Inline_%1:%0

/**
 * Makes `Inline:callback<...>` work for a shape of five or more parameters.
 * Shapes of up to four are already made.
 *
 *     Inline_Signature(iiiis)
 */
#define Inline_Signature(%0) stock Inline_%0:operator=(InlineSite:site) return Inline_%0:SSI@Inline_Capture(site, #%0); stock Inline:operator=(Inline_%0:closure) return Inline:_:closure;

#define SSI@Inline_Signatures(%0) Inline_Signature(%0i) Inline_Signature(%0f) Inline_Signature(%0s)
#define SSI@Inline_Signatures2(%0) SSI@Inline_Signatures(%0i) SSI@Inline_Signatures(%0f) SSI@Inline_Signatures(%0s)

static enum {
    SSI_INLINE_OP_PUSH_C = 39,
    SSI_INLINE_OP_STACK = 44,
    SSI_INLINE_OP_CALL = 49,
    SSI_INLINE_OP_JZER = 53,
    SSI_INLINE_OP_MOVS = 117,
    SSI_INLINE_OP_FILL = 119,
    SSI_INLINE_FAST = 8,
    SSI_INLINE_NAME = 32,
    SSI_INLINE_NO_OWNER = -1,
    SSI_INLINE_OWNER_GROUPS = 64
};

static enum E_INLINE_DATA {
    Inline:E_INLINE_TICKET,
    InlineSite:E_INLINE_SITE,
    E_INLINE_BELOW,
    E_INLINE_ENTER,
    E_INLINE_BYTES,
    E_INLINE_DEEP,
    E_INLINE_FROM,
    E_INLINE_ARGS,
    E_INLINE_COUNT,
    E_INLINE_ZERO_SKIP,
    bool:E_INLINE_SCALAR,
    E_INLINE_OWNER,
    E_INLINE_OWNER_TAG
};

static stock
    SSI@inlineInit[SSI_INLINE_SITES],
    SSI@inlineEntry[SSI_INLINE_SITES],
    SSI@inlineLocals[SSI_INLINE_SITES],
    SSI@inlineParams[SSI_INLINE_SITES],
    SSI@inlineParamBytes[SSI_INLINE_SITES],
    bool:SSI@inlineScalar[SSI_INLINE_SITES],
    SSI@inlineParam[SSI_INLINE_SITES][SSI_INLINE_PARAMS],
    SSI@inlineParamAt[SSI_INLINE_SITES][SSI_INLINE_PARAMS],
    SSI@inlineName[SSI_INLINE_SITES][SSI_INLINE_NAME char],
    SSI@inlineChecked[SSI_INLINE_SITES],
    InlineSite:SSI@inlineSites,
    InlineSite:SSI@inlineRegistering = INVALID_INLINE_SITE
;

static stock
    Collection:InlineClosure<SSI_INLINE_CLOSURES>,
    Collection:InlineOwner<SSI_INLINE_OWNER_GROUPS, SSI_INLINE_CLOSURES>
;

static stock
    SSI@inlineGeneration[SSI_INLINE_CLOSURES],
    SSI@inlineRecord[SSI_INLINE_CLOSURES][E_INLINE_DATA],
    SSI@inlineData[SSI_INLINE_CLOSURES][SSI_INLINE_CELLS + 3]
;

static enum {
    SSI_INLINE_CLOSURE_COUNT = sizeof SSI@inlineRecord,
    SSI_INLINE_RECORD_BYTES = sizeof SSI@inlineRecord[] * 4,
    SSI_INLINE_IMAGE_BYTES = sizeof SSI@inlineData[] * 4,
    SSI_INLINE_FROM_AT = _:E_INLINE_FROM * 4,
    SSI_INLINE_GENERATIONS = cellmax / sizeof SSI@inlineRecord - 1
};

#define SSI_Inline_Slot(%0) (InlineClosure:(_:(%0) % SSI_INLINE_CLOSURE_COUNT))
#define SSI_Inline_Ticket(%0) (Inline:(SSI@inlineGeneration[%0] * SSI_INLINE_CLOSURE_COUNT + _:(%0)))
#define SSI_Inline_Image(%0) (SSI@inlineDataBase + _:(%0) * SSI_INLINE_IMAGE_BYTES)

static stock
    SSI@inlineReturn = -1,
    SSI@inlineCaller,
    SSI@inlineAt,
    SSI@inlineDest,
    SSI@inlineRecordBase,
    SSI@inlineDataBase,
    SSI@inlinePatchIn,
    SSI@inlinePatchOut,
    SSI@inlinePatchOnce,
    SSI@inlinePatchFill,
    SSI@inlineValue,
    SSI@inlineGiven,
    SSI@inlineCount,
    SSI@inlineZeroSkip,
    SSI@inlineGivenSkip,
    SSI@inlineFrame,
    SSI@inlineZero,
    SSI@inlineOwner,
    SSI@inlineOwnerTag = SSI_INLINE_NO_OWNER
;

/**
 * # Functions
 */

/**
 * @brief      Call a captured inline. `@.closure(...)` does the same.
 *
 * @param      closure  The inline.
 * @param      ...      Its parameters, in order.
 *
 * @return     - what the inline returns, `0` when it ends without a value
 *             - `0` the inline was freed, or never made
 */
forward Inline_Call({Inline, SSI@Inline_Callee}:closure, OPEN_MP_TAGS:...);

/**
 * @brief      Call a captured inline once, then free it.
 *
 * @param      closure  The inline.
 * @param      ...      Its parameters, in order.
 *
 * @return     - what the inline returns, `0` when it ends without a value
 *             - `0` the inline was freed, or never made
 */
forward Inline_CallOnce({Inline, SSI@Inline_Callee}:closure, OPEN_MP_TAGS:...);

/**
 * @brief      Free a captured inline.
 *
 * Freeing it while it runs is safe: the call goes on, and keeps nothing.
 *
 * @param      closure  The inline.
 *
 * @return     - `true` it is freed
 *             - `false` it was freed already, or never made
 */
forward bool:Inline_Free(Inline:closure);

/**
 * @brief      Whether a captured inline can still be called.
 *
 * @param      closure  The inline.
 *
 * @return     - `true` it can
 *             - `false` it was freed, or never made
 */
forward bool:Inline_IsValid(Inline:closure);

/**
 * @brief      How many captures are alive.
 *
 * @return     - the count
 */
forward Inline_Count();

/**
 * @brief      Give a captured inline to an owner, as `EBC` does at the capture,
 *             in place of the owner it had.
 *
 * @param      closure  The inline.
 * @param      owner    The owner, as `EBC` takes it.
 *
 * @return     - `true` it is given
 *             - `false` it was freed, or never made
 */
forward bool:Inline_Give(Inline:closure, owner);
#define Inline_Give(%0,%1) SSI@Inline_Give(%0,_:(%1),tagof(%1))
#define SSI@Inline_Give(%0,_:(%1:%2),%3) SSI@Inline_Give(%0,_:%1:(%2),tagof(%1:))

/**
 * @brief      Free every inline of an owner, as when it is destroyed. A library
 *             calls it for the owners of its own tag.
 *
 * @param      owner  The owner, as `EBC` takes it.
 *
 * @return     - how many were freed
 */
forward Inline_FreeOwned(owner);
#define Inline_FreeOwned(%0) SSI@Inline_FreeOwned(_:(%0),tagof(%0))
#define SSI@Inline_FreeOwned(_:(%0:%1),%2) SSI@Inline_FreeOwned(_:%0:(%1),tagof(%0:))

/**
 * # Internal
 */

static stock SSI_InlineLayoutInternal({InlineSite, _}:found) {
    new
        zero
    ;

    #pragma unused found

    return 1 / zero;
}

static stock SSI_InlineSignatureInternal(const name[], const wanted[], const found[]) {
    new
        zero
    ;

    #pragma unused name, wanted, found

    return 1 / zero;
}

static stock InlineClosure:SSI_InlineSlotInternal(Inline:closure) {
    if (closure <= Inline:0) {
        return INVALID_INLINE_CLOSURE;
    }

    new const
        InlineClosure:slot = SSI_Inline_Slot(closure)
    ;

    if (SSI@inlineRecord[slot][E_INLINE_TICKET] != closure) {
        return INVALID_INLINE_CLOSURE;
    }

    return slot;
}

static stock SSI_InlineOperandInternal(address, wanted) {
    new
        opcode = SSI@Amx_Opcode(SSI@Amx_Read(address + SSI@amxCode))
    ;

    while (opcode != wanted) {
        if (opcode == -1) {
            return SSI_InlineLayoutInternal(-1);
        }

        address += 4 + SSI@amxOperands[opcode] * 4;
        opcode = SSI@Amx_Opcode(SSI@Amx_Read(address + SSI@amxCode));
    }

    return address + 4 + SSI@amxCode;
}

static stock SSI_InlineRecordInternal(record[E_INLINE_DATA], Inline:closure, InlineSite:site, locals, params, args, image) {
    record[E_INLINE_TICKET] = closure;
    record[E_INLINE_SITE] = site;
    record[E_INLINE_BELOW] = locals + params;
    record[E_INLINE_ENTER] = SSI@inlineEntry[site];
    record[E_INLINE_BYTES] = locals + 12 + args;
    record[E_INLINE_DEEP] = params + locals + 12 + args;
    record[E_INLINE_FROM] = image;
    record[E_INLINE_ARGS] = args;
    record[E_INLINE_COUNT] = SSI@inlineParams[site];
    record[E_INLINE_ZERO_SKIP] = (SSI_INLINE_FAST - SSI@inlineParams[site]) * 8;
    record[E_INLINE_SCALAR] = SSI@inlineScalar[site] && SSI@inlineParams[site] <= SSI_INLINE_FAST;
}

static stock SSI_InlineMismatchInternal(InlineSite:site, const signature[]) {
    new
        name[SSI_INLINE_NAME],
        found[SSI_INLINE_PARAMS + 1]
    ;

    for (new i; i != SSI@inlineParams[site]; ++i) {
        found[i] = (SSI@inlineParam[site][i] == 1) ? 'i' : 's';
    }

    strunpack(name, SSI@inlineName[site]);

    return SSI_InlineSignatureInternal(name, signature, found);
}

static stock SSI_InlineMatchInternal(InlineSite:site, const signature[]) {
    new const
        address = __emit(load.s.pri signature),
        count = SSI@inlineParams[site]
    ;

    if (SSI@inlineChecked[site] == address) {
        return 0;
    }

    for (new i; i != count; ++i) {
        if (signature[i] == EOS) {
            return SSI_InlineMismatchInternal(site, signature);
        }

        if ((signature[i] == 's') != (SSI@inlineParam[site][i] != 1)) {
            return SSI_InlineMismatchInternal(site, signature);
        }
    }

    if (signature[count] != EOS) {
        return SSI_InlineMismatchInternal(site, signature);
    }

    SSI@inlineChecked[site] = address;

    return 0;
}

static stock SSI_InlineParamInternal(at, source, cells) {
    if (cells == 1) {
        __emit(
            lref.s.pri source,
            sref.s.pri at
        );

        return;
    }

    __emit(
        load.s.pri cells,
        shl.c.pri 2,
        sref.pri SSI@inlinePatchFill,
        load.s.alt at,
        zero.pri,
        fill 4,
        push.s cells,
        push.s source,
        push.s at,
        push.c 12,
        sysreq.c strunpack,
        stack 16
    );
}

static stock SSI_InlineParamsInternal(InlineClosure:slot) {
    new const
        InlineSite:site = SSI@inlineRecord[slot][E_INLINE_SITE],
        base = SSI@inlineDest,
        count = SSI@inlineParams[site],
        given = SSI@Amx_Read(SSI@inlineCaller + 8) / 4 - 1
    ;

    for (new i; i != count; ++i) {
        new
            source = __emit(const.pri SSI@inlineZero)
        ;

        if (i < given) {
            source = SSI@Amx_Read(SSI@inlineCaller + 16 + i * 4);
        }

        SSI_InlineParamInternal(base + SSI@inlineParamAt[site][i], source, SSI@inlineParam[site][i]);
    }
}

stock SSI@Inline_Start(&InlineSite:site, const name[]) {
    if (site != INVALID_INLINE_SITE) {
        if (__emit(load.s.pri 0, add.c 4, load.i) != SSI@inlineReturn) {
            return 0;
        }

        if (InlineSite:__emit(load.s.pri 0, load.i, add.c -4, load.i) != site) {
            return 0;
        }

        __emit(
            load.s.pri 0,
            sctrl 4,
            zero.pri,
            retn
        );
    }

    SSI@Amx_Ready();

    if (SSI@inlinePatchIn == 0) {
        SSI_InlinePatchInternal();
    }

    new const
        frm = __emit(lctrl 5),
        caller = __emit(load.s.pri 0),
        ret = __emit(load.s.pri 4),
        opcode = SSI@Amx_Read(ret + SSI@amxCode)
    ;

    if (opcode != SSI@amxOpcode[SSI_INLINE_OP_JZER]) {
        return SSI_InlineLayoutInternal(opcode);
    }

    if (SSI@inlineSites == SSI_INLINE_SITES) {
        return SSI_InlineLayoutInternal(SSI_INLINE_SITES);
    }

    site = SSI@inlineSites++;

    SSI@inlineInit[site] = ret + 8;
    SSI@inlineLocals[site] = caller - (frm + 20);
    SSI@inlineRegistering = site;
    strpack(SSI@inlineName[site], name);

    return 1;
}

stock SSI@Inline_Loop() {
    __emit(
        load.pri SSI@inlineRegistering,
        eq.c.pri -1,
        jzer inline_loop_register,
        load.s.pri 0,
        sctrl 4,
        zero.pri,
        retn
    );

inline_loop_register:
    new const
        InlineSite:index = SSI@inlineRegistering,
        frm = __emit(lctrl 5),
        caller = __emit(load.s.pri 0),
        ret = __emit(load.s.pri 4),
        condition = ret - 16
    ;

    SSI@inlineRegistering = INVALID_INLINE_SITE;

    if (SSI@Amx_Read(ret + SSI@amxCode) != SSI@amxOpcode[SSI_INLINE_OP_JZER]) {
        return SSI_InlineLayoutInternal(SSI@Amx_Read(ret + SSI@amxCode));
    }

    if (SSI@Amx_Read(condition + SSI@amxCode) != SSI@amxOpcode[SSI_INLINE_OP_PUSH_C]) {
        return SSI_InlineLayoutInternal(SSI@Amx_Read(condition + SSI@amxCode));
    }

    if (SSI@Amx_Read(condition + 8 + SSI@amxCode) != SSI@amxOpcode[SSI_INLINE_OP_CALL]) {
        return SSI_InlineLayoutInternal(SSI@Amx_Read(condition + 8 + SSI@amxCode));
    }

    new
        address = SSI@inlineInit[index],
        params,
        bytes,
        bool:scalar = true
    ;

    while (address < condition) {
        new const
            opcode = SSI@Amx_Opcode(SSI@Amx_Read(address + SSI@amxCode))
        ;

        if (opcode == -1) {
            return SSI_InlineLayoutInternal(-1);
        }

        if (opcode == SSI_INLINE_OP_STACK || opcode == SSI_INLINE_OP_PUSH_C) {
            new const
                size = (opcode == SSI_INLINE_OP_STACK) ? -SSI@Amx_Read(address + 4 + SSI@amxCode) : 4
            ;

            if (params == SSI_INLINE_PARAMS) {
                return SSI_InlineLayoutInternal(SSI_INLINE_PARAMS);
            }

            if (size != 4) {
                scalar = false;
            }

            bytes += size;
            SSI@inlineParam[index][params] = size / 4;
            SSI@inlineParamAt[index][params++] = -bytes;
        }

        address += 4 + SSI@amxOperands[opcode] * 4;
    }

    if (caller - (frm + 12) != SSI@inlineLocals[index] + bytes) {
        return SSI_InlineLayoutInternal(bytes);
    }

    for (new i; i != params; ++i) {
        SSI@inlineParamAt[index][i] += bytes;
    }

    SSI@inlineParams[index] = params;
    SSI@inlineParamBytes[index] = bytes;
    SSI@inlineScalar[index] = scalar;
    SSI@inlineEntry[index] = ret + 8;

    return 0;
}

stock SSI@Inline_Jump() {
    __emit(
        load.s.pri 4,
        stor.pri SSI@inlineReturn,
        load.alt SSI@inlineAt,
        const.pri E_INLINE_BELOW,
        lidx,
        move.alt,
        lctrl 5,
        sub,
        sctrl 4,
        load.alt SSI@inlineAt,
        const.pri E_INLINE_ENTER,
        lidx,
        sctrl 6
    );
}

stock SSI@Inline_Return({SSI@Inline_Nothing, _}:value) {
    __emit(
        load.s.alt value,
        load.s.pri 0,
        sctrl 4,
        move.pri,
        retn
    );
}

stock Inline:SSI@Inline_Capture(InlineSite:site, const signature[]) {
    new const
        owner = SSI@inlineOwner,
        tag = SSI@inlineOwnerTag
    ;

    SSI@inlineOwnerTag = SSI_INLINE_NO_OWNER;

    if (!(InlineSite:0 <= site < SSI@inlineSites)) {
        return INVALID_INLINE;
    }

    if (signature[0] != '*' && SSI@inlineChecked[site] != __emit(load.s.pri signature)) {
        SSI_InlineMatchInternal(site, signature);
    }

    new const
        outer = __emit(load.s.pri 0, load.i),
        locals = SSI@inlineLocals[site],
        params = SSI@inlineParamBytes[site]
    ;

    new
        args = SSI@Amx_Read(outer + 8)
    ;

    if (args < 0) {
        args = SSI@Amx_Read(SSI@Amx_Read(outer) + 8);
    }

    if ((locals + args) / 4 > SSI_INLINE_CELLS) {
        return INVALID_INLINE;
    }

    new const
        InlineClosure:slot = Collection_Alloc(InlineClosure)
    ;

    if (slot == INVALID_INLINE_CLOSURE) {
        return INVALID_INLINE;
    }

    SSI@inlineGeneration[slot] = SSI@inlineGeneration[slot] % SSI_INLINE_GENERATIONS + 1;

    new const
        span = locals + 12 + args,
        source = outer - locals,
        image = SSI_Inline_Image(slot),
        Inline:closure = SSI_Inline_Ticket(slot)
    ;

    SSI_InlineRecordInternal(SSI@inlineRecord[slot], closure, site, locals, params, args, image);
    SSI_InlineOwnInternal(slot, owner, tag);

    __emit(
        load.s.pri span,
        shr.c.pri 2,
        push.pri,
        push.s span,
        push.c 0,
        push.s source,
        push.s image,
        push.c 20,
        sysreq.c memcpy,
        stack 24
    );

    return closure;
}

stock InlineSite:SSI@Inline_Own(owner, tag, InlineSite:site) {
    SSI@inlineOwner = owner;
    SSI@inlineOwnerTag = tag;

    return site;
}

static stock SSI_InlineOwnInternal(InlineClosure:slot, owner, tag) {
    SSI@inlineRecord[slot][E_INLINE_OWNER] = owner;
    SSI@inlineRecord[slot][E_INLINE_OWNER_TAG] = tag;

    if (tag == SSI_INLINE_NO_OWNER) {
        return;
    }

    Collection_Add(InlineOwner<(owner ^ tag) & (SSI_INLINE_OWNER_GROUPS - 1)>, _:slot);
}

stock bool:SSI@Inline_Give(Inline:closure, owner, tag) {
    new const
        InlineClosure:slot = SSI_InlineSlotInternal(closure)
    ;

    if (slot == INVALID_INLINE_CLOSURE) {
        return false;
    }

    if (SSI@inlineRecord[slot][E_INLINE_OWNER_TAG] != SSI_INLINE_NO_OWNER) {
        Collection_Remove(InlineOwner<>, _:slot);
    }

    SSI_InlineOwnInternal(slot, owner, tag);

    return true;
}

stock SSI@Inline_FreeOwned(owner, tag) {
    new const
        group = (owner ^ tag) & (SSI_INLINE_OWNER_GROUPS - 1)
    ;

    new
        freed = 0
    ;

    foreach (new InlineClosure:slot : InlineOwner<group>) {
        if (SSI@inlineRecord[slot][E_INLINE_OWNER] != owner) {
            continue;
        }

        if (SSI@inlineRecord[slot][E_INLINE_OWNER_TAG] != tag) {
            continue;
        }

        Inline_Free(SSI@inlineRecord[slot][E_INLINE_TICKET]);
        ++freed;
    }

    return freed;
}

/**
 * # Inline
 */

stock Inline:operator=(InlineSite:site) {
    return SSI@Inline_Capture(site, "*");
}

Inline_Signature()
SSI@Inline_Signatures()
SSI@Inline_Signatures2()
SSI@Inline_Signatures2(i)
SSI@Inline_Signatures2(f)
SSI@Inline_Signatures2(s)
SSI@Inline_Signatures2(ii)
SSI@Inline_Signatures2(if)
SSI@Inline_Signatures2(is)
SSI@Inline_Signatures2(fi)
SSI@Inline_Signatures2(ff)
SSI@Inline_Signatures2(fs)
SSI@Inline_Signatures2(si)
SSI@Inline_Signatures2(sf)
SSI@Inline_Signatures2(ss)

stock Inline_Call({Inline, SSI@Inline_Callee}:closure, OPEN_MP_TAGS:...) {
    new
        InlineSite:site,
        record,
        result,
        top
    ;

    __emit(
        load.s.pri closure,
        zero.alt,
        jsleq inline_call_none,
        const.alt SSI_INLINE_CLOSURE_COUNT,
        xchg,
        sdiv.alt,
        move.pri,
        smul.c SSI_INLINE_RECORD_BYTES,
        load.alt SSI@inlineRecordBase,
        add,
        stor.s.pri record,
        stor.pri SSI@inlineAt,
        load.i,
        load.s.alt closure,
        jneq inline_call_none,
        load.s.alt record,
        const.pri E_INLINE_SITE,
        lidx,
        stor.s.pri site,
        lctrl 5,
        stor.pri SSI@inlineCaller,
        const.pri E_INLINE_COUNT,
        lidx,
        jzer inline_call_enter,
        stor.pri SSI@inlineCount,
        const.pri E_INLINE_SCALAR,
        lidx,
        jzer inline_call_mixed,
        const.pri E_INLINE_BYTES,
        lidx,
        move.alt,
        lctrl 4,
        sub,
        stor.pri SSI@inlineDest,
        load.s.alt record,
        const.pri E_INLINE_ZERO_SKIP,
        lidx,
        stor.pri SSI@inlineZeroSkip,
        load.pri SSI@inlineCaller,
        add.c 8,
        load.i,
        shr.c.pri 2,
        add.c -1,
        stor.pri SSI@inlineGiven,
        load.alt SSI@inlineCount,
        jsleq inline_call_scalar,
        stor.alt SSI@inlineGiven
    );

inline_call_scalar:
    __emit(
        load.pri SSI@inlineGiven,
        neg,
        add.c SSI_INLINE_FAST,
        smul.c 24,
        stor.pri SSI@inlineGivenSkip,
        lctrl 5,
        stor.pri SSI@inlineFrame,
        load.pri SSI@inlineDest,
        sctrl 5,
        lctrl 6,
        add.c 28,
        load.alt SSI@inlineZeroSkip,
        add,
        sctrl 6,
        zero.s -32,
        zero.s -28,
        zero.s -24,
        zero.s -20,
        zero.s -16,
        zero.s -12,
        zero.s -8,
        zero.s -4,
        lctrl 6,
        add.c 36,
        load.alt SSI@inlineGivenSkip,
        add,
        load.alt SSI@inlineCaller,
        sctrl 6,
        const.pri 11,
        lidx,
        load.i,
        stor.s.pri -32,
        const.pri 10,
        lidx,
        load.i,
        stor.s.pri -28,
        const.pri 9,
        lidx,
        load.i,
        stor.s.pri -24,
        const.pri 8,
        lidx,
        load.i,
        stor.s.pri -20,
        const.pri 7,
        lidx,
        load.i,
        stor.s.pri -16,
        const.pri 6,
        lidx,
        load.i,
        stor.s.pri -12,
        const.pri 5,
        lidx,
        load.i,
        stor.s.pri -8,
        const.pri 4,
        lidx,
        load.i,
        stor.s.pri -4,
        load.pri SSI@inlineFrame,
        sctrl 5
    );

inline_call_enter:
    __emit(
        lctrl 4,
        stor.s.pri top,
        load.s.alt record,
        const.pri E_INLINE_BYTES,
        lidx,
        sref.pri SSI@inlinePatchIn,
        move.alt,
        load.s.pri top,
        sub,
        sctrl 4,
        move.alt,
        load.s.pri record,
        add.c SSI_INLINE_FROM_AT,
        load.i,
        movs 4,
        load.s.alt record,
        const.pri E_INLINE_ARGS,
        lidx,
        move.alt,
        load.s.pri top,
        sub,
        sctrl 4,
        push.alt,
        load.s.pri record,
        stor.pri SSI@inlineAt,
        call SSI@Inline_Jump,
        stor.s.pri result,
        load.s.alt record,
        const.pri E_INLINE_BYTES,
        lidx,
        stor.pri SSI@inlineValue,
        move.alt,
        load.s.pri top,
        sub,
        sctrl 4,
        load.s.alt record,
        move.pri,
        load.i,
        load.s.alt closure,
        eq,
        load.alt SSI@inlineValue,
        smul,
        sref.pri SSI@inlinePatchOut,
        load.s.alt record,
        const.pri E_INLINE_FROM,
        lidx,
        move.alt,
        lctrl 4,
        movs 4,
        load.s.pri top,
        sctrl 4
    );

    return result;

inline_call_mixed:
    __emit(
        load.s.alt record,
        const.pri E_INLINE_DEEP,
        lidx,
        move.alt,
        lctrl 4,
        sub,
        sctrl 4,
        stor.pri SSI@inlineDest
    );

    SSI_InlineParamsInternal(SSI_Inline_Slot(closure));

    __emit(jump inline_call_enter);

inline_call_none:
    return 0;
}

stock Inline_CallOnce({Inline, SSI@Inline_Callee}:closure, OPEN_MP_TAGS:...) {
    new
        result
    ;

    __emit(
        load.pri SSI@inlinePatchOnce,
        jzer inline_once_none,
        load.s.pri 8,
        sref.pri SSI@inlinePatchOnce,
        move.alt,
        lctrl 4,
        sub,
        sctrl 4,
        move.alt,
        addr.pri 12,
        movs 4,
        load.s.pri 8,
        push.pri,
        call Inline_Call,
        stor.s.pri result,
        push.s closure,
        push.c 4,
        call Inline_Free
    );

    return result;

inline_once_none:
    return 0;
}

stock bool:Inline_Free(Inline:closure) {
    new const
        InlineClosure:slot = SSI_InlineSlotInternal(closure)
    ;

    if (slot == INVALID_INLINE_CLOSURE) {
        return false;
    }

    if (SSI@inlineRecord[slot][E_INLINE_OWNER_TAG] != SSI_INLINE_NO_OWNER) {
        Collection_Remove(InlineOwner<>, _:slot);
    }

    SSI@inlineRecord[slot][E_INLINE_TICKET] = INVALID_INLINE;
    Collection_Remove(InlineClosure, slot);

    return true;
}

stock bool:Inline_IsValid(Inline:closure) {
    return SSI_InlineSlotInternal(closure) != INVALID_INLINE_CLOSURE;
}

stock Inline_Count() {
    return Collection_Count(InlineClosure);
}

static stock SSI_InlinePatchInternal() {
    SSI@inlineRecordBase = __emit(const.pri SSI@inlineRecord) + sizeof SSI@inlineRecord * 4;
    SSI@inlineDataBase = __emit(const.pri SSI@inlineData) + sizeof SSI@inlineData * 4;
    SSI@inlinePatchIn = SSI_InlineOperandInternal(__addressof(Inline_Call), SSI_INLINE_OP_MOVS);
    SSI@inlinePatchOut = SSI_InlineOperandInternal(SSI@inlinePatchIn - SSI@amxCode + 4, SSI_INLINE_OP_MOVS);
    SSI@inlinePatchOnce = SSI_InlineOperandInternal(__addressof(Inline_CallOnce), SSI_INLINE_OP_MOVS);
    SSI@inlinePatchFill = SSI_InlineOperandInternal(__addressof(SSI_InlineParamInternal), SSI_INLINE_OP_FILL);
}

/**
 * # Calls
 */

hook OnPlayerConnect@Inline(playerid) {
    Inline_FreeOwned(playerid);

    return 1;
}

hook OnPlayerDisconnect@Inline(playerid, reason) {
    Inline_FreeOwned(playerid);

    return 1;
}

hook native bool:DestroyVehicle(vehicleid) {
    Inline_FreeOwned(Vehicle:vehicleid);

    return DestroyVehicle(vehicleid);
}

hook native bool:DestroyObject(objectid) {
    Inline_FreeOwned(Object:objectid);

    return DestroyObject(objectid);
}

hook native bool:DestroyPickup(pickup) {
    Inline_FreeOwned(Pickup:pickup);

    return DestroyPickup(pickup);
}
