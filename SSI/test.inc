#if defined _INC_SSI_TEST
    #endinput
#endif
#define _INC_SSI_TEST

#if defined _INC_y_testing
    #error SSI\test is not compatible with y_testing
#endif

#include <SSI\amx>
#include <SSI\hooks>

/**
 * Tests, as in y_testing: functions declared with `test` that the script runs
 * one after another when it starts, with checks that print what failed and
 * where. They are compiled only when `SSI_TESTS` is defined, so a script keeps
 * its tests next to its code at no cost.
 *
 *     #define SSI_TESTS
 *     #include <SSI\test>
 *
 *     test BusinessPrice() {
 *         new const
 *             Business:businessid = CreateBusiness("Burger Shot", 2500)
 *         ;
 *
 *         ASSERT(IsValidBusiness(businessid));
 *         ASSERT_EQ(GetBusinessPrice(businessid), 2500);
 *     }
 *
 * The tests run in the order they were declared, from a timer that
 * `OnGameModeInit` starts, or `OnFilterScriptInit` in a filterscript, so the
 * script is ready when they run. Every failed check prints the test, the line,
 * the check as written and the values it compared:
 *
 *     [test] FAIL BusinessPrice line 12: ASSERT_EQ(GetBusinessPrice(businessid), 2500) got 0, want 2500
 *
 * The text of a check is made by the compiler, so a string in a check with a
 * bracket and no pair, as `"a(b"`, does not compile. Such a string goes in a
 * variable first.
 *
 * A test stopped by a run time error fails, and the next one runs. At the end
 * the script prints the tests, the checks and the failures, raises
 * `OnTestsFinished` and, with `SSI_TEST_EXIT` defined, closes the server.
 *
 * A test that waits for the server, as for a bot to connect or a timer to fire,
 * calls `Test_Async` and then `Test_Done` once it saw what it waited for. The
 * next test runs after that, and the checks made in between count for it:
 *
 *     test BotConnects() {
 *         Test_Async(3000);
 *         gBot = NPC_Create("Bot");
 *     }
 *
 *     hook OnPlayerConnect(playerid) {
 *         if (playerid == gBot) {
 *             ASSERT(IsPlayerNPC(playerid));
 *             Test_Done();
 *         }
 *
 *         return 1;
 *     }
 *
 * `Test_Log` writes numbers down in the order they come, and `ASSERT_LOG`
 * checks that order, as for the hooks of a callback. Each test starts with an
 * empty log.
 *
 * - `SSI_TESTS` compiles and runs the tests.
 * - `SSI_TEST_ONLY` runs only the tests whose names start with it:
 *   `#define SSI_TEST_ONLY "Business"`.
 * - `SSI_TEST_EXIT` closes the server when the tests end.
 * - `SSI_TEST_VERBOSE` prints a line when each test starts and ends.
 */

/**
 * # Header
 */

#if !defined SSI_TEST_MAX
    #define SSI_TEST_MAX (512)
#endif

#if !defined SSI_TEST_LOG
    #define SSI_TEST_LOG (128)
#endif

#if !defined SSI_TEST_TIMEOUT
    #define SSI_TEST_TIMEOUT (5000)
#endif

/**
 * Holds what a check got, from the statement that reads it to the one that
 * compares it, so the value is read once.
 */
stock
    SSI@testGot
;

/**
 * Always `0`, as the condition of the loop around a check and of the branch
 * that only exists for the compiler to check the tags. A constant there would
 * be a warning.
 */
stock
    SSI@testNever
;

/**
 * # Functions
 */

/**
 * @brief      Declare a test: a function the script runs when it starts, if
 *             `SSI_TESTS` is defined.
 *
 *     test SpawnsAtHome() {
 *         ASSERT(IsPlayerAtHome(gBot));
 *     }
 *
 * Without `SSI_TESTS` the test is a function nothing calls, so it takes no
 * space.
 */
