# SSI_Extra\inline-object

```pawn
#include <SSI_Extra\inline-object>
```

## Requirements

- `SSI\iterator`
- `SSI\hooks`
- `SSI\inline`
- [streamer](https://github.com/samp-incognito/samp-streamer-plugin)

## Quick Start

Dynamic objects that call an inline when they finish moving, while a player
edits them, or when a player selects one:

```pawn
#include <SSI_Extra\inline-object>

OpenGate(playerid, STREAMER_TAG_OBJECT:gate) {
    inline OnOpened() {
        SendClientMessage(playerid, -1, "The gate is open.");
    }

    DynamicObject_MoveInline(gate, 10.0, 0.0, 3.0, 2.0, using inline OnOpened);
}

Place(playerid, STREAMER_TAG_OBJECT:objectid) {
    inline OnEdited(EDIT_RESPONSE:response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
        if (response != EDIT_RESPONSE_FINAL) {
            @return;
        }

        SetDynamicObjectPos(objectid, x, y, z);
        SetDynamicObjectRot(objectid, rx, ry, rz);
    }

    DynamicObject_EditInline(playerid, objectid, using inline OnEdited);
}
```

- A move calls its inline once, when the object reaches the place it was
  sent to. A new move with an inline replaces the old one. An object that
  is stopped, or moved somewhere else without an inline, never calls the old
  inline, which is freed on the next arrival.
- An edit calls its inline on every update, and frees it after the last
  answer, kept or cancelled.
- A selection calls its inline once, with the object, its model and where
  it was hit.
- A player edits or selects one thing at a time: a new edit or selection
  frees the inline of the old one, and so does leaving.
- A move keeps its inline and where it goes in the object's own streamer
  data, under keys of their own, so `E_STREAMER_EXTRA_ID` stays free and an
  id the streamer hands out again starts with none.
- `DestroyDynamicObject` frees the inlines of the object.
  `Streamer_DestroyAllItems` does not: destroy the objects one by one.

## API

### `DynamicObject_MoveInline`

```pawn
forward DynamicObject_MoveInline(STREAMER_TAG_OBJECT:objectid, Float:x, Float:y, Float:z, Float:speed, Inline:callback<>, Float:rx = -1000.0, Float:ry = -1000.0, Float:rz = -1000.0);
```

Move an object, then call an inline when it gets there.

| Parameter | Description |
| --- | --- |
| `objectid` | The object. |
| `x` | Where to, on the x axis. |
| `y` | Where to, on the y axis. |
| `z` | Where to, on the z axis. |
| `speed` | The speed. |
| `callback` | The inline, as `using inline Name`, taking nothing. |
| `rx` | The rotation on the x axis, `-1000.0` to keep it. |
| `ry` | The rotation on the y axis, `-1000.0` to keep it. |
| `rz` | The rotation on the z axis, `-1000.0` to keep it. |

**Returns**

- the time the move takes, in milliseconds
- `0` the inline is freed, when:
    + the inline could not be captured
    + the object could not move

### `DynamicObject_EditInline`

```pawn
forward bool:DynamicObject_EditInline(playerid, STREAMER_TAG_OBJECT:objectid, Inline:callback<iffffff>);
```

Let a player edit an object, and call an inline with each answer.

| Parameter | Description |
| --- | --- |
| `playerid` | The player. |
| `objectid` | The object. |
| `callback` | The inline, as `using inline Name`, taking the response and the position and rotation. |

**Returns**

- `true` the editor is open
- `false` the inline is freed, when:
    + the inline could not be captured
    + the player is not connected
    + the object does not exist

### `DynamicObject_SelectInline`

```pawn
forward bool:DynamicObject_SelectInline(playerid, Inline:callback<iifff>);
```

Let a player select an object, and call an inline with it.

| Parameter | Description |
| --- | --- |
| `playerid` | The player. |
| `callback` | The inline, as `using inline Name`, taking the object, its model and where it was hit. |

**Returns**

- `true` the player is selecting
- `false` the inline is freed, when:
    + the inline could not be captured
    + the player is not connected
