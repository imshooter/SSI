# SSI_Extra\inline-pg

```pawn
#include <SSI_Extra\inline-pg>
```

## Requirements

- `SSI\inline`
- `SSI\collection`
- `SSI\hooks`
- [omp-postgresql](https://github.com/itskoleban/omp-postgresql)

## Quick Start

Queries of the omp-postgresql component answered by an inline, with every
value sent apart from the query, so nothing is ever escaped:

```pawn
#include <SSI_Extra\inline-pg>

new
    gDatabase
;

public OnGameModeInit() {
    gDatabase = Postgres_Connect("game");

    return 1;
}

ShowAge(playerid, const name[]) {
    inline OnFound(error) {
        if (error != PG_ERROR_NONE) {
            @return;
        }

        if (Postgres_Rows() == 0) {
            @return;
        }

        new
            days
        ;

        Postgres_GetInt(0, "days", days);
        SendClientMessage(playerid, -1, "Registered %i days ago.", days);
    }

    Postgres_QueryInline(gDatabase, using inline OnFound, "SELECT current_date - registered AS days FROM accounts WHERE name = %s", name);
}
```

- A query is written as for `format`, and each specifier is a parameter
  bound to the argument in its place: `%i` an integer, `%f` a float, `%b` a
  boolean, `%s` text, `%u` a UUID and `%j` JSON. `%%` is a percent sign. A
  specifier is never quoted. Any other type is text cast in the query, as
  `%s::bigint`.
- The queries of a connection run one after another, in the order they were
  sent. One sent before the connection is up, or while the component holds
  all the jobs it takes, waits here and goes when there is room.
- The inline takes the error of the query, `PG_ERROR_NONE` when it ran. It is
  called once, on the main thread, with the result active, so the getters
  read it. The result is gone once the inline returns.
- `Postgres_Query` sends a query that needs no answer, so a write spends no
  inline. A failed query of either kind calls `OnPostgresQueryFailed`.
- The script can run jobs of its own through the component next to these.
  They share its room, and closing one lets the waiting queries go.
- Text goes in and comes out in the code page of the clients, Windows-1252,
  since the component speaks UTF-8 only. Strings are unpacked.
- The inline keeps the arguments and locals of the function that started it,
  so the player id needs no passing. A player who left by then is still in
  it: check that the player is the same one when it matters.
- The connection settings come from the service file the component reads,
  named by `PGSERVICEFILE` in the environment of the server.

## API

### `Postgres_Connect`

```pawn
forward Postgres_Connect(const profile[], pool = 1);
```

Open a connection. The component connects on its own threads, and `OnPostgresConnected` follows.

| Parameter | Description |
| --- | --- |
| `profile` | Name of the service in the service file. |
| `pool` | Sessions of the connection. |

**Returns**

- the connection
- `0` the component refused it

### `Postgres_Close`

```pawn
forward bool:Postgres_Close(connection);
```

Close a connection. The queries still waiting here call their inline with `PG_ERROR_CONNECTION`, and the ones sent are cancelled.

| Parameter | Description |
| --- | --- |
| `connection` | The connection. |

**Returns**

- `true` it is closing
- `false` it is not a connection

### `Postgres_QueryInline`

```pawn
forward bool:Postgres_QueryInline(connection, Inline:callback<i>, const query[], OPEN_MP_TAGS:...);
```

Send a query, then call an inline with its error.

| Parameter | Description |
| --- | --- |
| `connection` | The connection. |
| `callback` | The inline, as `using inline Name`, taking the error, `PG_ERROR_NONE` when the query ran. |
| `query` | The query, with a specifier for each argument after it. |

**Returns**

- `true` the query is sent, or waits for room
- `false` the inline is freed, when:
    + it could not be captured
    + a specifier is unknown or quoted
    + the arguments do not match the specifiers
    + the query does not fit `SSI_POSTGRES_QUERY_LENGTH`
    + a text does not fit `SSI_POSTGRES_TEXT_LENGTH`
    + the component refused it, or `connection` is closed
    + `SSI_POSTGRES_REQUESTS` queries are waiting

### `Postgres_Query`

```pawn
forward bool:Postgres_Query(connection, const query[], OPEN_MP_TAGS:...);
```

Send a query that needs no answer.

| Parameter | Description |
| --- | --- |
| `connection` | The connection. |
| `query` | The query, with a specifier for each argument after it. |

**Returns**

- `true` the query is sent, or waits for room
- `false` for the reasons of `Postgres_QueryInline`

### `Postgres_Rows`

```pawn
forward Postgres_Rows();
```

The rows of the active result. Called in the inline of a query, as the getters below.

**Returns**

- the count
- `0` outside an inline, or for a query that returned none

### `Postgres_AffectedRows`

```pawn
forward Postgres_AffectedRows();
```

The rows the active query changed.

**Returns**

- the count
- `0` outside an inline, or for a query that changes none

### `Postgres_IsNull`

```pawn
forward bool:Postgres_IsNull(row, const column[]);
```

Whether a value of the active result is NULL.

| Parameter | Description |
| --- | --- |
| `row` | The row, from `0`. |
| `column` | Name of the column. |

**Returns**

- `true` it is NULL
- `false` it has a value, or the cell does not exist

### `Postgres_GetInt`

```pawn
forward bool:Postgres_GetInt(row, const column[], &value);
```

An integer of the active result.

| Parameter | Description |
| --- | --- |
| `row` | The row, from `0`. |
| `column` | Name of the column. |
| `value` | Reads back the integer. |

**Returns**

- `true` it was read
- `false` when:
    + the cell does not exist
    + it is NULL or not an integer

### `Postgres_GetFloat`

```pawn
forward bool:Postgres_GetFloat(row, const column[], &Float:value);
```

A float of the active result.

| Parameter | Description |
| --- | --- |
| `row` | The row, from `0`. |
| `column` | Name of the column. |
| `value` | Reads back the float. |

**Returns**

- `true` it was read
- `false` when:
    + the cell does not exist
    + it is NULL or not a number

### `Postgres_GetBool`

```pawn
forward bool:Postgres_GetBool(row, const column[], &bool:value);
```

A boolean of the active result.

| Parameter | Description |
| --- | --- |
| `row` | The row, from `0`. |
| `column` | Name of the column. |
| `value` | Reads back the boolean. |

**Returns**

- `true` it was read
- `false` when:
    + the cell does not exist
    + it is NULL or not a boolean

### `Postgres_GetString`

```pawn
forward bool:Postgres_GetString(row, const column[], output[], size = sizeof (output));
```

A value of the active result as text, in Windows-1252. Text longer than the output is cut.

| Parameter | Description |
| --- | --- |
| `row` | The row, from `0`. |
| `column` | Name of the column. |
| `output` | Reads back the text. |
| `size` | Size of `output`. |

**Returns**

- `true` it was read
- `false` the output is cleared, when:
    + the cell does not exist
    + it is NULL
    + it does not fit `SSI_POSTGRES_TEXT_LENGTH` in UTF-8

### `Postgres_GetErrorState`

```pawn
forward bool:Postgres_GetErrorState(output[], size = sizeof (output));
```

The SQLSTATE of the active query when it failed, as `23505` for a duplicate key.

| Parameter | Description |
| --- | --- |
| `output` | Reads back the five characters. |
| `size` | Size of `output`. |

**Returns**

- `true` it was read
- `false` the output is cleared, the query did not reach the
  server or did not fail

## Events

### `OnPostgresConnected`

```pawn
event OnPostgresConnected(connection);
```

Every session of a connection is up, the first time and after a lost connection came back.

| Parameter | Description |
| --- | --- |
| `connection` | The connection. |

### `OnPostgresConnectionFailed`

```pawn
event OnPostgresConnectionFailed(connection, const message[]);
```

A connection gave up after its attempts. The queries waiting for it called their inline with `PG_ERROR_CONNECTION`. A new connection tries again.

| Parameter | Description |
| --- | --- |
| `connection` | The connection. |
| `message` | What the component said. |

### `OnPostgresQueryFailed`

```pawn
event OnPostgresQueryFailed(connection, error, const sqlstate[], const message[]);
```

A query failed, with an inline or without.

| Parameter | Description |
| --- | --- |
| `connection` | The connection. |
| `error` | The kind of error, one of `PG_ERROR_*`. |
| `sqlstate` | The SQLSTATE, or empty when the query did not reach the server. |
| `message` | What PostgreSQL or the component said. It can quote values of the query. |
