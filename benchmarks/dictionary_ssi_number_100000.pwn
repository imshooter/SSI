#define BENCH_SIDE "SSI"

#include <open.mp>
#include <SSI\dictionary>
#include "bench.inc"

new
    Dictionary:Numbers<100000>
;

Setup() {
}

Run() {
    new
        value,
        fill,
        remove,
        rounds,
        start
    ;

    do {
        start = GetTickCount();

        for (new i; i != 100000; ++i) {
            Dictionary_Set(Numbers, i * 15838, i);
        }

        fill += GetTickCount() - start;
        Bench_Check("keys", Dictionary_Count(Numbers), 100000);

        start = GetTickCount();

        for (new i; i != 100000; ++i) {
            Dictionary_Remove(Numbers, i * 15838);
        }

        remove += GetTickCount() - start;
        ++rounds;
    } while (fill + remove < BENCH_TIME);

    Bench_Report("dictionary", "insert, 100000 number keys", fill, rounds * 100000);
    Bench_Report("dictionary", "remove, 100000 number keys", remove, rounds * 100000);

    for (new i; i != 100000; ++i) {
        Dictionary_Set(Numbers, i * 15838, i);
    }

    Bench_Begin();

    do {
        for (new i; i != 100000; ++i) {
            Dictionary_Get(Numbers, i * 15838, value);
        }
    } while (Bench_Next(100000));

    Bench_End("dictionary", "get, 100000 number keys");

    Bench_Begin();

    do {
        for (new i; i != 100000; ++i) {
            if (Dictionary_Contains(Numbers, i * 15838 + 1)) {
                ++value;
            }
        }
    } while (Bench_Next(100000));

    Bench_End("dictionary", "missing key, 100000 number keys");

    Bench_Begin();

    do {
        for (new i; i != 100000; ++i) {
            Dictionary_Set(Numbers, i * 15838, i);
        }
    } while (Bench_Next(100000));

    Bench_End("dictionary", "set a key that is there, 100000 number keys");

    for (new i; i != 100000; ++i) {
        Dictionary_Remove(Numbers, i * 15838);
    }

    gBenchSink += value;
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
