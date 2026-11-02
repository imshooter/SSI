#if defined _INC_SSI_VA
    #endinput
#endif
#define _INC_SSI_VA

#include <SSI\amx>

/**
 * Variable arguments: `___(n)` passes on the arguments a function got, from
 * its `n`th on, anywhere among the arguments of a call, as y_va's `___`.
 *
 *     stock SendFormatted(playerid, colour, const message[], OPEN_MP_TAGS:...) {
 *         return SendClientMessage(playerid, colour, message, ___(3));
 *     }
 *
 *     stock PrintBetween(OPEN_MP_TAGS:...) {
 *         printf("%d %s %d", 5, ___(0), 8);
 *     }
 *
 * pawncc writes the number of arguments of every call as a constant, so the
 * first time a `___` runs it rewrites the call it is in: the arguments are
 * copied where pawncc would push one cell for the `___`, the count is taken
 * from the stack, and the arguments a native leaves behind are taken off by
 * that count. Nothing is scanned at start up. The arguments passed on must be
 * references, as the variable arguments of a function are. `n` must be a
 * constant, and a `___` must be an argument of the call itself, not part of an
 * expression. Code compiled with `-O2` is not supported.
 */

/**
 * # Header
 */

#if !defined MAX_VA_DEPTH
    #define MAX_VA_DEPTH (32)
#endif

/**
 * # Functions
 */

/**
 * @brief      Pass on the arguments of the function this is written in.
 *
 * @param      first  Index of the first argument passed on, a constant.
 */
forward ___(first);
#define ___(%0) SSI@VaSpread(%0)

/**
 * # Internal
 */

static stock
    SSI@vaUnsupported[1],
    bool:SSI@vaReady,
    SSI@vaNestedEntry,
    SSI@vaJoinedEntry,
    SSI@vaPlainEntry,
    SSI@vaNestedCountEntry,
    SSI@vaPlainCountEntry,
    SSI@vaPopEntry,
    SSI@vaMovs,
    SSI@vaFrom,
    SSI@vaReturn,
    SSI@vaLast,
    SSI@vaTop,
    SSI@vaStart[MAX_VA_DEPTH]
;

static stock SSI_VaReadInternal(address) {
    return SSI@Amx_Read(address + SSI@amxCode);
}

static stock SSI_VaWriteInternal(address, value) {
    SSI@Amx_Write(address + SSI@amxCode, value);
}

static stock SSI_VaSpreadRaw() {
    __emit(
        stor.pri SSI@vaFrom,
        lctrl 4,
        add,
        move.alt,
        load.pri SSI@vaTop,
        add.c 4,
        bounds 0,
        stor.pri SSI@vaTop,
        sref.alt SSI@vaTop,
        jump ssi_va_raw,
        stor.pri SSI@vaFrom,
        jump ssi_va_raw,
        stor.pri SSI@vaFrom,
        lctrl 4,
        add,
        stor.pri SSI@vaLast,
        pop.pri,
        stor.pri SSI@vaReturn,
        load.s.pri 8,
        addr.alt 8,
        add,
        load.alt SSI@vaFrom,
        sub,
        zero.alt,
        jsgeq ssi_va_raw,
        addr.pri 8,
        stor.pri SSI@vaFrom,
        zero.pri,
        add.c 4,
        sref.pri SSI@vaMovs,
        move.alt,
        lctrl 4,
        sub,
        sctrl 4,
        move.alt,
        load.pri SSI@vaFrom,
        movs 4,
        pop.alt,
        load.pri SSI@vaReturn,
        sctrl 6
    );

ssi_va_raw:
    return 0;
}

static stock SSI_VaNestedCountRaw() {
    __emit(
        lref.alt SSI@vaTop,
        load.pri SSI@vaTop,
        add.c -4,
        stor.pri SSI@vaTop,
        lctrl 4,
        sub.alt,
        swap.pri,
        sctrl 6
    );
}

static stock SSI_VaPlainCountRaw() {
    __emit(
        load.alt SSI@vaLast,
        lctrl 4,
        sub.alt,
        swap.pri,
        sctrl 6
    );
}

static stock SSI_VaPopRaw() {
    __emit(
        push.adr 0,
        retn
    );
}

