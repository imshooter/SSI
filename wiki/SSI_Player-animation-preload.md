# SSI_Player\animation-preload

```pawn
#include <SSI_Player\animation-preload>
```

## Requirements

- `SSI\hooks`

## Quick Start

Animation libraries loaded ahead. The game loads an animation library the
first time one of its animations is played, and that first animation does
not play. The libraries given to `PreloadAnimationLibrary` are loaded on the
first spawn of each player, so the first animation a script plays shows like
the others. Bots of the server are left out.

Give only the libraries the scripts play: every library is read from disk
by the game on spawn, and all of them at once stall it for seconds and can
crash it. PED is always loaded.

## API

### `PreloadAnimationLibrary`

```pawn
forward bool:PreloadAnimationLibrary(const library[]);
```

Load an animation library for every player on their first spawn.

| Parameter | Description |
| --- | --- |
| `library` | The library, such as `"GYMNASIUM"`. |

**Returns**

- `true` it is loaded from now on, or was already
- `false` there are `MAX_PRELOADED_ANIMATION_LIBRARIES` already
