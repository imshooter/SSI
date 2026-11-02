#define BENCH_SIDE "PawnPlus"

#include <open.mp>
#include <PawnPlus>
#include "bench.inc"

new
    Pool:gPool,
    Pool:gSet
;

Setup() {
    gPool = pool_new(100000);
    gSet = pool_new(100000);

    for (new i; i != 99000; ++i) {
        pool_add(gPool, 0);
    }

    for (new i; i < 100000; ++i) {
        if (i & 1) {
            pool_add(gSet, 0);
        } else {
            pool_add(gSet, 1);
        }
    }

    for (new i = 1; i < 100000; i += 2) {
        pool_remove(gSet, i);
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
            id = pool_add(gPool, 0);
            pool_remove(gPool, id);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("collection", "take and give back an id, 99000 of 100000 used");
    Bench_Check("ids used", pool_size(gPool), 99000);

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            if (pool_has(gPool, j)) {
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
            pool_remove(gSet, j);
            pool_set(gSet, j, 1);

            if ((j += 2) >= 100000) {
                j = 0;
            }
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("collection", "remove and add a value, 100000 values");

    Bench_Begin();

    do {
        for (new Iter:it = pool_iter(gPool); iter_inside(it); iter_move_next(it)) {
            gBenchSink += iter_get_key(it);
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