#if defined SSI_TESTS
    #define test%9\32;%0() forward @Ts_%0();@Ts_%0(){SSI@Te_%0();return 1;}SSI@Te_%0()
#else
    #define test%9\32;%0() static stock SSI@Te_%0()
#endif

/**
 * @brief      Check that a condition holds.
 *
 * @param      condition  What must be true.
 */
forward ASSERT(bool:condition);
#define ASSERT(%0) SSI@Test_Check(!!(%0),__line,SSI@TEST_TEXT(ASSERT\40;%0\41;))

/**
 * @brief      Check that a condition does not hold.
 *
 * @param      condition  What must be false.
 */
forward ASSERT_FALSE(bool:condition);
#define ASSERT_FALSE(%0) SSI@Test_Check(!(%0),__line,SSI@TEST_TEXT(ASSERT_FALSE\40;%0\41;))

/**
 * @brief      Check that a value equals another.
 *
 * Both take the same tag, or the compiler warns. A `Float:` compares as a
 * float and prints as one, a `bool:` prints as `true` or `false`, and any other
 * tag prints as a number. `got` is read once. `want` is read once at run time.
 *
 * @param      got   The value the code gave.
 * @param      want  The value it should give.
 */
forward ASSERT_EQ(got, want);
#define ASSERT_EQ(%0,%1) SSI@TEST_COMPARE((%0),(%1),0,SSI@TEST_TEXT(ASSERT_EQ\40;%0,%1\41;))

/**
 * @brief      Check that a value differs from another.
 *
 * @param      got   The value the code gave.
 * @param      want  The value it should not give.
 */
forward ASSERT_NE(got, want);
#define ASSERT_NE(%0,%1) SSI@TEST_COMPARE((%0),(%1),1,SSI@TEST_TEXT(ASSERT_NE\40;%0,%1\41;))

/**
 * @brief      Check that a value is below another.
 *
 * @param      got   The value the code gave.
 * @param      want  The value it should stay below.
 */
forward ASSERT_LT(got, want);
#define ASSERT_LT(%0,%1) SSI@TEST_COMPARE((%0),(%1),2,SSI@TEST_TEXT(ASSERT_LT\40;%0,%1\41;))

/**
 * @brief      Check that a value is not above another.
 *
 * @param      got   The value the code gave.
 * @param      want  The value it should not pass.
 */
forward ASSERT_LE(got, want);
#define ASSERT_LE(%0,%1) SSI@TEST_COMPARE((%0),(%1),3,SSI@TEST_TEXT(ASSERT_LE\40;%0,%1\41;))

/**
 * @brief      Check that a value is above another.
 *
 * @param      got   The value the code gave.
 * @param      want  The value it should pass.
 */
forward ASSERT_GT(got, want);
#define ASSERT_GT(%0,%1) SSI@TEST_COMPARE((%0),(%1),4,SSI@TEST_TEXT(ASSERT_GT\40;%0,%1\41;))

/**
 * @brief      Check that a value is not below another.
 *
 * @param      got   The value the code gave.
 * @param      want  The value it should reach.
 */
forward ASSERT_GE(got, want);
#define ASSERT_GE(%0,%1) SSI@TEST_COMPARE((%0),(%1),5,SSI@TEST_TEXT(ASSERT_GE\40;%0,%1\41;))

/**
 * @brief      Check that a float is within a range of another.
 *
 * @param      got    The value the code gave.
 * @param      want   The value it should be close to.
 * @param      range  How far from `want` it may be.
 */
forward ASSERT_NEAR(Float:got, Float:want, Float:range);
#define ASSERT_NEAR(%0,%1,%2) SSI@Test_Near((%0),(%1),(%2),__line,SSI@TEST_TEXT(ASSERT_NEAR\40;%0,%1,%2\41;))

/**
 * @brief      Check that a string equals another, packed or not.
 *
 * @param      got   The string the code gave.
 * @param      want  The string it should give.
 */
