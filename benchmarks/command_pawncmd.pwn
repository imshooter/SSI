#define BENCH_SIDE "Pawn.CMD"

#include <open.mp>
#include <Pawn.CMD>
#include "bench.inc"

new
    gHits,
    gRank[MAX_PLAYERS],
    gAdminBot = INVALID_PLAYER_ID,
    gPlainBot = INVALID_PLAYER_ID
;

First() {
    gAdminBot = NPC_Create("AdminBot");
    gPlainBot = NPC_Create("PlainBot");
    gRank[gAdminBot] = 3;
}

public OnPlayerCommandReceived(playerid, cmd[], params[], flags) {
    return flags <= gRank[playerid];
}

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags) {
    return 1;
}

Run() {
    new
        inherited[] = "/c5 hello",
        last[] = "/c999 hello",
        denied[] = "/c15 hello",
        unknown[] = "/nothing hello"
    ;

    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            PC_EmulateCommand(gAdminBot, inherited);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("command", "allowed through 2 parent groups, 1000 commands");
    Bench_Check("allowed commands ran", gHits, gBenchOps);

    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            PC_EmulateCommand(gPlainBot, last);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("command", "free, the last of 1000 commands");
    Bench_Check("free commands ran", gHits, gBenchOps);

    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            PC_EmulateCommand(gPlainBot, last);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("command", "typed by a player, the last of 1000 commands");
    Bench_Check("typed commands ran", gHits, gBenchOps);

    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            PC_EmulateCommand(gPlainBot, denied);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("command", "denied, 1000 commands");
    Bench_Check("denied commands ran", gHits, 0);

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            PC_EmulateCommand(gPlainBot, unknown);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("command", "unknown, 1000 commands");
}

Setup() {
}

