# SSI

> [!NOTE]
> Experimental version, already running in production. Made with Claude Opus 5.5.

SSI is a set of Pawn libraries for open.mp, built the way YSI is. The libraries live in the `SSI` folder, and the inline versions of plugin functions in `SSI_Extra`. Each one is included by its folder and name:

```pawn
#include <SSI\collection>
#include <SSI\command>
#include <SSI\hooks>
```

## Guides

* [Installation](Installation.md) lists what each library needs and the order of the includes.
* [Conventions](Conventions.md) explains the names, tags, events and macros every library shares.
* [Troubleshooting](Troubleshooting.md) covers the errors seen most often and how to solve them.

## Libraries

### SSI

| Library | Description |
| --- | --- |
| [amx](SSI-amx.md) | Access to the memory of the script beyond its data, for the libraries that read or write code at run time: the code as the server relocated it, and the header with its table of publics. |
| [bits](SSI-bits.md) | Sets of bits, as y_bit keeps them: one bit for each id up to a size, 32 to a cell. |
| [collection](SSI-collection.md) | Collections: the structures of these libraries under one name, as y_iterate keeps every iterator under `Iterator:`. |
| [command](SSI-command.md) | Commands, as Pawn.CMD and y_commands keep them: a function for each command, found by its name when a player types it. |
| [dictionary](SSI-dictionary.md) | Dictionaries hold a value for each key. |
| [extra](SSI-extra.md) | Extra data: values kept on the ids of something else, with a row of cells for each id and a column for each name. |
| [group](SSI-group.md) | Groups of players, as y_groups keeps them: a name, its members and what they may do. |
| [hooks](SSI-hooks.md) | Hooks, as in y_hooks: any number of functions for one callback, and hooks that replace a native or a function. |
| [inline](SSI-inline.md) | Inline functions: a function written inside another, that reads and changes the arguments of the outer function and the locals it had where the inline is written, and can be called after the outer function returned, as by a timer. |
| [iterator](SSI-iterator.md) | The ids the server hands out, in collections this script walks with `foreach`, as y_foreach keeps its iterators. |
| [queue](SSI-queue.md) | Queues hand out the rows of an array and take them back first in, first out. |
| [schedule](SSI-schedule.md) | Schedules hold a time for each id. |
| [string](SSI-string.md) | Strings changed in place and compared, beyond the natives of open.mp. |
| [test](SSI-test.md) | Tests, as in y_testing: functions declared with `test` that the script runs one after another when it starts, with checks that print what failed and where. |
| [unique](SSI-unique.md) | Unique names: every `#include <SSI\unique>` moves on to a new suffix of two characters, and `SSI_UNIQUE<prefix...suffix>` writes the current one where the `...` is. |
| [va](SSI-va.md) | Variable arguments: `___(n)` passes on the arguments a function got, from its `n`th on, anywhere among the arguments of a call, as y_va's `___`. |

### SSI_Extra

| Library | Description |
| --- | --- |
| [inline-argon2](SSI_Extra-inline-argon2.md) | Hashing and checking passwords with Argon2id through the async_crypto plugin, answered by an inline. |
| [inline-bcrypt](SSI_Extra-inline-bcrypt.md) | Hashing and checking passwords with bcrypt, answered by an inline. |
| [inline-dialog](SSI_Extra-inline-dialog.md) | Dialogs answered by an inline. |
| [inline-mysql](SSI_Extra-inline-mysql.md) | Queries of the mysql component answered by an inline. |
| [inline-object](SSI_Extra-inline-object.md) | Dynamic objects that call an inline when they finish moving, while a player edits them, or when a player selects one. |
| [inline-pg](SSI_Extra-inline-pg.md) | Queries of the omp-postgresql component answered by an inline, with every value sent apart from the query, so nothing is ever escaped. |
| [inline-timers](SSI_Extra-inline-timers.md) | Timers that call an inline. |
