# SSI_Vehicle\forklift

```pawn
#include <SSI_Vehicle\forklift>
```

## Requirements

- `SSI_Extra\inline-timers`
- `SSI\bits`
- `SSI\collection`
- `SSI\dictionary`
- `SSI\hooks`
- [streamer](https://github.com/samp-incognito/samp-streamer-plugin)
- [3DAndreas](https://github.com/imshooter/3DAndreas)

## Quick Start

Crates a forklift lifts, carries and stacks. A crate is a streamer object
with the collision of its model in 3DAndreas, so crates stack on each other
and none is put down inside a wall.

```pawn
new const
    Crate:crateid = CreateCrate(1558, 2795.0, -2417.0, 12.55, 0.0)
;
```

- The client attaches an object to a forklift by its fork carriage, which
  sits `FORKLIFT_FRAME_Y` ahead of the position of the vehicle and
  `FORKLIFT_FRAME_Z` above it with the forks down. A crate on the forks
  rises and falls with them once attached.
- The client does not report how high the forks are. The library works it
  out from how long the driver holds the fork keys, clamped at both ends,
  where the real forks stop too.
- A crate is lifted when the forks rise under it: centred on them, turned
  with the forklift, and at the height of the forks. It then sits straight
  against the mast. Only the top crate of a stack is lifted. It is put down
  when the forks lower it onto the ground or onto another crate, which it is
  lined up with.
- The game lets a vehicle push some models, which the server never learns.
  A crate a driven forklift touches without lifting goes back to its place
  once the forklift leaves it.
- A crate on a forklift that respawns, dies or is destroyed goes back to
  where it was lifted from. When something stands there now, it is put
  down under the forks instead.
- `Crate` is a collection to walk with `foreach`. Only this library changes
  it.

`streamer` and `SSI_Extra\inline-timers` include `SSI\hooks` themselves, so
they come first.

## API

### `CreateCrate`

```pawn
forward Crate:CreateCrate(modelid, Float:x, Float:y, Float:z, Float:angle, worldid = 0, interiorid = 0);
```

Put a crate on the ground.

| Parameter | Description |
| --- | --- |
| `modelid` | Model of the crate, which needs a collision. |
| `x` | Centre on the X axis. |
| `y` | Centre on the Y axis. |
| `z` | Height of its bottom, such as the ground. |
| `angle` | Its heading. |
| `worldid` | Virtual world. |
| `interiorid` | Interior. |

**Returns**

- the crate
- `INVALID_CRATE_ID` when:
    + `MAX_CRATES` already exist
    + the model has no collision

### `StackCrate`

```pawn
forward Crate:StackCrate(Crate:belowid, modelid);
```

Put a crate on top of another, lined up with it.

| Parameter | Description |
| --- | --- |
| `belowid` | Crate to stack on, on the ground or on a stack. |
| `modelid` | Model of the new crate. |

**Returns**

- the crate
- `INVALID_CRATE_ID` when:
    + `belowid` is not a crate, is carried or has a crate on it
    + `MAX_CRATES` already exist
    + the model has no collision

### `DestroyCrate`

```pawn
forward bool:DestroyCrate(Crate:crateid);
```

Destroy a crate, also off the forks. A crate stacked on it stays where it is.

| Parameter | Description |
| --- | --- |
| `crateid` | Crate to destroy. |

**Returns**

- `true` it was destroyed
- `false` `crateid` is not a crate

### `IsValidCrate`

```pawn
forward bool:IsValidCrate(Crate:crateid);
```

Whether a crate exists.

| Parameter | Description |
| --- | --- |
| `crateid` | Crate to check. |

**Returns**

- `true` it exists
- `false` it does not

### `GetCrateObject`

```pawn
forward STREAMER_TAG_OBJECT:GetCrateObject(Crate:crateid);
```

The streamer object of a crate. It changes each time the crate is lifted or put down.

| Parameter | Description |
| --- | --- |
| `crateid` | Crate to read. |

**Returns**

- the object
- `INVALID_STREAMER_ID` `crateid` is not a crate

### `GetCrateVehicle`

```pawn
forward GetCrateVehicle(Crate:crateid);
```

The forklift carrying a crate.

| Parameter | Description |
| --- | --- |
| `crateid` | Crate to read. |

**Returns**

- the vehicle
- `INVALID_VEHICLE_ID` it is on the ground or on another crate,
  or `crateid` is not a crate

### `GetVehicleCrate`

```pawn
forward Crate:GetVehicleCrate(vehicleid);
```

The crate a forklift carries.

| Parameter | Description |
| --- | --- |
| `vehicleid` | Vehicle to read. |

**Returns**

- the crate
- `INVALID_CRATE_ID` it carries none

### `GetCrateBelow`

```pawn
forward Crate:GetCrateBelow(Crate:crateid);
```

The crate under a crate in a stack.

| Parameter | Description |
| --- | --- |
| `crateid` | Crate to read. |

**Returns**

- the crate under it
- `INVALID_CRATE_ID` it is on the ground or carried, or
  `crateid` is not a crate

### `GetCrateAbove`

```pawn
forward Crate:GetCrateAbove(Crate:crateid);
```

The crate on top of a crate in a stack.

| Parameter | Description |
| --- | --- |
| `crateid` | Crate to read. |

**Returns**

- the crate on it
- `INVALID_CRATE_ID` nothing is on it, or `crateid` is not a
  crate

### `GetForkliftHeight`

```pawn
forward Float:GetForkliftHeight(vehicleid);
```

How high the forks of a forklift are thought to be, from how long the fork keys were held.

| Parameter | Description |
| --- | --- |
| `vehicleid` | Vehicle to read. |

**Returns**

- the height above the lowest, from `0.0` to `FORKLIFT_TRAVEL`

## Events

### `OnCrateLift`

```pawn
event OnCrateLift(Crate:crateid, vehicleid);
```

The forks of a forklift are rising under a crate.

| Parameter | Description |
| --- | --- |
| `crateid` | The crate. |
| `vehicleid` | The forklift. |

**Returns**

- `0` it is lifted
- `1` it is not

### `OnCrateLifted`

```pawn
event OnCrateLifted(Crate:crateid, vehicleid);
```

A forklift lifted a crate.

| Parameter | Description |
| --- | --- |
| `crateid` | The crate. |
| `vehicleid` | The forklift. |

### `OnCrateDrop`

```pawn
event OnCrateDrop(Crate:crateid, vehicleid, Crate:belowid);
```

A forklift is lowering a crate onto the ground or another crate. It is asked again while the forks keep going down.

| Parameter | Description |
| --- | --- |
| `crateid` | The crate. |
| `vehicleid` | The forklift. |
| `belowid` | The crate it lands on, or `INVALID_CRATE_ID`. |

**Returns**

- `0` it is put down
- `1` it stays on the forks

### `OnCrateDropped`

```pawn
event OnCrateDropped(Crate:crateid, vehicleid, Crate:belowid);
```

A crate came off the forks, lowered, or put down under them because the forklift is gone and its place is taken.

| Parameter | Description |
| --- | --- |
| `crateid` | The crate. |
| `vehicleid` | The forklift. |
| `belowid` | The crate it lies on, or `INVALID_CRATE_ID`. |

### `OnCrateReturned`

```pawn
event OnCrateReturned(Crate:crateid, vehicleid);
```

A crate went back to where it was lifted from, because its forklift respawned, died or was destroyed.

| Parameter | Description |
| --- | --- |
| `crateid` | The crate. |
| `vehicleid` | The forklift. |
