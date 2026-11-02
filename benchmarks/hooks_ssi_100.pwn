#define BENCH_SIDE "SSI"

#include <open.mp>
#include <SSI\hooks>
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

hook OnBench@0(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@1(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@2(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@3(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@4(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@5(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@6(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@7(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@8(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@9(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@10(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@11(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@12(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@13(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@14(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@15(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@16(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@17(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@18(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@19(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@20(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@21(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@22(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@23(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@24(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@25(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@26(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@27(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@28(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@29(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@30(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@31(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@32(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@33(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@34(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@35(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@36(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@37(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@38(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@39(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@40(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@41(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@42(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@43(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@44(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@45(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@46(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@47(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@48(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@49(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@50(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@51(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@52(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@53(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@54(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@55(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@56(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@57(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@58(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@59(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@60(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@61(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@62(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@63(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@64(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@65(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@66(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@67(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@68(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@69(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@70(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@71(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@72(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@73(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@74(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@75(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@76(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@77(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@78(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@79(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@80(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@81(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@82(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@83(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@84(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@85(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@86(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@87(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@88(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@89(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@90(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@91(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@92(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@93(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@94(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@95(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@96(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@97(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@98(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

hook OnBench@99(a, b, c) {
    gBenchSink += b;
    ++gHits;

    return 0;
}

Setup() {
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