forward ASSERT_SAME(const got[], const want[]);
#define ASSERT_SAME(%0,%1) SSI@Test_Same(%0,%1,true,__line,SSI@TEST_TEXT(ASSERT_SAME\40;%0,%1\41;))

/**
 * @brief      Check that a string differs from another, packed or not.
 *
 * @param      got   The string the code gave.
 * @param      want  The string it should not give.
 */
forward ASSERT_DIFF(const got[], const want[]);
#define ASSERT_DIFF(%0,%1) SSI@Test_Same(%0,%1,false,__line,SSI@TEST_TEXT(ASSERT_DIFF\40;%0,%1\41;))

/**
 * @brief      Check the numbers `Test_Log` wrote down since the test started or
 *             since the last `ASSERT_LOG`, then empty the log.
 *
 *     ASSERT_LOG({1, 2, 3});
 *
 * @param      want  The numbers, in order.
 */
forward ASSERT_LOG(const want[]);
#define ASSERT_LOG(%0) SSI@Test_Log(%0,__line,SSI@TEST_TEXT(ASSERT_LOG\40;%0\41;))

/**
 * @brief      Write a number down in the log of the running test.
 *
 * @param      value  The number.
 */
forward Test_Log(value);

/**
 * @brief      Keep the running test open after it returns, until `Test_Done`
 *             is called.
 *
 * @param      timeout  Milliseconds to wait. The test fails when they pass
 *                      first.
 *
 * @return     - `true` the test waits
 *             - `false` no test is running
 */
forward bool:Test_Async(timeout = SSI_TEST_TIMEOUT);

/**
 * @brief      End the test that `Test_Async` kept open, and run the next one.
 *
 * @return     - `true` the test ended
 *             - `false` no test was waiting
 */
forward bool:Test_Done();

#if defined SSI_TESTS
    /**
     * # Events
     */

    /**
     * @brief      The tests ended.
     *
     * @param      tests   Tests that ran.
     * @param      checks  Checks they made.
     * @param      fails   Checks that failed, tests stopped by a run time
     *                     error and tests that waited too long.
     */
    event OnTestsFinished(tests, checks, fails);
#endif

/**
 * # Internal
 */

#define SSI@TEST_TEXT(%0) _:SSI@TT_P:SSI@TT_B:SSI@TT_Q:SSI@TT_E:```%0```
#define SSI@TT_P:%9```%0(%1)%2``` SSI@TT_P:%9```%0\40;%1\41;%2```
#define SSI@TT_B:%9```%0!%1``` SSI@TT_B:%9```%0\33;%1```
#define SSI@TT_Q:%9```%0"%1"%2``` SSI@TT_Q:%9```%0\34;%1\34;%2```
#define SSI@TT_E:```%0``` "\"%0\""
#define SSI@TEST_COMPARE(%0,%1,%2,%3) do{SSI@testGot=_:(SSI@testNever?%1:%0);__pragma("warning push");__pragma("warning disable 213");SSI@Test_Compare(%1,%2,__line,%3);__pragma("warning pop");}while(SSI@testNever)

native SSI@TestTick() = GetTickCount;

#if defined SSI_TESTS
    forward @SSI_TestStart();
    forward @SSI_TestNext();
    forward @SSI_TestTimeout(at);
#endif

static stock const SSI@testOperator[][] = {
    "",
    "not ",
    "under ",
    "at most ",
    "over ",
    "at least "
};

static stock
    SSI@testPublic[SSI_TEST_MAX],
    SSI@testCount,
    SSI@testAt = -1,
    SSI@testName[64],
    SSI@testRan,
    SSI@testChecks,
    SSI@testFails,
    SSI@testStart,
    SSI@testWait,
    SSI@testTimer,
    bool:SSI@testCalling,
    bool:SSI@testWaiting,
    bool:SSI@testDone,
    SSI@testLog[SSI_TEST_LOG],
    SSI@testLogCount
