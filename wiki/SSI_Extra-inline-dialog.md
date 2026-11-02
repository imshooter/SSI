# SSI_Extra\inline-dialog

```pawn
#include <SSI_Extra\inline-dialog>
```

## Requirements

- `SSI\hooks`
- `SSI\inline`
- `SSI\va`

## Quick Start

Dialogs answered by an inline:

```pawn
#include <SSI_Extra\inline-dialog>

AskName(playerid) {
    inline OnAnswer(response, listitem, inputtext[MAX_PLAYER_NAME + 1]) {
        if (!response) {
            @return;
        }

        SetPlayerName(playerid, inputtext);
    }

    Dialog_ShowInputInline(playerid, using inline OnAnswer, "Name", "Your new name:", "Save", "Cancel");
}
```

- The inline takes the response, the list item and the text, and is called
  once.
- A new dialog for the same player takes the place of the one waiting: the
  old inline is freed and never called. So is the inline of a player who
  leaves, or of a dialog closed with `Dialog_Close`.
- Every dialog shown here uses `SSI_DIALOG_ID`. A dialog with another id
  never reaches an inline.

## API

### `Dialog_ShowInline`

```pawn
forward bool:Dialog_ShowInline(playerid, Inline:callback<iis>, DIALOG_STYLE:style, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...);
```

Show a dialog whose answer calls an inline.

The body is formatted with the arguments after `button2`, as
`ShowPlayerDialog` does.

| Parameter | Description |
| --- | --- |
| `playerid` | The player. |
| `callback` | The inline, as `using inline Name`, taking the response, the list item and the text. |
| `style` | The style. |
| `title` | The title. |
| `body` | The body. |
| `button1` | The left button. |
| `button2` | The right button, empty for none. |

**Returns**

- `true` it is shown
- `false` the inline is freed, when:
    + the player is not connected
    + the inline could not be captured
    + the dialog could not be shown

### `Dialog_ShowMessageBoxInline`

```pawn
forward bool:Dialog_ShowMessageBoxInline(playerid, Inline:callback<iis>, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...);
```

`Dialog_ShowInline` with `DIALOG_STYLE_MSGBOX`.

### `Dialog_ShowInputInline`

```pawn
forward bool:Dialog_ShowInputInline(playerid, Inline:callback<iis>, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...);
```

`Dialog_ShowInline` with `DIALOG_STYLE_INPUT`.

### `Dialog_ShowListInline`

```pawn
forward bool:Dialog_ShowListInline(playerid, Inline:callback<iis>, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...);
```

`Dialog_ShowInline` with `DIALOG_STYLE_LIST`.

### `Dialog_ShowPasswordInline`

```pawn
forward bool:Dialog_ShowPasswordInline(playerid, Inline:callback<iis>, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...);
```

`Dialog_ShowInline` with `DIALOG_STYLE_PASSWORD`.

### `Dialog_ShowTabListInline`

```pawn
forward bool:Dialog_ShowTabListInline(playerid, Inline:callback<iis>, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...);
```

`Dialog_ShowInline` with `DIALOG_STYLE_TABLIST`.

### `Dialog_ShowTabListHeadersInline`

```pawn
forward bool:Dialog_ShowTabListHeadersInline(playerid, Inline:callback<iis>, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...);
```

`Dialog_ShowInline` with `DIALOG_STYLE_TABLIST_HEADERS`.

### `Dialog_Close`

```pawn
forward bool:Dialog_Close(playerid);
```

Close the inline dialog of a player without calling its inline.

| Parameter | Description |
| --- | --- |
| `playerid` | The player. |

**Returns**

- `true` it was closed
- `false` no inline dialog was waiting

### `Dialog_IsOpen`

```pawn
forward bool:Dialog_IsOpen(playerid);
```

Whether an inline dialog waits for an answer from a player.

| Parameter | Description |
| --- | --- |
| `playerid` | The player. |

**Returns**

- `true` it does
- `false` it does not