cmd:c0(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c0(1)

cmd:c1(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c1(1)

cmd:c2(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c2(1)

cmd:c3(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c3(1)

cmd:c4(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c4(1)

cmd:c5(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c5(1)

cmd:c6(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c6(1)

cmd:c7(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c7(1)

cmd:c8(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c8(1)

cmd:c9(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c9(1)

cmd:c10(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c10(2)

cmd:c11(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c11(2)

cmd:c12(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c12(2)

cmd:c13(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c13(2)

cmd:c14(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c14(2)

cmd:c15(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c15(2)

cmd:c16(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c16(2)

cmd:c17(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c17(2)

cmd:c18(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c18(2)

cmd:c19(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c19(2)

cmd:c20(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c20(3)

cmd:c21(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c21(3)

cmd:c22(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c22(3)

cmd:c23(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c23(3)

cmd:c24(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c24(3)

cmd:c25(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c25(3)

cmd:c26(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c26(3)

cmd:c27(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c27(3)

cmd:c28(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c28(3)

cmd:c29(playerid, params[]) {
    ++gHits;

    return 1;
}

flags:c29(3)

cmd:c30(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c31(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c32(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c33(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c34(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c35(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c36(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c37(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c38(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c39(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c40(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c41(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c42(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c43(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c44(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c45(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c46(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c47(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c48(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c49(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c50(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c51(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c52(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c53(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c54(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c55(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c56(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c57(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c58(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c59(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c60(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c61(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c62(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c63(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c64(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c65(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c66(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c67(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c68(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c69(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c70(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c71(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c72(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c73(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c74(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c75(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c76(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c77(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c78(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c79(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c80(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c81(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c82(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c83(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c84(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c85(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c86(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c87(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c88(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c89(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c90(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c91(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c92(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c93(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c94(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c95(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c96(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c97(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c98(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c99(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c100(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c101(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c102(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c103(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c104(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c105(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c106(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c107(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c108(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c109(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c110(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c111(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c112(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c113(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c114(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c115(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c116(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c117(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c118(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c119(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c120(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c121(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c122(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c123(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c124(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c125(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c126(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c127(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c128(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c129(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c130(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c131(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c132(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c133(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c134(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c135(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c136(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c137(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c138(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c139(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c140(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c141(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c142(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c143(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c144(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c145(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c146(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c147(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c148(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c149(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c150(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c151(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c152(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c153(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c154(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c155(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c156(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c157(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c158(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c159(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c160(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c161(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c162(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c163(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c164(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c165(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c166(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c167(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c168(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c169(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c170(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c171(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c172(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c173(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c174(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c175(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c176(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c177(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c178(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c179(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c180(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c181(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c182(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c183(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c184(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c185(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c186(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c187(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c188(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c189(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c190(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c191(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c192(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c193(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c194(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c195(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c196(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c197(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c198(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c199(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c200(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c201(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c202(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c203(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c204(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c205(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c206(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c207(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c208(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c209(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c210(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c211(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c212(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c213(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c214(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c215(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c216(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c217(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c218(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c219(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c220(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c221(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c222(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c223(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c224(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c225(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c226(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c227(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c228(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c229(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c230(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c231(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c232(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c233(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c234(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c235(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c236(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c237(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c238(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c239(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c240(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c241(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c242(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c243(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c244(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c245(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c246(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c247(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c248(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c249(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c250(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c251(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c252(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c253(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c254(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c255(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c256(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c257(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c258(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c259(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c260(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c261(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c262(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c263(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c264(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c265(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c266(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c267(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c268(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c269(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c270(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c271(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c272(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c273(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c274(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c275(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c276(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c277(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c278(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c279(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c280(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c281(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c282(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c283(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c284(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c285(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c286(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c287(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c288(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c289(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c290(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c291(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c292(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c293(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c294(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c295(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c296(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c297(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c298(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c299(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c300(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c301(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c302(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c303(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c304(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c305(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c306(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c307(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c308(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c309(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c310(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c311(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c312(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c313(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c314(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c315(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c316(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c317(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c318(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c319(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c320(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c321(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c322(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c323(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c324(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c325(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c326(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c327(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c328(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c329(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c330(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c331(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c332(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c333(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c334(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c335(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c336(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c337(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c338(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c339(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c340(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c341(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c342(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c343(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c344(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c345(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c346(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c347(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c348(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c349(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c350(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c351(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c352(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c353(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c354(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c355(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c356(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c357(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c358(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c359(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c360(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c361(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c362(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c363(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c364(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c365(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c366(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c367(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c368(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c369(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c370(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c371(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c372(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c373(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c374(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c375(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c376(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c377(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c378(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c379(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c380(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c381(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c382(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c383(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c384(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c385(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c386(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c387(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c388(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c389(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c390(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c391(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c392(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c393(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c394(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c395(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c396(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c397(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c398(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c399(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c400(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c401(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c402(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c403(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c404(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c405(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c406(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c407(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c408(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c409(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c410(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c411(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c412(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c413(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c414(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c415(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c416(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c417(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c418(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c419(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c420(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c421(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c422(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c423(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c424(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c425(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c426(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c427(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c428(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c429(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c430(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c431(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c432(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c433(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c434(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c435(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c436(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c437(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c438(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c439(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c440(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c441(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c442(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c443(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c444(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c445(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c446(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c447(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c448(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c449(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c450(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c451(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c452(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c453(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c454(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c455(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c456(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c457(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c458(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c459(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c460(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c461(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c462(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c463(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c464(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c465(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c466(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c467(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c468(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c469(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c470(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c471(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c472(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c473(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c474(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c475(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c476(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c477(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c478(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c479(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c480(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c481(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c482(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c483(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c484(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c485(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c486(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c487(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c488(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c489(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c490(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c491(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c492(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c493(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c494(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c495(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c496(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c497(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c498(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c499(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c500(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c501(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c502(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c503(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c504(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c505(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c506(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c507(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c508(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c509(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c510(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c511(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c512(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c513(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c514(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c515(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c516(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c517(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c518(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c519(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c520(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c521(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c522(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c523(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c524(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c525(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c526(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c527(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c528(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c529(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c530(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c531(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c532(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c533(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c534(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c535(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c536(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c537(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c538(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c539(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c540(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c541(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c542(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c543(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c544(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c545(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c546(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c547(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c548(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c549(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c550(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c551(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c552(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c553(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c554(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c555(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c556(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c557(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c558(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c559(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c560(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c561(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c562(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c563(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c564(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c565(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c566(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c567(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c568(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c569(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c570(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c571(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c572(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c573(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c574(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c575(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c576(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c577(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c578(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c579(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c580(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c581(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c582(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c583(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c584(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c585(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c586(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c587(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c588(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c589(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c590(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c591(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c592(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c593(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c594(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c595(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c596(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c597(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c598(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c599(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c600(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c601(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c602(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c603(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c604(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c605(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c606(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c607(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c608(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c609(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c610(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c611(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c612(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c613(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c614(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c615(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c616(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c617(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c618(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c619(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c620(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c621(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c622(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c623(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c624(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c625(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c626(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c627(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c628(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c629(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c630(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c631(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c632(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c633(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c634(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c635(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c636(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c637(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c638(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c639(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c640(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c641(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c642(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c643(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c644(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c645(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c646(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c647(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c648(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c649(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c650(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c651(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c652(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c653(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c654(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c655(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c656(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c657(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c658(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c659(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c660(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c661(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c662(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c663(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c664(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c665(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c666(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c667(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c668(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c669(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c670(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c671(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c672(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c673(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c674(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c675(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c676(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c677(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c678(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c679(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c680(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c681(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c682(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c683(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c684(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c685(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c686(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c687(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c688(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c689(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c690(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c691(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c692(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c693(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c694(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c695(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c696(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c697(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c698(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c699(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c700(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c701(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c702(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c703(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c704(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c705(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c706(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c707(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c708(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c709(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c710(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c711(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c712(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c713(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c714(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c715(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c716(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c717(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c718(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c719(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c720(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c721(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c722(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c723(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c724(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c725(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c726(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c727(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c728(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c729(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c730(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c731(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c732(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c733(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c734(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c735(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c736(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c737(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c738(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c739(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c740(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c741(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c742(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c743(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c744(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c745(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c746(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c747(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c748(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c749(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c750(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c751(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c752(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c753(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c754(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c755(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c756(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c757(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c758(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c759(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c760(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c761(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c762(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c763(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c764(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c765(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c766(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c767(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c768(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c769(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c770(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c771(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c772(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c773(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c774(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c775(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c776(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c777(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c778(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c779(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c780(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c781(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c782(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c783(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c784(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c785(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c786(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c787(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c788(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c789(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c790(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c791(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c792(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c793(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c794(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c795(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c796(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c797(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c798(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c799(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c800(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c801(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c802(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c803(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c804(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c805(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c806(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c807(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c808(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c809(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c810(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c811(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c812(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c813(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c814(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c815(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c816(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c817(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c818(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c819(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c820(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c821(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c822(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c823(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c824(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c825(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c826(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c827(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c828(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c829(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c830(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c831(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c832(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c833(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c834(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c835(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c836(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c837(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c838(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c839(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c840(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c841(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c842(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c843(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c844(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c845(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c846(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c847(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c848(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c849(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c850(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c851(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c852(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c853(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c854(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c855(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c856(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c857(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c858(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c859(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c860(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c861(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c862(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c863(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c864(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c865(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c866(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c867(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c868(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c869(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c870(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c871(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c872(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c873(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c874(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c875(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c876(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c877(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c878(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c879(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c880(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c881(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c882(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c883(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c884(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c885(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c886(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c887(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c888(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c889(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c890(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c891(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c892(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c893(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c894(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c895(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c896(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c897(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c898(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c899(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c900(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c901(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c902(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c903(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c904(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c905(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c906(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c907(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c908(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c909(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c910(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c911(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c912(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c913(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c914(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c915(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c916(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c917(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c918(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c919(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c920(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c921(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c922(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c923(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c924(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c925(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c926(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c927(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c928(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c929(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c930(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c931(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c932(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c933(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c934(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c935(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c936(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c937(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c938(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c939(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c940(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c941(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c942(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c943(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c944(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c945(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c946(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c947(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c948(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c949(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c950(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c951(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c952(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c953(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c954(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c955(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c956(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c957(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c958(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c959(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c960(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c961(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c962(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c963(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c964(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c965(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c966(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c967(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c968(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c969(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c970(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c971(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c972(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c973(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c974(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c975(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c976(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c977(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c978(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c979(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c980(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c981(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c982(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c983(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c984(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c985(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c986(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c987(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c988(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c989(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c990(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c991(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c992(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c993(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c994(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c995(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c996(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c997(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c998(playerid, params[]) {
    ++gHits;

    return 1;
}

cmd:c999(playerid, params[]) {
    ++gHits;

    return 1;
}

main() {
}

forward @Bench();
public @Bench() {
    if (gBenchRound == 0) {
        First();
        gBenchQuiet = true;
        Run();
        gBenchQuiet = false;
    } else {
        Bench_Calibrate();
        Run();
    }

    if (++gBenchRound > BENCH_ROUNDS) {
        Bench_Done();
    } else {
        SetTimer("@Bench", 500, false);
    }
}

public OnGameModeInit() {
    Setup();
    SetTimer("@Bench", 1000, false);

    return 1;
}
