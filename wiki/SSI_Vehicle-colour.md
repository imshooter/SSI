# SSI_Vehicle\colour

```pawn
#include <SSI_Vehicle\colour>
```

## Quick Start

The 128 paint colours of the game, from `carcols.dat`, as RGBA for drawing a
swatch of them.

## API

### `GetVehiclePaintRGBA`

```pawn
forward GetVehiclePaintRGBA(paint);
```

The colour a paint of the game shows.

| Parameter | Description |
| --- | --- |
| `paint` | The paint, as `ChangeVehicleColours` takes it. |

**Returns**

- its RGBA
- `0` it is not below `MAX_VEHICLE_PAINT`
