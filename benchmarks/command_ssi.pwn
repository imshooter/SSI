#define BENCH_SIDE "SSI"

#include <open.mp>
#define MAX_COMMANDS (Command:1024)
#define MAX_COMMAND_NAMES (2048)

#include <SSI\iterator>
#include <SSI\command>
#include <SSI\group>
#include <SSI\hooks>
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
    Group_AddPlayer(gAdmin, gAdminBot);
    Group_AddPlayer(gChain[15], gChainBot);
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
            Command_Run(gAdminBot, inherited);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("command", "allowed through 2 parent groups, 1000 commands");
    Bench_Check("allowed commands ran", gHits, gBenchOps);

    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            Command_Run(gPlainBot, last);
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
            Command_Run(gPlainBot, denied);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("command", "denied, 1000 commands");
    Bench_Check("denied commands ran", gHits, 0);

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            Command_Run(gPlainBot, unknown);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("command", "unknown, 1000 commands");

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            Group_AddPlayer(gHelper, gPlainBot);
            Group_RemovePlayer(gHelper, gPlainBot);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("group", "join and leave a group");

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            Group_AddPlayer(gChain[15], gPlainBot);
            Group_RemovePlayer(gChain[15], gPlainBot);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("group", "join and leave the end of a chain of 16 groups");

    member = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            if (Group_HasPlayer(gHelper, gAdminBot)) {
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
            if (Group_HasPlayer(gChain[0], gChainBot)) {
                ++member;
            }
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("group", "member through 15 parent groups");
    Bench_Check("chain members", member, gBenchOps);
}

