# SSI\unique

```pawn
#include <SSI\unique>
```

## Quick Start

Unique names: every `#include <SSI\unique>` moves on to a new suffix
of two characters, and `SSI_UNIQUE<prefix...suffix>` writes the current one
where the `...` is. The same declaration in two files, each including this
first, becomes two names:

```pawn
#include <SSI\unique>

forward SSI_UNIQUE<@Reload_...>();
public SSI_UNIQUE<@Reload_...>() {
}
```

The suffixes run `00`, `01`, ... `0z`, `10`, ... `zz`, 4096 of them, and sort
in the order the includes were made, so names that differ only in it sort
from the first include to the last. `SSI_UNIQUE_COUNT` is how many includes
there have been, starting from 1.
