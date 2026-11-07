# SSI_Extra\inline-timers

```pawn
#include <SSI_Extra\inline-timers>
```

## Requirements

- `SSI\inline`
- `SSI\collection`

## Quick Start

Timers that call an inline:

```pawn
#include <SSI_Extra\inline-timers>

Remind(playerid) {
    new
        calls = 0
    ;

    inline OnTick() {
        SendClientMessage(playerid, -1, "call %d", ++calls);
    }

    new const
        Timer:timer = Timer_StartInline(using inline OnTick, 1000, 5)
    ;
}
```

- A timer takes the inline and frees it when it ends: after its last call,
  or when it is stopped.
- A count of `0` calls it until the timer is stopped. Any other count calls
  it that many times.
- The first call comes after `delay`, the same as `interval` when it is not
  given.
- An inline stops its own timer with `Timer_Stop(Timer_Current())`, so it
  needs no copy of the id. Stopping a timer that ended, or was never made,
  does nothing.

## API

### `Timer_StartInline`

```pawn
forward Timer:Timer_StartInline(Inline:callback<>, interval, count = 0, delay = -1);
```

Call an inline on a timer.

The timer takes the inline, and frees it even when it cannot start. The
inline takes no parameters.

| Parameter | Description |
| --- | --- |
| `callback` | The inline, as `using inline Name`. |
| `interval` | Milliseconds between calls. |
| `count` | Calls to make, or `0` until it is stopped. |
| `delay` | Milliseconds before the first call, or `-1` for `interval`. |

**Returns**

- the timer
- `INVALID_TIMER_ID` when:
    + the inline could not be captured
    + `interval` is `0` or less, or `count` is below `0`
    + `SSI_TIMERS` timers are running

### `Timer_Stop`

```pawn
forward bool:Timer_Stop(Timer:timer);
```

Stop a timer and free its inline.

| Parameter | Description |
| --- | --- |
| `timer` | The timer. |

**Returns**

- `true` it is stopped
- `false` it ended already, or was never made

### `Timer_IsRunning`

```pawn
forward bool:Timer_IsRunning(Timer:timer);
```

Whether a timer is still running.

| Parameter | Description |
| --- | --- |
| `timer` | The timer. |

**Returns**

- `true` it is
- `false` it ended, was stopped, or was never made

### `Timer_Current`

```pawn
forward Timer:Timer_Current();
```

The timer whose inline is running.

```pawn
inline OnSecond() {
    if (++seconds == limit) {
        Timer_Stop(Timer_Current());
    }
}
```

**Returns**

- the timer
- `INVALID_TIMER_ID` outside the inline of a timer
