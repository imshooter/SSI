#define BENCH_SIDE "PawnPlus"

#include <open.mp>
#include <PawnPlus>
#include "bench.inc"

new
    gKey[20000][33],
    gMiss[20000][33]
;

MakeKeys() {
    for (new i; i != sizeof (gKey); ++i) {
        format(gKey[i], sizeof (gKey[]), "account_%08i_character_name", i * 7919);
        format(gMiss[i], sizeof (gMiss[]), "account_%08i_character_other", i * 7919);
    }
}

new
    Map:gNames
;

Setup() {
    MakeKeys();
    gNames = map_new();
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

        for (new i; i != 20000; ++i) {
            map_str_set(gNames, gKey[i], i);
        }

        fill += GetTickCount() - start;
        Bench_Check("keys", map_size(gNames), 20000);

        start = GetTickCount();

        for (new i; i != 20000; ++i) {
            map_str_remove(gNames, gKey[i]);
        }

        remove += GetTickCount() - start;
        ++rounds;
    } while (fill + remove < BENCH_TIME);

    Bench_Report("dictionary", "insert, 20000 text keys", fill, rounds * 20000);
    Bench_Report("dictionary", "remove, 20000 text keys", remove, rounds * 20000);

    for (new i; i != 20000; ++i) {
        map_str_set(gNames, gKey[i], i);
    }

    Bench_Begin();

    do {
        for (new i; i != 20000; ++i) {
            value += map_str_get(gNames, gKey[i]);
        }
    } while (Bench_Next(20000));

    Bench_End("dictionary", "get, 20000 text keys");

    Bench_Begin();

    do {
        for (new i; i != 20000; ++i) {
            if (map_has_str_key(gNames, gMiss[i])) {
                ++value;
            }
        }
    } while (Bench_Next(20000));

    Bench_End("dictionary", "missing key, 20000 text keys");

    Bench_Begin();

    do {
        for (new i; i != 20000; ++i) {
            map_str_set(gNames, gKey[i], i);
        }
    } while (Bench_Next(20000));

    Bench_End("dictionary", "set a key that is there, 20000 text keys");

    for (new i; i != 20000; ++i) {
        map_str_remove(gNames, gKey[i]);
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
