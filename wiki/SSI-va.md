# SSI\va

```pawn
#include <SSI\va>
```

## Requirements

- `SSI\amx`

## Quick Start

Variable arguments: `___(n)` passes on the arguments a function got, from
its `n`th on, anywhere among the arguments of a call, as y_va's `___`.

```pawn
stock SendFormatted(playerid, colour, const message[], OPEN_MP_TAGS:...) {
    return SendClientMessage(playerid, colour, message, ___(3));
}

stock PrintBetween(OPEN_MP_TAGS:...) {
    printf("%d %s %d", 5, ___(0), 8);
}
```

pawncc writes the number of arguments of every call as a constant, so the
first time a `___` runs it rewrites the call it is in: the arguments are
copied where pawncc would push one cell for the `___`, the count is taken
from the stack, and the arguments a native leaves behind are taken off by
that count. Nothing is scanned at start up. The arguments passed on must be
references, as the variable arguments of a function are. `n` must be a
constant, and a `___` must be an argument of the call itself, not part of an
expression. Code compiled with `-O2` is not supported.

## API

### `___`

```pawn
forward ___(first);
```

Pass on the arguments of the function this is written in.

| Parameter | Description |
| --- | --- |
| `first` | Index of the first argument passed on, a constant. |
