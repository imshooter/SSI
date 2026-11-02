# SSI\queue

```pawn
#include <SSI\queue>
```

## Quick Start

Queues hand out the rows of an array and take them back first in, first out.
The array is declared with the queue and read and written as any array, a row
at a time, with the fields of an enum when it has two dimensions:

```pawn
#include <SSI\queue>

enum E_TAXI_CALL {
    E_TAXI_CALL_PLAYER,
    E_TAXI_CALL_TIME
}

static
    Queue:TaxiCall<MAX_PLAYERS, E_TAXI_CALL>
;

new
    TaxiCall:row = Queue_Push(TaxiCall)
;

TaxiCall[row][E_TAXI_CALL_PLAYER] = playerid;
TaxiCall[row][E_TAXI_CALL_TIME] = gettime();

if (!Queue_IsEmpty(TaxiCall)) {
    row = Queue_Pop(TaxiCall);
}
```

The rows carry the tag of the queue, as the ids of a collection do, and the
first dimension of the array takes that tag, so a row is the only index that
reaches it without a warning. The size takes any tag. A tag before the
keyword tags the cells, as `Vehicle:Queue:Respawn<MAX_VEHICLES>`.

The rows go round the array, which has one row more than the size. A row
taken out keeps its cells until the next one is taken out, so a walk of a tree
in breadth reads a row after taking it out while it pushes its children.

## API

### `Queue_Clear`

```pawn
forward Queue_Clear(Queue:queue<>);
```

Empty the queue.

The next row handed out is the first of the array.

| Parameter | Description |
| --- | --- |
| `queue` | The queue. |

### `Queue_Push`

```pawn
forward Queue_Push(Queue:queue<>);
```

Hand out a row, last in the queue.

The row keeps what it held before, so every field it uses is written.

| Parameter | Description |
| --- | --- |
| `queue` | The queue. |

**Returns**

- the row, with the tag of the queue
- `-1` with that tag, when the queue is full

### `Queue_Pop`

```pawn
forward Queue_Pop(Queue:queue<>);
```

Take out the first row.

The row keeps its cells until the next row is taken out.

| Parameter | Description |
| --- | --- |
| `queue` | The queue. |

**Returns**

- the row, with the tag of the queue
- `-1` with that tag, when the queue is empty

### `Queue_Size`

```pawn
forward Queue_Size(Queue:queue<>);
```

How many rows are in the queue.

| Parameter | Description |
| --- | --- |
| `queue` | The queue. |

### `Queue_IsEmpty`

```pawn
forward bool:Queue_IsEmpty(Queue:queue<>);
```

Whether the queue has no row.

| Parameter | Description |
| --- | --- |
| `queue` | The queue. |