;

static stock bool:SSI_TestRunningInternal() {
    return (0 <= SSI@testAt < SSI@testCount);
}

static stock SSI_TestFailInternal(line, const text[], const detail[]) {
    new
        check[256]
    ;

    ++SSI@testFails;
    strmid(check, text, 1, strlen(text) - 1);

    if (!SSI_TestRunningInternal()) {
        printf("[test] FAIL line %d: %s%s", line, check, detail);

        return;
    }

    printf("[test] FAIL %s line %d: %s%s", SSI@testName[4], line, check, detail);
}

static stock SSI_TestStopInternal(const reason[]) {
    ++SSI@testFails;

    if (!SSI_TestRunningInternal()) {
        printf("[test] FAIL %s", reason);

        return;
    }

    printf("[test] FAIL %s: %s", SSI@testName[4], reason);
}

static stock SSI_TestValueInternal(output[], value, tag, size = sizeof (output)) {
    if (tag == tagof (Float:)) {
        format(output, size, "%.6f", value);

        return;
    }

    if (tag == tagof (bool:)) {
        format(output, size, "%s", value ? ("true") : ("false"));

        return;
    }

    format(output, size, "%d", value);
}

static stock SSI_TestListInternal(output[], const values[], count, size = sizeof (output)) {
    new
        piece[16]
    ;

    format(output, size, "{");

    for (new i; i != count; ++i) {
        if (i == 16) {
            strcat(output, ", ...", size);

            break;
        }

        format(piece, sizeof (piece), i == 0 ? ("%d") : (", %d"), values[i]);
        strcat(output, piece, size);
    }

    strcat(output, "}", size);
}

static stock bool:SSI_TestPrefixInternal(name, const prefix[], offset) {
    for (new i; prefix[i] != EOS; ++i) {
        if (SSI@Amx_ReadByte(name + offset + i) != prefix[i]) {
            return false;
        }
    }

    return true;
}

static stock SSI_TestEntryInternal(index) {
    return SSI@amxBase + SSI@Amx_Header(32) + index * ((SSI@Amx_Header(8) >>> 16) & 0xFFFF);
}

static stock SSI_TestCollectInternal() {
    new const
        count = (SSI@Amx_Header(36) - SSI@Amx_Header(32)) / ((SSI@Amx_Header(8) >>> 16) & 0xFFFF)
    ;

    new
        skipped
    ;

    for (new i; i != count; ++i) {
        new const
            name = SSI@amxBase + SSI@Amx_Read(SSI_TestEntryInternal(i) + 4)
        ;

        if (!SSI_TestPrefixInternal(name, "@Ts_", 0)) {
            continue;
        }

        #if defined SSI_TEST_ONLY
            if (!SSI_TestPrefixInternal(name, SSI_TEST_ONLY, 4)) {
                continue;
            }
        #endif

        if (SSI@testCount == SSI_TEST_MAX) {
            ++skipped;

            continue;
        }

        new const
            address = SSI@Amx_Read(SSI_TestEntryInternal(i))
        ;

        new
            k = SSI@testCount++
        ;

        while (k != 0 && SSI@Amx_Read(SSI_TestEntryInternal(SSI@testPublic[k - 1])) > address) {
            SSI@testPublic[k] = SSI@testPublic[--k];
        }

        SSI@testPublic[k] = i;
    }

    if (skipped != 0) {
        new
            detail[48]
        ;

        format(detail, sizeof (detail), "%d tests past SSI_TEST_MAX did not run", skipped);
        SSI_TestStopInternal(detail);
    }
}

static stock SSI_TestNameInternal(index) {
    new const
        name = SSI@amxBase + SSI@Amx_Read(SSI_TestEntryInternal(index) + 4)
    ;

    for (new i; i != sizeof (SSI@testName) - 1; ++i) {
        if ((SSI@testName[i] = SSI@Amx_ReadByte(name + i)) == EOS) {
            return;
        }
    }

    SSI@testName[sizeof (SSI@testName) - 1] = EOS;
}

