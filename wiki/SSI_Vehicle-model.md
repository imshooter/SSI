# SSI_Vehicle\model

```pawn
#include <SSI_Vehicle\model>
```

## Requirements

- `SSI\dictionary`
- `SSI\string`
- `SSI_Vehicle\components`
- `SSI\hooks`

## Quick Start

Name, category and flags of every vehicle model, read by model id.

A model has one category, such as Off Road for a Sanchez, and any number of
flags: a Seasparrow is a helicopter, floats and is armed. Pushbikes and train
carriages have flags of their own, since the game treats them as bikes and
cars.

A model is also found by its name, in any case. Of two models with one name,
as the Boxville, the first is found.

The data is from y_vehicledata of YSI, so this file stays under the Mozilla
Public License 1.1, as its notice at the top says.

## API

### `GetVehicleModelFlags`

```pawn
forward VEHICLE_FLAGS:GetVehicleModelFlags(modelid);
```

The flags of a vehicle model.

| Parameter | Description |
| --- | --- |
| `modelid` | Model to read. |

**Returns**

- its flags
- `VEHICLE_NONE` `modelid` is not a vehicle model

### `IsVehicleModelFlagged`

```pawn
forward bool:IsVehicleModelFlagged(modelid, VEHICLE_FLAGS:flags);
```

Whether a vehicle model has all of some flags.

`VEHICLE_POLICE | VEHICLE_CAR` finds a police car and not a police boat.

| Parameter | Description |
| --- | --- |
| `modelid` | Model to check. |
| `flags` | Flags to look for. |

**Returns**

- `true` it has all of them
- `false` it lacks one

### `GetVehicleModelCategory`

```pawn
forward VEHICLE_CATEGORY:GetVehicleModelCategory(modelid);
```

The category of a vehicle model.

| Parameter | Description |
| --- | --- |
| `modelid` | Model to read. |

**Returns**

- the category
- `VEHICLE_CATEGORY_NONE` `modelid` is not a vehicle model

### `GetVehicleModelName`

```pawn
forward bool:GetVehicleModelName(modelid, output[], size = sizeof (output));
```

The name of a vehicle model.

| Parameter | Description |
| --- | --- |
| `modelid` | Model to read. |
| `output` | Reads back the name, or is emptied on failure. |
| `size` | Size of `output`. |

**Returns**

- `true` the name was written
- `false` `modelid` is not a vehicle model

### `GetVehicleModelByName`

```pawn
forward GetVehicleModelByName(const name[]);
```

The vehicle model with a name, in any case.

| Parameter | Description |
| --- | --- |
| `name` | Name to find, such as "infernus". |

**Returns**

- the model
- `0` no model has that name

### `GetVehicleFlags`

```pawn
forward VEHICLE_FLAGS:GetVehicleFlags(vehicleid);
```

The flags of a vehicle.

| Parameter | Description |
| --- | --- |
| `vehicleid` | Vehicle to read. |

**Returns**

- its flags
- `VEHICLE_NONE` `vehicleid` is not a valid vehicle

### `IsVehicleFlagged`

```pawn
forward bool:IsVehicleFlagged(vehicleid, VEHICLE_FLAGS:flags);
```

Whether a vehicle has all of some flags.

| Parameter | Description |
| --- | --- |
| `vehicleid` | Vehicle to check. |
| `flags` | Flags to look for. |

**Returns**

- `true` it has all of them
- `false` it lacks one

### `GetVehicleCategory`

```pawn
forward VEHICLE_CATEGORY:GetVehicleCategory(vehicleid);
```

The category of a vehicle.

| Parameter | Description |
| --- | --- |
| `vehicleid` | Vehicle to read. |

**Returns**

- the category
- `VEHICLE_CATEGORY_NONE` `vehicleid` is not a valid vehicle

### `IsVehicleModelGround`

```pawn
forward bool:IsVehicleModelGround(modelid);
```

Whether a model drives on roads, as a garage takes.

| Parameter | Description |
| --- | --- |
| `modelid` | Model to check. |

**Returns**

- `true` it is a car or a motorbike
- `false` it is not

### `IsVehicleModelAir`

```pawn
forward bool:IsVehicleModelAir(modelid);
```

Whether a model flies, as a hangar takes.

| Parameter | Description |
| --- | --- |
| `modelid` | Model to check. |

**Returns**

- `true` it is a plane or a helicopter
- `false` it is not

### `IsVehicleModelWater`

```pawn
forward bool:IsVehicleModelWater(modelid);
```

Whether a model goes on water, as a marina takes.

A Seasparrow is both air and water.

| Parameter | Description |
| --- | --- |
| `modelid` | Model to check. |

**Returns**

- `true` it goes on water
- `false` it does not

### `IsVehicleModelOwnable`

```pawn
forward bool:IsVehicleModelOwnable(modelid);
```

Whether a model can be owned.

Trailers, train carriages, pushbikes and remote control toys cannot.

| Parameter | Description |
| --- | --- |
| `modelid` | Model to check. |

**Returns**

- `true` it can be owned
- `false` it cannot
