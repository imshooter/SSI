#if defined _INC_BENCH
    #endinput
#endif
#define _INC_BENCH

/**
 * Timing for the benchmarks. Each measurement repeats its loop until
 * `BENCH_TIME` milliseconds have passed and prints the time of one operation
 * in nanoseconds, without the cost of an empty loop:
 *
 *     [bench] SSI|collection|contains, 4096 ids|12.34
 *
 * Every benchmark runs once without printing, so the code it rewrites at run
 * time is in place, then `BENCH_ROUNDS` times, each round in its own timer
 * call. It then prints `[bench] DONE` and closes the server.
 */

#if !defined BENCH_TIME
    #define BENCH_TIME (250)
#endif

#if !defined BENCH_ROUNDS
    #define BENCH_ROUNDS (5)
#endif

#define BENCH_BATCH (1000)

new
    gBenchSink,
    gBenchStart,
    gBenchOps,
    gBenchRound,
    bool:gBenchQuiet,
    Float:gBenchLoop
;

/**
 * @brief      Start a measurement.
 */
stock Bench_Begin() {
    gBenchOps = 0;
    gBenchStart = GetTickCount();
}

/**
 * @brief      Count the operations of one pass of a loop.
 *
 * @param      ops   The operations the pass made.
 *
 * @return     - `true` the loop goes on
 *             - `false` the time is up
 */
stock bool:Bench_Next(ops) {
    gBenchOps += ops;

    return GetTickCount() - gBenchStart < BENCH_TIME;
}

/**
 * @brief      Print the time of one operation.
 *
 * @param      area    The library measured.
 * @param      name    The operation.
 * @param      ms      The time of every operation.
 * @param      ops     The operations.
 * @param      loop    Whether to take away the cost of an empty loop.
 */
stock Bench_Report(const area[], const name[], ms, ops, bool:loop = true) {
    if (gBenchQuiet) {
        return;
    }

    new
        Float:ns = float(ms) * 1000000.0 / float(ops)
    ;

    if (loop) {
        ns -= gBenchLoop;
    }

    printf("[bench] %s|%s|%s|%.2f", BENCH_SIDE, area, name, ns);
}

/**
 * @brief      End a measurement started with `Bench_Begin` and print it.
 *
 * @param      area    The library measured.
 * @param      name    The operation.
 * @param      unit    Operations in each counted one, as the elements of a walk.
 */
stock Bench_End(const area[], const name[], unit = 1) {
    Bench_Report(area, name, GetTickCount() - gBenchStart, gBenchOps * unit, unit == 1);
}

/**
 * @brief      Print a check that failed, so a library cannot win by doing less.
 *
 * @param      name    The check.
 * @param      got     The value found.
 * @param      want    The value expected.
 */
stock Bench_Check(const name[], got, want) {
    if (got != want) {
        printf("[bench] CHECK %s|%s got %d, want %d", BENCH_SIDE, name, got, want);
    }
}

/**
 * @brief      Measure an empty loop, taken away from every operation.
 */
stock Bench_Calibrate() {
    gBenchLoop = 0.0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
        }
    } while (Bench_Next(BENCH_BATCH));

    gBenchLoop = float(GetTickCount() - gBenchStart) * 1000000.0 / float(gBenchOps);
}

/**
 * @brief      Print the end of the run and close the server.
 */
stock Bench_Done() {
    printf("[bench] DONE %d", gBenchSink & 1);
    SendRconCommand("exit");
}