CMD:c0(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c1(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c2(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c3(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c4(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c5(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c6(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c7(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c8(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c9(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c10(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c11(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c12(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c13(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c14(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c15(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c16(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c17(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c18(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c19(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c20(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c21(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c22(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c23(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c24(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c25(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c26(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c27(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c28(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c29(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c30(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c31(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c32(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c33(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c34(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c35(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c36(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c37(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c38(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c39(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c40(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c41(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c42(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c43(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c44(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c45(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c46(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c47(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c48(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c49(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c50(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c51(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c52(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c53(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c54(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c55(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c56(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c57(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c58(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c59(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c60(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c61(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c62(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c63(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c64(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c65(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c66(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c67(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c68(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c69(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c70(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c71(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c72(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c73(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c74(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c75(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c76(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c77(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c78(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c79(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c80(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c81(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c82(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c83(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c84(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c85(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c86(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c87(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c88(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c89(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c90(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c91(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c92(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c93(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c94(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c95(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c96(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c97(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c98(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c99(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c100(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c101(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c102(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c103(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c104(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c105(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c106(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c107(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c108(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c109(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c110(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c111(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c112(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c113(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c114(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c115(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c116(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c117(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c118(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c119(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c120(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c121(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c122(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c123(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c124(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c125(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c126(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c127(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c128(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c129(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c130(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c131(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c132(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c133(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c134(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c135(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c136(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c137(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c138(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c139(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c140(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c141(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c142(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c143(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c144(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c145(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c146(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c147(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c148(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c149(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c150(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c151(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c152(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c153(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c154(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c155(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c156(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c157(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c158(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c159(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c160(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c161(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c162(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c163(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c164(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c165(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c166(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c167(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c168(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c169(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c170(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c171(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c172(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c173(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c174(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c175(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c176(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c177(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c178(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c179(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c180(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c181(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c182(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c183(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c184(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c185(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c186(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c187(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c188(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c189(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c190(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c191(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c192(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c193(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c194(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c195(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c196(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c197(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c198(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c199(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c200(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c201(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c202(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c203(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c204(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c205(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c206(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c207(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c208(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c209(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c210(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c211(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c212(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c213(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c214(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c215(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c216(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c217(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c218(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c219(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c220(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c221(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c222(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c223(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c224(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c225(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c226(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c227(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c228(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c229(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c230(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c231(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c232(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c233(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c234(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c235(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c236(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c237(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c238(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c239(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c240(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c241(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c242(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c243(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c244(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c245(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c246(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c247(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c248(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c249(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c250(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c251(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c252(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c253(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c254(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c255(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c256(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c257(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c258(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c259(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c260(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c261(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c262(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c263(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c264(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c265(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c266(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c267(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c268(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c269(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c270(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c271(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c272(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c273(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c274(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c275(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c276(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c277(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c278(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c279(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c280(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c281(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c282(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c283(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c284(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c285(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c286(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c287(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c288(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c289(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c290(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c291(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c292(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c293(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c294(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c295(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c296(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c297(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c298(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c299(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c300(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c301(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c302(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c303(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c304(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c305(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c306(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c307(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c308(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c309(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c310(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c311(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c312(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c313(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c314(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c315(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c316(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c317(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c318(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c319(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c320(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c321(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c322(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c323(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c324(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c325(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c326(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c327(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c328(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c329(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c330(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c331(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c332(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c333(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c334(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c335(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c336(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c337(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c338(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c339(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c340(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c341(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c342(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c343(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c344(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c345(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c346(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c347(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c348(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c349(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c350(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c351(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c352(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c353(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c354(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c355(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c356(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c357(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c358(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c359(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c360(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c361(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c362(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c363(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c364(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c365(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c366(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c367(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c368(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c369(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c370(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c371(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c372(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c373(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c374(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c375(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c376(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c377(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c378(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c379(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c380(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c381(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c382(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c383(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c384(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c385(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c386(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c387(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c388(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c389(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c390(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c391(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c392(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c393(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c394(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c395(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c396(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c397(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c398(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c399(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c400(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c401(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c402(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c403(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c404(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c405(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c406(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c407(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c408(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c409(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c410(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c411(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c412(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c413(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c414(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c415(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c416(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c417(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c418(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c419(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c420(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c421(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c422(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c423(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c424(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c425(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c426(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c427(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c428(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c429(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c430(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c431(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c432(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c433(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c434(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c435(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c436(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c437(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c438(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c439(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c440(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c441(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c442(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c443(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c444(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c445(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c446(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c447(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c448(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c449(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c450(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c451(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c452(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c453(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c454(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c455(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c456(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c457(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c458(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c459(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c460(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c461(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c462(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c463(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c464(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c465(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c466(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c467(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c468(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c469(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c470(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c471(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c472(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c473(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c474(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c475(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c476(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c477(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c478(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c479(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c480(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c481(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c482(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c483(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c484(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c485(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c486(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c487(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c488(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c489(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c490(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c491(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c492(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c493(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c494(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c495(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c496(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c497(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c498(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c499(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c500(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c501(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c502(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c503(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c504(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c505(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c506(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c507(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c508(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c509(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c510(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c511(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c512(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c513(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c514(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c515(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c516(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c517(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c518(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c519(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c520(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c521(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c522(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c523(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c524(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c525(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c526(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c527(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c528(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c529(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c530(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c531(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c532(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c533(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c534(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c535(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c536(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c537(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c538(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c539(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c540(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c541(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c542(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c543(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c544(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c545(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c546(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c547(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c548(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c549(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c550(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c551(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c552(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c553(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c554(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c555(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c556(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c557(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c558(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c559(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c560(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c561(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c562(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c563(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c564(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c565(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c566(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c567(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c568(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c569(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c570(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c571(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c572(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c573(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c574(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c575(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c576(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c577(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c578(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c579(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c580(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c581(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c582(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c583(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c584(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c585(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c586(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c587(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c588(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c589(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c590(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c591(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c592(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c593(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c594(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c595(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c596(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c597(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c598(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c599(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c600(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c601(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c602(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c603(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c604(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c605(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c606(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c607(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c608(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c609(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c610(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c611(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c612(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c613(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c614(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c615(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c616(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c617(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c618(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c619(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c620(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c621(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c622(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c623(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c624(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c625(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c626(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c627(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c628(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c629(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c630(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c631(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c632(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c633(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c634(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c635(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c636(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c637(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c638(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c639(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c640(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c641(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c642(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c643(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c644(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c645(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c646(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c647(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c648(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c649(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c650(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c651(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c652(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c653(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c654(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c655(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c656(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c657(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c658(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c659(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c660(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c661(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c662(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c663(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c664(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c665(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c666(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c667(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c668(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c669(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c670(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c671(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c672(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c673(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c674(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c675(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c676(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c677(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c678(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c679(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c680(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c681(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c682(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c683(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c684(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c685(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c686(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c687(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c688(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c689(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c690(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c691(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c692(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c693(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c694(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c695(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c696(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c697(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c698(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c699(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c700(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c701(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c702(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c703(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c704(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c705(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c706(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c707(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c708(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c709(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c710(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c711(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c712(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c713(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c714(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c715(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c716(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c717(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c718(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c719(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c720(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c721(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c722(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c723(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c724(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c725(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c726(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c727(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c728(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c729(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c730(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c731(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c732(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c733(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c734(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c735(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c736(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c737(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c738(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c739(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c740(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c741(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c742(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c743(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c744(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c745(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c746(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c747(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c748(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c749(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c750(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c751(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c752(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c753(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c754(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c755(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c756(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c757(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c758(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c759(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c760(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c761(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c762(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c763(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c764(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c765(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c766(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c767(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c768(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c769(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c770(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c771(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c772(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c773(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c774(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c775(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c776(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c777(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c778(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c779(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c780(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c781(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c782(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c783(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c784(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c785(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c786(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c787(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c788(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c789(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c790(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c791(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c792(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c793(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c794(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c795(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c796(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c797(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c798(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c799(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c800(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c801(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c802(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c803(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c804(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c805(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c806(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c807(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c808(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c809(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c810(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c811(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c812(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c813(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c814(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c815(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c816(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c817(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c818(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c819(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c820(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c821(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c822(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c823(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c824(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c825(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c826(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c827(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c828(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c829(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c830(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c831(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c832(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c833(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c834(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c835(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c836(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c837(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c838(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c839(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c840(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c841(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c842(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c843(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c844(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c845(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c846(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c847(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c848(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c849(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c850(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c851(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c852(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c853(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c854(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c855(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c856(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c857(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c858(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c859(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c860(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c861(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c862(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c863(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c864(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c865(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c866(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c867(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c868(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c869(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c870(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c871(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c872(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c873(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c874(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c875(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c876(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c877(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c878(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c879(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c880(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c881(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c882(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c883(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c884(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c885(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c886(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c887(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c888(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c889(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c890(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c891(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c892(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c893(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c894(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c895(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c896(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c897(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c898(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c899(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c900(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c901(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c902(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c903(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c904(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c905(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c906(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c907(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c908(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c909(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c910(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c911(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c912(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c913(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c914(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c915(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c916(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c917(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c918(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c919(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c920(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c921(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c922(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c923(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c924(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c925(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c926(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c927(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c928(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c929(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c930(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c931(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c932(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c933(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c934(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c935(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c936(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c937(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c938(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c939(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c940(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c941(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c942(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c943(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c944(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c945(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c946(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c947(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c948(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c949(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c950(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c951(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c952(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c953(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c954(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c955(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c956(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c957(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c958(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c959(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c960(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c961(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c962(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c963(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c964(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c965(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c966(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c967(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c968(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c969(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c970(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c971(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c972(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c973(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c974(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c975(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c976(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c977(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c978(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c979(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c980(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c981(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c982(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c983(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c984(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c985(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c986(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c987(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c988(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c989(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c990(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c991(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c992(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c993(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c994(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c995(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c996(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c997(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c998(playerid, params[]) {
    ++gHits;

    return 1;
}

CMD:c999(playerid, params[]) {
    ++gHits;

    return 1;
}

Setup() {
    gHelper = Group_Create("Helper");
    gModerator = Group_Create("Moderator");
    gAdmin = Group_Create("Administrator");
    Group_SetParent(gModerator, gHelper);
    Group_SetParent(gAdmin, gModerator);

    for (new i; i != sizeof (gChain); ++i) {
        new
            name[16]
        ;

        format(name, sizeof (name), "Chain%i", i);
        gChain[i] = Group_Create(name);

        if (i != 0) {
            Group_SetParent(gChain[i], gChain[i - 1]);
        }
    }

    Group_AllowCommand(gHelper, "c0");
    Group_AllowCommand(gHelper, "c1");
    Group_AllowCommand(gHelper, "c2");
    Group_AllowCommand(gHelper, "c3");
    Group_AllowCommand(gHelper, "c4");
    Group_AllowCommand(gHelper, "c5");
    Group_AllowCommand(gHelper, "c6");
    Group_AllowCommand(gHelper, "c7");
    Group_AllowCommand(gHelper, "c8");
    Group_AllowCommand(gHelper, "c9");
    Group_AllowCommand(gModerator, "c10");
    Group_AllowCommand(gModerator, "c11");
    Group_AllowCommand(gModerator, "c12");
    Group_AllowCommand(gModerator, "c13");
    Group_AllowCommand(gModerator, "c14");
    Group_AllowCommand(gModerator, "c15");
    Group_AllowCommand(gModerator, "c16");
    Group_AllowCommand(gModerator, "c17");
    Group_AllowCommand(gModerator, "c18");
    Group_AllowCommand(gModerator, "c19");
    Group_AllowCommand(gAdmin, "c20");
    Group_AllowCommand(gAdmin, "c21");
    Group_AllowCommand(gAdmin, "c22");
    Group_AllowCommand(gAdmin, "c23");
    Group_AllowCommand(gAdmin, "c24");
    Group_AllowCommand(gAdmin, "c25");
    Group_AllowCommand(gAdmin, "c26");
    Group_AllowCommand(gAdmin, "c27");
    Group_AllowCommand(gAdmin, "c28");
    Group_AllowCommand(gAdmin, "c29");
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
