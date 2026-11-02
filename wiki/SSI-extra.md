# SSI\extra

```pawn
#include <SSI\extra>
```

## Requirements

- `SSI\hooks`

## Quick Start

Extra data: values kept on the ids of something else, with a row of cells
for each id and a column for each name. A column has a type, which is a
number, a float, a boolean or a string, and a default. Reading or writing a
number is an array index. Columns are made by name in a hook of
`OnExtraInit`, and every id starts with the default of each column:

```pawn
#include <SSI\extra>

new
    Extra:VehicleExtra<MAX_VEHICLES, 8>
;

static
    VehicleExtra:gFuelColumn,
    VehicleExtra:gPlateColumn
;

hook OnExtraInit() {
    gFuelColumn = Extra_Column(VehicleExtra, "fuel", EXTRA_FLOAT, 50.0);
    gPlateColumn = Extra_Column(VehicleExtra, "plate", EXTRA_STRING, 8);

    return 0;
}

Extra_Set(VehicleExtra, vehicleid, gFuelColumn, 37.5);
Extra_SetString(VehicleExtra, vehicleid, gPlateColumn, "ABC 123");

Extra_Reset(VehicleExtra, vehicleid);
```

- `Name<IDS, CELLS>` keeps a row of `CELLS` cells for each id below `IDS`.
  A number, a float or a boolean takes one cell. A string of `LENGTH`
  characters takes `(LENGTH + 1) char` cells, packed.
- A column is the cell it starts at, tagged `Name:`. Columns are laid out in
  the order they are made.
- A read gives the value back untagged. `Extra_Get` of a string column gives
  its first cell, which is `0` only when the text is empty.
- An id out of range is an array error, as with any array. The owner of the
  ids calls `Extra_Reset` when an id is made, so a reused id starts with the
  defaults again.
- `Extra_View` hands a row and its columns to a function that writes them
  somewhere else, such as a JSON document.

## API

### `Extra_Column`

```pawn
forward Extra_Column(Extra:extra<>, const name[], E_EXTRA_TYPE:type, value);
```

Make a column, or find the one made with the same name.

Every id gets the default. Called in a hook of `OnExtraInit`.

| Parameter | Description |
| --- | --- |
| `extra` | The extra. |
| `name` | Name of the column. |
| `type` | What it holds. |
| `value` | The default, of any tag: a float column takes a float such as `50.0`. For a string, the most characters it holds. The default of a string is empty. |

**Returns**

- the column, tagged with the extra
- `-1` when:
    + `name` is empty, or longer than `SSI_EXTRA_NAME`
    + a column of another type has that name
    + a string is shorter than a character, or longer than
      `SSI_EXTRA_STRING`
    + the row has no room left

### `Extra_Get`

```pawn
forward Extra_Get(Extra:extra<>, id, column);
```

The value of an id in a number, float or boolean column.

| Parameter | Description |
| --- | --- |
| `extra` | The extra. |
| `id` | The id. |
| `column` | The column. |

**Returns**

- the value, untagged

### `Extra_Set`

```pawn
forward Extra_Set(Extra:extra<>, id, column, value);
```

Give an id a value in a number, float or boolean column.

| Parameter | Description |
| --- | --- |
| `extra` | The extra. |
| `id` | The id. |
| `column` | The column. |
| `value` | The value, of any tag. |

**Returns**

- the value

### `Extra_GetString`

```pawn
forward bool:Extra_GetString(Extra:extra<>, id, column, output[], size = sizeof (output));
```

The text of an id in a string column.

| Parameter | Description |
| --- | --- |
| `extra` | The extra. |
| `id` | The id. |
| `column` | The column. |
| `output` | Reads back the text. |
| `size` | Size of `output`. |

**Returns**

- `true` the text was written
- `false` the column holds no string, and the output is cleared

### `Extra_SetString`

```pawn
forward bool:Extra_SetString(Extra:extra<>, id, column, const text[]);
```

Give an id a text in a string column.

Text longer than the cells of the column hold is cut. The cells are whole,
so a column of 8 characters holds 11.

| Parameter | Description |
| --- | --- |
| `extra` | The extra. |
| `id` | The id. |
| `column` | The column. |
| `text` | The text. |

**Returns**

- `true` the text is written
- `false` the column holds no string

### `Extra_Reset`

```pawn
forward Extra_Reset(Extra:extra<>, id);
```

Give an id the default of every column.

| Parameter | Description |
| --- | --- |
| `extra` | The extra. |
| `id` | The id. |

### `Extra_Type`

```pawn
forward E_EXTRA_TYPE:Extra_Type(Extra:extra<>, column);
```

What a column holds.

| Parameter | Description |
| --- | --- |
| `extra` | The extra. |
| `column` | The column. |

**Returns**

- the type

### `Extra_Name`

```pawn
forward bool:Extra_Name(Extra:extra<>, column, name[]);
```

The name of a column.

| Parameter | Description |
| --- | --- |
| `extra` | The extra. |
| `column` | The column. |
| `name` | Reads back the name, an array of known size. |

**Returns**

- `true` the name was written
- `false` the column is not made, and the name is cleared

## Events

### `OnExtraInit`

```pawn
event OnExtraInit();
```

The columns can be made.

Called when the script starts, from a hook of `OnGameModeInit`, or of
`OnFilterScriptInit` in a filterscript. The hooks of those callbacks run in
the order of the includes, so the ones declared before `SSI\extra` run
first. Include it before any file that reads or writes extra data when the
script starts. Modules make their columns here.
