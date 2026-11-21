# SSI_World\map-file

```pawn
#include <SSI_World\map-file>
```

## Requirements

- `SSI\iterator`
- `SSI\hooks`
- [streamer](https://github.com/samp-incognito/samp-streamer-plugin)

## Quick Start

Loads a map file kept in scriptfiles, so a map is changed without touching
the gamemode. A map file is the lines a mapping tool writes: `CreateObject`,
`CreateDynamicObject`, `SetObjectMaterial`, `SetObjectMaterialText`,
`RemoveBuildingForPlayer` and `AddSimpleModel`.

```pawn
options(world, interior, stream distance)
```

sets the world, interior and stream distance of the objects after it in the
same file. `//` starts a comment, on its own line or after a call.

A material or a text goes on the last object made, and the object id written
in the call is ignored. A removal is done for every player connected now and
later, as one made by `RemoveMapBuilding`. A model is only added when its id
is free, since the server keeps the custom models when the gamemode
restarts.

Based on Southclaws' samp-object-loader, rewritten as an include.

## API

### `LoadMap`

```pawn
forward LoadMap(const filename[], worldid = -1, interiorid = -1, STREAMER_TAG_OBJECT:objects[] = { STREAMER_TAG_OBJECT:INVALID_STREAMER_ID }, size = 0);
```

Make everything a map file says.

| Parameter | Description |
| --- | --- |
| `filename` | File to read, from scriptfiles. |
| `worldid` | World the objects are in until an options line says otherwise, `-1` for every world. |
| `interiorid` | Interior the objects are in until an options line says otherwise, `-1` for every interior. |
| `objects` | Reads back the objects made, in the order the file makes them. Left out, nothing is read back. |
| `size` | Size of `objects`. Objects past it are still made. |

**Returns**

- how many objects were made
- `-1` the file could not be opened

### `RemoveMapBuilding`

```pawn
forward bool:RemoveMapBuilding(modelid, Float:x, Float:y, Float:z, Float:radius);
```

Remove buildings of the map for every player connected now and later.

| Parameter | Description |
| --- | --- |
| `modelid` | Model to remove, or `-1` for every model. |
| `x` | Centre on the X axis. |
| `y` | Centre on the Y axis. |
| `z` | Centre on the Z axis. |
| `radius` | Distance from the centre. |

**Returns**

- `true` the removal was kept
- `false` there are already `MAX_MAP_REMOVALS`

### `GetMapRemovalCount`

```pawn
forward GetMapRemovalCount();
```

How many buildings the loaded maps and `RemoveMapBuilding` remove.

**Returns**

- the count, up to `MAX_MAP_REMOVALS`

## Events

### `OnMapBuildingRemoved`

```pawn
event OnMapBuildingRemoved(modelid, Float:x, Float:y, Float:z, Float:radius);
```

Buildings of the map were removed for every player, so what else knows the map, such as physics, can remove them too.

| Parameter | Description |
| --- | --- |
| `modelid` | Model removed, or `-1` for every model. |
| `x` | Centre on the X axis. |
| `y` | Centre on the Y axis. |
| `z` | Centre on the Z axis. |
| `radius` | Distance from the centre. |
