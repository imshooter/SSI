#define BENCH_SIDE "SSI"

#include <open.mp>
#include <SSI\collection>
#include "bench.inc"

new
    Collection:Pool<4096>,
    Collection:Set<4096>
;

#define Pool: _:
#define Set: _:

Setup() {
    for (new i; i != 2048; ++i) {
        Collection_Alloc(Pool);
    }

    for (new i; i < 4096; i += 2) {
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

    Bench_End("collection", "take and give back an id, 2048 of 4096 used");
    Bench_Check("ids used", Collection_Count(Pool), 2048);

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            if (Collection_Contains(Pool, j)) {
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
            Collection_Remove(Set, j);
            Collection_Add(Set, j);

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
