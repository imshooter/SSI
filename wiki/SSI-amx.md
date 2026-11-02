# SSI\amx

```pawn
#include <SSI\amx>
```

## Quick Start

Access to the memory of the script beyond its data, for the libraries that
read or write code at run time: the code as the server relocated it, and the
header with its table of publics. Nothing here is meant to be called by a
script.

A data address is what Pawn uses, counted from the start of the data. A code
address counts from the start of the code, as `__addressof` gives it and as
the table of publics stores it. A base offset counts from the start of the
header, as the header stores its tables and the names of the publics.

`SSI@amxOpcode` holds the cell that the server stores for each opcode, read
from a sample of every opcode. A call or a jump stores the code address of
its target plus `SSI@amxDelta`. Adding `SSI@amxCode` to a code address gives
its data address, and adding `SSI@amxBase` to a base offset does the same.
