# SSI\dictionary

```pawn
#include <SSI\dictionary>
```

## Requirements

- `SSI\collection`

## Quick Start

Dictionaries hold a value for each key. Setting, finding and removing a key
take about the same time with ten keys or with a hundred thousand. The
brackets of the declaration pick the kind of key, and every call names a
dictionary of text keys with `<>`:

```pawn
#include <SSI\dictionary>

static
    Dictionary:Expiry<MAX_EXPIRY_BUCKETS>,
    Dictionary:Command<MAX_COMMANDS, MAX_COMMAND_LENGTH>
;

Dictionary_Set(Expiry, second, _:bucket);
Dictionary_Set(Command<>, "help", _:COMMAND_HELP);

new
    value
;

if (Dictionary_Get(Command<>, "help", value)) {
}

foreach (new entry : Command) {
    new
        name[MAX_COMMAND_LENGTH + 1]
    ;

    Dictionary_Key(Command<>, entry, name);
    printf("%s: %d", name, Dictionary_Value(Command<>, entry));
}
```

- `Name<SIZE>` holds number keys: any number a cell holds.
- `Name<SIZE, LENGTH>` holds text keys of `LENGTH` characters at most,
  compared as bytes, case and all.

The dictionary is named by its tag, which its entries carry. Keys and values
take any tag, as in PawnPlus.

## API

### `Dictionary_Set`

```pawn
forward bool:Dictionary_Set(Dictionary:dictionary<>, key, value);
```

Give a key a value, adding the key when it is new.

| Parameter | Description |
| --- | --- |
| `dictionary` | `Name`, or `Name<>` for text keys. |
| `key` | The key: a number, or text with `Name<>`. |
| `value` | Its value. |

**Returns**

- `true` the key has the value
- `false` the key is new and the dictionary is full, or the text
  is longer than the dictionary takes

### `Dictionary_Get`

```pawn
forward bool:Dictionary_Get(Dictionary:dictionary<>, key, &value);
```

The value of a key.

| Parameter | Description |
| --- | --- |
| `dictionary` | `Name`, or `Name<>` for text keys. |
| `key` | The key: a number, or text with `Name<>`. |
| `value` | Where to write the value, when the key is there. |

**Returns**

- `true` the key is there
- `false` it is not

### `Dictionary_Contains`

```pawn
forward bool:Dictionary_Contains(Dictionary:dictionary<>, key);
```

Whether a key is there.

| Parameter | Description |
| --- | --- |
| `dictionary` | `Name`, or `Name<>` for text keys. |
| `key` | The key: a number, or text with `Name<>`. |

**Returns**

- `true` it is there
- `false` it is not

### `Dictionary_Remove`

```pawn
forward bool:Dictionary_Remove(Dictionary:dictionary<>, key);
```

Remove a key and its value.

| Parameter | Description |
| --- | --- |
| `dictionary` | `Name`, or `Name<>` for text keys. |
| `key` | The key: a number, or text with `Name<>`. |

**Returns**

- `true` it was removed
- `false` it was not there

### `Dictionary_Count`

```pawn
forward Dictionary_Count(Dictionary:dictionary<>);
```

How many keys a dictionary holds.

| Parameter | Description |
| --- | --- |
| `dictionary` | `Name`, or `Name<>` for text keys. |

**Returns**

- the count

### `Dictionary_Clear`

```pawn
forward Dictionary_Clear(Dictionary:dictionary<>);
```

Remove every key.

It takes as long as the keys held, not as the size, so a dictionary filled
and emptied for each load costs what that load put in.

| Parameter | Description |
| --- | --- |
| `dictionary` | `Name`, or `Name<>` for text keys. |

### `Dictionary_Key`

```pawn
forward Dictionary_Key(Dictionary:dictionary<>, entry, key[] = "");
```

The key of an entry, as `foreach` walks them.

A number key is returned. A text key is copied into `key`, unpacked.

| Parameter | Description |
| --- | --- |
| `dictionary` | `Name`, or `Name<>` for text keys. |
| `entry` | The entry. |
| `key` | Where to write a text key, an array of known size. |

**Returns**

- the number key

### `Dictionary_Value`

```pawn
forward Dictionary_Value(Dictionary:dictionary<>, entry);
```

The value of an entry, as `foreach` walks them.

| Parameter | Description |
| --- | --- |
| `dictionary` | `Name`, or `Name<>` for text keys. |
| `entry` | The entry. |

**Returns**

- the value
