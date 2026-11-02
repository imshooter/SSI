#define BENCH_SIDE "PawnPlus"

#include <open.mp>
#include <PawnPlus>
#include "bench.inc"

new
    Pool:gPool,
    Pool:gSet
;

Setup() {
    gPool = pool_new(4096);
    gSet = pool_new(4096);

    for (new i; i != 2048; ++i) {
        pool_add(gPool, 0);
    }

    for (new i; i < 4096; ++i) {
        if (i & 1) {
            pool_add(gSet, 0);
        } else {
            pool_add(gSet, 1);
        }
    }

    for (new i = 1; i < 4096; i += 2) {
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

    Bench_End("collection", "take and give back an id, 2048 of 4096 used");
    Bench_Check("ids used", pool_size(gPool), 2048);

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            if (pool_has(gPool, j)) {
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
            pool_remove(gSet, j);
            pool_set(gSet, j, 1);

            if ((j += 2) >= 4096) {
                j = 0;
            }
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("collection", "remove and add a value, 4096 values");

    Bench_Begin();

    do {
        for (new Iter:it = pool_iter(gPool); iter_inside(it); iter_move_next(it)) {
            gBenchSink += iter_get_key(it);
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
