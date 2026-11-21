# SSI_World\zone

```pawn
#include <SSI_World\zone>
```

## Requirements

- `SSI\hooks`
- [streamer](https://github.com/samp-incognito/samp-streamer-plugin)

## Quick Start

The named zones of the map of San Andreas, the ones the story mode writes at
the corner of the screen.

```pawn
new
    name[MAX_ZONE_NAME]
;

GetZoneName(GetPlayerZone2D(playerid), name);
```

A zone is made of one or more boxes, and where boxes overlap the most
specific one wins. Finding the zone of a point looks only at the boxes of its
square of a grid of `ZONE_CELL_SIZE` metres, made when the script starts.
`Zone` walks with `foreach (new Zone:zoneid : N(GetZoneCount()))`.

`OnPlayerLeftZone` and `OnPlayerEnteredZone` tell when the zone of a player
changes, at any height as `GetPlayerZone2D` finds it, in the world
`ZONE_WORLD` and the interior `ZONE_INTERIOR` alone. Every box is an area of
the streamer, and the zone is found again only when a player crosses the
edge of one. Going to another world or interior leaves the zone, and coming
back enters it again.

## API

### `GetZoneAtPoint`

```pawn
forward Zone:GetZoneAtPoint(Float:x, Float:y, Float:z);
```

Find the zone of a point.

| Parameter | Description |
| --- | --- |
| `x` | World X. |
| `y` | World Y. |
| `z` | World Z. |

**Returns**

- the zone
- `INVALID_ZONE_ID` the point is in no zone

### `GetZoneAtPoint2D`

```pawn
forward Zone:GetZoneAtPoint2D(Float:x, Float:y);
```

Find the zone of a point on the map, at any height.

| Parameter | Description |
| --- | --- |
| `x` | World X. |
| `y` | World Y. |

**Returns**

- the zone
- `INVALID_ZONE_ID` the point is in no zone

### `GetPlayerZone`

```pawn
forward Zone:GetPlayerZone(playerid);
```

Find the zone a player is in.

| Parameter | Description |
| --- | --- |
| `playerid` | The player. |

**Returns**

- the zone
- `INVALID_ZONE_ID` when:
    + `playerid` is not connected
    + they are in no zone

### `GetPlayerZone2D`

```pawn
forward Zone:GetPlayerZone2D(playerid);
```

Find the zone a player is in, at any height.

| Parameter | Description |
| --- | --- |
| `playerid` | The player. |

**Returns**

- the zone
- `INVALID_ZONE_ID` when:
    + `playerid` is not connected
    + they are in no zone

### `GetVehicleZone`

```pawn
forward Zone:GetVehicleZone(vehicleid);
```

Find the zone a vehicle is in.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |

**Returns**

- the zone
- `INVALID_ZONE_ID` when:
    + `vehicleid` does not exist
    + it is in no zone

### `GetVehicleZone2D`

```pawn
forward Zone:GetVehicleZone2D(vehicleid);
```

Find the zone a vehicle is in, at any height.

| Parameter | Description |
| --- | --- |
| `vehicleid` | The vehicle. |

**Returns**

- the zone
- `INVALID_ZONE_ID` when:
    + `vehicleid` does not exist
    + it is in no zone

### `GetZoneCount`

```pawn
forward GetZoneCount();
```

Count the zones of the map.

**Returns**

How many there are.

### `IsValidZone`

```pawn
forward bool:IsValidZone(Zone:zoneid);
```

Whether a zone exists.

| Parameter | Description |
| --- | --- |
| `zoneid` | The zone. |

**Returns**

- `true` it exists
- `false` it does not

### `GetZoneName`

```pawn
forward bool:GetZoneName(Zone:zoneid, output[], size = sizeof (output));
```

Read the name of a zone.

| Parameter | Description |
| --- | --- |
| `zoneid` | The zone. |
| `output` | Reads back the name. |
| `size` | Size of `output`. |

**Returns**

- `true` it was read
- `false` the zone does not exist, and `output` is left alone

### `GetZoneSound`

```pawn
forward bool:GetZoneSound(Zone:zoneid, &soundid);
```

Read the sound of the name of a zone, as the story mode says it.

| Parameter | Description |
| --- | --- |
| `zoneid` | The zone. |
| `soundid` | Reads back the sound. |

**Returns**

- `true` it was read
- `false` the zone does not exist

### `GetZoneAreaCount`

```pawn
forward bool:GetZoneAreaCount(Zone:zoneid, &count);
```

Count the boxes of a zone.

| Parameter | Description |
| --- | --- |
| `zoneid` | The zone. |
| `count` | Reads back how many. |

**Returns**

- `true` it was read
- `false` the zone does not exist

### `GetZoneAreaPos`

```pawn
forward GetZoneAreaPos(Zone:zoneid, &Float:minX = 0.0, &Float:minY = 0.0, &Float:minZ = 0.0, &Float:maxX = 0.0, &Float:maxY = 0.0, &Float:maxZ = 0.0, start = 0);
```

Read the next box of a zone.

| Parameter | Description |
| --- | --- |
| `zoneid` | The zone. |
| `minX` | Reads back the lowest X. |
| `minY` | Reads back the lowest Y. |
| `minZ` | Reads back the lowest Z. |
| `maxX` | Reads back the highest X. |
| `maxY` | Reads back the highest Y. |
| `maxZ` | Reads back the highest Z. |
| `start` | Where to look from, one past the last index returned. |

**Returns**

- the index of the box
- `-1` there are no more, or the zone does not exist

## Events

### `OnPlayerEnteredZone`

```pawn
event OnPlayerEnteredZone(playerid, Zone:zoneid);
```

A player came into a zone, by walking, driving, spawning or coming back to the world and the interior of the zones.

| Parameter | Description |
| --- | --- |
| `playerid` | The player. |
| `zoneid` | The zone. |

### `OnPlayerLeftZone`

```pawn
event OnPlayerLeftZone(playerid, Zone:zoneid);
```

A player went out of a zone, into another, off the map or to another world or interior. It comes before the zone they entered.

| Parameter | Description |
| --- | --- |
| `playerid` | The player. |
| `zoneid` | The zone. |
