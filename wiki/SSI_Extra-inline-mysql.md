# SSI_Extra\inline-mysql

```pawn
#include <SSI_Extra\inline-mysql>
```

## Requirements

- `SSI\inline`
- `SSI\va`
- [MySQL](https://github.com/imshooter/MySQL)

## Quick Start

Queries of the mysql component answered by an inline:

```pawn
#include <SSI_Extra\inline-mysql>

ShowAge(playerid, const name[]) {
    inline OnFound(error) {
        if (error != 0) {
            @return;
        }

        if (MySQL_GetRowCount() == 0) {
            @return;
        }

        SendClientMessage(playerid, -1, "Registered %i days ago.", MySQL_GetInt(0, "days"));
    }

    MySQL_ThreadedQueryInline(gDatabase, using inline OnFound, "SELECT DATEDIFF(NOW(), registered) AS days FROM accounts WHERE name = %q", name);
}
```

- `MySQL_ThreadedQueryInline` runs a query after the ones sent before it, and
  `MySQL_ParallelQueryInline` on the pool of the handle, in any order.
  `MySQL_SendQueryInline` sends a query built with `MySQL_CreateQuery`.
  `MySQL_ExecuteStatementInline` runs a prepared statement once, and
  `MySQL_ExecuteBatchInline` sends a batch of its rows.
- The component formats the query, with no length limit, so `%q` quotes and
  escapes a string.
- The inline takes the error of the query, `0` when it ran. It is called
  once, with the result read by the `MySQL_Get` natives, and also when the
  query failed.
- The inline keeps the arguments and locals of the function that started
  it, so the player id needs no passing. A player who left by then is still
  in it: check that the player is the same one when it matters.

Passwords hashed and verified on the threads of the component, answered by
an inline the same way:

```pawn
Register(playerid, const password[]) {
    inline OnHashed(hash[MYSQL_HASH_LENGTH]) {
        if (hash[0] == EOS) {
            @return;
        }

        SavePassword(playerid, hash);
    }

    MySQL_HashArgon2Inline(using inline OnHashed, password);
}

Login(playerid, const password[], const hash[]) {
    inline OnVerified(bool:match) {
        if (!match) {
            @return;
        }

        SpawnPlayer(playerid);
    }

    MySQL_VerifyPasswordInline(using inline OnVerified, password, hash);
}
```

## API

### `MySQL_ThreadedQueryInline`

```pawn
forward bool:MySQL_ThreadedQueryInline(MySQL:handle, Inline:callback<i>, const query[], MYSQL_TAGS:...);
```

Send a query to run after the ones sent before it, then call an inline with its error.

| Parameter | Description |
| --- | --- |
| `handle` | The handle. |
| `callback` | The inline, as `using inline Name`, taking the error, `0` when the query ran. |
| `query` | The query, formatted with the values after it. |

**Returns**

- `true` the query is sent
- `false` the inline is freed, when:
    + it could not be captured
    + `handle` does not exist or the format is not valid
    + a limit of the connection refused the query

### `MySQL_ParallelQueryInline`

```pawn
forward bool:MySQL_ParallelQueryInline(MySQL:handle, Inline:callback<i>, const query[], MYSQL_TAGS:...);
```

Send a query that any connection of the pool may run, out of order with the rest, then call an inline with its error.

| Parameter | Description |
| --- | --- |
| `handle` | The handle. |
| `callback` | The inline, as `using inline Name`, taking the error, `0` when the query ran. |
| `query` | The query, formatted with the values after it. |

**Returns**

- `true` the query is sent
- `false` the inline is freed, when:
    + it could not be captured
    + `handle` does not exist or the format is not valid
    + a limit of the connection refused the query

### `MySQL_SendQueryInline`

```pawn
forward bool:MySQL_SendQueryInline(Query:query, Inline:callback<i>, bool:parallel = false);
```

Send a query built with `MySQL_CreateQuery`, then call an inline with its error.

| Parameter | Description |
| --- | --- |
| `query` | The query, which is forgotten once sent. |
| `callback` | The inline, as `using inline Name`, taking the error, `0` when the query ran. |
| `parallel` | Whether any connection of the pool may run it. |

**Returns**

- `true` the query is sent
- `false` the inline is freed, when:
    + it could not be captured
    + `query` does not exist
    + a limit of the connection refused it

### `MySQL_ExecuteStatementInline`

```pawn
forward bool:MySQL_ExecuteStatementInline(Statement:statement, Inline:callback<i>, MYSQL_TAGS:...);
```

Run a prepared statement once, after the queries sent before it, then call an inline with its error.

| Parameter | Description |
| --- | --- |
| `statement` | The statement, from `MySQL_PrepareStatement`. |
| `callback` | The inline, as `using inline Name`, taking the error, `0` when it ran. |
| `...` | A value for each specifier of the statement. |

**Returns**

- `true` the statement is sent
- `false` the inline is freed, when:
    + it could not be captured
    + `statement` does not exist or the values do not match it
    + a limit of the connection refused it

### `MySQL_ExecuteBatchInline`

```pawn
forward bool:MySQL_ExecuteBatchInline(Batch:batch, Inline:callback<i>);
```

Send the rows of a batch, then call an inline with its error.

| Parameter | Description |
| --- | --- |
| `batch` | The batch, which is forgotten once sent. |
| `callback` | The inline, as `using inline Name`, taking the error, `0` when every row went in. |

**Returns**

- `true` the batch is sent
- `false` the inline is freed, when:
    + it could not be captured
    + `batch` or its statement does not exist
    + a limit of the connection refused it

### `MySQL_HashArgon2Inline`

```pawn
forward bool:MySQL_HashArgon2Inline(Inline:callback<s>, const password[], memory = MYSQL_ARGON2_MEMORY, iterations = MYSQL_ARGON2_ITERATIONS, parallelism = MYSQL_ARGON2_PARALLELISM);
```

Hash a password with Argon2id, then call an inline with the hash.

| Parameter | Description |
| --- | --- |
| `callback` | The inline, as `using inline Name`, taking the hash, empty when it failed. |
| `password` | The password. |
| `memory` | Memory, in KiB, from `8192` to `1048576`. |
| `iterations` | Passes, from `1` to `16`. |
| `parallelism` | Lanes, from `1` to `8`. |

**Returns**

- `true` the work started
- `false` the inline is freed, when:
    + it could not be captured
    + a cost is out of range

### `MySQL_HashBcryptInline`

```pawn
forward bool:MySQL_HashBcryptInline(Inline:callback<s>, const password[], cost = MYSQL_BCRYPT_COST);
```

Hash a password with bcrypt, then call an inline with the hash.

| Parameter | Description |
| --- | --- |
| `callback` | The inline, as `using inline Name`, taking the hash, empty when it failed. |
| `password` | The password. |
| `cost` | Cost, from `4` to `20`. |

**Returns**

- `true` the work started
- `false` the inline is freed, when:
    + it could not be captured
    + the cost is out of range

### `MySQL_VerifyPasswordInline`

```pawn
forward bool:MySQL_VerifyPasswordInline(Inline:callback<i>, const password[], const hash[]);
```

Verify a password against an Argon2 or bcrypt hash, then call an inline with whether they match.

| Parameter | Description |
| --- | --- |
| `callback` | The inline, as `using inline Name`, taking whether they match. A hash that cannot be read never matches. |
| `password` | The password. |
| `hash` | The hash. |

**Returns**

- `true` the work started
- `false` the inline could not be captured, and is freed
