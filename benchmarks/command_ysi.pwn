#define BENCH_SIDE "YSI"

#include <open.mp>
#define _FOREACH_NO_TEST
#define MAX_COMMANDS (1024)

#include <YSI_Visual\y_commands>
#include <YSI_Players\y_groups>
#include <YSI_Coding\y_hooks>
#include "bench.inc"

new
    Group:gHelper,
    Group:gModerator,
    Group:gAdmin,
    Group:gChain[16]
;

new
    gHits,
    gAdminBot = INVALID_PLAYER_ID,
    gPlainBot = INVALID_PLAYER_ID,
    gChainBot = INVALID_PLAYER_ID
;

First() {
    gAdminBot = NPC_Create("AdminBot");
    gPlainBot = NPC_Create("PlainBot");
    gChainBot = NPC_Create("ChainBot");
    Group_SetPlayer(gAdmin, gAdminBot, true);
    Group_SetPlayer(gChain[15], gChainBot, true);
}

Run() {
    new
        inherited[] = "/c5 hello",
        last[] = "/c999 hello",
        denied[] = "/c15 hello",
        unknown[] = "/nothing hello",
        member
    ;

    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            Command_ReProcess(gAdminBot, inherited, false, false);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("command", "allowed through 2 parent groups, 1000 commands");
    Bench_Check("allowed commands ran", gHits, gBenchOps);

    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            Command_ReProcess(gPlainBot, last, false, false);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("command", "free, the last of 1000 commands");
    Bench_Check("free commands ran", gHits, gBenchOps);

    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            CallLocalFunction("OnPlayerCommandText", "is", gPlainBot, last);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("command", "typed by a player, the last of 1000 commands");
    Bench_Check("typed commands ran", gHits, gBenchOps);

    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            Command_ReProcess(gPlainBot, denied, false, false);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("command", "denied, 1000 commands");
    Bench_Check("denied commands ran", gHits, 0);

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            Command_ReProcess(gPlainBot, unknown, false, false);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("command", "unknown, 1000 commands");

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            Group_SetPlayer(gHelper, gPlainBot, true);
            Group_SetPlayer(gHelper, gPlainBot, false);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("group", "join and leave a group");

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            Group_SetPlayer(gChain[15], gPlainBot, true);
            Group_SetPlayer(gChain[15], gPlainBot, false);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("group", "join and leave the end of a chain of 16 groups");

    member = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            if (Group_GetPlayer(gHelper, gAdminBot)) {
                ++member;
            }
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("group", "member through 2 parent groups");
    Bench_Check("members", member, gBenchOps);

    member = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            if (Group_GetPlayer(gChain[0], gChainBot)) {
                ++member;
            }
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("group", "member through 15 parent groups");
    Bench_Check("chain members", member, gBenchOps);
}

