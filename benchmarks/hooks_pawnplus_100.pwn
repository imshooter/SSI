#define BENCH_SIDE "PawnPlus"

#include <open.mp>
#include <PawnPlus>
#include "bench.inc"

#define HOOKS (100)

new
    gHits
;

forward OnBench(a, b, c);
public OnBench(a, b, c) {
    gBenchSink += a;
    ++gHits;

    return 1;
}

forward @Handler0(a, b, c);
public @Handler0(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler1(a, b, c);
public @Handler1(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler2(a, b, c);
public @Handler2(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler3(a, b, c);
public @Handler3(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler4(a, b, c);
public @Handler4(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler5(a, b, c);
public @Handler5(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler6(a, b, c);
public @Handler6(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler7(a, b, c);
public @Handler7(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler8(a, b, c);
public @Handler8(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler9(a, b, c);
public @Handler9(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler10(a, b, c);
public @Handler10(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler11(a, b, c);
public @Handler11(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler12(a, b, c);
public @Handler12(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler13(a, b, c);
public @Handler13(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler14(a, b, c);
public @Handler14(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler15(a, b, c);
public @Handler15(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler16(a, b, c);
public @Handler16(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler17(a, b, c);
public @Handler17(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler18(a, b, c);
public @Handler18(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler19(a, b, c);
public @Handler19(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler20(a, b, c);
public @Handler20(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler21(a, b, c);
public @Handler21(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler22(a, b, c);
public @Handler22(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler23(a, b, c);
public @Handler23(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler24(a, b, c);
public @Handler24(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler25(a, b, c);
public @Handler25(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler26(a, b, c);
public @Handler26(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler27(a, b, c);
public @Handler27(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler28(a, b, c);
public @Handler28(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler29(a, b, c);
public @Handler29(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler30(a, b, c);
public @Handler30(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler31(a, b, c);
public @Handler31(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler32(a, b, c);
public @Handler32(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler33(a, b, c);
public @Handler33(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler34(a, b, c);
public @Handler34(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler35(a, b, c);
public @Handler35(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler36(a, b, c);
public @Handler36(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler37(a, b, c);
public @Handler37(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler38(a, b, c);
public @Handler38(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler39(a, b, c);
public @Handler39(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler40(a, b, c);
public @Handler40(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler41(a, b, c);
public @Handler41(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler42(a, b, c);
public @Handler42(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler43(a, b, c);
public @Handler43(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler44(a, b, c);
public @Handler44(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler45(a, b, c);
public @Handler45(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler46(a, b, c);
public @Handler46(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler47(a, b, c);
public @Handler47(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler48(a, b, c);
public @Handler48(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler49(a, b, c);
public @Handler49(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler50(a, b, c);
public @Handler50(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler51(a, b, c);
public @Handler51(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler52(a, b, c);
public @Handler52(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler53(a, b, c);
public @Handler53(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler54(a, b, c);
public @Handler54(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler55(a, b, c);
public @Handler55(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler56(a, b, c);
public @Handler56(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler57(a, b, c);
public @Handler57(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler58(a, b, c);
public @Handler58(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler59(a, b, c);
public @Handler59(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler60(a, b, c);
public @Handler60(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler61(a, b, c);
public @Handler61(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler62(a, b, c);
public @Handler62(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler63(a, b, c);
public @Handler63(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler64(a, b, c);
public @Handler64(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler65(a, b, c);
public @Handler65(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler66(a, b, c);
public @Handler66(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler67(a, b, c);
public @Handler67(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler68(a, b, c);
public @Handler68(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler69(a, b, c);
public @Handler69(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler70(a, b, c);
public @Handler70(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler71(a, b, c);
public @Handler71(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler72(a, b, c);
public @Handler72(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler73(a, b, c);
public @Handler73(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler74(a, b, c);
public @Handler74(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler75(a, b, c);
public @Handler75(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler76(a, b, c);
public @Handler76(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler77(a, b, c);
public @Handler77(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler78(a, b, c);
public @Handler78(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler79(a, b, c);
public @Handler79(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler80(a, b, c);
public @Handler80(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler81(a, b, c);
public @Handler81(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler82(a, b, c);
public @Handler82(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler83(a, b, c);
public @Handler83(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler84(a, b, c);
public @Handler84(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler85(a, b, c);
public @Handler85(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler86(a, b, c);
public @Handler86(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler87(a, b, c);
public @Handler87(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler88(a, b, c);
public @Handler88(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler89(a, b, c);
public @Handler89(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler90(a, b, c);
public @Handler90(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler91(a, b, c);
public @Handler91(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler92(a, b, c);
public @Handler92(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler93(a, b, c);
public @Handler93(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler94(a, b, c);
public @Handler94(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler95(a, b, c);
public @Handler95(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler96(a, b, c);
public @Handler96(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler97(a, b, c);
public @Handler97(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler98(a, b, c);
public @Handler98(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

forward @Handler99(a, b, c);
public @Handler99(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

Setup() {
    pawn_register_callback("OnBench", "@Handler0");
    pawn_register_callback("OnBench", "@Handler1");
    pawn_register_callback("OnBench", "@Handler2");
    pawn_register_callback("OnBench", "@Handler3");
    pawn_register_callback("OnBench", "@Handler4");
    pawn_register_callback("OnBench", "@Handler5");
    pawn_register_callback("OnBench", "@Handler6");
    pawn_register_callback("OnBench", "@Handler7");
    pawn_register_callback("OnBench", "@Handler8");
    pawn_register_callback("OnBench", "@Handler9");
    pawn_register_callback("OnBench", "@Handler10");
    pawn_register_callback("OnBench", "@Handler11");
    pawn_register_callback("OnBench", "@Handler12");
    pawn_register_callback("OnBench", "@Handler13");
    pawn_register_callback("OnBench", "@Handler14");
    pawn_register_callback("OnBench", "@Handler15");
    pawn_register_callback("OnBench", "@Handler16");
    pawn_register_callback("OnBench", "@Handler17");
    pawn_register_callback("OnBench", "@Handler18");
    pawn_register_callback("OnBench", "@Handler19");
    pawn_register_callback("OnBench", "@Handler20");
    pawn_register_callback("OnBench", "@Handler21");
    pawn_register_callback("OnBench", "@Handler22");
    pawn_register_callback("OnBench", "@Handler23");
    pawn_register_callback("OnBench", "@Handler24");
    pawn_register_callback("OnBench", "@Handler25");
    pawn_register_callback("OnBench", "@Handler26");
    pawn_register_callback("OnBench", "@Handler27");
    pawn_register_callback("OnBench", "@Handler28");
    pawn_register_callback("OnBench", "@Handler29");
    pawn_register_callback("OnBench", "@Handler30");
    pawn_register_callback("OnBench", "@Handler31");
    pawn_register_callback("OnBench", "@Handler32");
    pawn_register_callback("OnBench", "@Handler33");
    pawn_register_callback("OnBench", "@Handler34");
    pawn_register_callback("OnBench", "@Handler35");
    pawn_register_callback("OnBench", "@Handler36");
    pawn_register_callback("OnBench", "@Handler37");
    pawn_register_callback("OnBench", "@Handler38");
    pawn_register_callback("OnBench", "@Handler39");
    pawn_register_callback("OnBench", "@Handler40");
    pawn_register_callback("OnBench", "@Handler41");
    pawn_register_callback("OnBench", "@Handler42");
    pawn_register_callback("OnBench", "@Handler43");
    pawn_register_callback("OnBench", "@Handler44");
    pawn_register_callback("OnBench", "@Handler45");
    pawn_register_callback("OnBench", "@Handler46");
    pawn_register_callback("OnBench", "@Handler47");
    pawn_register_callback("OnBench", "@Handler48");
    pawn_register_callback("OnBench", "@Handler49");
    pawn_register_callback("OnBench", "@Handler50");
    pawn_register_callback("OnBench", "@Handler51");
    pawn_register_callback("OnBench", "@Handler52");
    pawn_register_callback("OnBench", "@Handler53");
    pawn_register_callback("OnBench", "@Handler54");
    pawn_register_callback("OnBench", "@Handler55");
    pawn_register_callback("OnBench", "@Handler56");
    pawn_register_callback("OnBench", "@Handler57");
    pawn_register_callback("OnBench", "@Handler58");
    pawn_register_callback("OnBench", "@Handler59");
    pawn_register_callback("OnBench", "@Handler60");
    pawn_register_callback("OnBench", "@Handler61");
    pawn_register_callback("OnBench", "@Handler62");
    pawn_register_callback("OnBench", "@Handler63");
    pawn_register_callback("OnBench", "@Handler64");
    pawn_register_callback("OnBench", "@Handler65");
    pawn_register_callback("OnBench", "@Handler66");
    pawn_register_callback("OnBench", "@Handler67");
    pawn_register_callback("OnBench", "@Handler68");
    pawn_register_callback("OnBench", "@Handler69");
    pawn_register_callback("OnBench", "@Handler70");
    pawn_register_callback("OnBench", "@Handler71");
    pawn_register_callback("OnBench", "@Handler72");
    pawn_register_callback("OnBench", "@Handler73");
    pawn_register_callback("OnBench", "@Handler74");
    pawn_register_callback("OnBench", "@Handler75");
    pawn_register_callback("OnBench", "@Handler76");
    pawn_register_callback("OnBench", "@Handler77");
    pawn_register_callback("OnBench", "@Handler78");
    pawn_register_callback("OnBench", "@Handler79");
    pawn_register_callback("OnBench", "@Handler80");
    pawn_register_callback("OnBench", "@Handler81");
    pawn_register_callback("OnBench", "@Handler82");
    pawn_register_callback("OnBench", "@Handler83");
    pawn_register_callback("OnBench", "@Handler84");
    pawn_register_callback("OnBench", "@Handler85");
    pawn_register_callback("OnBench", "@Handler86");
    pawn_register_callback("OnBench", "@Handler87");
    pawn_register_callback("OnBench", "@Handler88");
    pawn_register_callback("OnBench", "@Handler89");
    pawn_register_callback("OnBench", "@Handler90");
    pawn_register_callback("OnBench", "@Handler91");
    pawn_register_callback("OnBench", "@Handler92");
    pawn_register_callback("OnBench", "@Handler93");
    pawn_register_callback("OnBench", "@Handler94");
    pawn_register_callback("OnBench", "@Handler95");
    pawn_register_callback("OnBench", "@Handler96");
    pawn_register_callback("OnBench", "@Handler97");
    pawn_register_callback("OnBench", "@Handler98");
    pawn_register_callback("OnBench", "@Handler99");
}

Run() {
    gHits = 0;
    CallLocalFunction("OnBench", "iii", 1, 2, 3);
    Bench_Check("hooks run", gHits, HOOKS + 1);

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            CallLocalFunction("OnBench", "iii", i, 2, 3);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("hooks", "callback with 100 hooks");
}

First() {
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
