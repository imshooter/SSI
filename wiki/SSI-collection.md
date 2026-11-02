# SSI\collection

```pawn
#include <SSI\collection>
```

## Quick Start

Collections: the structures of these libraries under one name, as y_iterate
keeps every iterator under `Iterator:`. The brackets of the declaration pick
the structure, and every call and walk names the collection with the same
brackets.

```pawn
static
    Collection:Business<MAX_BUSINESSES>,
    Collection:FactionVehicle[MAX_FACTIONS]<MAX_FACTION_VEHICLES>
;

new
    Collection:OwnedHouse<MAX_PLAYERS, MAX_HOUSES>
;

new const
    Business:businessid = Collection_Alloc(Business),
    FactionVehicle:slot = Collection_Alloc(FactionVehicle[factionid])
;

Collection_Add(OwnedHouse<playerid>, houseid);
Collection_Remove(OwnedHouse<>, houseid);

foreach (new businessid : Business) {
}

foreach (new House:houseid : OwnedHouse<playerid>) {
}
```

- `Name<SIZE>` is a handle pool: the ids from `0` to `SIZE - 1`.
- `Collection<Generation>:Name<SIZE>` declares a handle pool that also
  counts the generations of its ids, for `Collection_Generation`,
  `Collection_Alive`, `Collection_Ticket` and `Collection_Redeem`.
- `Name[COUNT]<SIZE>` is an indexed pool: a pool of `SIZE` ids for each
  index, so one id lives in several of them.
- `Name<GROUPS, SIZE>` is one range of `SIZE` values shared out among
  `GROUPS` groups, each value in one group at most.

A collection either hands out its own ids with `Collection_Alloc`, or holds
the values given to it with `Collection_Add`. `Collection_Remove` serves both
cases. Using both in one collection breaks its stack of free ids.

The ids of a pool carry the tag of the collection, and the calls check it.
The values of groups are plain numbers, and `Collection_Alloc` gives them the
tag of the collection. A collection of plain numbers, such as the players of
iterator.inc, defines its tag away after the declaration:

```pawn
new
    Collection:Player<MAX_PLAYERS>
;

#define Player: _:
```

`Name<>` names a group collection where the group does not matter. A group
is read between angle brackets, so it is a variable or an expression without
a comma.

## API

### `Collection_Alloc`

```pawn
forward Collection_Alloc(Collection:collection<>);
```

Take a free id and put it in, last in its group.

The id given back last, or else the lowest never used.

| Parameter | Description |
| --- | --- |
| `collection` | `Name`, `Name[index]` or `Name<group>`. |

**Returns**

- the id, with the tag of the collection
- `-1` with that tag, when every id is in use, or the index or
  the group is out of range

### `Collection_Add`

```pawn
forward bool:Collection_Add(Collection:collection<>, value);
```

Put a given value in.

| Parameter | Description |
| --- | --- |
| `collection` | `Name`, `Name[index]` or `Name<group>`. |
| `value` | The value. |

**Returns**

- `true` it was put in
- `false` when:
    + it, the index or the group is out of range
    + it is in already, in any group of a group collection

### `Collection_Remove`

```pawn
forward bool:Collection_Remove(Collection:collection<>, value);
```

Take an id or a value out.

| Parameter | Description |
| --- | --- |
| `collection` | `Name`, `Name[index]` or `Name<>`. |
| `value` | The id or value. |

**Returns**

- `true` it was taken out
- `false` it was not in, or is out of range

### `Collection_Retire`

```pawn
forward bool:Collection_Retire(Collection:collection<>, id);
```

Take an id out of use, but do not hand it out again yet.

It stays counted until `Collection_Recycle`, so it can be destroyed in two
steps: out of use first, free once everything that reads it is done.

| Parameter | Description |
| --- | --- |
| `collection` | `Name` or `Name[index]`. |
| `id` | The id. |

**Returns**

- `true` it was taken out of use
- `false` it was not in use, or the index is out of range

### `Collection_Recycle`

```pawn
forward bool:Collection_Recycle(Collection:collection<>, id);
```

Hand out again an id taken out of use with `Collection_Retire`.

| Parameter | Description |
| --- | --- |
| `collection` | `Name` or `Name[index]`. |
| `id` | The id. |

**Returns**

- `true` it is free
- `false` it was not retired, or the index is out of range

### `Collection_Contains`

```pawn
forward bool:Collection_Contains(Collection:collection<>, value);
```

Whether an id or a value is in.

| Parameter | Description |
| --- | --- |
| `collection` | `Name`, `Name[index]` or `Name<group>`. |
| `value` | The id or value. |

**Returns**

- `true` it is in, in that group for a group collection
- `false` it is not, or it, the index or the group is out of
  range

### `Collection_Count`

```pawn
forward Collection_Count(Collection:collection<>);
```

How many ids or values are in.

| Parameter | Description |
| --- | --- |
| `collection` | `Name`, `Name[index]` or `Name<group>`. |

**Returns**