static stock SSI_TestEndInternal() {
    SSI@testWaiting = false;

    #if defined SSI_TEST_VERBOSE
        printf("[test] END %s", SSI@testName[4]);
    #endif
}

static stock SSI_TestFinishInternal() {
    printf("[test] DONE tests %d checks %d fails %d in %d ms", SSI@testRan, SSI@testChecks, SSI@testFails, SSI@TestTick() - SSI@testStart);

    #if defined SSI_TESTS
        call OnTestsFinished(SSI@testRan, SSI@testChecks, SSI@testFails);
    #endif

    #if defined SSI_TEST_EXIT
        SendRconCommand("exit");
    #endif
}

static stock SSI_TestRunInternal() {
    while (++SSI@testAt < SSI@testCount) {
        SSI_TestNameInternal(SSI@testPublic[SSI@testAt]);

        SSI@testLogCount = 0;
        SSI@testWaiting = false;
        SSI@testDone = false;
        ++SSI@testRan;

        #if defined SSI_TEST_VERBOSE
            printf("[test] RUN %s", SSI@testName[4]);
        #endif

        SSI@testCalling = true;

        new const
            returned = CallLocalFunction(SSI@testName, "")
        ;

        SSI@testCalling = false;

        if (!returned) {
            SSI_TestStopInternal("stopped by a run time error");
            SSI_TestEndInternal();

            continue;
        }

        if (SSI@testWaiting && !SSI@testDone) {
            SSI@testTimer = SetTimerEx("@SSI_TestTimeout", SSI@testWait, false, "i", SSI@testAt);

            return;
        }

        SSI_TestEndInternal();
    }

    SSI_TestFinishInternal();
}

/**
 * # Checks
 */

stock SSI@Test_Check(bool:ok, line, const text[]) {
    ++SSI@testChecks;

    if (ok) {
        return;
    }

    SSI_TestFailInternal(line, text, "");
}

stock SSI@Test_Compare({_, Float, bool}:want, comparison, line, const text[], tag = tagof (want)) {
    ++SSI@testChecks;

    new
        bool:ok
    ;

    if (tag == tagof (Float:)) {
        new const
            Float:got = Float:SSI@testGot,
            Float:wanted = Float:want
        ;

        switch (comparison) {
            case 0: {
                ok = (got == wanted);
            }
            case 1: {
                ok = (got != wanted);
            }
            case 2: {
                ok = (got < wanted);
            }
            case 3: {
                ok = (got <= wanted);
            }
            case 4: {
                ok = (got > wanted);
            }
            default: {
                ok = (got >= wanted);
            }
        }
    } else {
        switch (comparison) {
            case 0: {
                ok = (SSI@testGot == _:want);
            }
            case 1: {
                ok = (SSI@testGot != _:want);
            }
            case 2: {
                ok = (SSI@testGot < _:want);
            }
            case 3: {
                ok = (SSI@testGot <= _:want);
            }
            case 4: {
                ok = (SSI@testGot > _:want);
            }
            default: {
                ok = (SSI@testGot >= _:want);
            }
        }
    }

    if (ok) {
        return;
    }

    new
        got[24],
        wanted[24],
        detail[80]
    ;

    SSI_TestValueInternal(got, SSI@testGot, tag);
    SSI_TestValueInternal(wanted, _:want, tag);
    format(detail, sizeof (detail), " got %s, want %s%s", got, SSI@testOperator[comparison], wanted);
    SSI_TestFailInternal(line, text, detail);
}

stock SSI@Test_Near(Float:got, Float:want, Float:range, line, const text[]) {
    ++SSI@testChecks;

    if (floatabs(got - want) <= range) {
        return;
    }

    new
        detail[96]
    ;

    format(detail, sizeof (detail), " got %.6f, want %.6f within %.6f", got, want, range);
    SSI_TestFailInternal(line, text, detail);
}

