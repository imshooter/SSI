#define BENCH_SIDE "YSI"

#include <open.mp>
#define _FOREACH_NO_TEST
#include <YSI_Data\y_bit>
#include <YSI_Data\y_iterate>
#include "bench.inc"

new
    BitArray:Sparse<1024>,
    BitArray:Dense<1024>,
    BitArray:Work<1024>
;

Setup() {
    for (new i; i < 1024; i += 1024 / 64) {
        Bit_Let(Sparse, i);
    }

    for (new i; i != 1024; i += 2) {
        Bit_Let(Dense, i);
    }
}

Run() {
    new
        j
    ;

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            if (Bit_Get(Dense, j)) {
                ++gBenchSink;
            }

            j = (j + 1) & 1023;
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("bits", "test a bit");

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            Bit_Let(Work, j);
            Bit_Vet(Work, j);
            j = (j + 1) & 1023;
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("bits", "turn a bit on and off");

    Bench_Begin();

    do {
        gBenchSink += Bit_Count(Sparse);
    } while (Bench_Next(1));

    Bench_End("bits", "count, 1024 bits");

    Bench_Begin();

    do {
        foreach (new bit : Bits(Sparse)) {
            gBenchSink += bit;
        }
    } while (Bench_Next(1));

    Bench_End("bits", "walk 64 bits on of 1024");

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
