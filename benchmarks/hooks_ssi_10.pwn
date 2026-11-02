#define BENCH_SIDE "SSI"

#include <open.mp>
#include <SSI\hooks>
#include "bench.inc"

#define HOOKS (10)

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

    Bench_End("hooks", "callback with 10 hooks");
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
