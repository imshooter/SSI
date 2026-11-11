# SSI_Vehicle\freight

```pawn
#include <SSI_Vehicle\freight>
```

## Requirements

- `SSI\bits`
- `SSI\collection`
- `SSI\hooks`
- [streamer](https://github.com/samp-incognito/samp-streamer-plugin)
- [3DAndreas](https://github.com/imshooter/3DAndreas)

## Quick Start

Freight that rides in the back of a vehicle, each piece in a slot of a grid
set for that vehicle. A slot is where the bottom of a piece stands, so
pieces of any model stand on the floor.

```pawn
SetVehicleFreight(vehicleid, 2, 3, -0.500, -0.430, -0.093, 1.050, 1.050);
AddVehicleFreight(vehicleid, 1558);
```

- The slots go from the front left one to the right, then back row by row.
- A piece is a streamer object attached to the vehicle. Pieces go away when
  the vehicle respawns or is destroyed, and the grid stays until then.
- With `SSI_Vehicle\forklift` included first, a vehicle whose freight is open
  takes a crate a forklift lowers onto its floor: the crate goes in when
  its bottom comes down to the floor, from `FORKLIFT_DROP_GAP` above it to
  `FREIGHT_FLOOR_REACH` under it. The forklift faces a side the vehicle
  opens from, within `FREIGHT_FACING` degrees. Where the forks cannot pass
  that side the crate may stay outside the vehicle, its edge at most
  `FREIGHT_REACH` from the end of the vehicle model. On a flat bed the
  forks reach over, and half the crate at least is over the outer slots on
  that side. Towards the sides it is not brought from its centre stays over
  the slots. Brought from an end of the vehicle, the crate goes to the free
  slot furthest in, and from a side to the nearest. A stack of two takes two
  free slots of one row, side by side, or the next slot by the same rule
  when no row has two. `OnCrateLoad` can refuse a crate, once each time it
  is lowered, and the crate or the stack is then put down as usual.

## API

### `SetVehicleFreight`

```pawn
forward bool:SetVehicleFreight(vehicleid, columns, rows, Float:x, Float:y, Float:floor, Float:columnGap, Float:rowGap, FREIGHT_SIDE:sides = FREIGHT_SIDE_BACK, bool:bed = false);
```

Set the grid of slots in the back of a vehicle. Freight already in it goes away.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `columns` | Slots side by side. |
| `rows` | Slots one behind the other. |
| `x` | X of the front left slot, from the vehicle. |
| `y` | Y of the front left slot, from the vehicle. |
| `floor` | Height of the floor, from the vehicle. |
| `columnGap` | Distance between columns, to the right. |
| `rowGap` | Distance between rows, backwards. |
| `sides` | The sides a forklift loads it from. |
| `bed` | `true` for a flat bed the forks reach over, so a crate is lowered over the slots. |

**Returns**

- `true` it was set
- `false` when:
    + the vehicle does not exist
    + `columns` or `rows` is below 1
    + there are more than `MAX_FREIGHT_SLOTS` slots

### `AddVehicleFreight`

```pawn
forward AddVehicleFreight(vehicleid, modelid, slot = -1);
```

Put a piece of freight in the back of a vehicle.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `modelid` | Model of the piece, which stands on the floor. |
| `slot` | The slot, or `-1` for the first free one. |

**Returns**

- the slot
- `-1` when:
    + the vehicle has no grid
    + the slot is taken or out of the grid
    + every slot is taken

### `RemoveVehicleFreight`

```pawn
forward bool:RemoveVehicleFreight(vehicleid, slot);
```

Take a piece of freight out of the back of a vehicle.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `slot` | The slot. |

**Returns**

- `true` it was taken out
- `false` the slot is empty or out of the grid

### `ClearVehicleFreight`

```pawn
forward bool:ClearVehicleFreight(vehicleid);
```

Take all the freight out of the back of a vehicle. The grid stays.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |

**Returns**

- `true` it was emptied
- `false` the vehicle has no grid

### `GetVehicleFreightCount`

```pawn
forward GetVehicleFreightCount(vehicleid);
```

How many pieces of freight a vehicle carries.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |

**Returns**

How many.

### `GetVehicleFreightSlots`

```pawn
forward GetVehicleFreightSlots(vehicleid);
```

How many slots the grid of a vehicle has.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |

**Returns**

- how many
- `0` it has no grid

### `GetVehicleFreightObject`

```pawn
forward STREAMER_TAG_OBJECT:GetVehicleFreightObject(vehicleid, slot);
```

The object of a piece of freight.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `slot` | The slot. |

**Returns**

- the object
- `INVALID_STREAMER_ID` the slot is empty or out of the grid

### `GetVehicleFreightPos`

```pawn
forward bool:GetVehicleFreightPos(vehicleid, slot, &Float:x, &Float:y, &Float:z);
```

Where the floor of a slot is in the world.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `slot` | The slot. |
| `x` | Reads back the position on the X axis. |
| `y` | Reads back the position on the Y axis. |
| `z` | Reads back the height of the floor. |

**Returns**

- `true` the outputs were written
- `false` the slot is out of the grid

### `SetVehicleFreightOpen`

```pawn
forward bool:SetVehicleFreightOpen(vehicleid, bool:open);
```

Open or close the back of a vehicle to forklifts.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `open` | `true` takes crates. |

**Returns**

- `true` it was set
- `false` the vehicle has no grid

### `IsVehicleFreightOpen`

```pawn
forward bool:IsVehicleFreightOpen(vehicleid);
```

Whether the back of a vehicle takes crates from forklifts.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |

**Returns**

- `true` it does
- `false` it does not

## Events

### `OnCrateLoad`

```pawn
event OnCrateLoad(Crate:crateid, forkliftid, vehicleid, slot);
```

A forklift is lowering a crate into the back of a vehicle. A stack gives a call for the bottom crate, then one for the top crate, and either refuses both.

| Parameter | Description |
| --- | --- |
| `crateid` | The crate. |
| `forkliftid` | The forklift. |
| `vehicleid` | The vehicle. |
| `slot` | The slot it goes to. |

**Returns**

- `0` it is loaded
- `1` it is not

### `OnCrateLoaded`

```pawn
event OnCrateLoaded(Crate:crateid, forkliftid, vehicleid, slot);
```

A crate is in the back of a vehicle as freight. The crate still exists here and is destroyed after, unless a handler destroyed it. A stack gives a call for the bottom crate, then one for the top crate.

| Parameter | Description |
| --- | --- |
| `crateid` | The crate. |
| `forkliftid` | The forklift. |
| `vehicleid` | The vehicle. |
| `slot` | Its slot. |
