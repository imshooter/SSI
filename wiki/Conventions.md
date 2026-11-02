# Conventions

Every SSI library follows the same rules, so a library that is new to you reads like the ones you know.

## Folders

| Folder | Holds |
| --- | --- |
| `SSI` | The libraries: hooks, inline functions, collections, dictionaries, iterators, bits, queues, schedules, extra data, commands, groups and tests. |
| `SSI_Extra` | Inline versions of plugin and component functions. |

## Names

* Functions are named after their structure and what they do: `Collection_Alloc`, `Dictionary_Set`, `Bits_Let`, `Command_GetByName`, `Group_AddPlayer`.
* A function that answers through an inline ends in `Inline`, after the function it wraps: `MySQL_ThreadedQueryInline`, `Dialog_ShowInline`.
* The verbs keep one meaning everywhere. `Set` writes a value, `Clear` empties the whole structure, `Count` gives how many there are and `IsValid` tells whether an id exists.
* Names that start with `SSI@` are internal. The macros call them from your code, so they are global, but they are not part of the interface and may change.
* Variables that a declaration makes for you end in `@SSI_` and a field, as `Name@SSI_next`.

## Declarations

Structures are declared with a keyword and the size in angle brackets, the way YSI declares iterators:

```pawn
new
    Collection:Vehicle<MAX_VEHICLES>,
    Collection:OwnedHouse[MAX_PLAYERS]<MAX_HOUSES>,
    Dictionary:HouseByName<MAX_HOUSES, 32>,
    Bits:Seen<MAX_VEHICLES>
;
```

The calls name the structure with the same brackets, `Collection_Add(OwnedHouse[playerid], houseid)`, and `foreach` walks it:

```pawn
foreach (new House:houseid : OwnedHouse[playerid]) {
}
```

## Tags

An id handed out by a collection carries the name of the collection as its tag, and the calls check it. A collection that holds values of another tag says so with a define after its declaration:

```pawn
#define OwnedHouse: House:
```

A collection of plain numbers writes `#define Name: _:`. Sizes and indexes may carry any tag.

## Events

A library raises events with `call` and the script answers them with hooks. The name says when the event happens:

* A name in the present tense is raised before anything changes, and any hook may refuse it by returning a value other than `0`. `OnPlayerUseCommand` runs before a command and `OnPlayerJoinGroup` before a player joins a group.
* A name in the past tense is raised after the change, and its return value is not used. `OnPlayerUsedCommand` and `OnPlayerJoinedGroup` follow the ones above.

A hook that returns `~1` ends the chain at once, so the hooks after it do not run.

## Macros

Every function that is a macro has a `forward` with its documentation right above the `#define`, so an editor shows its parameters and documentation as it would for a function. A macro that reads an argument more than once says so in its documentation.

An argument of a macro may hold any expression, the operators `|` and `||` included. A group or index inside angle brackets must not hold a comma.

## Documentation

Each include starts with a short description of the library and an example. Every function, macro and event has a documentation block with what it does, its parameters and what it returns. The wiki pages are made from those blocks.
