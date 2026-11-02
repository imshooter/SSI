# SSI\inline

```pawn
#include <SSI\inline>
```

## Requirements

- `SSI\amx`
- `SSI\collection`
- `SSI\hooks`

## Quick Start

Inline functions: a function written inside another, that reads and changes
the arguments of the outer function and the locals it had where the inline
is written, and can be called after the outer function returned, as by a
timer:

```pawn
#include <SSI\inline>

Remind(playerid) {
    new
        minutes = 0
    ;

    inline OnTick() {
        ++minutes;
        SendClientMessage(playerid, -1, "%d minutes", minutes);
    }

    Timer_StartInline(using inline OnTick, 60000);
}
```

- `using inline Name` captures it: a copy of the arguments of the outer
  function and of its locals written before the inline. A function that
  takes an `Inline:` captures it on the call, so `using inline` only makes
  the call easier to read.
- `@.closure(...)` calls it. A call runs on the copy and keeps what the
  inline changed for the next call. The outer function never sees the
  changes. `@once.closure(...)`, or `@@.closure(...)`, calls it once and
  frees it.
- Parameters are cells of any tag, or arrays of a given size, which take a
  string: `inline OnAnswer(response, text[64])`. A parameter the call leaves
  out is `0`, or an empty string. References are not allowed.
- `return` belongs to the outer function, so it returns a value of its type.
  `@return value;` returns any value, and `@return;` only ends the call.
  `break` and `continue` end it too.
- Arguments passed by reference, and arrays passed as arguments, point to
  memory of whoever called the outer function: an inline called after the
  outer function returned must not use them.
- A capture holds at most `SSI_INLINE_CELLS` cells, counting the arguments
  and the locals it copies. A larger capture gives `INVALID_INLINE`. The
  parameters of the inline are written on the stack at each call, so they do
  not count.

A function that takes an inline:

```pawn
static
    Inline:gDialog[MAX_PLAYERS] = { INVALID_INLINE, ... }
;

stock Dialog_ShowInline(playerid, Inline:callback<iis>, style, const title[], const body[], const button1[], const button2[] = "") {
    Inline_Free(gDialog[playerid]);
    gDialog[playerid] = callback;

    return ShowPlayerDialog(playerid, DIALOG_ID, style, title, body, button1, button2);
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
    new const
        Inline:callback = gDialog[playerid]
    ;

    gDialog[playerid] = INVALID_INLINE;
    @once.callback(response, listitem, inputtext);

    return 1;
}
```

- Whoever takes an `Inline:` owns it, and ends it with `Inline_CallOnce`,
  `@once.` or `@@.`, which call and free it, or with `Inline_Free`. They do
  nothing with a handle freed or never made, so `INVALID_INLINE` needs no
  check.
- `Inline:callback<iis>` takes only an inline with those parameters: `i` a
  cell, `f` a float, `s` a string. Another shape stops with a run time error
  at the capture, naming the inline. A float and a cell look the same there.
- A handle of one shape does not go where another is wanted, and any of them
  goes into an `Inline:`.
- `Inline_Count` tells how many captures are alive, which a test can check
  for leaks.

An inline can belong to something, as with y_ebc. It is freed when that
thing goes, so an answer that comes later, as from the database, never runs,
even when something else took its id by then:

```pawn
MySQL_ThreadedQueryInline(gDatabase, EBC(playerid, using inline OnFound), "SELECT ...");
```

The tag of the owner tells what it is. Without one it is a player, freed when
they leave. `Vehicle:`, `Object:` and `Pickup:` are freed by `DestroyVehicle`,
`DestroyObject` and `DestroyPickup`, so a vehicle is written
`EBC(Vehicle:vehicleid, using inline OnFound)`. A library with a tag of its
own frees those with `Inline_FreeOwned` when it destroys one.

## API

### `EBC`

```pawn
forward InlineSite:EBC(owner, InlineSite:callback);
```

Give an inline to an owner, as y_ebc does: it is freed, and never called again, when the owner goes.

```pawn
MySQL_ThreadedQueryInline(gDatabase, EBC(playerid, using inline OnFound), "SELECT ...");
Timer_StartInline(EBC(Vehicle:vehicleid, using inline OnTick), 1000);
```

The owner is a variable, whose tag tells what it is, or an id written with
its tag, as `Vehicle:vehicleid`. It goes to the capture made by the `Inline:`
it is passed as.

| Parameter | Description |
| --- | --- |
| `owner` | The owner. |
| `callback` | The inline, as `using inline Name`. |

### `Inline_Call`

```pawn
forward Inline_Call({Inline, SSI@Inline_Callee}:closure, OPEN_MP_TAGS:...);
```

Call a captured inline. `@.closure(...)` does the same.

| Parameter | Description |
| --- | --- |
| `closure` | The inline. |
| `...` | Its parameters, in order. |

**Returns**

- what the inline returns, `0` when it ends without a value
- `0` the inline was freed, or never made

### `Inline_CallOnce`

```pawn
forward Inline_CallOnce({Inline, SSI@Inline_Callee}:closure, OPEN_MP_TAGS:...);
```

Call a captured inline once, then free it.

| Parameter | Description |
| --- | --- |
| `closure` | The inline. |
| `...` | Its parameters, in order. |

**Returns**

- what the inline returns, `0` when it ends without a value
- `0` the inline was freed, or never made

### `Inline_Free`

```pawn
forward bool:Inline_Free(Inline:closure);
```

Free a captured inline.

Freeing it while it runs is safe: the call goes on, and keeps nothing.

| Parameter | Description |
| --- | --- |
| `closure` | The inline. |

**Returns**

- `true` it is freed
- `false` it was freed already, or never made

### `Inline_IsValid`

```pawn
forward bool:Inline_IsValid(Inline:closure);
```

Whether a captured inline can still be called.

| Parameter | Description |
| --- | --- |
| `closure` | The inline. |

**Returns**

- `true` it can
- `false` it was freed, or never made

### `Inline_Count`

```pawn
forward Inline_Count();
```

How many captures are alive.

**Returns**

- the count

### `Inline_Give`

```pawn
forward bool:Inline_Give(Inline:closure, owner);
```

Give a captured inline to an owner, as `EBC` does at the capture, in place of the owner it had.

| Parameter | Description |
| --- | --- |
| `closure` | The inline. |
| `owner` | The owner, as `EBC` takes it. |

**Returns**

- `true` it is given
- `false` it was freed, or never made

### `Inline_FreeOwned`

```pawn
forward Inline_FreeOwned(owner);
```

Free every inline of an owner, as when it is destroyed. A library calls it for the owners of its own tag.

| Parameter | Description |
| --- | --- |
| `owner` | The owner, as `EBC` takes it. |

**Returns**

- how many were freed
