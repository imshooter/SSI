# SSI\iterator

```pawn
#include <SSI\iterator>
```

## Requirements

- `SSI\hooks`
- `SSI\collection`
- [PawnPlus](https://github.com/IllidanS4/PawnPlus)

## Quick Start

The ids the server hands out, in collections this script walks with
`foreach`, as y_foreach keeps its iterators:

```pawn
#include <SSI\iterator>

foreach (new playerid : Player) {
}

foreach (new vehicleid : StreamedVehicle[playerid]) {
}
```

- `Player`: the connected players who are not NPCs.
- `Bot`, also `NPC`: the connected NPCs.
- `Character`: both.
- `RconAdmin`: the players logged in to RCON.
- `Vehicle` and `Actor`: every one on the server.
- `LocalVehicle` and `LocalActor`: the ones made by this script.
- `StreamedPlayer[playerid]`, `StreamedBot[playerid]`,
  `StreamedCharacter[playerid]`, `StreamedVehicle[playerid]` and
  `StreamedActor[playerid]`: what that player has streamed in. Each is a
  collection per player, about 48 MB in all with the default 1000 players and
  2000 vehicles, so they exist only when `SSI_ITERATOR_STREAMED` is defined
  before this file.

A player is added on `OnPlayerConnect` and removed after every hook and the
public of `OnPlayerDisconnect` have run, so all of them still walk the
player who is leaving. Vehicles and actors are tracked by PawnPlus filters
that run after the natives that create and destroy them, whichever script
calls them. Those that already exist when the script starts are counted too.
The ids are plain numbers, so the loop variable has no tag.
`Collection_Count`, `Collection_Contains` and the other calls read these
collections, and only this file changes them.

It also has the iterator functions of y_foreach, walked the same way:
`Range`, `N`, `Powers`, `Fib`, `Random`, `Null`, `NonNull`, `Until`,
`Filter`, `VehicleOccupant`, `VehicleDriver` and `VehiclePassenger`.

```pawn
foreach (new i : Range(10, 100, 2)) {
}

foreach (new playerid : VehicleOccupant(vehicleid)) {
}
```

## API

### `N@SSI_loop`

Walk the numbers from `0` up to `count`, `count` left out.

```pawn
foreach (new i : N(6)) {
}
```

| Parameter | Description |
| --- | --- |
| `count` | How many numbers. |

### `Range@SSI_loop`

Walk the numbers from `min` towards `max`, `max` left out.

```pawn
foreach (new i : Range(10, 100, 2)) {
}
```

| Parameter | Description |
| --- | --- |
| `min` | The first number. |
| `max` | The number the walk stops at. |
| `step` | What is added each time, negative to count down, or `1` when left out. A step of `0` never ends the walk. |

### `Powers@SSI_loop`

Walk the powers of `base` that fit in a cell, from `1`.

```pawn
foreach (new i : Powers(3)) {
}
```

| Parameter | Description |
| --- | --- |
| `base` | The number raised. |

### `Fib@SSI_loop`

Walk the Fibonacci numbers that fit in a cell, from `0`.

```pawn
foreach (new i : Fib()) {
}
```

### `Random@SSI_loop`

Walk `count` random numbers.

With one number after `count`, the numbers range from `0` up to that
number, which is left out. With two, they range from the first up to the
second, which is left out.

```pawn
foreach (new i : Random(12, 10)) {
}
```

| Parameter | Description |
| --- | --- |
| `count` | How many numbers. |
| `min` | The lowest number, or with no `max` the number they stay under. |
| `max` | The number they stay under. |

### `Null@SSI_loop`

Walk the indexes of an array that hold `0`.

```pawn
foreach (new i : Null(array)) {
}
```

| Parameter | Description |
| --- | --- |
| `array` | The array. |
| `size` | How many of its cells to walk, or all of them when left out. |

### `NonNull@SSI_loop`

Walk the indexes of an array that hold anything but `0`.

| Parameter | Description |
| --- | --- |
| `array` | The array. |
| `size` | How many of its cells to walk, or all of them when left out. |

### `Until@SSI_loop`

Walk the indexes of an array up to the first that holds `value`, which is left out.

```pawn
foreach (new i : Until(5, array)) {
}
```

| Parameter | Description |
| --- | --- |
| `value` | The value the walk stops at. |
| `array` | The array. |
| `size` | How many of its cells to walk, or all of them when left out. |

### `Filter@SSI_loop`

Walk the indexes of an array that hold `value`.

| Parameter | Description |
| --- | --- |
| `value` | The value looked for. |
| `array` | The array. |
| `size` | How many of its cells to walk, or all of them when left out. |

### `VehicleOccupant@SSI_loop`

Walk the players in a vehicle, seat by seat from the driver, or the players in any vehicle.

A player who leaves the vehicle inside the loop does not stop the walk.

```pawn
foreach (new playerid : VehicleOccupant(vehicleid)) {
}
```

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle, or every vehicle when left out. |
| `driver` | Whether the driver is walked. |
| `passenger` | Whether the passengers are walked. |

### `VehicleDriver@SSI_loop`

Walk the driver of a vehicle, or the drivers of every vehicle.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle, or every vehicle when left out. |

### `VehiclePassenger@SSI_loop`

Walk the passengers of a vehicle, or of every vehicle.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle, or every vehicle when left out. |
