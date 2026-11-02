#define BENCH_SIDE "YSI"

#include <open.mp>
#define _FOREACH_NO_TEST
#include <YSI_Data\y_iterate>
#include "bench.inc"

new
    Iterator:Pool<4096>,
    Iterator:Set<4096>
;

Setup() {
    for (new i; i != 2048; ++i) {
        Iter_Alloc(Pool);
    }

    for (new i; i < 4096; i += 2) {
        Iter_Add(Set, i);
    }
}

Run() {
    new
        j,
        id
    ;

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            id = Iter_Alloc(Pool);
            Iter_Remove(Pool, id);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("collection", "take and give back an id, 2048 of 4096 used");
    Bench_Check("ids used", Iter_Count(Pool), 2048);

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            if (Iter_Contains(Pool, j)) {
                ++gBenchSink;
            }

            if (++j == 4096) {
                j = 0;
            }
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("collection", "contains, 4096 ids");

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            Iter_Remove(Set, j);
            Iter_Add(Set, j);

            if ((j += 2) >= 4096) {
                j = 0;
            }
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("collection", "remove and add a value, 4096 values");

    Bench_Begin();

    do {
        foreach (new k : Pool) {
            gBenchSink += k;
        }
    } while (Bench_Next(1));

    Bench_End("collection", "walk, per id, 2048 ids", 2048);
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
