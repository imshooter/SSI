# SSI_Vehicle\speed-camera

```pawn
#include <SSI_Vehicle\speed-camera>
```

## Requirements

- `SSI_Vehicle\math`
- `SSI\collection`
- `SSI\dictionary`
- `SSI\inline`
- `SSI_Extra\inline-timers`
- `SSI\hooks`
- [streamer](https://github.com/samp-incognito/samp-streamer-plugin)

## Quick Start

Speed cameras: a pole by the road and a sphere of streamer area around it.
A driver who enters the sphere faster than the limit of the camera is caught,
and the script is told.

```pawn
new const
    SpeedCamera:cameraid = CreateSpeedCamera(1363.0, -1288.3, 13.3, 180.0, 60.0)
;

hook OnPlayerTriggeredSpeedCamera(playerid, SpeedCamera:cameraid, Float:speed, Float:limit) {
    GivePlayerMoney(playerid, -100);

    return 1;
}
```

- The speed is read once, as the vehicle enters, so a pass is counted once.
- Speeds are `GetVehicleSpeed` with the multiplier of
  `SetSpeedCameraMultiplier`, `VEHICLE_SPEED_MULTIPLIER` until the script
  sets another, and limits are written in the same unit.
- `OnPlayerTriggerSpeedCamera` can refuse a pass, as for a police car.
- With `SPEED_CAMERA_FLASH` defined before the include, the screen of a
  driver caught flashes white for `SPEED_CAMERA_FLASH_TIME` milliseconds.

## API

### `CreateSpeedCamera`

```pawn
forward SpeedCamera:CreateSpeedCamera(Float:x, Float:y, Float:z, Float:angle, Float:limit, Float:range = SPEED_CAMERA_RANGE, modelid = SPEED_CAMERA_MODEL, worldid = -1, interiorid = -1);
```

Put a speed camera by the road.

| Parameter | Description |
| --- | --- |
| `x` | X of the pole. |
| `y` | Y of the pole. |
| `z` | Z of the ground at the pole. |
| `angle` | Where the camera faces. |
| `limit` | Speed above which a driver is caught, in the units of `SetSpeedCameraMultiplier`. |
| `range` | Radius of the sphere watched. |
| `modelid` | Object of the pole. |
| `worldid` | Virtual world, `-1` for every one. |
| `interiorid` | Interior, `-1` for every one. |

**Returns**

- the camera
- `INVALID_SPEED_CAMERA_ID` when `MAX_SPEED_CAMERAS` already
  exist

### `DestroySpeedCamera`

```pawn
forward bool:DestroySpeedCamera(SpeedCamera:cameraid);
```

Take a speed camera away.

| Parameter | Description |
| --- | --- |
| `cameraid` | The camera. |

**Returns**

- `true` it was taken away
- `false` `cameraid` is not a camera

### `IsValidSpeedCamera`

```pawn
forward bool:IsValidSpeedCamera(SpeedCamera:cameraid);
```

Whether a speed camera exists.

| Parameter | Description |
| --- | --- |
| `cameraid` | The camera. |

### `SetSpeedCameraLimit`

```pawn
forward bool:SetSpeedCameraLimit(SpeedCamera:cameraid, Float:limit);
```

Change the limit of a speed camera.

| Parameter | Description |
| --- | --- |
| `cameraid` | The camera. |
| `limit` | The new limit. |

**Returns**

- `true` it was changed
- `false` `cameraid` is not a camera

### `GetSpeedCameraLimit`

```pawn
forward Float:GetSpeedCameraLimit(SpeedCamera:cameraid);
```

The limit of a speed camera.

| Parameter | Description |
| --- | --- |
| `cameraid` | The camera. |

**Returns**

- the limit
- `0.0` when `cameraid` is not a camera

### `GetSpeedCameraPos`

```pawn
forward bool:GetSpeedCameraPos(SpeedCamera:cameraid, &Float:x, &Float:y, &Float:z);
```

Where a speed camera stands.

| Parameter | Description |
| --- | --- |
| `cameraid` | The camera. |
| `x` | Where its X goes. |
| `y` | Where its Y goes. |
| `z` | Where its Z goes. |

**Returns**

- `true` it was read
- `false` `cameraid` is not a camera

### `SetSpeedCameraMultiplier`

```pawn
forward SetSpeedCameraMultiplier(Float:multiplier);
```

Set the unit of every speed camera, as the multiplier of `GetVehicleSpeed`.

Limits are not converted, so set it before creating cameras.

| Parameter | Description |
| --- | --- |
| `multiplier` | `VEHICLE_SPEED_KMH`, `VEHICLE_SPEED_MPH`, or the factor of any other unit. |

### `GetSpeedCameraMultiplier`

```pawn
forward Float:GetSpeedCameraMultiplier();
```

The multiplier speed cameras read speeds with.

## Events

### `OnPlayerTriggerSpeedCamera`

```pawn
event OnPlayerTriggerSpeedCamera(playerid, SpeedCamera:cameraid, Float:speed, Float:limit);
```

A driver is about to be caught passing a speed camera faster than its limit.

| Parameter | Description |
| --- | --- |
| `playerid` | The driver. |
| `cameraid` | The camera. |
| `speed` | Their speed. |
| `limit` | The limit of the camera. |

**Returns**

- `0` they are caught
- `1` they are not

### `OnPlayerTriggeredSpeedCamera`

```pawn
event OnPlayerTriggeredSpeedCamera(playerid, SpeedCamera:cameraid, Float:speed, Float:limit);
```

A driver was caught by a speed camera.

The return value is not used.

| Parameter | Description |
| --- | --- |
| `playerid` | The driver. |
| `cameraid` | The camera. |
| `speed` | Their speed. |
| `limit` | The limit of the camera. |