static stock bool:SSI_VaReadyInternal() {
    if (SSI@vaReady) {
        return true;
    }

    if (!SSI@Amx_Ready()) {
        return false;
    }

    new
        address
    ;

    SSI@vaNestedEntry = SSI@Amx_Entry(__addressof(SSI_VaSpreadRaw));
    SSI@vaNestedCountEntry = SSI@Amx_Entry(__addressof(SSI_VaNestedCountRaw));
    SSI@vaPlainCountEntry = SSI@Amx_Entry(__addressof(SSI_VaPlainCountRaw));
    SSI@vaPopEntry = SSI@Amx_Entry(__addressof(SSI_VaPopRaw));

    new
        jumps,
        jumpAt[2],
        tail,
        branch,
        skip,
        bound,
        first
    ;

    for (address = SSI@vaNestedEntry; SSI_VaReadInternal(address) != SSI@amxOpcode[117]; ) {
        new const
            opcode = SSI@Amx_Opcode(SSI_VaReadInternal(address))
        ;

        switch (opcode) {
            case 51: {
                jumpAt[jumps++] = address;
            }
            case 42: {
                tail = address;
            }
            case 64: {
                branch = address;
            }
            case 89: {
                skip = address + 4;
            }
            case 121: {
                bound = address;
            }
        }

        address += 4 + SSI@amxOperands[opcode] * 4;
    }

    SSI@vaMovs = address + 4 + SSI@amxCode;
    SSI@vaJoinedEntry = jumpAt[0] + 8;
    SSI@vaPlainEntry = jumpAt[1] + 8;

    SSI_VaWriteInternal(jumpAt[0] + 4, tail + SSI@amxDelta);
    SSI_VaWriteInternal(jumpAt[1] + 4, tail + SSI@amxDelta);
    SSI_VaWriteInternal(branch + 4, skip + SSI@amxDelta);

    __emit(
        const.pri SSI@vaStart,
        stor.s.pri first
    );

    SSI@vaTop = first - 4;
    SSI_VaWriteInternal(bound + 4, first + (MAX_VA_DEPTH - 1) * 4);

    SSI@vaReady = true;

    return true;
}

static stock SSI_VaFailInternal(address) {
    return SSI@vaUnsupported[address];
}

