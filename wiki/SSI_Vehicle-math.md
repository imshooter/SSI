# SSI_Vehicle\math

```pawn
#include <SSI_Vehicle\math>
```

## Requirements

- `SSI_Vehicle\parts`

## Quick Start

The geometry of a vehicle in the world: its speed, whether it lies on its
roof, and where a point of its body, its bonnet, boot or a wheel is as it
leans and turns.

```pawn
new const
    Float:kmh = GetVehicleSpeed(vehicleid),
    Float:mph = GetVehicleSpeed(vehicleid, VEHICLE_SPEED_MPH)
;

GetVehicleBootPos(vehicleid, x, y, z);
```

- The speed is the velocity of the game times a factor,
  `VEHICLE_SPEED_MULTIPLIER` unless one is given. It is kilometres an hour
  unless the script defines it before the include, as
  `#define VEHICLE_SPEED_MULTIPLIER VEHICLE_SPEED_MPH`. `VEHICLE_SPEED_KMH`
  and `VEHICLE_SPEED_MPH` can be defined before the include too.
- Points use the matrix of the vehicle, so they follow it on a slope or on
  its side.

## API

### `GetVehicleSpeed`

```pawn
forward Float:GetVehicleSpeed(vehicleid, Float:multiplier = VEHICLE_SPEED_MULTIPLIER);
```

The speed of a vehicle: the length of its velocity times `multiplier`.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `multiplier` | Factor of the unit wanted, `VEHICLE_SPEED_KMH`, `VEHICLE_SPEED_MPH`, or `1.0` for the velocity of the game. |

**Returns**

- the speed
- `0.0` when `vehicleid` is not a vehicle

### `IsVehicleUpsideDown`

```pawn
forward bool:IsVehicleUpsideDown(vehicleid);
```

Whether a vehicle lies on its roof: its up points below the horizon.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |

**Returns**

- `true` it is upside down
- `false` it is not, or `vehicleid` is not a vehicle

### `GetVehicleOffsetPos`

```pawn
forward bool:GetVehicleOffsetPos(vehicleid, Float:offsetX, Float:offsetY, Float:offsetZ, &Float:x, &Float:y, &Float:z);
```

The world position of a point given in the frame of a vehicle, right, forward and up, as it leans and turns.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `offsetX` | To the right. |
| `offsetY` | Forward. |
| `offsetZ` | Up. |
| `x` | Where the world X goes. |
| `y` | Where the world Y goes. |
| `z` | Where the world Z goes. |

**Returns**

- `true` it was found
- `false` `vehicleid` is not a vehicle

### `GetVehicleBonnetOffset`

```pawn
forward Float:GetVehicleBonnetOffset(vehicleid, Float:margin = 0.1);
```

Distance from the middle of a vehicle to its bonnet.

Half the length of its model plus `margin`, along the Y of the vehicle. Used
as the `offsetY` of `GetVehicleOffsetPos`.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `margin` | Distance past the bumper. |

**Returns**

- the offset
- `margin` when `vehicleid` is not a vehicle

### `GetVehicleBootOffset`

```pawn
forward Float:GetVehicleBootOffset(vehicleid, Float:margin = 0.1);
```

Distance from the middle of a vehicle to its boot, negative.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `margin` | Distance past the bumper. |

**Returns**

- the offset
- `-margin` when `vehicleid` is not a vehicle

### `GetVehicleBonnetPos`

```pawn
forward bool:GetVehicleBonnetPos(vehicleid, &Float:x, &Float:y, &Float:z, Float:margin = 0.1);
```

The world position of the bonnet of a vehicle, at the height of its middle.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `x` | Where the world X goes. |
| `y` | Where the world Y goes. |
| `z` | Where the world Z goes. |
| `margin` | Distance past the bumper. |

**Returns**

- `true` it was found
- `false` `vehicleid` is not a vehicle

### `GetVehicleBootPos`

```pawn
forward bool:GetVehicleBootPos(vehicleid, &Float:x, &Float:y, &Float:z, Float:margin = 0.1);
```

The world position of the boot of a vehicle, at the height of its middle.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `x` | Where the world X goes. |
| `y` | Where the world Y goes. |
| `z` | Where the world Z goes. |
| `margin` | Distance past the bumper. |

**Returns**

- `true` it was found
- `false` `vehicleid` is not a vehicle

### `GetVehicleWheelPos`

```pawn
forward bool:GetVehicleWheelPos(vehicleid, VEHICLE_CORNER:wheel, &Float:x, &Float:y, &Float:z);
```

The world position of the centre of a wheel.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `wheel` | The wheel. |
| `x` | Where the world X goes. |
| `y` | Where the world Y goes. |
| `z` | Where the world Z goes. |

**Returns**

- `true` it was found
- `false` `vehicleid` is not a vehicle
