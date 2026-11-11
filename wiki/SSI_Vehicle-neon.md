# SSI_Vehicle\neon

```pawn
#include <SSI_Vehicle\neon>
```

## Requirements

- `SSI\hooks`
- [streamer](https://github.com/samp-incognito/samp-streamer-plugin)

## Quick Start

Neon under a vehicle: two tubes of a colour along its sides, or one down the
middle of a model narrower than `VEHICLE_NEON_NARROW`, such as a motorbike.
They are attached as streamer objects, so the light follows the vehicle
wherever it goes.

```pawn
SetVehicleNeon(vehicleid, VEHICLE_NEON_BLUE);
SetVehicleNeon(vehicleid, VEHICLE_NEON_NONE);
```

- The tubes stand `VEHICLE_NEON_SIDE` of the width out from the middle, at
  the height of the axles plus `VEHICLE_NEON_LIFT`, so they fit the model. A
  model without wheels has them `VEHICLE_NEON_LOW` of its height down.
- They keep the world and interior of the vehicle when the script moves it
  with `SetVehicleVirtualWorld` or `LinkVehicleToInterior`, and go away with
  it in `DestroyVehicle`.

## API

### `SetVehicleNeon`

```pawn
forward bool:SetVehicleNeon(vehicleid, VEHICLE_NEON:neon);
```

Put neon of a colour under a vehicle, in place of any it had.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `neon` | The colour, or `VEHICLE_NEON_NONE` to take it off. |

**Returns**

- `true` it was set
- `false` `vehicleid` is not a vehicle

### `GetVehicleNeon`

```pawn
forward VEHICLE_NEON:GetVehicleNeon(vehicleid);
```

The neon under a vehicle.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |

**Returns**

- the colour
- `VEHICLE_NEON_NONE` when it has none or is not a vehicle