stock SSI@Test_Same(const got[], const want[], bool:same, line, const text[]) {
    ++SSI@testChecks;

    new const
        bool:equal = strequal(got, want)
    ;

    if (equal == same) {
        return;
    }

    new
        detail[160]
    ;

    if (same) {
        format(detail, sizeof (detail), " got \"%s\", want \"%s\"", got, want);
    } else {
        format(detail, sizeof (detail), " got \"%s\", want any other text", got);
    }

    SSI_TestFailInternal(line, text, detail);
}

stock SSI@Test_Log(const want[], line, const text[], count = sizeof (want)) {
    ++SSI@testChecks;

    new
        bool:same = (SSI@testLogCount == count && count <= SSI_TEST_LOG)
    ;

    for (new i; same && i != count; ++i) {
        same = (SSI@testLog[i] == want[i]);
    }

    if (!same) {
        new
            got[128],
            wanted[128],
            detail[280]
        ;

        SSI_TestListInternal(got, SSI@testLog, SSI@testLogCount < SSI_TEST_LOG ? SSI@testLogCount : SSI_TEST_LOG);
        SSI_TestListInternal(wanted, want, count);
        format(detail, sizeof (detail), " got %d %s, want %d %s", SSI@testLogCount, got, count, wanted);
        SSI_TestFailInternal(line, text, detail);
    }

    SSI@testLogCount = 0;
}

/**
 * # Tests
 */

stock Test_Log(value) {
    if (SSI@testLogCount < SSI_TEST_LOG) {
        SSI@testLog[SSI@testLogCount] = value;
    }

    ++SSI@testLogCount;
}

stock bool:Test_Async(timeout = SSI_TEST_TIMEOUT) {
    if (!SSI_TestRunningInternal()) {
        return false;
    }

    SSI@testWaiting = true;
    SSI@testWait = timeout;

    return true;
}

stock bool:Test_Done() {
    if (!SSI@testWaiting) {
        return false;
    }

    if (SSI@testDone) {
        return false;
    }

    SSI@testDone = true;

    if (SSI@testCalling) {
        return true;
    }

    KillTimer(SSI@testTimer);
    SetTimer("@SSI_TestNext", 0, false);

    return true;
}

/**
 * # Calls
 */

#if defined SSI_TESTS
    public @SSI_TestStart() {
        SSI@testStart = SSI@TestTick();

        if (!SSI@Amx_Ready()) {
            SSI_TestStopInternal("the code of the script cannot be read");
            SSI_TestFinishInternal();

            return 1;
        }

        SSI_TestCollectInternal();
        SSI_TestRunInternal();

        return 1;
    }

    public @SSI_TestNext() {
        if (!SSI_TestRunningInternal()) {
            return 1;
        }

        if (!SSI@testDone) {
            return 1;
        }

        SSI_TestEndInternal();
        SSI_TestRunInternal();

        return 1;
    }

    public @SSI_TestTimeout(at) {
        if (at != SSI@testAt) {
            return 1;
        }

        if (!SSI@testWaiting) {
            return 1;
        }

        if (SSI@testDone) {
            return 1;
        }

        SSI@testDone = true;

        new
            reason[48]
        ;

        format(reason, sizeof (reason), "no Test_Done in %d ms", SSI@testWait);
        SSI_TestStopInternal(reason);
        SSI_TestEndInternal();
        SSI_TestRunInternal();

        return 1;
    }

    #if defined FILTERSCRIPT
        hook OnFilterScriptInit() {
            SetTimer("@SSI_TestStart", 0, false);

            return 1;
        }
    #else
        hook OnGameModeInit() {
            SetTimer("@SSI_TestStart", 0, false);

            return 1;
        }
    #endif
#endif
