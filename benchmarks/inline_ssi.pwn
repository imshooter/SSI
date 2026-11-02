#define BENCH_SIDE "SSI"

#include <open.mp>
#include <SSI\inline>
#include "bench.inc"

new
    gHits,
    Inline:gKept
;

stock CallNow(Inline:callback) {
    return @once.callback();
}

stock Keep(Inline:callback) {
    gKept = callback;
}

Setup() {
}

CaptureNow() {
    new
        value = 3
    ;

    inline Bump() {
        gBenchSink += value;
        ++gHits;
    }

    CallNow(using inline Bump);
}

CaptureKept() {
    new
        value = 3
    ;

    inline Bump() {
        gBenchSink += value;
        ++gHits;
    }

    Keep(using inline Bump);
}

CaptureWide() {
    new
        a0 = 1, a1, a2, a3, a4, a5, a6, a7, a8, a9,
        b0, b1, b2, b3, b4, b5, b6, b7, b8, b9,
        c0, c1, c2, c3, c4, c5, c6, c7, c8, c9,
        d0, d1
    ;

    inline AddAll() {
        gBenchSink += a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9;
        gBenchSink += b0 + b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8 + b9;
        gBenchSink += c0 + c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8 + c9;
        gBenchSink += d0 + d1;
        ++gHits;
    }

    CallNow(using inline AddAll);
}

Run() {
    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            CaptureNow();
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("inline", "capture and call at once");
    Bench_Check("inline calls", gHits, gBenchOps);

    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            CaptureKept();
            @once.gKept();
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("inline", "capture, keep, call later and free");
    Bench_Check("kept inline calls", gHits, gBenchOps);

    CaptureKept();
    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            @.gKept();
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("inline", "call a kept inline again");
    Bench_Check("repeated inline calls", gHits, gBenchOps);
    Inline_Free(gKept);

    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            CaptureWide();
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("inline", "capture 32 locals and call at once");
    Bench_Check("wide inline calls", gHits, gBenchOps);
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
