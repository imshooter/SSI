#define BENCH_SIDE "PawnPlus"

#include <open.mp>
#include <PawnPlus>
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