static stock SSI_VaPatchInternal(first) {
    new
        call
    ;

    __emit(
        load.s.pri 0,
        add.c 4,
        load.i,
        stor.s.pri call
    );

    if (!SSI_VaReadyInternal()) {
        return SSI_VaFailInternal(call);
    }

    if (SSI_VaReadInternal(call - 8) != SSI@amxOpcode[49]) {
        return SSI_VaFailInternal(call);
    }

    if (SSI_VaReadInternal(call - 12) != 4) {
        return SSI_VaFailInternal(call);
    }

    if (SSI_VaReadInternal(call - 16) != SSI@amxOpcode[39]) {
        return SSI_VaFailInternal(call);
    }

    new
        start
    ;

    if (SSI_VaReadInternal(call - 20) == SSI@amxOpcode[36] && SSI_VaReadInternal(call - 24) == first && SSI_VaReadInternal(call - 28) == SSI@amxOpcode[11]) {
        start = call - 28;
    } else if (SSI_VaReadInternal(call - 20) == SSI@amxOpcode[36] && first == 0 && SSI_VaReadInternal(call - 24) == SSI@amxOpcode[89]) {
        start = call - 24;
    } else if (SSI_VaReadInternal(call - 20) == first && SSI_VaReadInternal(call - 24) == SSI@amxOpcode[39]) {
        start = call - 24;
    } else {
        return SSI_VaFailInternal(call);
    }

    new
        address = call,
        end
    ;

    for (new i; i != 6 && !end; ++i) {
        new const
            opcode = SSI@Amx_Opcode(SSI_VaReadInternal(address))
        ;

        switch (opcode) {
            case 36, 37: {
                end = address + 4;
            }
            case 45, 23, 33, 34: {
            }
            default: {
                return SSI_VaFailInternal(call);
            }
        }

        address += 4 + SSI@amxOperands[opcode] * 4;
    }

    if (!end) {
        return SSI_VaFailInternal(call);
    }

    if (end - 32 < start) {
        return SSI_VaFailInternal(call);
    }

    new const
        spread = SSI_VaReadInternal(call - 4)
    ;

    new
        depth = 1,
        lastCount,
        countAt = -1,
        callAt,
        bool:joined,
        bool:nested
    ;

    for (new i; i != 4096 && countAt == -1; ++i) {
        new const
            opcode = SSI@Amx_Opcode(SSI_VaReadInternal(address))
        ;

        if (opcode == -1) {
            return SSI_VaFailInternal(call);
        }

        if (SSI@amxOperands[opcode] == -1) {
            return SSI_VaFailInternal(call);
        }

        new const
            next = address + 4 + SSI@amxOperands[opcode] * 4
        ;

        switch (opcode) {
            case 39: {
                new const
                    following = SSI@Amx_Opcode(SSI_VaReadInternal(next)),
                    count = SSI_VaReadInternal(address + 4)
                ;

                if ((following == 49 || following == 123) && count / 4 >= depth) {
                    countAt = address;
                    callAt = next;
                } else {
                    lastCount = count;
                    ++depth;
                }
            }
            case 49: {
                new const
                    target = SSI_VaReadInternal(address + 4)
                ;

                if (target == SSI@vaNestedCountEntry + SSI@amxDelta || target == SSI@vaPlainCountEntry + SSI@amxDelta) {
                    countAt = address;
                    joined = true;
                } else {
                    if (target != spread) {
                        nested = true;
                    }

                    depth -= lastCount / 4 + 1;
                }
            }
            case 123: {
                nested = true;
            }
            case 36, 37, 40, 41, 133: {
                ++depth;
            }
            case 42, 43: {
                --depth;
            }
            case 44: {
                depth -= SSI_VaReadInternal(address + 4) / 4;
            }
            case 47, 48, 50, 120, 122, 128, 129, 130: {
                return SSI_VaFailInternal(call);
            }
        }

        address = next;
    }

    if (countAt == -1) {
        return SSI_VaFailInternal(call);
    }

    new
        entry = SSI@vaJoinedEntry,
        right
    ;

    if (!joined) {
        new const
            callOpcode = SSI@Amx_Opcode(SSI_VaReadInternal(callAt))
        ;

        if (callOpcode == 123) {
            if (SSI@Amx_Opcode(SSI_VaReadInternal(callAt + 8)) != 44) {
                return SSI_VaFailInternal(call);
            }

            SSI_VaWriteInternal(callAt + 8, SSI@amxOpcode[49]);
            SSI_VaWriteInternal(callAt + 12, SSI@vaPopEntry + SSI@amxDelta);
        } else if (callOpcode != 49) {
            return SSI_VaFailInternal(call);
        }

        right = SSI_VaReadInternal(countAt + 4) - depth * 4;
        entry = nested ? SSI@vaNestedEntry : SSI@vaPlainEntry;

        SSI_VaWriteInternal(countAt, SSI@amxOpcode[49]);
        SSI_VaWriteInternal(countAt + 4, (nested ? SSI@vaNestedCountEntry : SSI@vaPlainCountEntry) + SSI@amxDelta);
    }

    new const
        code = end - 32
    ;

    if (code - start >= 8) {
        SSI_VaWriteInternal(start, SSI@amxOpcode[51]);
        SSI_VaWriteInternal(start + 4, code + SSI@amxDelta);
    } else if (code != start) {
        SSI_VaWriteInternal(start, SSI@amxOpcode[134]);
    }

    SSI_VaWriteInternal(code, SSI@amxOpcode[45]);
    SSI_VaWriteInternal(code + 4, 4);
    SSI_VaWriteInternal(code + 8, SSI@amxOpcode[13]);
    SSI_VaWriteInternal(code + 12, 8 + first * 4);
    SSI_VaWriteInternal(code + 16, SSI@amxOpcode[12]);
    SSI_VaWriteInternal(code + 20, right);
    SSI_VaWriteInternal(code + 24, SSI@amxOpcode[49]);
    SSI_VaWriteInternal(code + 28, entry + SSI@amxDelta);

    return start;
}

stock SSI@VaSpread(first) {
    new const
        start = SSI_VaPatchInternal(first)
    ;

    __emit(
        load.s.pri start,
        stor.s.pri 4
    );

    return 0;
}
