# SSI_Player\fps

```pawn
#include <SSI_Player\fps>
```

## Requirements

- `SSI\task`
- `SSI\hooks`

## Quick Start

Frames per second of each player's game. The game lowers the drunk level by
one each frame, so the level is set high enough to count from and read
again each second. Levels under 2000 are not drawn as drunk.

A script that already has a `GetPlayerFPS` keeps its own: this library
then adds nothing, and the libraries that read the frame rate use that one.
The check also looks for this library's own mark, a function: functions
stay known from one compiler pass to the next, so `defined GetPlayerFPS`
alone would find this very library on the second pass and drop it there.

## API

### `GetPlayerFPS`

```pawn
forward GetPlayerFPS(playerid);
```

The frames per second of a player's game, measured over the last second.

| Parameter | Description |
| --- | --- |
| `playerid` | Player to read. |

**Returns**

- the frames per second
- `0` until a second was measured, or for bots