YCMD:c0(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c1(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c2(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c3(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c4(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c5(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c6(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c7(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c8(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c9(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c10(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c11(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c12(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c13(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c14(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c15(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c16(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c17(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c18(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c19(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c20(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c21(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c22(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c23(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c24(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c25(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c26(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c27(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c28(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c29(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c30(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c31(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c32(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c33(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c34(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c35(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c36(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c37(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c38(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c39(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c40(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c41(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c42(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c43(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c44(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c45(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c46(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c47(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c48(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c49(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c50(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c51(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c52(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c53(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c54(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c55(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c56(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c57(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c58(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c59(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c60(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c61(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c62(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c63(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c64(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c65(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c66(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c67(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c68(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c69(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c70(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c71(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c72(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c73(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c74(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c75(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c76(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c77(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c78(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c79(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c80(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c81(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c82(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c83(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c84(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c85(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c86(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c87(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c88(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c89(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c90(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c91(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c92(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c93(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c94(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c95(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c96(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c97(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c98(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c99(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c100(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c101(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c102(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c103(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c104(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c105(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c106(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c107(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c108(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c109(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c110(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c111(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c112(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c113(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c114(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c115(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c116(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c117(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c118(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c119(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c120(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c121(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c122(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c123(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c124(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c125(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c126(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c127(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c128(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c129(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c130(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c131(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c132(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c133(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c134(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c135(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c136(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c137(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c138(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c139(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c140(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c141(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c142(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c143(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c144(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c145(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c146(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c147(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c148(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c149(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c150(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c151(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c152(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c153(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c154(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c155(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c156(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c157(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c158(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c159(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c160(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c161(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c162(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c163(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c164(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c165(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c166(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c167(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c168(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c169(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c170(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c171(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c172(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c173(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c174(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c175(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c176(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c177(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c178(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c179(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c180(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c181(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c182(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c183(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c184(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c185(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c186(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c187(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c188(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c189(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c190(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c191(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c192(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c193(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c194(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c195(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c196(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c197(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c198(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c199(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c200(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c201(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c202(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c203(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c204(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c205(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c206(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c207(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c208(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c209(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c210(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c211(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c212(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c213(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c214(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c215(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c216(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c217(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c218(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c219(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c220(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c221(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c222(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c223(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c224(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c225(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c226(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c227(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c228(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c229(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c230(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c231(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c232(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c233(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c234(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c235(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c236(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c237(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c238(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c239(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c240(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c241(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c242(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c243(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c244(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c245(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c246(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c247(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c248(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c249(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c250(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c251(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c252(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c253(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c254(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c255(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c256(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c257(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c258(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c259(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c260(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c261(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c262(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c263(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c264(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c265(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c266(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c267(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c268(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c269(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c270(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c271(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c272(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c273(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c274(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c275(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c276(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c277(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c278(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c279(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c280(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c281(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c282(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c283(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c284(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c285(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c286(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c287(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c288(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c289(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c290(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c291(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c292(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c293(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c294(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c295(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c296(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c297(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c298(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c299(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c300(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c301(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c302(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c303(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c304(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c305(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c306(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c307(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c308(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c309(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c310(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c311(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c312(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c313(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c314(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c315(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c316(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c317(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c318(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c319(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c320(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c321(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c322(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c323(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c324(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c325(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c326(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c327(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c328(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c329(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c330(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c331(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c332(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c333(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c334(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c335(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c336(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c337(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c338(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c339(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c340(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c341(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c342(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c343(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c344(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c345(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c346(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c347(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c348(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c349(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c350(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c351(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c352(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c353(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c354(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c355(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c356(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c357(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c358(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c359(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c360(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c361(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c362(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c363(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c364(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c365(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c366(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c367(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c368(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c369(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c370(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c371(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c372(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c373(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c374(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c375(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c376(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c377(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c378(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c379(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c380(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c381(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c382(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c383(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c384(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c385(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c386(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c387(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c388(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c389(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c390(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c391(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c392(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c393(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c394(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c395(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c396(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c397(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c398(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c399(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c400(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c401(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c402(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c403(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c404(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c405(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c406(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c407(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c408(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c409(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c410(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c411(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c412(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c413(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c414(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c415(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c416(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c417(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c418(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c419(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c420(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c421(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c422(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c423(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c424(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c425(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c426(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c427(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c428(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c429(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c430(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c431(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c432(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c433(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c434(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c435(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c436(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c437(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c438(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c439(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c440(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c441(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c442(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c443(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c444(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c445(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c446(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c447(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c448(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c449(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c450(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c451(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c452(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c453(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c454(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c455(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c456(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c457(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c458(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c459(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c460(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c461(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c462(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c463(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c464(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c465(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c466(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c467(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c468(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c469(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c470(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c471(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c472(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c473(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c474(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c475(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c476(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c477(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c478(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c479(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c480(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c481(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c482(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c483(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c484(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c485(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c486(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c487(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c488(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c489(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c490(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c491(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c492(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c493(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c494(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c495(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c496(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c497(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c498(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c499(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c500(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c501(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c502(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c503(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c504(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c505(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c506(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c507(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c508(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c509(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c510(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c511(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c512(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c513(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c514(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c515(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c516(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c517(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c518(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c519(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c520(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c521(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c522(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c523(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c524(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c525(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c526(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c527(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c528(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c529(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c530(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c531(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c532(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c533(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c534(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c535(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c536(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c537(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c538(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c539(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c540(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c541(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c542(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c543(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c544(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c545(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c546(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c547(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c548(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c549(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c550(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c551(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c552(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c553(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c554(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c555(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c556(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c557(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c558(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c559(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c560(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c561(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c562(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c563(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c564(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c565(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c566(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c567(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c568(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c569(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c570(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c571(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c572(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c573(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c574(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c575(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c576(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c577(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c578(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c579(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c580(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c581(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c582(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c583(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c584(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c585(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c586(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c587(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c588(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c589(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c590(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c591(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c592(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c593(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c594(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c595(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c596(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c597(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c598(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c599(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c600(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c601(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c602(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c603(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c604(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c605(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c606(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c607(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c608(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c609(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c610(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c611(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c612(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c613(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c614(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c615(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c616(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c617(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c618(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c619(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c620(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c621(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c622(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c623(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c624(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c625(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c626(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c627(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c628(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c629(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c630(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c631(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c632(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c633(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c634(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c635(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c636(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c637(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c638(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c639(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c640(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c641(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c642(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c643(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c644(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c645(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c646(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c647(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c648(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c649(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c650(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c651(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c652(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c653(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c654(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c655(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c656(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c657(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c658(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c659(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c660(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c661(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c662(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c663(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c664(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c665(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c666(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c667(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c668(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c669(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c670(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c671(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c672(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c673(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c674(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c675(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c676(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c677(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c678(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c679(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c680(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c681(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c682(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c683(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c684(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c685(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c686(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c687(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c688(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c689(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c690(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c691(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c692(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c693(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c694(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c695(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c696(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c697(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c698(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c699(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c700(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c701(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c702(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c703(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c704(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c705(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c706(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c707(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c708(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c709(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c710(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c711(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c712(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c713(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c714(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c715(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c716(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c717(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c718(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c719(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c720(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c721(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c722(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c723(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c724(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c725(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c726(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c727(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c728(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c729(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c730(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c731(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c732(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c733(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c734(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c735(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c736(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c737(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c738(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c739(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c740(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c741(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c742(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c743(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c744(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c745(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c746(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c747(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c748(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c749(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c750(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c751(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c752(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c753(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c754(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c755(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c756(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c757(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c758(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c759(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c760(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c761(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c762(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c763(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c764(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c765(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c766(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c767(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c768(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c769(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c770(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c771(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c772(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c773(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c774(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c775(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c776(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c777(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c778(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c779(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c780(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c781(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c782(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c783(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c784(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c785(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c786(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c787(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c788(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c789(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c790(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c791(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c792(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c793(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c794(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c795(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c796(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c797(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c798(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c799(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c800(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c801(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c802(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c803(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c804(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c805(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c806(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c807(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c808(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c809(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c810(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c811(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c812(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c813(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c814(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c815(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c816(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c817(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c818(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c819(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c820(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c821(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c822(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c823(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c824(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c825(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c826(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c827(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c828(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c829(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c830(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c831(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c832(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c833(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c834(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c835(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c836(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c837(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c838(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c839(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c840(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c841(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c842(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c843(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c844(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c845(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c846(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c847(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c848(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c849(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c850(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c851(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c852(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c853(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c854(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c855(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c856(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c857(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c858(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c859(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c860(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c861(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c862(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c863(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c864(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c865(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c866(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c867(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c868(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c869(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c870(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c871(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c872(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c873(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c874(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c875(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c876(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c877(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c878(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c879(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c880(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c881(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c882(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c883(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c884(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c885(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c886(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c887(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c888(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c889(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c890(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c891(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c892(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c893(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c894(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c895(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c896(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c897(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c898(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c899(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c900(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c901(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c902(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c903(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c904(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c905(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c906(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c907(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c908(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c909(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c910(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c911(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c912(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c913(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c914(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c915(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c916(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c917(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c918(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c919(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c920(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c921(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c922(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c923(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c924(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c925(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c926(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c927(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c928(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c929(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c930(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c931(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c932(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c933(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c934(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c935(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c936(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c937(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c938(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c939(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c940(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c941(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c942(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c943(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c944(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c945(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c946(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c947(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c948(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c949(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c950(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c951(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c952(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c953(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c954(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c955(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c956(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c957(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c958(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c959(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c960(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c961(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c962(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c963(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c964(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c965(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c966(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c967(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c968(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c969(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c970(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c971(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c972(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c973(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c974(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c975(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c976(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c977(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c978(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c979(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c980(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c981(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c982(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c983(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c984(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c985(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c986(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c987(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c988(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c989(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c990(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c991(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c992(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c993(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c994(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c995(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c996(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c997(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c998(playerid, params[], help) {
    ++gHits;

    return 1;
}

YCMD:c999(playerid, params[], help) {
    ++gHits;

    return 1;
}

Setup() {
    gHelper = Group_Create("Helper");
    gModerator = Group_Create("Moderator");
    gAdmin = Group_Create("Administrator");
    Group_AddChild(gAdmin, gModerator);
    Group_AddChild(gModerator, gHelper);

    for (new i; i != sizeof (gChain); ++i) {
        new
            name[16]
        ;

        format(name, sizeof (name), "Chain%i", i);
        gChain[i] = Group_Create(name);

        if (i != 0) {
            Group_AddChild(gChain[i], gChain[i - 1]);
        }
    }

    Group_SetGlobalCommand(YCMD:c0, UNDEF);
    Group_SetCommand(gHelper, YCMD:c0, ALLOW);
    Group_SetGlobalCommand(YCMD:c1, UNDEF);
    Group_SetCommand(gHelper, YCMD:c1, ALLOW);
    Group_SetGlobalCommand(YCMD:c2, UNDEF);
    Group_SetCommand(gHelper, YCMD:c2, ALLOW);
    Group_SetGlobalCommand(YCMD:c3, UNDEF);
    Group_SetCommand(gHelper, YCMD:c3, ALLOW);
    Group_SetGlobalCommand(YCMD:c4, UNDEF);
    Group_SetCommand(gHelper, YCMD:c4, ALLOW);
    Group_SetGlobalCommand(YCMD:c5, UNDEF);
    Group_SetCommand(gHelper, YCMD:c5, ALLOW);
    Group_SetGlobalCommand(YCMD:c6, UNDEF);
    Group_SetCommand(gHelper, YCMD:c6, ALLOW);
    Group_SetGlobalCommand(YCMD:c7, UNDEF);
    Group_SetCommand(gHelper, YCMD:c7, ALLOW);
    Group_SetGlobalCommand(YCMD:c8, UNDEF);
    Group_SetCommand(gHelper, YCMD:c8, ALLOW);
    Group_SetGlobalCommand(YCMD:c9, UNDEF);
    Group_SetCommand(gHelper, YCMD:c9, ALLOW);
    Group_SetGlobalCommand(YCMD:c10, UNDEF);
    Group_SetCommand(gModerator, YCMD:c10, ALLOW);
    Group_SetGlobalCommand(YCMD:c11, UNDEF);
    Group_SetCommand(gModerator, YCMD:c11, ALLOW);
    Group_SetGlobalCommand(YCMD:c12, UNDEF);
    Group_SetCommand(gModerator, YCMD:c12, ALLOW);
    Group_SetGlobalCommand(YCMD:c13, UNDEF);
    Group_SetCommand(gModerator, YCMD:c13, ALLOW);
    Group_SetGlobalCommand(YCMD:c14, UNDEF);
    Group_SetCommand(gModerator, YCMD:c14, ALLOW);
    Group_SetGlobalCommand(YCMD:c15, UNDEF);
    Group_SetCommand(gModerator, YCMD:c15, ALLOW);
    Group_SetGlobalCommand(YCMD:c16, UNDEF);
    Group_SetCommand(gModerator, YCMD:c16, ALLOW);
    Group_SetGlobalCommand(YCMD:c17, UNDEF);
    Group_SetCommand(gModerator, YCMD:c17, ALLOW);
    Group_SetGlobalCommand(YCMD:c18, UNDEF);
    Group_SetCommand(gModerator, YCMD:c18, ALLOW);
    Group_SetGlobalCommand(YCMD:c19, UNDEF);
    Group_SetCommand(gModerator, YCMD:c19, ALLOW);
    Group_SetGlobalCommand(YCMD:c20, UNDEF);
    Group_SetCommand(gAdmin, YCMD:c20, ALLOW);
    Group_SetGlobalCommand(YCMD:c21, UNDEF);
    Group_SetCommand(gAdmin, YCMD:c21, ALLOW);
    Group_SetGlobalCommand(YCMD:c22, UNDEF);
    Group_SetCommand(gAdmin, YCMD:c22, ALLOW);
    Group_SetGlobalCommand(YCMD:c23, UNDEF);
    Group_SetCommand(gAdmin, YCMD:c23, ALLOW);
    Group_SetGlobalCommand(YCMD:c24, UNDEF);
    Group_SetCommand(gAdmin, YCMD:c24, ALLOW);
    Group_SetGlobalCommand(YCMD:c25, UNDEF);
    Group_SetCommand(gAdmin, YCMD:c25, ALLOW);
    Group_SetGlobalCommand(YCMD:c26, UNDEF);
    Group_SetCommand(gAdmin, YCMD:c26, ALLOW);
    Group_SetGlobalCommand(YCMD:c27, UNDEF);
    Group_SetCommand(gAdmin, YCMD:c27, ALLOW);
    Group_SetGlobalCommand(YCMD:c28, UNDEF);
    Group_SetCommand(gAdmin, YCMD:c28, ALLOW);
    Group_SetGlobalCommand(YCMD:c29, UNDEF);
    Group_SetCommand(gAdmin, YCMD:c29, ALLOW);
    Group_SetGlobalCommand(YCMD:c30, ALLOW);
    Group_SetGlobalCommand(YCMD:c31, ALLOW);
    Group_SetGlobalCommand(YCMD:c32, ALLOW);
    Group_SetGlobalCommand(YCMD:c33, ALLOW);
    Group_SetGlobalCommand(YCMD:c34, ALLOW);
    Group_SetGlobalCommand(YCMD:c35, ALLOW);
    Group_SetGlobalCommand(YCMD:c36, ALLOW);
    Group_SetGlobalCommand(YCMD:c37, ALLOW);
    Group_SetGlobalCommand(YCMD:c38, ALLOW);
    Group_SetGlobalCommand(YCMD:c39, ALLOW);
    Group_SetGlobalCommand(YCMD:c40, ALLOW);
    Group_SetGlobalCommand(YCMD:c41, ALLOW);
    Group_SetGlobalCommand(YCMD:c42, ALLOW);
    Group_SetGlobalCommand(YCMD:c43, ALLOW);
    Group_SetGlobalCommand(YCMD:c44, ALLOW);
    Group_SetGlobalCommand(YCMD:c45, ALLOW);
    Group_SetGlobalCommand(YCMD:c46, ALLOW);
    Group_SetGlobalCommand(YCMD:c47, ALLOW);
    Group_SetGlobalCommand(YCMD:c48, ALLOW);
    Group_SetGlobalCommand(YCMD:c49, ALLOW);
    Group_SetGlobalCommand(YCMD:c50, ALLOW);
    Group_SetGlobalCommand(YCMD:c51, ALLOW);
    Group_SetGlobalCommand(YCMD:c52, ALLOW);
    Group_SetGlobalCommand(YCMD:c53, ALLOW);
    Group_SetGlobalCommand(YCMD:c54, ALLOW);
    Group_SetGlobalCommand(YCMD:c55, ALLOW);
    Group_SetGlobalCommand(YCMD:c56, ALLOW);
    Group_SetGlobalCommand(YCMD:c57, ALLOW);
    Group_SetGlobalCommand(YCMD:c58, ALLOW);
    Group_SetGlobalCommand(YCMD:c59, ALLOW);
    Group_SetGlobalCommand(YCMD:c60, ALLOW);
    Group_SetGlobalCommand(YCMD:c61, ALLOW);
    Group_SetGlobalCommand(YCMD:c62, ALLOW);
    Group_SetGlobalCommand(YCMD:c63, ALLOW);
    Group_SetGlobalCommand(YCMD:c64, ALLOW);
    Group_SetGlobalCommand(YCMD:c65, ALLOW);
    Group_SetGlobalCommand(YCMD:c66, ALLOW);
    Group_SetGlobalCommand(YCMD:c67, ALLOW);
    Group_SetGlobalCommand(YCMD:c68, ALLOW);
    Group_SetGlobalCommand(YCMD:c69, ALLOW);
    Group_SetGlobalCommand(YCMD:c70, ALLOW);
    Group_SetGlobalCommand(YCMD:c71, ALLOW);
    Group_SetGlobalCommand(YCMD:c72, ALLOW);
    Group_SetGlobalCommand(YCMD:c73, ALLOW);
    Group_SetGlobalCommand(YCMD:c74, ALLOW);
    Group_SetGlobalCommand(YCMD:c75, ALLOW);
    Group_SetGlobalCommand(YCMD:c76, ALLOW);
    Group_SetGlobalCommand(YCMD:c77, ALLOW);
    Group_SetGlobalCommand(YCMD:c78, ALLOW);
    Group_SetGlobalCommand(YCMD:c79, ALLOW);
    Group_SetGlobalCommand(YCMD:c80, ALLOW);
    Group_SetGlobalCommand(YCMD:c81, ALLOW);
    Group_SetGlobalCommand(YCMD:c82, ALLOW);
    Group_SetGlobalCommand(YCMD:c83, ALLOW);
    Group_SetGlobalCommand(YCMD:c84, ALLOW);
    Group_SetGlobalCommand(YCMD:c85, ALLOW);
    Group_SetGlobalCommand(YCMD:c86, ALLOW);
    Group_SetGlobalCommand(YCMD:c87, ALLOW);
    Group_SetGlobalCommand(YCMD:c88, ALLOW);
    Group_SetGlobalCommand(YCMD:c89, ALLOW);
    Group_SetGlobalCommand(YCMD:c90, ALLOW);
    Group_SetGlobalCommand(YCMD:c91, ALLOW);
    Group_SetGlobalCommand(YCMD:c92, ALLOW);
    Group_SetGlobalCommand(YCMD:c93, ALLOW);
    Group_SetGlobalCommand(YCMD:c94, ALLOW);
    Group_SetGlobalCommand(YCMD:c95, ALLOW);
    Group_SetGlobalCommand(YCMD:c96, ALLOW);
    Group_SetGlobalCommand(YCMD:c97, ALLOW);
    Group_SetGlobalCommand(YCMD:c98, ALLOW);
    Group_SetGlobalCommand(YCMD:c99, ALLOW);
    Group_SetGlobalCommand(YCMD:c100, ALLOW);
    Group_SetGlobalCommand(YCMD:c101, ALLOW);
    Group_SetGlobalCommand(YCMD:c102, ALLOW);
    Group_SetGlobalCommand(YCMD:c103, ALLOW);
    Group_SetGlobalCommand(YCMD:c104, ALLOW);
    Group_SetGlobalCommand(YCMD:c105, ALLOW);
    Group_SetGlobalCommand(YCMD:c106, ALLOW);
    Group_SetGlobalCommand(YCMD:c107, ALLOW);
    Group_SetGlobalCommand(YCMD:c108, ALLOW);
    Group_SetGlobalCommand(YCMD:c109, ALLOW);
    Group_SetGlobalCommand(YCMD:c110, ALLOW);
    Group_SetGlobalCommand(YCMD:c111, ALLOW);
    Group_SetGlobalCommand(YCMD:c112, ALLOW);
    Group_SetGlobalCommand(YCMD:c113, ALLOW);
    Group_SetGlobalCommand(YCMD:c114, ALLOW);
    Group_SetGlobalCommand(YCMD:c115, ALLOW);
    Group_SetGlobalCommand(YCMD:c116, ALLOW);
    Group_SetGlobalCommand(YCMD:c117, ALLOW);
    Group_SetGlobalCommand(YCMD:c118, ALLOW);
    Group_SetGlobalCommand(YCMD:c119, ALLOW);
    Group_SetGlobalCommand(YCMD:c120, ALLOW);
    Group_SetGlobalCommand(YCMD:c121, ALLOW);
    Group_SetGlobalCommand(YCMD:c122, ALLOW);
    Group_SetGlobalCommand(YCMD:c123, ALLOW);
    Group_SetGlobalCommand(YCMD:c124, ALLOW);
    Group_SetGlobalCommand(YCMD:c125, ALLOW);
    Group_SetGlobalCommand(YCMD:c126, ALLOW);
    Group_SetGlobalCommand(YCMD:c127, ALLOW);
    Group_SetGlobalCommand(YCMD:c128, ALLOW);
    Group_SetGlobalCommand(YCMD:c129, ALLOW);
    Group_SetGlobalCommand(YCMD:c130, ALLOW);
    Group_SetGlobalCommand(YCMD:c131, ALLOW);
    Group_SetGlobalCommand(YCMD:c132, ALLOW);
    Group_SetGlobalCommand(YCMD:c133, ALLOW);
    Group_SetGlobalCommand(YCMD:c134, ALLOW);
    Group_SetGlobalCommand(YCMD:c135, ALLOW);
    Group_SetGlobalCommand(YCMD:c136, ALLOW);
    Group_SetGlobalCommand(YCMD:c137, ALLOW);
    Group_SetGlobalCommand(YCMD:c138, ALLOW);
    Group_SetGlobalCommand(YCMD:c139, ALLOW);
    Group_SetGlobalCommand(YCMD:c140, ALLOW);
    Group_SetGlobalCommand(YCMD:c141, ALLOW);
    Group_SetGlobalCommand(YCMD:c142, ALLOW);
    Group_SetGlobalCommand(YCMD:c143, ALLOW);
    Group_SetGlobalCommand(YCMD:c144, ALLOW);
    Group_SetGlobalCommand(YCMD:c145, ALLOW);
    Group_SetGlobalCommand(YCMD:c146, ALLOW);
    Group_SetGlobalCommand(YCMD:c147, ALLOW);
    Group_SetGlobalCommand(YCMD:c148, ALLOW);
    Group_SetGlobalCommand(YCMD:c149, ALLOW);
    Group_SetGlobalCommand(YCMD:c150, ALLOW);
    Group_SetGlobalCommand(YCMD:c151, ALLOW);
    Group_SetGlobalCommand(YCMD:c152, ALLOW);
    Group_SetGlobalCommand(YCMD:c153, ALLOW);
    Group_SetGlobalCommand(YCMD:c154, ALLOW);
    Group_SetGlobalCommand(YCMD:c155, ALLOW);
    Group_SetGlobalCommand(YCMD:c156, ALLOW);
    Group_SetGlobalCommand(YCMD:c157, ALLOW);
    Group_SetGlobalCommand(YCMD:c158, ALLOW);
    Group_SetGlobalCommand(YCMD:c159, ALLOW);
    Group_SetGlobalCommand(YCMD:c160, ALLOW);
    Group_SetGlobalCommand(YCMD:c161, ALLOW);
    Group_SetGlobalCommand(YCMD:c162, ALLOW);
    Group_SetGlobalCommand(YCMD:c163, ALLOW);
    Group_SetGlobalCommand(YCMD:c164, ALLOW);
    Group_SetGlobalCommand(YCMD:c165, ALLOW);
    Group_SetGlobalCommand(YCMD:c166, ALLOW);
    Group_SetGlobalCommand(YCMD:c167, ALLOW);
    Group_SetGlobalCommand(YCMD:c168, ALLOW);
    Group_SetGlobalCommand(YCMD:c169, ALLOW);
    Group_SetGlobalCommand(YCMD:c170, ALLOW);
    Group_SetGlobalCommand(YCMD:c171, ALLOW);
    Group_SetGlobalCommand(YCMD:c172, ALLOW);
    Group_SetGlobalCommand(YCMD:c173, ALLOW);
    Group_SetGlobalCommand(YCMD:c174, ALLOW);
    Group_SetGlobalCommand(YCMD:c175, ALLOW);
    Group_SetGlobalCommand(YCMD:c176, ALLOW);
    Group_SetGlobalCommand(YCMD:c177, ALLOW);
    Group_SetGlobalCommand(YCMD:c178, ALLOW);
    Group_SetGlobalCommand(YCMD:c179, ALLOW);
    Group_SetGlobalCommand(YCMD:c180, ALLOW);
    Group_SetGlobalCommand(YCMD:c181, ALLOW);
    Group_SetGlobalCommand(YCMD:c182, ALLOW);
    Group_SetGlobalCommand(YCMD:c183, ALLOW);
    Group_SetGlobalCommand(YCMD:c184, ALLOW);
    Group_SetGlobalCommand(YCMD:c185, ALLOW);
    Group_SetGlobalCommand(YCMD:c186, ALLOW);
    Group_SetGlobalCommand(YCMD:c187, ALLOW);
    Group_SetGlobalCommand(YCMD:c188, ALLOW);
    Group_SetGlobalCommand(YCMD:c189, ALLOW);
    Group_SetGlobalCommand(YCMD:c190, ALLOW);
    Group_SetGlobalCommand(YCMD:c191, ALLOW);
    Group_SetGlobalCommand(YCMD:c192, ALLOW);
    Group_SetGlobalCommand(YCMD:c193, ALLOW);
    Group_SetGlobalCommand(YCMD:c194, ALLOW);
    Group_SetGlobalCommand(YCMD:c195, ALLOW);
    Group_SetGlobalCommand(YCMD:c196, ALLOW);
    Group_SetGlobalCommand(YCMD:c197, ALLOW);
    Group_SetGlobalCommand(YCMD:c198, ALLOW);
    Group_SetGlobalCommand(YCMD:c199, ALLOW);
    Group_SetGlobalCommand(YCMD:c200, ALLOW);
    Group_SetGlobalCommand(YCMD:c201, ALLOW);
    Group_SetGlobalCommand(YCMD:c202, ALLOW);
    Group_SetGlobalCommand(YCMD:c203, ALLOW);
    Group_SetGlobalCommand(YCMD:c204, ALLOW);
    Group_SetGlobalCommand(YCMD:c205, ALLOW);
    Group_SetGlobalCommand(YCMD:c206, ALLOW);
    Group_SetGlobalCommand(YCMD:c207, ALLOW);
    Group_SetGlobalCommand(YCMD:c208, ALLOW);
    Group_SetGlobalCommand(YCMD:c209, ALLOW);
    Group_SetGlobalCommand(YCMD:c210, ALLOW);
    Group_SetGlobalCommand(YCMD:c211, ALLOW);
    Group_SetGlobalCommand(YCMD:c212, ALLOW);
    Group_SetGlobalCommand(YCMD:c213, ALLOW);
    Group_SetGlobalCommand(YCMD:c214, ALLOW);
    Group_SetGlobalCommand(YCMD:c215, ALLOW);
    Group_SetGlobalCommand(YCMD:c216, ALLOW);
    Group_SetGlobalCommand(YCMD:c217, ALLOW);
    Group_SetGlobalCommand(YCMD:c218, ALLOW);
    Group_SetGlobalCommand(YCMD:c219, ALLOW);
    Group_SetGlobalCommand(YCMD:c220, ALLOW);
    Group_SetGlobalCommand(YCMD:c221, ALLOW);
    Group_SetGlobalCommand(YCMD:c222, ALLOW);
    Group_SetGlobalCommand(YCMD:c223, ALLOW);
    Group_SetGlobalCommand(YCMD:c224, ALLOW);
    Group_SetGlobalCommand(YCMD:c225, ALLOW);
    Group_SetGlobalCommand(YCMD:c226, ALLOW);
    Group_SetGlobalCommand(YCMD:c227, ALLOW);
    Group_SetGlobalCommand(YCMD:c228, ALLOW);
    Group_SetGlobalCommand(YCMD:c229, ALLOW);
    Group_SetGlobalCommand(YCMD:c230, ALLOW);
    Group_SetGlobalCommand(YCMD:c231, ALLOW);
    Group_SetGlobalCommand(YCMD:c232, ALLOW);
    Group_SetGlobalCommand(YCMD:c233, ALLOW);
    Group_SetGlobalCommand(YCMD:c234, ALLOW);
    Group_SetGlobalCommand(YCMD:c235, ALLOW);
    Group_SetGlobalCommand(YCMD:c236, ALLOW);
    Group_SetGlobalCommand(YCMD:c237, ALLOW);
    Group_SetGlobalCommand(YCMD:c238, ALLOW);
    Group_SetGlobalCommand(YCMD:c239, ALLOW);
    Group_SetGlobalCommand(YCMD:c240, ALLOW);
    Group_SetGlobalCommand(YCMD:c241, ALLOW);
    Group_SetGlobalCommand(YCMD:c242, ALLOW);
    Group_SetGlobalCommand(YCMD:c243, ALLOW);
    Group_SetGlobalCommand(YCMD:c244, ALLOW);
    Group_SetGlobalCommand(YCMD:c245, ALLOW);
    Group_SetGlobalCommand(YCMD:c246, ALLOW);
    Group_SetGlobalCommand(YCMD:c247, ALLOW);
    Group_SetGlobalCommand(YCMD:c248, ALLOW);
    Group_SetGlobalCommand(YCMD:c249, ALLOW);
    Group_SetGlobalCommand(YCMD:c250, ALLOW);
    Group_SetGlobalCommand(YCMD:c251, ALLOW);
    Group_SetGlobalCommand(YCMD:c252, ALLOW);
    Group_SetGlobalCommand(YCMD:c253, ALLOW);
    Group_SetGlobalCommand(YCMD:c254, ALLOW);
    Group_SetGlobalCommand(YCMD:c255, ALLOW);
    Group_SetGlobalCommand(YCMD:c256, ALLOW);
    Group_SetGlobalCommand(YCMD:c257, ALLOW);
    Group_SetGlobalCommand(YCMD:c258, ALLOW);
    Group_SetGlobalCommand(YCMD:c259, ALLOW);
    Group_SetGlobalCommand(YCMD:c260, ALLOW);
    Group_SetGlobalCommand(YCMD:c261, ALLOW);
    Group_SetGlobalCommand(YCMD:c262, ALLOW);
    Group_SetGlobalCommand(YCMD:c263, ALLOW);
    Group_SetGlobalCommand(YCMD:c264, ALLOW);
    Group_SetGlobalCommand(YCMD:c265, ALLOW);
    Group_SetGlobalCommand(YCMD:c266, ALLOW);
    Group_SetGlobalCommand(YCMD:c267, ALLOW);
    Group_SetGlobalCommand(YCMD:c268, ALLOW);
    Group_SetGlobalCommand(YCMD:c269, ALLOW);
    Group_SetGlobalCommand(YCMD:c270, ALLOW);
    Group_SetGlobalCommand(YCMD:c271, ALLOW);
    Group_SetGlobalCommand(YCMD:c272, ALLOW);
    Group_SetGlobalCommand(YCMD:c273, ALLOW);
    Group_SetGlobalCommand(YCMD:c274, ALLOW);
    Group_SetGlobalCommand(YCMD:c275, ALLOW);
    Group_SetGlobalCommand(YCMD:c276, ALLOW);
    Group_SetGlobalCommand(YCMD:c277, ALLOW);
    Group_SetGlobalCommand(YCMD:c278, ALLOW);
    Group_SetGlobalCommand(YCMD:c279, ALLOW);
    Group_SetGlobalCommand(YCMD:c280, ALLOW);
    Group_SetGlobalCommand(YCMD:c281, ALLOW);
    Group_SetGlobalCommand(YCMD:c282, ALLOW);
    Group_SetGlobalCommand(YCMD:c283, ALLOW);
    Group_SetGlobalCommand(YCMD:c284, ALLOW);
    Group_SetGlobalCommand(YCMD:c285, ALLOW);
    Group_SetGlobalCommand(YCMD:c286, ALLOW);
    Group_SetGlobalCommand(YCMD:c287, ALLOW);
    Group_SetGlobalCommand(YCMD:c288, ALLOW);
    Group_SetGlobalCommand(YCMD:c289, ALLOW);
    Group_SetGlobalCommand(YCMD:c290, ALLOW);
    Group_SetGlobalCommand(YCMD:c291, ALLOW);
    Group_SetGlobalCommand(YCMD:c292, ALLOW);
    Group_SetGlobalCommand(YCMD:c293, ALLOW);
    Group_SetGlobalCommand(YCMD:c294, ALLOW);
    Group_SetGlobalCommand(YCMD:c295, ALLOW);
    Group_SetGlobalCommand(YCMD:c296, ALLOW);
    Group_SetGlobalCommand(YCMD:c297, ALLOW);
    Group_SetGlobalCommand(YCMD:c298, ALLOW);
    Group_SetGlobalCommand(YCMD:c299, ALLOW);
    Group_SetGlobalCommand(YCMD:c300, ALLOW);
    Group_SetGlobalCommand(YCMD:c301, ALLOW);
    Group_SetGlobalCommand(YCMD:c302, ALLOW);
    Group_SetGlobalCommand(YCMD:c303, ALLOW);
    Group_SetGlobalCommand(YCMD:c304, ALLOW);
    Group_SetGlobalCommand(YCMD:c305, ALLOW);
    Group_SetGlobalCommand(YCMD:c306, ALLOW);
    Group_SetGlobalCommand(YCMD:c307, ALLOW);
    Group_SetGlobalCommand(YCMD:c308, ALLOW);
    Group_SetGlobalCommand(YCMD:c309, ALLOW);
    Group_SetGlobalCommand(YCMD:c310, ALLOW);
    Group_SetGlobalCommand(YCMD:c311, ALLOW);
    Group_SetGlobalCommand(YCMD:c312, ALLOW);
    Group_SetGlobalCommand(YCMD:c313, ALLOW);
    Group_SetGlobalCommand(YCMD:c314, ALLOW);
    Group_SetGlobalCommand(YCMD:c315, ALLOW);
    Group_SetGlobalCommand(YCMD:c316, ALLOW);
    Group_SetGlobalCommand(YCMD:c317, ALLOW);
    Group_SetGlobalCommand(YCMD:c318, ALLOW);
    Group_SetGlobalCommand(YCMD:c319, ALLOW);
    Group_SetGlobalCommand(YCMD:c320, ALLOW);
    Group_SetGlobalCommand(YCMD:c321, ALLOW);
    Group_SetGlobalCommand(YCMD:c322, ALLOW);
    Group_SetGlobalCommand(YCMD:c323, ALLOW);
    Group_SetGlobalCommand(YCMD:c324, ALLOW);
    Group_SetGlobalCommand(YCMD:c325, ALLOW);
    Group_SetGlobalCommand(YCMD:c326, ALLOW);
    Group_SetGlobalCommand(YCMD:c327, ALLOW);
    Group_SetGlobalCommand(YCMD:c328, ALLOW);
    Group_SetGlobalCommand(YCMD:c329, ALLOW);
    Group_SetGlobalCommand(YCMD:c330, ALLOW);
    Group_SetGlobalCommand(YCMD:c331, ALLOW);
    Group_SetGlobalCommand(YCMD:c332, ALLOW);
    Group_SetGlobalCommand(YCMD:c333, ALLOW);
    Group_SetGlobalCommand(YCMD:c334, ALLOW);
    Group_SetGlobalCommand(YCMD:c335, ALLOW);
    Group_SetGlobalCommand(YCMD:c336, ALLOW);
    Group_SetGlobalCommand(YCMD:c337, ALLOW);
    Group_SetGlobalCommand(YCMD:c338, ALLOW);
    Group_SetGlobalCommand(YCMD:c339, ALLOW);
    Group_SetGlobalCommand(YCMD:c340, ALLOW);
    Group_SetGlobalCommand(YCMD:c341, ALLOW);
    Group_SetGlobalCommand(YCMD:c342, ALLOW);
    Group_SetGlobalCommand(YCMD:c343, ALLOW);
    Group_SetGlobalCommand(YCMD:c344, ALLOW);
    Group_SetGlobalCommand(YCMD:c345, ALLOW);
    Group_SetGlobalCommand(YCMD:c346, ALLOW);
    Group_SetGlobalCommand(YCMD:c347, ALLOW);
    Group_SetGlobalCommand(YCMD:c348, ALLOW);
    Group_SetGlobalCommand(YCMD:c349, ALLOW);
    Group_SetGlobalCommand(YCMD:c350, ALLOW);
    Group_SetGlobalCommand(YCMD:c351, ALLOW);
    Group_SetGlobalCommand(YCMD:c352, ALLOW);
    Group_SetGlobalCommand(YCMD:c353, ALLOW);
    Group_SetGlobalCommand(YCMD:c354, ALLOW);
    Group_SetGlobalCommand(YCMD:c355, ALLOW);
    Group_SetGlobalCommand(YCMD:c356, ALLOW);
    Group_SetGlobalCommand(YCMD:c357, ALLOW);
    Group_SetGlobalCommand(YCMD:c358, ALLOW);
    Group_SetGlobalCommand(YCMD:c359, ALLOW);
    Group_SetGlobalCommand(YCMD:c360, ALLOW);
    Group_SetGlobalCommand(YCMD:c361, ALLOW);
    Group_SetGlobalCommand(YCMD:c362, ALLOW);
    Group_SetGlobalCommand(YCMD:c363, ALLOW);
    Group_SetGlobalCommand(YCMD:c364, ALLOW);
    Group_SetGlobalCommand(YCMD:c365, ALLOW);
    Group_SetGlobalCommand(YCMD:c366, ALLOW);
    Group_SetGlobalCommand(YCMD:c367, ALLOW);
    Group_SetGlobalCommand(YCMD:c368, ALLOW);
    Group_SetGlobalCommand(YCMD:c369, ALLOW);
    Group_SetGlobalCommand(YCMD:c370, ALLOW);
    Group_SetGlobalCommand(YCMD:c371, ALLOW);
    Group_SetGlobalCommand(YCMD:c372, ALLOW);
    Group_SetGlobalCommand(YCMD:c373, ALLOW);
    Group_SetGlobalCommand(YCMD:c374, ALLOW);
    Group_SetGlobalCommand(YCMD:c375, ALLOW);
    Group_SetGlobalCommand(YCMD:c376, ALLOW);
    Group_SetGlobalCommand(YCMD:c377, ALLOW);
    Group_SetGlobalCommand(YCMD:c378, ALLOW);
    Group_SetGlobalCommand(YCMD:c379, ALLOW);
    Group_SetGlobalCommand(YCMD:c380, ALLOW);
    Group_SetGlobalCommand(YCMD:c381, ALLOW);
    Group_SetGlobalCommand(YCMD:c382, ALLOW);
    Group_SetGlobalCommand(YCMD:c383, ALLOW);
    Group_SetGlobalCommand(YCMD:c384, ALLOW);
    Group_SetGlobalCommand(YCMD:c385, ALLOW);
    Group_SetGlobalCommand(YCMD:c386, ALLOW);
    Group_SetGlobalCommand(YCMD:c387, ALLOW);
    Group_SetGlobalCommand(YCMD:c388, ALLOW);
    Group_SetGlobalCommand(YCMD:c389, ALLOW);
    Group_SetGlobalCommand(YCMD:c390, ALLOW);
    Group_SetGlobalCommand(YCMD:c391, ALLOW);
    Group_SetGlobalCommand(YCMD:c392, ALLOW);
    Group_SetGlobalCommand(YCMD:c393, ALLOW);
    Group_SetGlobalCommand(YCMD:c394, ALLOW);
    Group_SetGlobalCommand(YCMD:c395, ALLOW);
    Group_SetGlobalCommand(YCMD:c396, ALLOW);
    Group_SetGlobalCommand(YCMD:c397, ALLOW);
    Group_SetGlobalCommand(YCMD:c398, ALLOW);
    Group_SetGlobalCommand(YCMD:c399, ALLOW);
    Group_SetGlobalCommand(YCMD:c400, ALLOW);
    Group_SetGlobalCommand(YCMD:c401, ALLOW);
    Group_SetGlobalCommand(YCMD:c402, ALLOW);
    Group_SetGlobalCommand(YCMD:c403, ALLOW);
    Group_SetGlobalCommand(YCMD:c404, ALLOW);
    Group_SetGlobalCommand(YCMD:c405, ALLOW);
    Group_SetGlobalCommand(YCMD:c406, ALLOW);
    Group_SetGlobalCommand(YCMD:c407, ALLOW);
    Group_SetGlobalCommand(YCMD:c408, ALLOW);
    Group_SetGlobalCommand(YCMD:c409, ALLOW);
    Group_SetGlobalCommand(YCMD:c410, ALLOW);
    Group_SetGlobalCommand(YCMD:c411, ALLOW);
    Group_SetGlobalCommand(YCMD:c412, ALLOW);
    Group_SetGlobalCommand(YCMD:c413, ALLOW);
    Group_SetGlobalCommand(YCMD:c414, ALLOW);
    Group_SetGlobalCommand(YCMD:c415, ALLOW);
    Group_SetGlobalCommand(YCMD:c416, ALLOW);
    Group_SetGlobalCommand(YCMD:c417, ALLOW);
    Group_SetGlobalCommand(YCMD:c418, ALLOW);
    Group_SetGlobalCommand(YCMD:c419, ALLOW);
    Group_SetGlobalCommand(YCMD:c420, ALLOW);
    Group_SetGlobalCommand(YCMD:c421, ALLOW);
    Group_SetGlobalCommand(YCMD:c422, ALLOW);
    Group_SetGlobalCommand(YCMD:c423, ALLOW);
    Group_SetGlobalCommand(YCMD:c424, ALLOW);
    Group_SetGlobalCommand(YCMD:c425, ALLOW);
    Group_SetGlobalCommand(YCMD:c426, ALLOW);
    Group_SetGlobalCommand(YCMD:c427, ALLOW);
    Group_SetGlobalCommand(YCMD:c428, ALLOW);
    Group_SetGlobalCommand(YCMD:c429, ALLOW);
    Group_SetGlobalCommand(YCMD:c430, ALLOW);
    Group_SetGlobalCommand(YCMD:c431, ALLOW);
    Group_SetGlobalCommand(YCMD:c432, ALLOW);
    Group_SetGlobalCommand(YCMD:c433, ALLOW);
    Group_SetGlobalCommand(YCMD:c434, ALLOW);
    Group_SetGlobalCommand(YCMD:c435, ALLOW);
    Group_SetGlobalCommand(YCMD:c436, ALLOW);
    Group_SetGlobalCommand(YCMD:c437, ALLOW);
    Group_SetGlobalCommand(YCMD:c438, ALLOW);
    Group_SetGlobalCommand(YCMD:c439, ALLOW);
    Group_SetGlobalCommand(YCMD:c440, ALLOW);
    Group_SetGlobalCommand(YCMD:c441, ALLOW);
    Group_SetGlobalCommand(YCMD:c442, ALLOW);
    Group_SetGlobalCommand(YCMD:c443, ALLOW);
    Group_SetGlobalCommand(YCMD:c444, ALLOW);
    Group_SetGlobalCommand(YCMD:c445, ALLOW);
    Group_SetGlobalCommand(YCMD:c446, ALLOW);
    Group_SetGlobalCommand(YCMD:c447, ALLOW);
    Group_SetGlobalCommand(YCMD:c448, ALLOW);
    Group_SetGlobalCommand(YCMD:c449, ALLOW);
    Group_SetGlobalCommand(YCMD:c450, ALLOW);
    Group_SetGlobalCommand(YCMD:c451, ALLOW);
    Group_SetGlobalCommand(YCMD:c452, ALLOW);
    Group_SetGlobalCommand(YCMD:c453, ALLOW);
    Group_SetGlobalCommand(YCMD:c454, ALLOW);
    Group_SetGlobalCommand(YCMD:c455, ALLOW);
    Group_SetGlobalCommand(YCMD:c456, ALLOW);
    Group_SetGlobalCommand(YCMD:c457, ALLOW);
    Group_SetGlobalCommand(YCMD:c458, ALLOW);
    Group_SetGlobalCommand(YCMD:c459, ALLOW);
    Group_SetGlobalCommand(YCMD:c460, ALLOW);
    Group_SetGlobalCommand(YCMD:c461, ALLOW);
    Group_SetGlobalCommand(YCMD:c462, ALLOW);
    Group_SetGlobalCommand(YCMD:c463, ALLOW);
    Group_SetGlobalCommand(YCMD:c464, ALLOW);
    Group_SetGlobalCommand(YCMD:c465, ALLOW);
    Group_SetGlobalCommand(YCMD:c466, ALLOW);
    Group_SetGlobalCommand(YCMD:c467, ALLOW);
    Group_SetGlobalCommand(YCMD:c468, ALLOW);
    Group_SetGlobalCommand(YCMD:c469, ALLOW);
    Group_SetGlobalCommand(YCMD:c470, ALLOW);
    Group_SetGlobalCommand(YCMD:c471, ALLOW);
    Group_SetGlobalCommand(YCMD:c472, ALLOW);
    Group_SetGlobalCommand(YCMD:c473, ALLOW);
    Group_SetGlobalCommand(YCMD:c474, ALLOW);
    Group_SetGlobalCommand(YCMD:c475, ALLOW);
    Group_SetGlobalCommand(YCMD:c476, ALLOW);
    Group_SetGlobalCommand(YCMD:c477, ALLOW);
    Group_SetGlobalCommand(YCMD:c478, ALLOW);
    Group_SetGlobalCommand(YCMD:c479, ALLOW);
    Group_SetGlobalCommand(YCMD:c480, ALLOW);
    Group_SetGlobalCommand(YCMD:c481, ALLOW);
    Group_SetGlobalCommand(YCMD:c482, ALLOW);
    Group_SetGlobalCommand(YCMD:c483, ALLOW);
    Group_SetGlobalCommand(YCMD:c484, ALLOW);
    Group_SetGlobalCommand(YCMD:c485, ALLOW);
    Group_SetGlobalCommand(YCMD:c486, ALLOW);
    Group_SetGlobalCommand(YCMD:c487, ALLOW);
    Group_SetGlobalCommand(YCMD:c488, ALLOW);
    Group_SetGlobalCommand(YCMD:c489, ALLOW);
    Group_SetGlobalCommand(YCMD:c490, ALLOW);
    Group_SetGlobalCommand(YCMD:c491, ALLOW);
    Group_SetGlobalCommand(YCMD:c492, ALLOW);
    Group_SetGlobalCommand(YCMD:c493, ALLOW);
    Group_SetGlobalCommand(YCMD:c494, ALLOW);
    Group_SetGlobalCommand(YCMD:c495, ALLOW);
    Group_SetGlobalCommand(YCMD:c496, ALLOW);
    Group_SetGlobalCommand(YCMD:c497, ALLOW);
    Group_SetGlobalCommand(YCMD:c498, ALLOW);
    Group_SetGlobalCommand(YCMD:c499, ALLOW);
    Group_SetGlobalCommand(YCMD:c500, ALLOW);
    Group_SetGlobalCommand(YCMD:c501, ALLOW);
    Group_SetGlobalCommand(YCMD:c502, ALLOW);
    Group_SetGlobalCommand(YCMD:c503, ALLOW);
    Group_SetGlobalCommand(YCMD:c504, ALLOW);
    Group_SetGlobalCommand(YCMD:c505, ALLOW);
    Group_SetGlobalCommand(YCMD:c506, ALLOW);
    Group_SetGlobalCommand(YCMD:c507, ALLOW);
    Group_SetGlobalCommand(YCMD:c508, ALLOW);
    Group_SetGlobalCommand(YCMD:c509, ALLOW);
    Group_SetGlobalCommand(YCMD:c510, ALLOW);
    Group_SetGlobalCommand(YCMD:c511, ALLOW);
    Group_SetGlobalCommand(YCMD:c512, ALLOW);
    Group_SetGlobalCommand(YCMD:c513, ALLOW);
    Group_SetGlobalCommand(YCMD:c514, ALLOW);
    Group_SetGlobalCommand(YCMD:c515, ALLOW);
    Group_SetGlobalCommand(YCMD:c516, ALLOW);
    Group_SetGlobalCommand(YCMD:c517, ALLOW);
    Group_SetGlobalCommand(YCMD:c518, ALLOW);
    Group_SetGlobalCommand(YCMD:c519, ALLOW);
    Group_SetGlobalCommand(YCMD:c520, ALLOW);
    Group_SetGlobalCommand(YCMD:c521, ALLOW);
    Group_SetGlobalCommand(YCMD:c522, ALLOW);
    Group_SetGlobalCommand(YCMD:c523, ALLOW);
    Group_SetGlobalCommand(YCMD:c524, ALLOW);
    Group_SetGlobalCommand(YCMD:c525, ALLOW);
    Group_SetGlobalCommand(YCMD:c526, ALLOW);
    Group_SetGlobalCommand(YCMD:c527, ALLOW);
    Group_SetGlobalCommand(YCMD:c528, ALLOW);
    Group_SetGlobalCommand(YCMD:c529, ALLOW);
    Group_SetGlobalCommand(YCMD:c530, ALLOW);
    Group_SetGlobalCommand(YCMD:c531, ALLOW);
    Group_SetGlobalCommand(YCMD:c532, ALLOW);
    Group_SetGlobalCommand(YCMD:c533, ALLOW);
    Group_SetGlobalCommand(YCMD:c534, ALLOW);
    Group_SetGlobalCommand(YCMD:c535, ALLOW);
    Group_SetGlobalCommand(YCMD:c536, ALLOW);
    Group_SetGlobalCommand(YCMD:c537, ALLOW);
    Group_SetGlobalCommand(YCMD:c538, ALLOW);
    Group_SetGlobalCommand(YCMD:c539, ALLOW);
    Group_SetGlobalCommand(YCMD:c540, ALLOW);
    Group_SetGlobalCommand(YCMD:c541, ALLOW);
    Group_SetGlobalCommand(YCMD:c542, ALLOW);
    Group_SetGlobalCommand(YCMD:c543, ALLOW);
    Group_SetGlobalCommand(YCMD:c544, ALLOW);
    Group_SetGlobalCommand(YCMD:c545, ALLOW);
    Group_SetGlobalCommand(YCMD:c546, ALLOW);
    Group_SetGlobalCommand(YCMD:c547, ALLOW);
    Group_SetGlobalCommand(YCMD:c548, ALLOW);
    Group_SetGlobalCommand(YCMD:c549, ALLOW);
    Group_SetGlobalCommand(YCMD:c550, ALLOW);
    Group_SetGlobalCommand(YCMD:c551, ALLOW);
    Group_SetGlobalCommand(YCMD:c552, ALLOW);
    Group_SetGlobalCommand(YCMD:c553, ALLOW);
    Group_SetGlobalCommand(YCMD:c554, ALLOW);
    Group_SetGlobalCommand(YCMD:c555, ALLOW);
    Group_SetGlobalCommand(YCMD:c556, ALLOW);
    Group_SetGlobalCommand(YCMD:c557, ALLOW);
    Group_SetGlobalCommand(YCMD:c558, ALLOW);
    Group_SetGlobalCommand(YCMD:c559, ALLOW);
    Group_SetGlobalCommand(YCMD:c560, ALLOW);
    Group_SetGlobalCommand(YCMD:c561, ALLOW);
    Group_SetGlobalCommand(YCMD:c562, ALLOW);
    Group_SetGlobalCommand(YCMD:c563, ALLOW);
    Group_SetGlobalCommand(YCMD:c564, ALLOW);
    Group_SetGlobalCommand(YCMD:c565, ALLOW);
    Group_SetGlobalCommand(YCMD:c566, ALLOW);
    Group_SetGlobalCommand(YCMD:c567, ALLOW);
    Group_SetGlobalCommand(YCMD:c568, ALLOW);
    Group_SetGlobalCommand(YCMD:c569, ALLOW);
    Group_SetGlobalCommand(YCMD:c570, ALLOW);
    Group_SetGlobalCommand(YCMD:c571, ALLOW);
    Group_SetGlobalCommand(YCMD:c572, ALLOW);
    Group_SetGlobalCommand(YCMD:c573, ALLOW);
    Group_SetGlobalCommand(YCMD:c574, ALLOW);
    Group_SetGlobalCommand(YCMD:c575, ALLOW);
    Group_SetGlobalCommand(YCMD:c576, ALLOW);
    Group_SetGlobalCommand(YCMD:c577, ALLOW);
    Group_SetGlobalCommand(YCMD:c578, ALLOW);
    Group_SetGlobalCommand(YCMD:c579, ALLOW);
    Group_SetGlobalCommand(YCMD:c580, ALLOW);
    Group_SetGlobalCommand(YCMD:c581, ALLOW);
    Group_SetGlobalCommand(YCMD:c582, ALLOW);
    Group_SetGlobalCommand(YCMD:c583, ALLOW);
    Group_SetGlobalCommand(YCMD:c584, ALLOW);
    Group_SetGlobalCommand(YCMD:c585, ALLOW);
    Group_SetGlobalCommand(YCMD:c586, ALLOW);
    Group_SetGlobalCommand(YCMD:c587, ALLOW);
    Group_SetGlobalCommand(YCMD:c588, ALLOW);
    Group_SetGlobalCommand(YCMD:c589, ALLOW);
    Group_SetGlobalCommand(YCMD:c590, ALLOW);
    Group_SetGlobalCommand(YCMD:c591, ALLOW);
    Group_SetGlobalCommand(YCMD:c592, ALLOW);
    Group_SetGlobalCommand(YCMD:c593, ALLOW);
    Group_SetGlobalCommand(YCMD:c594, ALLOW);
    Group_SetGlobalCommand(YCMD:c595, ALLOW);
    Group_SetGlobalCommand(YCMD:c596, ALLOW);
    Group_SetGlobalCommand(YCMD:c597, ALLOW);
    Group_SetGlobalCommand(YCMD:c598, ALLOW);
    Group_SetGlobalCommand(YCMD:c599, ALLOW);
    Group_SetGlobalCommand(YCMD:c600, ALLOW);
    Group_SetGlobalCommand(YCMD:c601, ALLOW);
    Group_SetGlobalCommand(YCMD:c602, ALLOW);
    Group_SetGlobalCommand(YCMD:c603, ALLOW);
    Group_SetGlobalCommand(YCMD:c604, ALLOW);
    Group_SetGlobalCommand(YCMD:c605, ALLOW);
    Group_SetGlobalCommand(YCMD:c606, ALLOW);
    Group_SetGlobalCommand(YCMD:c607, ALLOW);
    Group_SetGlobalCommand(YCMD:c608, ALLOW);
    Group_SetGlobalCommand(YCMD:c609, ALLOW);
    Group_SetGlobalCommand(YCMD:c610, ALLOW);
    Group_SetGlobalCommand(YCMD:c611, ALLOW);
    Group_SetGlobalCommand(YCMD:c612, ALLOW);
    Group_SetGlobalCommand(YCMD:c613, ALLOW);
    Group_SetGlobalCommand(YCMD:c614, ALLOW);
    Group_SetGlobalCommand(YCMD:c615, ALLOW);
    Group_SetGlobalCommand(YCMD:c616, ALLOW);
    Group_SetGlobalCommand(YCMD:c617, ALLOW);
    Group_SetGlobalCommand(YCMD:c618, ALLOW);
    Group_SetGlobalCommand(YCMD:c619, ALLOW);
    Group_SetGlobalCommand(YCMD:c620, ALLOW);
    Group_SetGlobalCommand(YCMD:c621, ALLOW);
    Group_SetGlobalCommand(YCMD:c622, ALLOW);
    Group_SetGlobalCommand(YCMD:c623, ALLOW);
    Group_SetGlobalCommand(YCMD:c624, ALLOW);
    Group_SetGlobalCommand(YCMD:c625, ALLOW);
    Group_SetGlobalCommand(YCMD:c626, ALLOW);
    Group_SetGlobalCommand(YCMD:c627, ALLOW);
    Group_SetGlobalCommand(YCMD:c628, ALLOW);
    Group_SetGlobalCommand(YCMD:c629, ALLOW);
    Group_SetGlobalCommand(YCMD:c630, ALLOW);
    Group_SetGlobalCommand(YCMD:c631, ALLOW);
    Group_SetGlobalCommand(YCMD:c632, ALLOW);
    Group_SetGlobalCommand(YCMD:c633, ALLOW);
    Group_SetGlobalCommand(YCMD:c634, ALLOW);
    Group_SetGlobalCommand(YCMD:c635, ALLOW);
    Group_SetGlobalCommand(YCMD:c636, ALLOW);
    Group_SetGlobalCommand(YCMD:c637, ALLOW);
    Group_SetGlobalCommand(YCMD:c638, ALLOW);
    Group_SetGlobalCommand(YCMD:c639, ALLOW);
    Group_SetGlobalCommand(YCMD:c640, ALLOW);
    Group_SetGlobalCommand(YCMD:c641, ALLOW);
    Group_SetGlobalCommand(YCMD:c642, ALLOW);
    Group_SetGlobalCommand(YCMD:c643, ALLOW);
    Group_SetGlobalCommand(YCMD:c644, ALLOW);
    Group_SetGlobalCommand(YCMD:c645, ALLOW);
    Group_SetGlobalCommand(YCMD:c646, ALLOW);
    Group_SetGlobalCommand(YCMD:c647, ALLOW);
    Group_SetGlobalCommand(YCMD:c648, ALLOW);
    Group_SetGlobalCommand(YCMD:c649, ALLOW);
    Group_SetGlobalCommand(YCMD:c650, ALLOW);
    Group_SetGlobalCommand(YCMD:c651, ALLOW);
    Group_SetGlobalCommand(YCMD:c652, ALLOW);
    Group_SetGlobalCommand(YCMD:c653, ALLOW);
    Group_SetGlobalCommand(YCMD:c654, ALLOW);
    Group_SetGlobalCommand(YCMD:c655, ALLOW);
    Group_SetGlobalCommand(YCMD:c656, ALLOW);
    Group_SetGlobalCommand(YCMD:c657, ALLOW);
    Group_SetGlobalCommand(YCMD:c658, ALLOW);
    Group_SetGlobalCommand(YCMD:c659, ALLOW);
    Group_SetGlobalCommand(YCMD:c660, ALLOW);
    Group_SetGlobalCommand(YCMD:c661, ALLOW);
    Group_SetGlobalCommand(YCMD:c662, ALLOW);
    Group_SetGlobalCommand(YCMD:c663, ALLOW);
    Group_SetGlobalCommand(YCMD:c664, ALLOW);
    Group_SetGlobalCommand(YCMD:c665, ALLOW);
    Group_SetGlobalCommand(YCMD:c666, ALLOW);
    Group_SetGlobalCommand(YCMD:c667, ALLOW);
    Group_SetGlobalCommand(YCMD:c668, ALLOW);
    Group_SetGlobalCommand(YCMD:c669, ALLOW);
    Group_SetGlobalCommand(YCMD:c670, ALLOW);
    Group_SetGlobalCommand(YCMD:c671, ALLOW);
    Group_SetGlobalCommand(YCMD:c672, ALLOW);
    Group_SetGlobalCommand(YCMD:c673, ALLOW);
    Group_SetGlobalCommand(YCMD:c674, ALLOW);
    Group_SetGlobalCommand(YCMD:c675, ALLOW);
    Group_SetGlobalCommand(YCMD:c676, ALLOW);
    Group_SetGlobalCommand(YCMD:c677, ALLOW);
    Group_SetGlobalCommand(YCMD:c678, ALLOW);
    Group_SetGlobalCommand(YCMD:c679, ALLOW);
    Group_SetGlobalCommand(YCMD:c680, ALLOW);
    Group_SetGlobalCommand(YCMD:c681, ALLOW);
    Group_SetGlobalCommand(YCMD:c682, ALLOW);
    Group_SetGlobalCommand(YCMD:c683, ALLOW);
    Group_SetGlobalCommand(YCMD:c684, ALLOW);
    Group_SetGlobalCommand(YCMD:c685, ALLOW);
    Group_SetGlobalCommand(YCMD:c686, ALLOW);
    Group_SetGlobalCommand(YCMD:c687, ALLOW);
    Group_SetGlobalCommand(YCMD:c688, ALLOW);
    Group_SetGlobalCommand(YCMD:c689, ALLOW);
    Group_SetGlobalCommand(YCMD:c690, ALLOW);
    Group_SetGlobalCommand(YCMD:c691, ALLOW);
    Group_SetGlobalCommand(YCMD:c692, ALLOW);
    Group_SetGlobalCommand(YCMD:c693, ALLOW);
    Group_SetGlobalCommand(YCMD:c694, ALLOW);
    Group_SetGlobalCommand(YCMD:c695, ALLOW);
    Group_SetGlobalCommand(YCMD:c696, ALLOW);
    Group_SetGlobalCommand(YCMD:c697, ALLOW);
    Group_SetGlobalCommand(YCMD:c698, ALLOW);
    Group_SetGlobalCommand(YCMD:c699, ALLOW);
    Group_SetGlobalCommand(YCMD:c700, ALLOW);
    Group_SetGlobalCommand(YCMD:c701, ALLOW);
    Group_SetGlobalCommand(YCMD:c702, ALLOW);
    Group_SetGlobalCommand(YCMD:c703, ALLOW);
    Group_SetGlobalCommand(YCMD:c704, ALLOW);
    Group_SetGlobalCommand(YCMD:c705, ALLOW);
    Group_SetGlobalCommand(YCMD:c706, ALLOW);
    Group_SetGlobalCommand(YCMD:c707, ALLOW);
    Group_SetGlobalCommand(YCMD:c708, ALLOW);
    Group_SetGlobalCommand(YCMD:c709, ALLOW);
    Group_SetGlobalCommand(YCMD:c710, ALLOW);
    Group_SetGlobalCommand(YCMD:c711, ALLOW);
    Group_SetGlobalCommand(YCMD:c712, ALLOW);
    Group_SetGlobalCommand(YCMD:c713, ALLOW);
    Group_SetGlobalCommand(YCMD:c714, ALLOW);
    Group_SetGlobalCommand(YCMD:c715, ALLOW);
    Group_SetGlobalCommand(YCMD:c716, ALLOW);
    Group_SetGlobalCommand(YCMD:c717, ALLOW);
    Group_SetGlobalCommand(YCMD:c718, ALLOW);
    Group_SetGlobalCommand(YCMD:c719, ALLOW);
    Group_SetGlobalCommand(YCMD:c720, ALLOW);
    Group_SetGlobalCommand(YCMD:c721, ALLOW);
    Group_SetGlobalCommand(YCMD:c722, ALLOW);
    Group_SetGlobalCommand(YCMD:c723, ALLOW);
    Group_SetGlobalCommand(YCMD:c724, ALLOW);
    Group_SetGlobalCommand(YCMD:c725, ALLOW);
    Group_SetGlobalCommand(YCMD:c726, ALLOW);
    Group_SetGlobalCommand(YCMD:c727, ALLOW);
    Group_SetGlobalCommand(YCMD:c728, ALLOW);
    Group_SetGlobalCommand(YCMD:c729, ALLOW);
    Group_SetGlobalCommand(YCMD:c730, ALLOW);
    Group_SetGlobalCommand(YCMD:c731, ALLOW);
    Group_SetGlobalCommand(YCMD:c732, ALLOW);
    Group_SetGlobalCommand(YCMD:c733, ALLOW);
    Group_SetGlobalCommand(YCMD:c734, ALLOW);
    Group_SetGlobalCommand(YCMD:c735, ALLOW);
    Group_SetGlobalCommand(YCMD:c736, ALLOW);
    Group_SetGlobalCommand(YCMD:c737, ALLOW);
    Group_SetGlobalCommand(YCMD:c738, ALLOW);
    Group_SetGlobalCommand(YCMD:c739, ALLOW);
    Group_SetGlobalCommand(YCMD:c740, ALLOW);
    Group_SetGlobalCommand(YCMD:c741, ALLOW);
    Group_SetGlobalCommand(YCMD:c742, ALLOW);
    Group_SetGlobalCommand(YCMD:c743, ALLOW);
    Group_SetGlobalCommand(YCMD:c744, ALLOW);
    Group_SetGlobalCommand(YCMD:c745, ALLOW);
    Group_SetGlobalCommand(YCMD:c746, ALLOW);
    Group_SetGlobalCommand(YCMD:c747, ALLOW);
    Group_SetGlobalCommand(YCMD:c748, ALLOW);
    Group_SetGlobalCommand(YCMD:c749, ALLOW);
    Group_SetGlobalCommand(YCMD:c750, ALLOW);
    Group_SetGlobalCommand(YCMD:c751, ALLOW);
    Group_SetGlobalCommand(YCMD:c752, ALLOW);
    Group_SetGlobalCommand(YCMD:c753, ALLOW);
    Group_SetGlobalCommand(YCMD:c754, ALLOW);
    Group_SetGlobalCommand(YCMD:c755, ALLOW);
    Group_SetGlobalCommand(YCMD:c756, ALLOW);
    Group_SetGlobalCommand(YCMD:c757, ALLOW);
    Group_SetGlobalCommand(YCMD:c758, ALLOW);
    Group_SetGlobalCommand(YCMD:c759, ALLOW);
    Group_SetGlobalCommand(YCMD:c760, ALLOW);
    Group_SetGlobalCommand(YCMD:c761, ALLOW);
    Group_SetGlobalCommand(YCMD:c762, ALLOW);
    Group_SetGlobalCommand(YCMD:c763, ALLOW);
    Group_SetGlobalCommand(YCMD:c764, ALLOW);
    Group_SetGlobalCommand(YCMD:c765, ALLOW);
    Group_SetGlobalCommand(YCMD:c766, ALLOW);
    Group_SetGlobalCommand(YCMD:c767, ALLOW);
    Group_SetGlobalCommand(YCMD:c768, ALLOW);
    Group_SetGlobalCommand(YCMD:c769, ALLOW);
    Group_SetGlobalCommand(YCMD:c770, ALLOW);
    Group_SetGlobalCommand(YCMD:c771, ALLOW);
    Group_SetGlobalCommand(YCMD:c772, ALLOW);
    Group_SetGlobalCommand(YCMD:c773, ALLOW);
    Group_SetGlobalCommand(YCMD:c774, ALLOW);
    Group_SetGlobalCommand(YCMD:c775, ALLOW);
    Group_SetGlobalCommand(YCMD:c776, ALLOW);
    Group_SetGlobalCommand(YCMD:c777, ALLOW);
    Group_SetGlobalCommand(YCMD:c778, ALLOW);
    Group_SetGlobalCommand(YCMD:c779, ALLOW);
    Group_SetGlobalCommand(YCMD:c780, ALLOW);
    Group_SetGlobalCommand(YCMD:c781, ALLOW);
    Group_SetGlobalCommand(YCMD:c782, ALLOW);
    Group_SetGlobalCommand(YCMD:c783, ALLOW);
    Group_SetGlobalCommand(YCMD:c784, ALLOW);
    Group_SetGlobalCommand(YCMD:c785, ALLOW);
    Group_SetGlobalCommand(YCMD:c786, ALLOW);
    Group_SetGlobalCommand(YCMD:c787, ALLOW);
    Group_SetGlobalCommand(YCMD:c788, ALLOW);
    Group_SetGlobalCommand(YCMD:c789, ALLOW);
    Group_SetGlobalCommand(YCMD:c790, ALLOW);
    Group_SetGlobalCommand(YCMD:c791, ALLOW);
    Group_SetGlobalCommand(YCMD:c792, ALLOW);
    Group_SetGlobalCommand(YCMD:c793, ALLOW);
    Group_SetGlobalCommand(YCMD:c794, ALLOW);
    Group_SetGlobalCommand(YCMD:c795, ALLOW);
    Group_SetGlobalCommand(YCMD:c796, ALLOW);
    Group_SetGlobalCommand(YCMD:c797, ALLOW);
    Group_SetGlobalCommand(YCMD:c798, ALLOW);
    Group_SetGlobalCommand(YCMD:c799, ALLOW);
    Group_SetGlobalCommand(YCMD:c800, ALLOW);
    Group_SetGlobalCommand(YCMD:c801, ALLOW);
    Group_SetGlobalCommand(YCMD:c802, ALLOW);
    Group_SetGlobalCommand(YCMD:c803, ALLOW);
    Group_SetGlobalCommand(YCMD:c804, ALLOW);
    Group_SetGlobalCommand(YCMD:c805, ALLOW);
    Group_SetGlobalCommand(YCMD:c806, ALLOW);
    Group_SetGlobalCommand(YCMD:c807, ALLOW);
    Group_SetGlobalCommand(YCMD:c808, ALLOW);
    Group_SetGlobalCommand(YCMD:c809, ALLOW);
    Group_SetGlobalCommand(YCMD:c810, ALLOW);
    Group_SetGlobalCommand(YCMD:c811, ALLOW);
    Group_SetGlobalCommand(YCMD:c812, ALLOW);
    Group_SetGlobalCommand(YCMD:c813, ALLOW);
    Group_SetGlobalCommand(YCMD:c814, ALLOW);
    Group_SetGlobalCommand(YCMD:c815, ALLOW);
    Group_SetGlobalCommand(YCMD:c816, ALLOW);
    Group_SetGlobalCommand(YCMD:c817, ALLOW);
    Group_SetGlobalCommand(YCMD:c818, ALLOW);
    Group_SetGlobalCommand(YCMD:c819, ALLOW);
    Group_SetGlobalCommand(YCMD:c820, ALLOW);
    Group_SetGlobalCommand(YCMD:c821, ALLOW);
    Group_SetGlobalCommand(YCMD:c822, ALLOW);
    Group_SetGlobalCommand(YCMD:c823, ALLOW);
    Group_SetGlobalCommand(YCMD:c824, ALLOW);
    Group_SetGlobalCommand(YCMD:c825, ALLOW);
    Group_SetGlobalCommand(YCMD:c826, ALLOW);
    Group_SetGlobalCommand(YCMD:c827, ALLOW);
    Group_SetGlobalCommand(YCMD:c828, ALLOW);
    Group_SetGlobalCommand(YCMD:c829, ALLOW);
    Group_SetGlobalCommand(YCMD:c830, ALLOW);
    Group_SetGlobalCommand(YCMD:c831, ALLOW);
    Group_SetGlobalCommand(YCMD:c832, ALLOW);
    Group_SetGlobalCommand(YCMD:c833, ALLOW);
    Group_SetGlobalCommand(YCMD:c834, ALLOW);
    Group_SetGlobalCommand(YCMD:c835, ALLOW);
    Group_SetGlobalCommand(YCMD:c836, ALLOW);
    Group_SetGlobalCommand(YCMD:c837, ALLOW);
    Group_SetGlobalCommand(YCMD:c838, ALLOW);
    Group_SetGlobalCommand(YCMD:c839, ALLOW);
    Group_SetGlobalCommand(YCMD:c840, ALLOW);
    Group_SetGlobalCommand(YCMD:c841, ALLOW);
    Group_SetGlobalCommand(YCMD:c842, ALLOW);
    Group_SetGlobalCommand(YCMD:c843, ALLOW);
    Group_SetGlobalCommand(YCMD:c844, ALLOW);
    Group_SetGlobalCommand(YCMD:c845, ALLOW);
    Group_SetGlobalCommand(YCMD:c846, ALLOW);
    Group_SetGlobalCommand(YCMD:c847, ALLOW);
    Group_SetGlobalCommand(YCMD:c848, ALLOW);
    Group_SetGlobalCommand(YCMD:c849, ALLOW);
    Group_SetGlobalCommand(YCMD:c850, ALLOW);
    Group_SetGlobalCommand(YCMD:c851, ALLOW);
    Group_SetGlobalCommand(YCMD:c852, ALLOW);
    Group_SetGlobalCommand(YCMD:c853, ALLOW);
    Group_SetGlobalCommand(YCMD:c854, ALLOW);
    Group_SetGlobalCommand(YCMD:c855, ALLOW);
    Group_SetGlobalCommand(YCMD:c856, ALLOW);
    Group_SetGlobalCommand(YCMD:c857, ALLOW);
    Group_SetGlobalCommand(YCMD:c858, ALLOW);
    Group_SetGlobalCommand(YCMD:c859, ALLOW);
    Group_SetGlobalCommand(YCMD:c860, ALLOW);
    Group_SetGlobalCommand(YCMD:c861, ALLOW);
    Group_SetGlobalCommand(YCMD:c862, ALLOW);
    Group_SetGlobalCommand(YCMD:c863, ALLOW);
    Group_SetGlobalCommand(YCMD:c864, ALLOW);
    Group_SetGlobalCommand(YCMD:c865, ALLOW);
    Group_SetGlobalCommand(YCMD:c866, ALLOW);
    Group_SetGlobalCommand(YCMD:c867, ALLOW);
    Group_SetGlobalCommand(YCMD:c868, ALLOW);
    Group_SetGlobalCommand(YCMD:c869, ALLOW);
    Group_SetGlobalCommand(YCMD:c870, ALLOW);
    Group_SetGlobalCommand(YCMD:c871, ALLOW);
    Group_SetGlobalCommand(YCMD:c872, ALLOW);
    Group_SetGlobalCommand(YCMD:c873, ALLOW);
    Group_SetGlobalCommand(YCMD:c874, ALLOW);
    Group_SetGlobalCommand(YCMD:c875, ALLOW);
    Group_SetGlobalCommand(YCMD:c876, ALLOW);
    Group_SetGlobalCommand(YCMD:c877, ALLOW);
    Group_SetGlobalCommand(YCMD:c878, ALLOW);
    Group_SetGlobalCommand(YCMD:c879, ALLOW);
    Group_SetGlobalCommand(YCMD:c880, ALLOW);
    Group_SetGlobalCommand(YCMD:c881, ALLOW);
    Group_SetGlobalCommand(YCMD:c882, ALLOW);
    Group_SetGlobalCommand(YCMD:c883, ALLOW);
    Group_SetGlobalCommand(YCMD:c884, ALLOW);
    Group_SetGlobalCommand(YCMD:c885, ALLOW);
    Group_SetGlobalCommand(YCMD:c886, ALLOW);
    Group_SetGlobalCommand(YCMD:c887, ALLOW);
    Group_SetGlobalCommand(YCMD:c888, ALLOW);
    Group_SetGlobalCommand(YCMD:c889, ALLOW);
    Group_SetGlobalCommand(YCMD:c890, ALLOW);
    Group_SetGlobalCommand(YCMD:c891, ALLOW);
    Group_SetGlobalCommand(YCMD:c892, ALLOW);
    Group_SetGlobalCommand(YCMD:c893, ALLOW);
    Group_SetGlobalCommand(YCMD:c894, ALLOW);
    Group_SetGlobalCommand(YCMD:c895, ALLOW);
    Group_SetGlobalCommand(YCMD:c896, ALLOW);
    Group_SetGlobalCommand(YCMD:c897, ALLOW);
    Group_SetGlobalCommand(YCMD:c898, ALLOW);
    Group_SetGlobalCommand(YCMD:c899, ALLOW);
    Group_SetGlobalCommand(YCMD:c900, ALLOW);
    Group_SetGlobalCommand(YCMD:c901, ALLOW);
    Group_SetGlobalCommand(YCMD:c902, ALLOW);
    Group_SetGlobalCommand(YCMD:c903, ALLOW);
    Group_SetGlobalCommand(YCMD:c904, ALLOW);
    Group_SetGlobalCommand(YCMD:c905, ALLOW);
    Group_SetGlobalCommand(YCMD:c906, ALLOW);
    Group_SetGlobalCommand(YCMD:c907, ALLOW);
    Group_SetGlobalCommand(YCMD:c908, ALLOW);
    Group_SetGlobalCommand(YCMD:c909, ALLOW);
    Group_SetGlobalCommand(YCMD:c910, ALLOW);
    Group_SetGlobalCommand(YCMD:c911, ALLOW);
    Group_SetGlobalCommand(YCMD:c912, ALLOW);
    Group_SetGlobalCommand(YCMD:c913, ALLOW);
    Group_SetGlobalCommand(YCMD:c914, ALLOW);
    Group_SetGlobalCommand(YCMD:c915, ALLOW);
    Group_SetGlobalCommand(YCMD:c916, ALLOW);
    Group_SetGlobalCommand(YCMD:c917, ALLOW);
    Group_SetGlobalCommand(YCMD:c918, ALLOW);
    Group_SetGlobalCommand(YCMD:c919, ALLOW);
    Group_SetGlobalCommand(YCMD:c920, ALLOW);
    Group_SetGlobalCommand(YCMD:c921, ALLOW);
    Group_SetGlobalCommand(YCMD:c922, ALLOW);
    Group_SetGlobalCommand(YCMD:c923, ALLOW);
    Group_SetGlobalCommand(YCMD:c924, ALLOW);
    Group_SetGlobalCommand(YCMD:c925, ALLOW);
    Group_SetGlobalCommand(YCMD:c926, ALLOW);
    Group_SetGlobalCommand(YCMD:c927, ALLOW);
    Group_SetGlobalCommand(YCMD:c928, ALLOW);
    Group_SetGlobalCommand(YCMD:c929, ALLOW);
    Group_SetGlobalCommand(YCMD:c930, ALLOW);
    Group_SetGlobalCommand(YCMD:c931, ALLOW);
    Group_SetGlobalCommand(YCMD:c932, ALLOW);
    Group_SetGlobalCommand(YCMD:c933, ALLOW);
    Group_SetGlobalCommand(YCMD:c934, ALLOW);
    Group_SetGlobalCommand(YCMD:c935, ALLOW);
    Group_SetGlobalCommand(YCMD:c936, ALLOW);
    Group_SetGlobalCommand(YCMD:c937, ALLOW);
    Group_SetGlobalCommand(YCMD:c938, ALLOW);
    Group_SetGlobalCommand(YCMD:c939, ALLOW);
    Group_SetGlobalCommand(YCMD:c940, ALLOW);
    Group_SetGlobalCommand(YCMD:c941, ALLOW);
    Group_SetGlobalCommand(YCMD:c942, ALLOW);
    Group_SetGlobalCommand(YCMD:c943, ALLOW);
    Group_SetGlobalCommand(YCMD:c944, ALLOW);
    Group_SetGlobalCommand(YCMD:c945, ALLOW);
    Group_SetGlobalCommand(YCMD:c946, ALLOW);
    Group_SetGlobalCommand(YCMD:c947, ALLOW);
    Group_SetGlobalCommand(YCMD:c948, ALLOW);
    Group_SetGlobalCommand(YCMD:c949, ALLOW);
    Group_SetGlobalCommand(YCMD:c950, ALLOW);
    Group_SetGlobalCommand(YCMD:c951, ALLOW);
    Group_SetGlobalCommand(YCMD:c952, ALLOW);
    Group_SetGlobalCommand(YCMD:c953, ALLOW);
    Group_SetGlobalCommand(YCMD:c954, ALLOW);
    Group_SetGlobalCommand(YCMD:c955, ALLOW);
    Group_SetGlobalCommand(YCMD:c956, ALLOW);
    Group_SetGlobalCommand(YCMD:c957, ALLOW);
    Group_SetGlobalCommand(YCMD:c958, ALLOW);
    Group_SetGlobalCommand(YCMD:c959, ALLOW);
    Group_SetGlobalCommand(YCMD:c960, ALLOW);
    Group_SetGlobalCommand(YCMD:c961, ALLOW);
    Group_SetGlobalCommand(YCMD:c962, ALLOW);
    Group_SetGlobalCommand(YCMD:c963, ALLOW);
    Group_SetGlobalCommand(YCMD:c964, ALLOW);
    Group_SetGlobalCommand(YCMD:c965, ALLOW);
    Group_SetGlobalCommand(YCMD:c966, ALLOW);
    Group_SetGlobalCommand(YCMD:c967, ALLOW);
    Group_SetGlobalCommand(YCMD:c968, ALLOW);
    Group_SetGlobalCommand(YCMD:c969, ALLOW);
    Group_SetGlobalCommand(YCMD:c970, ALLOW);
    Group_SetGlobalCommand(YCMD:c971, ALLOW);
    Group_SetGlobalCommand(YCMD:c972, ALLOW);
    Group_SetGlobalCommand(YCMD:c973, ALLOW);
    Group_SetGlobalCommand(YCMD:c974, ALLOW);
    Group_SetGlobalCommand(YCMD:c975, ALLOW);
    Group_SetGlobalCommand(YCMD:c976, ALLOW);
    Group_SetGlobalCommand(YCMD:c977, ALLOW);
    Group_SetGlobalCommand(YCMD:c978, ALLOW);
    Group_SetGlobalCommand(YCMD:c979, ALLOW);
    Group_SetGlobalCommand(YCMD:c980, ALLOW);
    Group_SetGlobalCommand(YCMD:c981, ALLOW);
    Group_SetGlobalCommand(YCMD:c982, ALLOW);
    Group_SetGlobalCommand(YCMD:c983, ALLOW);
    Group_SetGlobalCommand(YCMD:c984, ALLOW);
    Group_SetGlobalCommand(YCMD:c985, ALLOW);
    Group_SetGlobalCommand(YCMD:c986, ALLOW);
    Group_SetGlobalCommand(YCMD:c987, ALLOW);
    Group_SetGlobalCommand(YCMD:c988, ALLOW);
    Group_SetGlobalCommand(YCMD:c989, ALLOW);
    Group_SetGlobalCommand(YCMD:c990, ALLOW);
    Group_SetGlobalCommand(YCMD:c991, ALLOW);
    Group_SetGlobalCommand(YCMD:c992, ALLOW);
    Group_SetGlobalCommand(YCMD:c993, ALLOW);
    Group_SetGlobalCommand(YCMD:c994, ALLOW);
    Group_SetGlobalCommand(YCMD:c995, ALLOW);
    Group_SetGlobalCommand(YCMD:c996, ALLOW);
    Group_SetGlobalCommand(YCMD:c997, ALLOW);
    Group_SetGlobalCommand(YCMD:c998, ALLOW);
    Group_SetGlobalCommand(YCMD:c999, ALLOW);
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
