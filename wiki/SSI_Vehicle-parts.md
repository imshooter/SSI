# SSI_Vehicle\parts

```pawn
#include <SSI_Vehicle\parts>
```

## Quick Start

The parts of a vehicle one at a time: some parameters, a door, window,
tyre, lamp or panel is set while the others keep what the game has.

```pawn
SetVehicleParamsState(vehicleid, VEHICLE_PARAM_ENGINE | VEHICLE_PARAM_LIGHTS, VEHICLE_PARAMS_ON);
SetVehicleWindowOpen(vehicleid, VEHICLE_CORNER_FRONT_LEFT, true);
SetVehicleTyrePopped(vehicleid, VEHICLE_CORNER_REAR_RIGHT, true);
```

- Nothing is cached. Each call reads the state from the server and writes it
  back, so a native called elsewhere is never undone.
- Doors and windows are the four seats, named by `VEHICLE_CORNER` as tyres
  and wheels are. On a bike the front tyre is `VEHICLE_CORNER_FRONT_RIGHT`
  and the rear one `VEHICLE_CORNER_REAR_RIGHT`.
- The bonnet, boot and front doors break apart from the seats, so their
  damage is named by `VEHICLE_OPENING`.

## API

### `SetVehicleParamsState`

```pawn
forward bool:SetVehicleParamsState(vehicleid, VEHICLE_PARAM:params, value);
```

Set parameters of a vehicle to one value, keeping the others.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `params` | The parameters, joined with `\|`, such as `VEHICLE_PARAM_ENGINE \| VEHICLE_PARAM_LIGHTS`. |
| `value` | `VEHICLE_PARAMS_ON`, `VEHICLE_PARAMS_OFF`, or `VEHICLE_PARAMS_UNSET` to give them back to the game. |

**Returns**

- `true` they were set
- `false` `vehicleid` is not a vehicle

### `GetVehicleParamState`

```pawn
forward GetVehicleParamState(vehicleid, VEHICLE_PARAM:param);
```

One parameter of a vehicle.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `param` | The parameter, a single one. |

**Returns**

- `VEHICLE_PARAMS_ON`, `VEHICLE_PARAMS_OFF` or
  `VEHICLE_PARAMS_UNSET`
- `VEHICLE_PARAMS_UNSET` too when `vehicleid` is not a vehicle
  or `param` is not a single parameter

### `SetVehicleDoorOpen`

```pawn
forward bool:SetVehicleDoorOpen(vehicleid, VEHICLE_CORNER:door, bool:open);
```

Open or close the door of a seat.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `door` | The seat of the door. |
| `open` | Whether it opens. |

**Returns**

- `true` it was set
- `false` `vehicleid` is not a vehicle

### `IsVehicleDoorOpen`

```pawn
forward bool:IsVehicleDoorOpen(vehicleid, VEHICLE_CORNER:door);
```

Whether the door of a seat was opened by `SetVehicleDoorOpen`.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `door` | The seat of the door. |

### `SetVehicleWindowOpen`

```pawn
forward bool:SetVehicleWindowOpen(vehicleid, VEHICLE_CORNER:window, bool:open);
```

Open or close the window of a seat.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `window` | The seat of the window. |
| `open` | Whether it opens. |

**Returns**

- `true` it was set
- `false` `vehicleid` is not a vehicle

### `IsVehicleWindowOpen`

```pawn
forward bool:IsVehicleWindowOpen(vehicleid, VEHICLE_CORNER:window);
```

Whether the window of a seat was opened by `SetVehicleWindowOpen`.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `window` | The seat of the window. |

### `SetVehicleTyrePopped`

```pawn
forward bool:SetVehicleTyrePopped(vehicleid, VEHICLE_CORNER:tyre, bool:popped);
```

Pop or mend a tyre.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `tyre` | The tyre. |
| `popped` | Whether it is popped. |

**Returns**

- `true` it was set
- `false` `vehicleid` is not a vehicle

### `IsVehicleTyrePopped`

```pawn
forward bool:IsVehicleTyrePopped(vehicleid, VEHICLE_CORNER:tyre);
```

Whether a tyre is popped.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `tyre` | The tyre. |

### `SetVehicleLampBroken`

```pawn
forward bool:SetVehicleLampBroken(vehicleid, VEHICLE_LAMP:lamp, bool:broken);
```

Break or mend a lamp.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `lamp` | The lamp. `VEHICLE_LAMP_REAR` is both rear lamps. |
| `broken` | Whether it is broken. |

**Returns**

- `true` it was set
- `false` `vehicleid` is not a vehicle

### `IsVehicleLampBroken`

```pawn
forward bool:IsVehicleLampBroken(vehicleid, VEHICLE_LAMP:lamp);
```

Whether a lamp is broken.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `lamp` | The lamp. |

### `GetVehicleOpeningDamage`

```pawn
forward VEHICLE_DOOR_STATUS:GetVehicleOpeningDamage(vehicleid, VEHICLE_OPENING:opening);
```

The damage of the bonnet, the boot or a front door.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `opening` | The part. |

**Returns**

- the flags of `VEHICLE_DOOR_STATUS_BONNET_OPEN`,
  `VEHICLE_DOOR_STATUS_BONNET_DAMAGED` and
  `VEHICLE_DOOR_STATUS_BONNET_MISSING`, whatever the part
- `VEHICLE_DOOR_STATUS_NONE` when `vehicleid` is not a vehicle

### `SetVehicleOpeningDamage`

```pawn
forward bool:SetVehicleOpeningDamage(vehicleid, VEHICLE_OPENING:opening, VEHICLE_DOOR_STATUS:damage);
```

Set the damage of the bonnet, the boot or a front door.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `opening` | The part. |
| `damage` | Flags of `VEHICLE_DOOR_STATUS_BONNET_OPEN`, `VEHICLE_DOOR_STATUS_BONNET_DAMAGED` and `VEHICLE_DOOR_STATUS_BONNET_MISSING`, whatever the part. |

**Returns**

- `true` it was set
- `false` `vehicleid` is not a vehicle

### `GetVehiclePanelDamage`

```pawn
forward GetVehiclePanelDamage(vehicleid, VEHICLE_PANEL:panel);
```

The damage of a panel, from `0` for whole to `3`.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `panel` | The panel. |

**Returns**

- the damage
- `0` when `vehicleid` is not a vehicle

### `SetVehiclePanelDamage`

```pawn
forward bool:SetVehiclePanelDamage(vehicleid, VEHICLE_PANEL:panel, damage);
```

Set the damage of a panel.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |
| `panel` | The panel. |
| `damage` | From `0` for whole to `3`. |

**Returns**

- `true` it was set
- `false` `vehicleid` is not a vehicle
