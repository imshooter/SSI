# SSI\string

```pawn
#include <SSI\string>
```

## Quick Start

Strings changed in place and compared, beyond the natives of open.mp:

```pawn
new
    name[32] = "  grove street  "
;

String_Trim(name);
String_ToUpper(name);

switch (String_Hash(params, true)) {
    case HashI<gun>: {
    }
    case HashI<health>: {
    }
}
```

- Each function writes into the array it is given and takes its size last,
  `sizeof` by default. None returns a string.
- `Hash<text>` is the hash of a text written without quotes, worked out by
  the compiler, so it is a constant a `case` takes. `String_Hash` gives the
  same number for a string at run time. `HashI<text>` and
  `String_Hash(string, true)` ignore case. Two cases with the same hash do
  not compile, so a collision between them is never silent.
- A hashed text holds letters, digits, single spaces and `_ @ - .`. Any
  other character does not compile or gives another number.

## API

### `String_Hash`

```pawn
forward String_Hash(const string[], bool:ignorecase = false);
```

The hash of a string, the number `Hash<>` gives for the same text.

| Parameter | Description |
| --- | --- |
| `string` | The string. |
| `ignorecase` | Whether upper case letters count as lower case, as `HashI<>` does. |

**Returns**

- the hash

### `String_ToUpper`

```pawn
forward String_ToUpper(string[]);
```

Turn every letter of a string to upper case.

| Parameter | Description |
| --- | --- |
| `string` | The string. |

### `String_ToLower`

```pawn
forward String_ToLower(string[]);
```

Turn every letter of a string to lower case.

| Parameter | Description |
| --- | --- |
| `string` | The string. |

### `String_Trim`

```pawn
forward String_Trim(string[], const chars[] = "", STRING_EDGE:edge = STRING_EDGE_BOTH);
```

Remove characters from the edges of a string.

| Parameter | Description |
| --- | --- |
| `string` | The string. |
| `chars` | The characters to remove, or empty for spaces, tabs and line breaks. |
| `edge` | The edges to trim. |

**Returns**

- the new length

### `String_Pad`

```pawn
forward String_Pad(string[], length, const pad[] = " ", STRING_EDGE:edge = STRING_EDGE_RIGHT, size = sizeof (string));
```

Lengthen a string to `length` with copies of `pad`.

Padding both edges puts the odd character on the right.

| Parameter | Description |
| --- | --- |
| `string` | The string. |
| `length` | The length to reach, at most `size - 1`. |
| `pad` | The characters to repeat. |
| `edge` | The edges to pad. |
| `size` | Size of `string`. |

**Returns**

- the new length

### `String_Replace`

```pawn
forward String_Replace(string[], const search[], const replacement[], bool:ignorecase = false, limit = cellmax, size = sizeof (string));
```

Replace each occurrence of `search` in a string, from the left.

Text pushed past `size` is cut off.

| Parameter | Description |
| --- | --- |
| `string` | The string. |
| `search` | The text to find. |
| `replacement` | The text to put in its place. |
| `ignorecase` | Whether case is ignored when finding. |
| `limit` | The most occurrences to replace. |
| `size` | Size of `string`. |

**Returns**

- how many were replaced

### `String_Count`

```pawn
forward String_Count(const string[], const search[], bool:ignorecase = false);
```

How many times `search` occurs in a string, without overlaps.

| Parameter | Description |
| --- | --- |
| `string` | The string. |
| `search` | The text to find. |
| `ignorecase` | Whether case is ignored. |

**Returns**

- the count

### `String_StartsWith`

```pawn
forward bool:String_StartsWith(const string[], const prefix[], bool:ignorecase = false);
```

Whether a string starts with `prefix`.

| Parameter | Description |
| --- | --- |
| `string` | The string. |
| `prefix` | The start to look for. An empty one always matches. |
| `ignorecase` | Whether case is ignored. |

### `String_EndsWith`

```pawn
forward bool:String_EndsWith(const string[], const suffix[], bool:ignorecase = false);
```

Whether a string ends with `suffix`.

| Parameter | Description |
| --- | --- |
| `string` | The string. |
| `suffix` | The end to look for. An empty one always matches. |
| `ignorecase` | Whether case is ignored. |

### `String_Split`

```pawn
forward String_Split(const string[], const delimiter[], output[][], bool:ignorecase = false, count = sizeof (output), size = sizeof (output[]));
```

Split a string at each `delimiter` into the rows of `output`.

Empty pieces are kept, and the last row takes the rest of the string when
there are more pieces than rows. An empty `delimiter` gives the whole string.

| Parameter | Description |
| --- | --- |
| `string` | The string. |
| `delimiter` | The text between pieces. |
| `output` | Where the pieces go. |
| `ignorecase` | Whether case is ignored when finding `delimiter`. |
| `count` | Rows of `output`. |
| `size` | Size of each row. |

**Returns**

- how many rows were written, `0` only when `count` is `0`

### `String_Join`

```pawn
forward String_Join(output[], const glue[], const parts[][], count = sizeof (parts), size = sizeof (output));
```

Join the first `count` rows of `parts` into `output`, with `glue` between them.

| Parameter | Description |
| --- | --- |
| `output` | Where the text goes. |
| `glue` | The text between parts. |
| `parts` | The parts. |
| `count` | How many rows to join. |
| `size` | Size of `output`. |

**Returns**

- the length of `output`

### `String_Distance`

```pawn
forward String_Distance(const first[], const second[], bool:ignorecase = false);
```

The edit distance between two strings: how many characters must be inserted, removed or changed to turn one into the other.

Only the first `SSI_STRING_DISTANCE_MAX` characters of each are compared.

| Parameter | Description |
| --- | --- |
| `first` | A string. |
| `second` | Another string. |
| `ignorecase` | Whether case is ignored. |

**Returns**

- the distance, `0` for equal strings

### `String_UrlEncode`

```pawn
forward String_UrlEncode(output[], const input[], size = sizeof (output));
```

Encode a string for a URL: every byte but letters, digits and `- _ . ~` becomes `%` and two hex digits.

A byte that would not fit whole is left out with the rest.

| Parameter | Description |
| --- | --- |
| `output` | Where the text goes. |
| `input` | The string. |
| `size` | Size of `output`. |

**Returns**

- the length of `output`

### `String_UrlDecode`

```pawn
forward String_UrlDecode(output[], const input[], size = sizeof (output));
```

Decode a string from a URL: `%` and two hex digits become their byte and `+` a space.

| Parameter | Description |
| --- | --- |
| `output` | Where the text goes. |
| `input` | The encoded string. |
| `size` | Size of `output`. |

**Returns**

- the length of `output`
