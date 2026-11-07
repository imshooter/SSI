# SSI\task

```pawn
#include <SSI\task>
```

## Requirements

- `SSI\iterator`

## Quick Start

Functions that run on their own every so many milliseconds, as the tasks of
y_timers. A `task` runs from `OnGameModeInit` while the script lives. A
`ptask` runs for each player from the moment they connect until they leave.

```pawn
#include <SSI\task>
#include <SSI\hooks>

task SaveWorld[60000]() {
    SaveHouses();
}

ptask Hunger[30000](playerid) {
    new
        Float:health
    ;

    GetPlayerHealth(playerid, health);
    SetPlayerHealth(playerid, health - 1.0);
}

Task_Pause(SaveWorld);
PTask_PausePlayer(Hunger, playerid);
```

- The name is a public of the script, so it can also be called as any
  function, and two tasks cannot share it.
- The interval is read in `OnGameModeInit`, so it can be any expression.
- Tasks whose intervals are equal, or one a multiple of the other, start
  spread over the interval, as in y_timers: three tasks of a second run at
  0, 333 and 666 milliseconds into it, not in the same tick.
- Each task is a native repeating timer started by a hook, so a file that
  declares one includes `SSI\hooks` last, as for any hook.
- Bots connect as players do, so a `ptask` runs for them too.

## API

### `task`

Declare a function that runs every `interval` milliseconds from `OnGameModeInit`.

```pawn
task SaveWorld[60000]() {
}
```

### `ptask`

Declare a function that runs every `interval` milliseconds for each player, from `OnPlayerConnect` to `OnPlayerDisconnect`.

```pawn
ptask Hunger[30000](playerid) {
}
```

### `Task_Pause`

```pawn
forward bool:Task_Pause(name);
```

Stop a `task` until `Task_Resume`.

| Parameter | Description |
| --- | --- |
| `name` | The task. |

**Returns**

- `true` it was paused
- `false` it was paused already, or is not a `task`

### `Task_Resume`

```pawn
forward bool:Task_Resume(name);
```

Run a paused `task` again. It runs one interval after this.

| Parameter | Description |
| --- | --- |
| `name` | The task. |

**Returns**

- `true` it runs again
- `false` it was not paused, or is not a `task`

### `PTask_Pause`

```pawn
forward bool:PTask_Pause(name);
```

Stop a `ptask` for every player, and for those who connect, until `PTask_Resume`.

| Parameter | Description |
| --- | --- |
| `name` | The task. |

**Returns**

- `true` it was paused
- `false` it was paused already, or is not a `ptask`

### `PTask_Resume`

```pawn
forward bool:PTask_Resume(name);
```

Run a paused `ptask` again for every player.

| Parameter | Description |
| --- | --- |
| `name` | The task. |

**Returns**

- `true` it runs again
- `false` it was not paused, or is not a `ptask`

### `PTask_PausePlayer`

```pawn
forward bool:PTask_PausePlayer(name, playerid);
```

Stop a `ptask` for one player. It starts again when they reconnect, or with `PTask_ResumePlayer`.

| Parameter | Description |
| --- | --- |
| `name` | The task. |
| `playerid` | The player. |

**Returns**

- `true` it was stopped
- `false` it was not running for them

### `PTask_ResumePlayer`

```pawn
forward bool:PTask_ResumePlayer(name, playerid);
```

Run a `ptask` again for one player.

| Parameter | Description |
| --- | --- |
| `name` | The task. |
| `playerid` | The player. |

**Returns**

- `true` it runs again
- `false` it was running, the player is not connected, or the
  task is paused for everyone