- the count
- `0` when the index or the group is out of range

### `Collection_Clear`

```pawn
forward bool:Collection_Clear(Collection:collection<>);
```

Take everything out.

| Parameter | Description |
| --- | --- |
| `collection` | `Name`, `Name[index]` or `Name<group>`. |

**Returns**

- `true` it is empty
- `false` the index or the group is out of range

### `Collection_Group`

```pawn
forward Collection_Group(Collection:collection<>, value);
```

The group a value is in.

| Parameter | Description |
| --- | --- |
| `collection` | `Name<>`. |
| `value` | The value. |

**Returns**

- the group
- `-1` it is in none, or is out of range

### `Collection_Generation`

```pawn
forward Collection_Generation(Collection:collection<>, id);
```

The generation of an id in use.

It changes each time the id is taken out, retired or cleared, so an id kept
with its generation can be checked with `Collection_Alive` before it is used
again. Only for a pool declared as `Collection<Generation>:Name<SIZE>`.

```pawn
new const
    generation = Collection_Generation(Report, reportid)
;

if (Collection_Alive(Report, reportid, generation)) {
}
```

| Parameter | Description |
| --- | --- |
| `collection` | `Name`. |
| `id` | The id. |

**Returns**

- the generation, `0` or more
- `-1` the id is not in use, or is out of range

### `Collection_Alive`

```pawn
forward bool:Collection_Alive(Collection:collection<>, id, generation);
```

Whether an id is in use and still in the generation given.

Only for a pool declared as `Collection<Generation>:Name<SIZE>`.

| Parameter | Description |
| --- | --- |
| `collection` | `Name`. |
| `id` | The id. |
| `generation` | Its generation, from `Collection_Generation`. |

**Returns**

- `true` it is in use, in that generation
- `false` it was taken out since, or is out of range

### `Collection_Ticket`

```pawn
forward Collection_Ticket(Collection:collection<>, id);
```

An id in use and its generation in one number.

It is meant for places where only one number fits, such as an argument of a
timer. `Collection_Redeem` gives the id back while the id is still in the
same generation. The ticket holds the generation modulo `cellmax / SIZE`, so
it could pass for its id again only after that many more generations: 262143
for 8192 ids. Only for a pool declared as
`Collection<Generation>:Name<SIZE>`.

```pawn
SetTimerEx("@Report_Expire", 300000, false, "i", Collection_Ticket(Report, reportid));

public @Report_Expire(ticket) {
    new const
        Report:reportid = Collection_Redeem(Report, ticket)
    ;
}
```

| Parameter | Description |
| --- | --- |
| `collection` | `Name`. |
| `id` | The id. |

**Returns**

- the ticket, `0` or more
- `-1` the id is not in use, or is out of range

### `Collection_Redeem`

```pawn
forward Collection_Redeem(Collection:collection<>, ticket);
```

The id of a ticket from `Collection_Ticket`.

Only for a pool declared as `Collection<Generation>:Name<SIZE>`.

| Parameter | Description |
| --- | --- |
| `collection` | `Name`. |
| `ticket` | The ticket. |

**Returns**

- the id, with the tag of the collection
- `-1` with that tag, when the id was taken out since the ticket
  was made, or the ticket is not one

### `None@SSI_loop`

Walk the values a collection does not hold, lowest first.

The free ids of a pool or of one index, the values of a group collection in
no group with `Name<>`, or the values not in one group with `Name<group>`.

```pawn
foreach (new Business:businessid : None(Business)) {
}
```

| Parameter | Description |
| --- | --- |
| `collection` | `Name`, `Name[index]`, `Name<>` or `Name<group>`. |

### `All@SSI_loop`

Walk the values a collection holds, lowest first.

The values a walk of the collection gives, in order of value instead of the
order they went in. `Name<>` gives the values in any group.

```pawn
foreach (new value : All(OwnedHouse<>)) {
}
```

| Parameter | Description |
| --- | --- |
| `collection` | `Name`, `Name[index]`, `Name<>` or `Name<group>`. |

### `Empty@SSI_loop`

Walk the indexes of an indexed pool, or the groups of a group collection, that hold nothing.

```pawn
foreach (new factionid : Empty(FactionVehicle[])) {
}

foreach (new playerid : Empty(OwnedHouse<>)) {
}
```

| Parameter | Description |
| --- | --- |
| `collection` | `Name[]` or `Name<>`. |

### `NonEmpty@SSI_loop`

Walk the indexes, or the groups, that hold something.

| Parameter | Description |
| --- | --- |
| `collection` | `Name[]` or `Name<>`. |

### `Full@SSI_loop`

Walk the indexes, or the groups, that hold as many values as there is room for.

| Parameter | Description |
| --- | --- |
| `collection` | `Name[]` or `Name<>`. |

### `NonFull@SSI_loop`

Walk the indexes, or the groups, that have room for one more value.

| Parameter | Description |
| --- | --- |
| `collection` | `Name[]` or `Name<>`. |
