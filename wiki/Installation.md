# Installation

## Requirements

* An open.mp server and its includes, [omp-stdlib](https://github.com/openmultiplayer/omp-stdlib).
* The community Pawn compiler, version 3.10.11 or newer, which ships with open.mp as `qawno/pawncc.exe`.

## Getting the files

With sampctl:

```bash
sampctl package install imshooter/SSI
```

By hand, copy the `SSI`, `SSI_Extra` and `SSI_Vehicle` folders into the include folder of the compiler, such as `qawno/include`. The tree then looks like this:

```
qawno/include/
    SSI/
    SSI_Extra/
    SSI_Vehicle/
```

## Including

Each library is included by its folder and name, and includes the libraries it needs by itself:

```pawn
#include <open.mp>
#include <SSI\collection>
#include <SSI\iterator>
#include <SSI\command>
#include <SSI\hooks>
```

`SSI\hooks` gives every file that includes it new names for its hooks, so a file that declares hooks includes it after every other include. The libraries that declare hooks of their own include it for themselves.

## What each library needs

Most libraries need nothing beyond open.mp. These need a plugin or component:

| Library | Needs |
| --- | --- |
| `SSI\iterator` | [PawnPlus](https://github.com/IllidanS4/PawnPlus) |
| `SSI_Extra\inline-object` | [streamer](https://github.com/samp-incognito/samp-streamer-plugin) |
| `SSI_Extra\inline-mysql` | [MySQL](https://github.com/imshooter/MySQL) |
| `SSI_Extra\inline-bcrypt` | [samp-bcrypt](https://github.com/Sreyas-Sreelal/samp-bcrypt) |
| `SSI_Extra\inline-argon2` | [async-crypto](https://github.com/roseeast/async-crypto) |
| `SSI_Extra\inline-pg` | [omp-postgresql](https://github.com/itskoleban/omp-postgresql) |
| `SSI_Vehicle\objective`, `SSI_Vehicle\neon`, `SSI_Vehicle\speed-camera` | [streamer](https://github.com/samp-incognito/samp-streamer-plugin) |
| `SSI_Vehicle\forklift` | [streamer](https://github.com/samp-incognito/samp-streamer-plugin), [3DAndreas](https://github.com/imshooter/3DAndreas) |

`SSI\group` allows and denies commands only when `SSI\command` is included before it.

## Compatibility

* `SSI\hooks` does not compile together with y_hooks, and `SSI\test` does not compile together with y_testing.
* When foreach or y_iterate is included before `SSI\collection`, the SSI loop is written `each` instead of `foreach`.
