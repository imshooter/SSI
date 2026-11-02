#define BENCH_SIDE "YSI"

#include <open.mp>
#define _FOREACH_NO_TEST
#include <YSI_Data\y_iterate>
#include "bench.inc"

new
    Iterator:Pool<100000>,
    Iterator:Set<100000>
;

Setup() {
    for (new i; i != 99000; ++i) {
        Iter_Alloc(Pool);
    }

    for (new i; i < 100000; i += 2) {
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

    Bench_End("collection", "take and give back an id, 99000 of 100000 used");
    Bench_Check("ids used", Iter_Count(Pool), 99000);

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            if (Iter_Contains(Pool, j)) {
                ++gBenchSink;
            }

            if (++j == 100000) {
                j = 0;
            }
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("collection", "contains, 100000 ids");

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            Iter_Remove(Set, j);
            Iter_Add(Set, j);

            if ((j += 2) >= 100000) {
                j = 0;
            }
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("collection", "remove and add a value, 100000 values");

    Bench_Begin();

    do {
        foreach (new k : Pool) {
            gBenchSink += k;
        }
    } while (Bench_Next(1));

    Bench_End("collection", "walk, per id, 99000 ids", 99000);
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
