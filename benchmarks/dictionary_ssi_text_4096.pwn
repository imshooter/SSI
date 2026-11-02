#define BENCH_SIDE "SSI"

#include <open.mp>
#include <SSI\dictionary>
#include "bench.inc"

new
    gKey[4096][33],
    gMiss[4096][33]
;

MakeKeys() {
    for (new i; i != sizeof (gKey); ++i) {
        format(gKey[i], sizeof (gKey[]), "account_%08i_character_name", i * 7919);
        format(gMiss[i], sizeof (gMiss[]), "account_%08i_character_other", i * 7919);
    }
}

new
    Dictionary:Names<4096, 32>
;

Setup() {
    MakeKeys();
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

        for (new i; i != 4096; ++i) {
            Dictionary_Set(Names<>, gKey[i], i);
        }

        fill += GetTickCount() - start;
        Bench_Check("keys", Dictionary_Count(Names<>), 4096);

        start = GetTickCount();

        for (new i; i != 4096; ++i) {
            Dictionary_Remove(Names<>, gKey[i]);
        }

        remove += GetTickCount() - start;
        ++rounds;
    } while (fill + remove < BENCH_TIME);

    Bench_Report("dictionary", "insert, 4096 text keys", fill, rounds * 4096);
    Bench_Report("dictionary", "remove, 4096 text keys", remove, rounds * 4096);

    for (new i; i != 4096; ++i) {
        Dictionary_Set(Names<>, gKey[i], i);
    }

    Bench_Begin();

    do {
        for (new i; i != 4096; ++i) {
            Dictionary_Get(Names<>, gKey[i], value);
        }
    } while (Bench_Next(4096));

    Bench_End("dictionary", "get, 4096 text keys");

    Bench_Begin();

    do {
        for (new i; i != 4096; ++i) {
            if (Dictionary_Contains(Names<>, gMiss[i])) {
                ++value;
            }
        }
    } while (Bench_Next(4096));

    Bench_End("dictionary", "missing key, 4096 text keys");

    Bench_Begin();

    do {
        for (new i; i != 4096; ++i) {
            Dictionary_Set(Names<>, gKey[i], i);
        }
    } while (Bench_Next(4096));

    Bench_End("dictionary", "set a key that is there, 4096 text keys");

    for (new i; i != 4096; ++i) {
        Dictionary_Remove(Names<>, gKey[i]);
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
