# SSI\bits

```pawn
#include <SSI\bits>
```

## Requirements

- `SSI\collection`

## Quick Start

Sets of bits, as y_bit keeps them: one bit for each id up to a size, 32 to a
cell.

```pawn
static
    Bits:Seen<MAX_VEHICLES>,
    Bits:PlayerGroup[MAX_PLAYERS]<MAX_GROUPS>
;

Bits_Let(Seen, vehicleid);

if (Bits_Test(PlayerGroup[playerid], groupid)) {
}

foreach (new Group:groupid : Bits(PlayerGroup[playerid])) {
}
```

- `Bits:Name<SIZE>` declares a set of `SIZE` bits, and `Bits:Name[COUNT]<SIZE>`
  one for each of `COUNT` ids. Either is a plain array of cells, so a set is
  passed as `Name` or `Name[id]`, and works as a field of an enum too.
- A size and an index may carry a tag.
- The names are the ones of y_bit. `Bits_Set` turns a bit on or off, as told,
  `Bits_Let` turns it on, `Bits_Vet` turns it off and `Bits_Clear` turns every
  bit off.
- `Bits_Test`, `Bits_Set`, `Bits_Let` and `Bits_Vet` are macros, so the index
  is read twice and must have no side effect. Like any index of an array, it
  must be inside the set.
- `foreach (new i : Bits(Name))` walks the bits that are on, in order,
  skipping every empty cell at once.

## API

### `Bits_Test`

```pawn
forward bool:Bits_Test(const bits[], index);
```

Whether a bit is on.

| Parameter | Description |
| --- | --- |
| `bits` | The set. |
| `index` | The bit. |

**Returns**

- `true` it is on
- `false` it is off

### `Bits_Set`

```pawn
forward Bits_Set(bits[], index, bool:set);
```

Turn a bit on or off.

| Parameter | Description |
| --- | --- |
| `bits` | The set. |
| `index` | The bit. |
| `set` | Whether it is on. |

### `Bits_Let`

```pawn
forward Bits_Let(bits[], index);
```

Turn a bit on.

| Parameter | Description |
| --- | --- |
| `bits` | The set. |
| `index` | The bit. |

### `Bits_Vet`

```pawn
forward Bits_Vet(bits[], index);
```

Turn a bit off.

| Parameter | Description |
| --- | --- |
| `bits` | The set. |
| `index` | The bit. |

### `Bits_Clear`

```pawn
forward Bits_Clear(bits[], size = sizeof (bits));
```

Turn every bit off.

| Parameter | Description |
| --- | --- |
| `bits` | The set. |
| `size` | Cells of the set. |

### `Bits_Count`

```pawn
forward Bits_Count(const bits[], size = sizeof (bits));
```

The number of bits on.

| Parameter | Description |
| --- | --- |
| `bits` | The set. |
| `size` | Cells of the set. |

**Returns**

The count.

### `Bits_IsEmpty`

```pawn
forward bool:Bits_IsEmpty(const bits[], size = sizeof (bits));
```

Whether every bit is off.

| Parameter | Description |
| --- | --- |
| `bits` | The set. |
| `size` | Cells of the set. |

**Returns**

- `true` every bit is off
- `false` at least one is on

### `Bits_Or`

```pawn
forward Bits_Or(bits[], const other[], size = sizeof (bits));
```

Turn on every bit that is on in another set.

| Parameter | Description |
| --- | --- |
| `bits` | The set to change. |
| `other` | The set to add. |
| `size` | Cells of both sets. |

### `Bits_Copy`

```pawn
forward Bits_Copy(bits[], const other[], size = sizeof (bits));
```

Make a set the same as another.

| Parameter | Description |
| --- | --- |
| `bits` | The set to change. |
| `other` | The set to copy. |
| `size` | Cells of both sets. |

### `Bits_Intersects`

```pawn
forward bool:Bits_Intersects(const bits[], const other[], size = sizeof (bits));
```

Whether two sets have a bit on in common.

| Parameter | Description |
| --- | --- |
| `bits` | One set. |
| `other` | The other. |
| `size` | Cells of both sets. |

**Returns**

- `true` they do
- `false` they do not
