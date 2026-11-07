# SSI_Vehicle\components

```pawn
#include <SSI_Vehicle\components>
```

## Quick Start

The tuning parts of the game: their type, name, price, shop and pair, and
which vehicle models take each one.

```pawn
if (CanVehicleModelHaveComponent(GetVehicleModel(vehicleid), 1010)) {
    AddVehicleComponent(vehicleid, 1010);
}
```

- Sideskirts and vents come in two halves. The first half carries the type,
  name and price, and `GetVehicleComponentPair` gives the other one.
- `GetVehicleComponentInSlot` can return either half, so its id goes
  through `GetVehicleComponentPrimary` before a name or price is read.
- `CanVehicleModelHaveComponent` answers what the game accepts, a bit for
  each model and component, which is more than the shops sell.

## API

### `IsValidVehicleModel`

```pawn
forward bool:IsValidVehicleModel(modelid);
```

Whether a number is a vehicle model.

| Parameter | Description |
| --- | --- |
| `modelid` | Number to check. |

**Returns**

- `true` it is 400 to 611
- `false` it is not

### `IsValidVehicleComponent`

```pawn
forward bool:IsValidVehicleComponent(componentid);
```

Whether a number is a tuning component.

| Parameter | Description |
| --- | --- |
| `componentid` | Number to check. |

**Returns**

- `true` it is 1000 to 1193
- `false` it is not

### `GetVehicleComponentTypeName`

```pawn
forward bool:GetVehicleComponentTypeName(type, name[], size = sizeof (name));
```

The name of a component type.

Includes `COMPONENT_TYPE_COLORS` and `COMPONENT_TYPE_PAINT_JOBS`, which a
modshop menu lists with the real types.

| Parameter | Description |
| --- | --- |
| `type` | `COMPONENT_TYPE_VENTS` to `COMPONENT_TYPE_PAINT_JOBS`. |
| `name` | Reads back the name. |
| `size` | Size of `name`. |

**Returns**

- `true` the name was written
- `false` `type` is out of range

### `GetVehicleComponentTypeID`

```pawn
forward GetVehicleComponentTypeID(componentid);
```

The type a component is fitted as.

A `COMPONENT_TYPE_*` of this library, not the `CARMODTYPE` of the native
`GetVehicleComponentType`.

| Parameter | Description |
| --- | --- |
| `componentid` | Component, 1000 to 1193. |

**Returns**

- the type
- `COMPONENT_TYPE_NONE` when:
    + `componentid` is out of range
    + it is the second half of a pair

### `GetVehicleComponentCost`

```pawn
forward GetVehicleComponentCost(componentid);
```

The price of a component in a shop.

A pair is priced once, on the half a menu offers.

| Parameter | Description |
| --- | --- |
| `componentid` | Component, 1000 to 1193. |

**Returns**

- the price
- `0` when:
    + `componentid` is out of range
    + it is the second half of a pair

### `GetVehicleComponentPair`

```pawn
forward GetVehicleComponentPair(componentid);
```

The other half of a two piece component.

Sideskirts and vents come in left and right halves, fitted together.

| Parameter | Description |
| --- | --- |
| `componentid` | Component, 1000 to 1193. |

**Returns**

- the other half
- `INVALID_VEHICLE_COMPONENT_ID` when:
    + `componentid` is out of range
    + it is fitted on its own

### `GetVehicleComponentAvailability`

```pawn
forward GetVehicleComponentAvailability(componentid);
```

Which shop sells a component.

Not which cars take it, which `CanVehicleModelHaveComponent` answers.

| Parameter | Description |
| --- | --- |
| `componentid` | Component, 1000 to 1193. |

**Returns**

- `COMPONENT_AVAILABILITY_MOST` most cars, planes and helicopters
- `COMPONENT_AVAILABILITY_TRANSFENDER` some Transfender cars
- `COMPONENT_AVAILABILITY_EXCLUSIVE` a part made for one car,
  which `GetVehicleComponentExclusiveModel` gives
- `COMPONENT_AVAILABILITY_NONE` when:
    + `componentid` is out of range
    + it is the second half of a pair

### `GetVehicleComponentExclusiveModel`

```pawn
forward GetVehicleComponentExclusiveModel(componentid);
```

The car a component was made for, if it was made for one.

| Parameter | Description |
| --- | --- |
| `componentid` | Component, 1000 to 1193. |

**Returns**

- a vehicle model, 400 to 611
- `INVALID_VEHICLE_MODEL_ID` when:
    + `componentid` is out of range
    + it is sold for most cars or at Transfender

### `GetVehicleComponentName`

```pawn
forward bool:GetVehicleComponentName(componentid, name[], size = sizeof (name));
```

The name of a component, as the shop lists it.

The second half of a pair has no name, so pass an id from
`GetVehicleComponentInSlot` through `GetVehicleComponentPrimary` first.

| Parameter | Description |
| --- | --- |
| `componentid` | Component, 1000 to 1193. |
| `name` | Reads back the name. |
| `size` | Size of `name`. |

**Returns**

- `true` the name was written
- `false` `componentid` is out of range

### `CanVehicleModelHaveComponent`

```pawn
forward bool:CanVehicleModelHaveComponent(modelid, componentid);
```

Whether a vehicle model takes a component.

This is what the game accepts, which is more than the shops sell: nitro,
wheels and hydraulics also go on aircraft and boats.

| Parameter | Description |
| --- | --- |
| `modelid` | Vehicle model, 400 to 611. |
| `componentid` | Component, 1000 to 1193. |

**Returns**

- `true` the model takes it
- `false` when:
    + `modelid` is out of range
    + `componentid` is out of range
    + it does not fit that model

### `GetVehicleComponentPrimary`

```pawn
forward GetVehicleComponentPrimary(componentid);
```

The component a shop lists for any component.

`GetVehicleComponentInSlot` can return either half of a pair, and the second
half has no type, name or price. A component fitted on its own is its own
primary.

| Parameter | Description |
| --- | --- |
| `componentid` | Component, 1000 to 1193. |

**Returns**

- the primary
- `INVALID_VEHICLE_COMPONENT_ID` `componentid` is out of range
