# SSI\test

```pawn
#include <SSI\test>
```

## Requirements

- `SSI\amx`
- `SSI\hooks`

## Quick Start

Tests, as in y_testing: functions declared with `test` that the script runs
one after another when it starts, with checks that print what failed and
where. They are compiled only when `SSI_TESTS` is defined, so a script keeps
its tests next to its code at no cost.

```pawn
#define SSI_TESTS
#include <SSI\test>

test BusinessPrice() {
    new const
        Business:businessid = CreateBusiness("Burger Shot", 2500)
    ;

    ASSERT(IsValidBusiness(businessid));
    ASSERT_EQ(GetBusinessPrice(businessid), 2500);
}
```

The tests run in the order they were declared, from a timer that
`OnGameModeInit` starts, or `OnFilterScriptInit` in a filterscript, so the
script is ready when they run. Every failed check prints the test, the line,
the check as written and the values it compared:

```pawn
[test] FAIL BusinessPrice line 12: ASSERT_EQ(GetBusinessPrice(businessid), 2500) got 0, want 2500
```

The text of a check is made by the compiler, so a string in a check with a
bracket and no pair, as `"a(b"`, does not compile. Such a string goes in a
variable first.

A test stopped by a run time error fails, and the next one runs. At the end
the script prints the tests, the checks and the failures, raises
`OnTestsFinished` and, with `SSI_TEST_EXIT` defined, closes the server.

A test that waits for the server, as for a bot to connect or a timer to fire,
calls `Test_Async` and then `Test_Done` once it saw what it waited for. The
next test runs after that, and the checks made in between count for it:

```pawn
test BotConnects() {
    Test_Async(3000);
    gBot = NPC_Create("Bot");
}

hook OnPlayerConnect(playerid) {
    if (playerid == gBot) {
        ASSERT(IsPlayerNPC(playerid));
        Test_Done();
    }

    return 1;
}
```

`Test_Log` writes numbers down in the order they come, and `ASSERT_LOG`
checks that order, as for the hooks of a callback. Each test starts with an
empty log.

- `SSI_TESTS` compiles and runs the tests.
- `SSI_TEST_ONLY` runs only the tests whose names start with it:
  `#define SSI_TEST_ONLY "Business"`.
- `SSI_TEST_EXIT` closes the server when the tests end.
- `SSI_TEST_VERBOSE` prints a line when each test starts and ends.

## API

### `ASSERT`

```pawn
forward ASSERT(bool:condition);
```

Check that a condition holds.

| Parameter | Description |
| --- | --- |
| `condition` | What must be true. |

### `ASSERT_FALSE`

```pawn
forward ASSERT_FALSE(bool:condition);
```

Check that a condition does not hold.

| Parameter | Description |
| --- | --- |
| `condition` | What must be false. |

### `ASSERT_EQ`

```pawn
forward ASSERT_EQ(got, want);
```

Check that a value equals another.

Both take the same tag, or the compiler warns. A `Float:` compares as a
float and prints as one, a `bool:` prints as `true` or `false`, and any other
tag prints as a number. `got` is read once. `want` is read once at run time.

| Parameter | Description |
| --- | --- |
| `got` | The value the code gave. |
| `want` | The value it should give. |

### `ASSERT_NE`

```pawn
forward ASSERT_NE(got, want);
```

Check that a value differs from another.

| Parameter | Description |
| --- | --- |
| `got` | The value the code gave. |
| `want` | The value it should not give. |

### `ASSERT_LT`

```pawn
forward ASSERT_LT(got, want);
```

Check that a value is below another.

| Parameter | Description |
| --- | --- |
| `got` | The value the code gave. |
| `want` | The value it should stay below. |

### `ASSERT_LE`

```pawn
forward ASSERT_LE(got, want);
```

Check that a value is not above another.

| Parameter | Description |
| --- | --- |
| `got` | The value the code gave. |
| `want` | The value it should not pass. |

### `ASSERT_GT`

```pawn
forward ASSERT_GT(got, want);
```

Check that a value is above another.

| Parameter | Description |
| --- | --- |
| `got` | The value the code gave. |
| `want` | The value it should pass. |

### `ASSERT_GE`

```pawn
forward ASSERT_GE(got, want);
```

Check that a value is not below another.

| Parameter | Description |
| --- | --- |
| `got` | The value the code gave. |
| `want` | The value it should reach. |

### `ASSERT_NEAR`

```pawn
forward ASSERT_NEAR(Float:got, Float:want, Float:range);
```

Check that a float is within a range of another.

| Parameter | Description |
| --- | --- |
| `got` | The value the code gave. |
| `want` | The value it should be close to. |
| `range` | How far from `want` it may be. |

### `ASSERT_SAME`

```pawn
forward ASSERT_SAME(const got[], const want[]);
```

Check that a string equals another, packed or not.

| Parameter | Description |
| --- | --- |
| `got` | The string the code gave. |
| `want` | The string it should give. |

### `ASSERT_DIFF`

```pawn
forward ASSERT_DIFF(const got[], const want[]);
```

Check that a string differs from another, packed or not.

| Parameter | Description |
| --- | --- |
| `got` | The string the code gave. |
| `want` | The string it should not give. |

### `ASSERT_LOG`

```pawn
forward ASSERT_LOG(const want[]);
```

Check the numbers `Test_Log` wrote down since the test started or since the last `ASSERT_LOG`, then empty the log.

```pawn
ASSERT_LOG({1, 2, 3});
```

| Parameter | Description |
| --- | --- |
| `want` | The numbers, in order. |

### `Test_Log`

```pawn
forward Test_Log(value);
```

Write a number down in the log of the running test.

| Parameter | Description |
| --- | --- |
| `value` | The number. |

### `Test_Async`

```pawn
forward bool:Test_Async(timeout = SSI_TEST_TIMEOUT);
```

Keep the running test open after it returns, until `Test_Done` is called.

| Parameter | Description |
| --- | --- |
| `timeout` | Milliseconds to wait. The test fails when they pass first. |

**Returns**

- `true` the test waits
- `false` no test is running

### `Test_Done`

```pawn
forward bool:Test_Done();
```

End the test that `Test_Async` kept open, and run the next one.

**Returns**

- `true` the test ended
- `false` no test was waiting

## Events

### `OnTestsFinished`

```pawn
event OnTestsFinished(tests, checks, fails);
```

The tests ended.

| Parameter | Description |
| --- | --- |
| `tests` | Tests that ran. |
| `checks` | Checks they made. |
| `fails` | Checks that failed, tests stopped by a run time error and tests that waited too long. |
