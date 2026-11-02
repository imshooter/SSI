#if defined _INC_SSI_AMX
    #endinput
#endif
#define _INC_SSI_AMX

/**
 * Access to the memory of the script beyond its data, for the libraries that
 * read or write code at run time: the code as the server relocated it, and the
 * header with its table of publics. Nothing here is meant to be called by a
 * script.
 *
 * A data address is what Pawn uses, counted from the start of the data. A code
 * address counts from the start of the code, as `__addressof` gives it and as
 * the table of publics stores it. A base offset counts from the start of the
 * header, as the header stores its tables and the names of the publics.
 *
 * `SSI@amxOpcode` holds the cell that the server stores for each opcode, read
 * from a sample of every opcode. A call or a jump stores the code address of
 * its target plus `SSI@amxDelta`. Adding `SSI@amxCode` to a code address gives
 * its data address, and adding `SSI@amxBase` to a base offset does the same.
 */

stock
    SSI@amxOpcode[160],
    SSI@amxCode,
    SSI@amxBase,
    SSI@amxDelta,
    bool:SSI@amxReady
;

static stock
    SSI@amxPointer,
    SSI@amxSample
;

stock const SSI@amxOperands[160] = {
    0,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  0,  1,  0,  1,  0,  1,  1,  1,  1,
    1,  0,  0,  0,  0,  0, -1,  1,  1,  1,  0,  0,  1,  1,  0,  0,
    0,  1,  0,  1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  1,  1,  0,
    0,  0,  1,  1,  0,  1,  1,  1,  1,  1,  0,  1, -1, -1, -1, -1,
    0, -1, -1,  0,  0,  1,  0, -1, -1,  0, -1, -1, -1, -1, -1, -1,
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

stock SSI@Amx_Sample() {
    __emit(
        const.pri 0x5AFE5AFE,
        load.pri SSI@amxSample,
        load.alt SSI@amxSample,
        load.s.pri 4,
        load.s.alt 4,
        lref.pri SSI@amxSample,
        lref.alt SSI@amxSample,
        lref.s.pri 4,
        lref.s.alt 4,
        load.i,
        lodb.i 4,
        const.pri 4,
        const.alt 4,
        addr.pri 4,
        addr.alt 4,
        stor.pri SSI@amxSample,
        stor.alt SSI@amxSample,
        stor.s.pri 4,
        stor.s.alt 4,
        sref.pri SSI@amxSample,
        sref.alt SSI@amxSample,
        sref.s.pri 4,
        sref.s.alt 4,
        stor.i,
        strb.i 4,
        lidx,
        lidx.b 1,
        idxaddr,
        idxaddr.b 1,
        align.pri 1,
        align.alt 1,
        lctrl 4,
        sctrl 4,
        move.pri,
        move.alt,
        xchg,
        push.pri,
        push.alt,
        push.c 4,
        push SSI@amxSample,
        push.s 4,
        pop.pri,
        pop.alt,
        stack 4,
        heap 4,
        proc,
        ret,
        retn,
        call SSI@Amx_Sample,
        call.pri,
        jump ssi_amx_sample,
        jzer ssi_amx_sample,
        jnz ssi_amx_sample,
        jeq ssi_amx_sample,
        jneq ssi_amx_sample,
        jless ssi_amx_sample,
        jleq ssi_amx_sample,
        jgrtr ssi_amx_sample,
        jgeq ssi_amx_sample,
        jsless ssi_amx_sample,
        jsleq ssi_amx_sample,
        jsgrtr ssi_amx_sample,
        jsgeq ssi_amx_sample,
        shl,
        shr,
        sshr,
        shl.c.pri 1,
        shl.c.alt 1,
        shr.c.pri 1,
        shr.c.alt 1,
        smul,
        sdiv,
        sdiv.alt,
        umul,
        udiv,
        udiv.alt,
        add,
        sub,
        sub.alt,
        and,
        or,
        xor,
        not,
        neg,
        invert,
        add.c 4,
        smul.c 4,
        zero.pri,
        zero.alt,
        zero SSI@amxSample,
        zero.s 4,
        sign.pri,
        sign.alt,
        eq,
        neq,
        less,
        leq,
        grtr,
        geq,
        sless,
        sleq,
        sgrtr,
        sgeq,
        eq.c.pri 4,
        eq.c.alt 4,
        inc.pri,
        inc.alt,
        inc SSI@amxSample,
        inc.s 4,
        inc.i,
        dec.pri,
        dec.alt,
        dec SSI@amxSample,
        dec.s 4,
        dec.i,
        movs 4,
        cmps 4,
        fill 4,
        halt 4,
        bounds 4,
        sysreq.pri,
        sysreq.c printf,
        jump.pri,
        swap.pri,
        swap.alt,
        push.adr 4,
        nop,
        break
    );

ssi_amx_sample:
    return 0;
}

static stock const SSI@amxSampled[] = {
     11,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18, 19, 20, 21, 22, 23, 24, 25,
     26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  39,  40,  41,  42,  43,  44,  45, 46, 47, 48, 49, 50,
     51,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70, 71, 72, 73, 74, 75,
     76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94, 95, 96, 97, 98, 99,
    100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118,
    119, 120, 121, 122, 123, 128, 131, 132, 133, 134, 137
};

stock SSI@Amx_Read(address) {
    SSI@amxPointer = address;

    __emit(
        lref.pri SSI@amxPointer,
        retn
    );

    return 0;
}

stock SSI@Amx_Write(address, value) {
    SSI@amxPointer = address;

    __emit(
        load.s.pri value,
        sref.pri SSI@amxPointer
    );
}

stock SSI@Amx_ReadByte(address) {
    return (SSI@Amx_Read(address & ~3) >>> ((address & 3) * 8)) & 0xFF;
}

stock SSI@Amx_WriteByte(address, value) {
    new const
        shift = (address & 3) * 8,
        cell = SSI@Amx_Read(address & ~3)
    ;

    SSI@Amx_Write(address & ~3, (cell & ~(0xFF << shift)) | ((value & 0xFF) << shift));
}

stock SSI@Amx_Address(const array[]) {
    __emit(
        load.s.pri array,
        retn
    );

    return 0;
}

stock SSI@Amx_Entry(address) {
    while (SSI@Amx_Read(address + SSI@amxCode) == SSI@amxOpcode[46] || SSI@Amx_Read(address + SSI@amxCode) == SSI@amxOpcode[137]) {
        address += 4;
    }

    return address;
}

stock SSI@Amx_Opcode(cell) {
    for (new opcode; opcode != sizeof SSI@amxOpcode; ++opcode) {
        if (SSI@amxOpcode[opcode] == cell) {
            return opcode;
        }
    }

    return -1;
}

stock SSI@Amx_Header(offset) {
    return SSI@Amx_Read(SSI@amxBase + offset);
}

stock bool:SSI@Amx_Ready() {
    if (SSI@amxReady) {
        return true;
    }

    __emit(
        lctrl 0,
        move.alt,
        lctrl 1,
        xchg,
        sub,
        stor.pri SSI@amxCode,
        lctrl 1,
        neg,
        stor.pri SSI@amxBase
    );

    for (new i; i != sizeof SSI@amxOpcode; ++i) {
        SSI@amxOpcode[i] = -1;
    }

    new const
        start = __addressof(SSI@Amx_Sample)
    ;

    new
        address = start + SSI@amxCode
    ;

    while (SSI@Amx_Read(address + 4) != 0x5AFE5AFE) {
        address += 4;

        if (address == start + SSI@amxCode + 64) {
            return false;
        }
    }

    for (new i; i != sizeof SSI@amxSampled; ++i) {
        new const
            opcode = SSI@amxSampled[i]
        ;

        if (opcode == 49) {
            SSI@amxDelta = SSI@Amx_Read(address + 4) - start;
        }

        SSI@amxOpcode[opcode] = SSI@Amx_Read(address);
        address += 4 + SSI@amxOperands[opcode] * 4;
    }

    if (SSI@amxOpcode[46] != SSI@Amx_Read(start + SSI@amxCode)) {
        return false;
    }

    SSI@amxReady = true;

    return true;
}
