# SSI_Vehicle\objective

```pawn
#include <SSI_Vehicle\objective>
```

## Requirements

- `SSI\hooks`
- [streamer](https://github.com/samp-incognito/samp-streamer-plugin)

## Quick Start

Marks the vehicle a player was sent to with the yellow arrow and a radar
blip. The marks are hidden while the player is in it, as driver or
passenger, and come back when they get out. A player is sent to one vehicle
at a time.

## API

### `SetPlayerObjectiveVehicle`

```pawn
forward bool:SetPlayerObjectiveVehicle(playerid, vehicleid);
```

Send a player to a vehicle.

Replaces the vehicle they were sent to before.

| Parameter | Description |
| --- | --- |
| `playerid` | Player to send. |
| `vehicleid` | Vehicle to send them to. |

**Returns**

- `true` they are sent to it
- `false` `vehicleid` is not a valid vehicle

### `ClearPlayerObjectiveVehicle`

```pawn
forward bool:ClearPlayerObjectiveVehicle(playerid);
```

Stop sending a player to a vehicle.

| Parameter | Description |
| --- | --- |
| `playerid` | Player to change. |

**Returns**

- `true` the marks were removed
- `false` they were not sent anywhere

### `GetPlayerObjectiveVehicle`

```pawn
forward GetPlayerObjectiveVehicle(playerid);
```

The vehicle a player was sent to.

A vehicle destroyed since is found here, since open.mp does not report it.

| Parameter | Description |
| --- | --- |
| `playerid` | Player to read. |

**Returns**

- the vehicle
- `INVALID_VEHICLE_ID` they were not sent to one

### `RefreshPlayerObjectiveVehicle`

```pawn
forward bool:RefreshPlayerObjectiveVehicle(playerid);
```

Show the arrow again.

The client loses it when the player changes virtual world, which is not
reported, so call this after moving one.

| Parameter | Description |
| --- | --- |
| `playerid` | Player to show it to. |

**Returns**

- `true` it is shown again
- `false` they were not sent anywhere
