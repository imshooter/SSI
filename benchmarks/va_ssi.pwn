#define BENCH_SIDE "SSI"

#include <open.mp>
#include <SSI\va>
#include "bench.inc"

new
    gOutput[256]
;

stock Wrap(output[], size, const text[], OPEN_MP_TAGS:...) {
    return format(output, size, text, ___(3));
}

Setup() {
}

Run() {
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            format(gOutput, sizeof (gOutput), "%i %i %i", i, 2, 3);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("va", "format, 3 values, called directly");

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            Wrap(gOutput, sizeof (gOutput), "%i %i %i", i, 2, 3);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("va", "format, 3 values, through a wrapper");

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            format(gOutput, sizeof (gOutput), "%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i", i, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("va", "format, 16 values, called directly");

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            Wrap(gOutput, sizeof (gOutput), "%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i", i, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("va", "format, 16 values, through a wrapper");

    Bench_Check("wrapped text", strlen(gOutput) > 30, 1);
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
