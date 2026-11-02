#define BENCH_SIDE "SSI"

#include <open.mp>
#include <SSI\bits>
#include "bench.inc"

new
    Bits:Sparse<1048576>,
    Bits:Dense<1024>,
    Bits:Work<1024>
;

Setup() {
    for (new i; i < 1048576; i += 1048576 / 64) {
        Bits_Let(Sparse, i);
    }

    for (new i; i != 1024; i += 2) {
        Bits_Let(Dense, i);
    }
}

Run() {
    new
        j
    ;

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            if (Bits_Test(Dense, j)) {
                ++gBenchSink;
            }

            j = (j + 1) & 1023;
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("bits", "test a bit");

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            Bits_Let(Work, j);
            Bits_Vet(Work, j);
            j = (j + 1) & 1023;
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("bits", "turn a bit on and off");

    Bench_Begin();

    do {
        gBenchSink += Bits_Count(Sparse);
    } while (Bench_Next(1));

    Bench_End("bits", "count, 1048576 bits");

    Bench_Begin();

    do {
        foreach (new bit : Bits(Sparse)) {
            gBenchSink += bit;
        }
    } while (Bench_Next(1));

    Bench_End("bits", "walk 64 bits on of 1048576");

    Bench_Begin();

    do {
        foreach (new bit : Bits(Dense)) {
            gBenchSink += bit;
        }
    } while (Bench_Next(1));

    Bench_End("bits", "walk, per bit, 512 of 1024 on", 512);
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
