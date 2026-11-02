#define BENCH_SIDE "SSI"

#include <open.mp>
#include <SSI\collection>
#include "bench.inc"

new
    Collection:Pool<100000>,
    Collection:Set<100000>
;

#define Pool: _:
#define Set: _:

Setup() {
    for (new i; i != 99000; ++i) {
        Collection_Alloc(Pool);
    }

    for (new i; i < 100000; i += 2) {
        Collection_Add(Set, i);
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
            id = Collection_Alloc(Pool);
            Collection_Remove(Pool, id);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("collection", "take and give back an id, 99000 of 100000 used");
    Bench_Check("ids used", Collection_Count(Pool), 99000);

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            if (Collection_Contains(Pool, j)) {
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
            Collection_Remove(Set, j);
            Collection_Add(Set, j);

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
