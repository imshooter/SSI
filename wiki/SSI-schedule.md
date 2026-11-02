# SSI\schedule

```pawn
#include <SSI\schedule>
```

## Requirements

- `SSI\collection`

## Quick Start

Schedules hold a time for each id. Setting, moving and removing a time take
the same time with ten ids or with a hundred thousand. One timer of the
script takes out the ids that are due, instead of one timer for each id:

```pawn
#include <SSI\schedule>

static
    Schedule:JailRelease<MAX_PLAYERS>
;

Schedule_Set(JailRelease, playerid, gettime() + 300);
Schedule_Remove(JailRelease, playerid);

foreach (new playerid : Due(JailRelease, gettime())) {
    ReleasePlayer(playerid);
}
```

An id has one time at most: setting it again moves it. Times are whole units
of any kind, seconds or tenths of a second, compared by their difference, so
a count that wraps around is fine while no time is more than half the range
away. Each unit is a step of the walk, so the unit is the coarsest one that is
precise enough. Ids and times take any tag.

## API

### `Schedule_Set`

```pawn
forward bool:Schedule_Set(Schedule:schedule<>, id, time);
```

Give an id a time, or move it to another.

A time already past is due at the next walk.

| Parameter | Description |
| --- | --- |
| `schedule` | The schedule, named by its tag. |
| `id` | The id. |
| `time` | Its time. |

**Returns**

- `true` the id has the time
- `false` the id is out of range

### `Schedule_Remove`

```pawn
forward bool:Schedule_Remove(Schedule:schedule<>, id);
```

Take an id out.

| Parameter | Description |
| --- | --- |
| `schedule` | The schedule, named by its tag. |
| `id` | The id. |

**Returns**

- `true` it was taken out
- `false` it was not in, or is out of range

### `Schedule_Contains`

```pawn
forward bool:Schedule_Contains(Schedule:schedule<>, id);
```

Whether an id has a time.

| Parameter | Description |
| --- | --- |
| `schedule` | The schedule, named by its tag. |
| `id` | The id. |

**Returns**

- `true` it has
- `false` it has not, or is out of range

### `Schedule_Time`

```pawn
forward Schedule_Time(Schedule:schedule<>, id);
```

The time of an id.

| Parameter | Description |
| --- | --- |
| `schedule` | The schedule, named by its tag. |
| `id` | The id. |

**Returns**

- the time
- `0` it has none, or is out of range

### `Schedule_Count`

```pawn
forward Schedule_Count(Schedule:schedule<>);
```

How many ids have a time.

| Parameter | Description |
| --- | --- |
| `schedule` | The schedule, named by its tag. |

**Returns**

- the count

### `Schedule_Clear`

```pawn
forward Schedule_Clear(Schedule:schedule<>);
```

Take every id out.

| Parameter | Description |
| --- | --- |
| `schedule` | The schedule, named by its tag. |

### `Due@SSI_loop`

Walk the ids due at `now`, taking each out.

Earlier units come first, and the ids of one unit come in any order. An id
given a time that the walks have already passed comes with the next unit. An
id set again inside the loop to a time not after `now` comes back in the
same walk. A `break` leaves the remaining ids in.

```pawn
foreach (new playerid : Due(JailRelease, gettime())) {
}
```

| Parameter | Description |
| --- | --- |
| `schedule` | The schedule, named by its tag. |
| `now` | The current time, read once before the walk. |
