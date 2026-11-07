# SSI

[![sampctl](https://img.shields.io/badge/sampctl-SSI-2f2f2f.svg?style=for-the-badge)](https://github.com/imshooter/SSI)

> [!NOTE]
> Experimental version, already running in production. Made with Claude Opus 5.5.

SSI is a set of Pawn libraries for open.mp, built the way YSI is: collections, iterators, hooks, inline functions, commands, groups and more. Each library is one include that works on its own, and the libraries talk to each other through events, so one can answer another without depending on it.

## Installation

Simply install to your project:

```bash
sampctl package install imshooter/SSI
```

Or copy the `SSI`, `SSI_Extra` and `SSI_Vehicle` folders into the include folder of your compiler, such as `qawno/include`.

Include in your code and begin using the library:

```pawn
#include <SSI\collection>
```

A file that declares hooks includes `SSI\hooks` after every other include. See [Installation](wiki/Installation.md) for the requirements of each library.

## Libraries

### SSI

| Library | Description |
| --- | --- |
| [amx](wiki/SSI-amx.md) | Access to the memory of the script beyond its data, for the libraries that read or write code at run time: the code as the server relocated it, and the header with its table of publics. |
| [bits](wiki/SSI-bits.md) | Sets of bits, as y_bit keeps them: one bit for each id up to a size, 32 to a cell. |
| [collection](wiki/SSI-collection.md) | Collections: the structures of these libraries under one name, as y_iterate keeps every iterator under `Iterator:`. |
| [command](wiki/SSI-command.md) | Commands, as Pawn.CMD and y_commands keep them: a function for each command, found by its name when a player types it. |
| [dictionary](wiki/SSI-dictionary.md) | Dictionaries hold a value for each key. |
| [extra](wiki/SSI-extra.md) | Extra data: values kept on the ids of something else, with a row of cells for each id and a column for each name. |
| [group](wiki/SSI-group.md) | Groups of players, as y_groups keeps them: a name, its members and what they may do. |
| [hooks](wiki/SSI-hooks.md) | Hooks, as in y_hooks: any number of functions for one callback, and hooks that replace a native or a function. |
| [inline](wiki/SSI-inline.md) | Inline functions: a function written inside another, that reads and changes the arguments of the outer function and the locals it had where the inline is written, and can be called after the outer function returned, as by a timer. |
| [iterator](wiki/SSI-iterator.md) | The ids the server hands out, in collections this script walks with `foreach`, as y_foreach keeps its iterators. |
| [queue](wiki/SSI-queue.md) | Queues hand out the rows of an array and take them back first in, first out. |
| [schedule](wiki/SSI-schedule.md) | Schedules hold a time for each id. |
| [string](wiki/SSI-string.md) | Strings changed in place and compared, beyond the natives of open.mp. |
| [task](wiki/SSI-task.md) | Functions that run on their own every so many milliseconds, as the tasks of y_timers. |
| [test](wiki/SSI-test.md) | Tests, as in y_testing: functions declared with `test` that the script runs one after another when it starts, with checks that print what failed and where. |
| [unique](wiki/SSI-unique.md) | Unique names: every `#include <SSI\unique>` moves on to a new suffix of two characters, and `SSI_UNIQUE<prefix...suffix>` writes the current one where the `...` is. |
| [va](wiki/SSI-va.md) | Variable arguments: `___(n)` passes on the arguments a function got, from its `n`th on, anywhere among the arguments of a call, as y_va's `___`. |

### SSI_Extra

| Library | Description |
| --- | --- |
| [inline-argon2](wiki/SSI_Extra-inline-argon2.md) | Hashing and checking passwords with Argon2id through the async_crypto plugin, answered by an inline. |
| [inline-bcrypt](wiki/SSI_Extra-inline-bcrypt.md) | Hashing and checking passwords with bcrypt, answered by an inline. |
| [inline-dialog](wiki/SSI_Extra-inline-dialog.md) | Dialogs answered by an inline. |
| [inline-mysql](wiki/SSI_Extra-inline-mysql.md) | Queries of the mysql component answered by an inline. |
| [inline-object](wiki/SSI_Extra-inline-object.md) | Dynamic objects that call an inline when they finish moving, while a player edits them, or when a player selects one. |
| [inline-pg](wiki/SSI_Extra-inline-pg.md) | Queries of the omp-postgresql component answered by an inline, with every value sent apart from the query, so nothing is ever escaped. |
| [inline-timers](wiki/SSI_Extra-inline-timers.md) | Timers that call an inline. |

### SSI_Vehicle

| Library | Description |
| --- | --- |
| [components](wiki/SSI_Vehicle-components.md) | The tuning parts of the game: their type, name, price, shop and pair, and which vehicle models take each one. |
| [forklift](wiki/SSI_Vehicle-forklift.md) | Crates a forklift lifts, carries and stacks. |
| [math](wiki/SSI_Vehicle-math.md) | The geometry of a vehicle in the world: its speed, whether it lies on its roof, and where a point of its body, its bonnet, boot or a wheel is as it leans and turns. |
| [model](wiki/SSI_Vehicle-model.md) | Name, category and flags of every vehicle model, read by model id. |
| [neon](wiki/SSI_Vehicle-neon.md) | Neon under a vehicle: two tubes of a colour along its sides, attached as streamer objects, so the light follows the vehicle wherever it goes. |
| [objective](wiki/SSI_Vehicle-objective.md) | Marks the vehicle a player was sent to with the yellow arrow and a radar blip. |
| [parts](wiki/SSI_Vehicle-parts.md) | The parts of a vehicle one at a time: some parameters, a door, window, tyre, lamp or panel is set while the others keep what the game has. |
| [speed-camera](wiki/SSI_Vehicle-speed-camera.md) | Speed cameras: a pole by the road and a sphere of streamer area around it. |

## Documentation

The [wiki](wiki/Home.md) has a page for each library, with a quick start and every function, macro and event it declares. Each folder also has a `.md` file next to each include that links to its page.

* [Installation](wiki/Installation.md)
* [Conventions](wiki/Conventions.md)
* [Troubleshooting](wiki/Troubleshooting.md)

## Testing

The `tests` folder holds a game mode for each library that has tests, written with `SSI\test`. Compile one with the root of this repository and the open.mp includes in the include path, then run it on a server that allows at least one bot and loads the plugins the library needs:

```bash
pawncc tests/bits.pwn -i. -i<open.mp includes>
```

The test prints every failed check and a summary, then closes the server.

## License

SSI is released under the [MIT License](LICENSE), apart from `SSI_Vehicle\model`. Its model data comes from y_vehicledata of YSI, so that file stays under the [Mozilla Public License 1.1](LICENSE-MPL), with the notice of YSI at its top.

## Thanks to

* [@Y-Less](https://github.com/Y-Less) for YSI, the model for the layout of this repository and for many of its interfaces, and for the vehicle data of y_vehicledata.
* [@IllidanS4](https://github.com/IllidanS4) for PawnPlus, which `SSI\iterator` uses to follow vehicles and actors.
