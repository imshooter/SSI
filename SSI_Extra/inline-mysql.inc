#if defined _INC_SSI_EXTRA_INLINE_MYSQL
    #endinput
#endif
#define _INC_SSI_EXTRA_INLINE_MYSQL

#include <open.mp>
#include <mysql>
#include <SSI\inline>
#include <SSI\va>

/**
 * Queries of the mysql component answered by an inline:
 *
 *     #include <SSI_Extra\inline-mysql>
 *
 *     ShowAge(playerid, const name[]) {
 *         inline OnFound(error) {
 *             if (error != 0) {
 *                 @return;
 *             }
 *
 *             if (MySQL_GetRowCount() == 0) {
 *                 @return;
 *             }
 *
 *             SendClientMessage(playerid, -1, "Registered %i days ago.", MySQL_GetInt(0, "days"));
 *         }
 *
 *         MySQL_ThreadedQueryInline(gDatabase, using inline OnFound, "SELECT DATEDIFF(NOW(), registered) AS days FROM accounts WHERE name = %q", name);
 *     }
 *
 * - `MySQL_ThreadedQueryInline` runs a query after the ones sent before it, and
 *   `MySQL_ParallelQueryInline` on the pool of the handle, in any order.
 *   `MySQL_SendQueryInline` sends a query built with `MySQL_CreateQuery`.
 *   `MySQL_ExecuteStatementInline` runs a prepared statement once, and
 *   `MySQL_ExecuteBatchInline` sends a batch of its rows.
 * - The component formats the query, with no length limit, so `%q` quotes and
 *   escapes a string.
 * - The inline takes the error of the query, `0` when it ran. It is called
 *   once, with the result read by the `MySQL_Get` natives, and also when the
 *   query failed.
 * - The inline keeps the arguments and locals of the function that started
 *   it, so the player id needs no passing. A player who left by then is still
 *   in it: check that the player is the same one when it matters.
 *
 * Passwords hashed and verified on the threads of the component, answered by
 * an inline the same way:
 *
 *     Register(playerid, const password[]) {
 *         inline OnHashed(hash[MYSQL_HASH_LENGTH]) {
 *             if (hash[0] == EOS) {
 *                 @return;
 *             }
 *
 *             SavePassword(playerid, hash);
 *         }
 *
 *         MySQL_HashArgon2Inline(using inline OnHashed, password);
 *     }
 *
 *     Login(playerid, const password[], const hash[]) {
 *         inline OnVerified(bool:match) {
 *             if (!match) {
 *                 @return;
 *             }
 *
 *             SpawnPlayer(playerid);
 *         }
 *
 *         MySQL_VerifyPasswordInline(using inline OnVerified, password, hash);
 *     }
 */

/**
 * # Functions
 */

/**
 * @brief      Send a query to run after the ones sent before it, then call an
 *             inline with its error.
 *
 * @param      handle    The handle.
 * @param      callback  The inline, as `using inline Name`, taking the error,
 *                       `0` when the query ran.
 * @param      query     The query, formatted with the values after it.
 *
 * @return     - `true` the query is sent
 *             - `false` the inline is freed, when:
 *                 + it could not be captured
 *                 + `handle` does not exist or the format is not valid
 *                 + a limit of the connection refused the query
 */
forward bool:MySQL_ThreadedQueryInline(MySQL:handle, Inline:callback<i>, const query[], MYSQL_TAGS:...);

/**
 * @brief      Send a query that any connection of the pool may run, out of
 *             order with the rest, then call an inline with its error.
 *
 * @param      handle    The handle.
 * @param      callback  The inline, as `using inline Name`, taking the error,
 *                       `0` when the query ran.
 * @param      query     The query, formatted with the values after it.
 *
 * @return     - `true` the query is sent
 *             - `false` the inline is freed, when:
 *                 + it could not be captured
 *                 + `handle` does not exist or the format is not valid
 *                 + a limit of the connection refused the query
 */
forward bool:MySQL_ParallelQueryInline(MySQL:handle, Inline:callback<i>, const query[], MYSQL_TAGS:...);

/**
 * @brief      Send a query built with `MySQL_CreateQuery`, then call an inline
 *             with its error.
 *
 * @param      query     The query, which is forgotten once sent.
 * @param      callback  The inline, as `using inline Name`, taking the error,
 *                       `0` when the query ran.
 * @param      parallel  Whether any connection of the pool may run it.
 *
 * @return     - `true` the query is sent
 *             - `false` the inline is freed, when:
 *                 + it could not be captured
 *                 + `query` does not exist
 *                 + a limit of the connection refused it
 */
forward bool:MySQL_SendQueryInline(Query:query, Inline:callback<i>, bool:parallel = false);

/**
 * @brief      Run a prepared statement once, after the queries sent before it,
 *             then call an inline with its error.
 *
 * @param      statement  The statement, from `MySQL_PrepareStatement`.
 * @param      callback   The inline, as `using inline Name`, taking the error,
 *                        `0` when it ran.
 * @param      ...        A value for each specifier of the statement.
 *
 * @return     - `true` the statement is sent
 *             - `false` the inline is freed, when:
 *                 + it could not be captured
 *                 + `statement` does not exist or the values do not match it
 *                 + a limit of the connection refused it
 */
forward bool:MySQL_ExecuteStatementInline(Statement:statement, Inline:callback<i>, MYSQL_TAGS:...);

/**
 * @brief      Send the rows of a batch, then call an inline with its error.
 *
 * @param      batch     The batch, which is forgotten once sent.
 * @param      callback  The inline, as `using inline Name`, taking the error,
 *                       `0` when every row went in.
 *
 * @return     - `true` the batch is sent
 *             - `false` the inline is freed, when:
 *                 + it could not be captured
 *                 + `batch` or its statement does not exist
 *                 + a limit of the connection refused it
 */
forward bool:MySQL_ExecuteBatchInline(Batch:batch, Inline:callback<i>);

/**
 * @brief      Hash a password with Argon2id, then call an inline with the hash.
 *
 * @param      callback     The inline, as `using inline Name`, taking the hash,
 *                          empty when it failed.
 * @param      password     The password.
 * @param      memory       Memory, in KiB, from `8192` to `1048576`.
 * @param      iterations   Passes, from `1` to `16`.
 * @param      parallelism  Lanes, from `1` to `8`.
 *
 * @return     - `true` the work started
 *             - `false` the inline is freed, when:
 *                 + it could not be captured
 *                 + a cost is out of range
 */
forward bool:MySQL_HashArgon2Inline(Inline:callback<s>, const password[], memory = MYSQL_ARGON2_MEMORY, iterations = MYSQL_ARGON2_ITERATIONS, parallelism = MYSQL_ARGON2_PARALLELISM);

/**
 * @brief      Hash a password with bcrypt, then call an inline with the hash.
 *
 * @param      callback  The inline, as `using inline Name`, taking the hash,
 *                       empty when it failed.
 * @param      password  The password.
 * @param      cost      Cost, from `4` to `20`.
 *
 * @return     - `true` the work started
 *             - `false` the inline is freed, when:
 *                 + it could not be captured
 *                 + the cost is out of range
 */
forward bool:MySQL_HashBcryptInline(Inline:callback<s>, const password[], cost = MYSQL_BCRYPT_COST);

/**
 * @brief      Verify a password against an Argon2 or bcrypt hash, then call an
 *             inline with whether they match.
 *
 * @param      callback  The inline, as `using inline Name`, taking whether
 *                       they match. A hash that cannot be read never matches.
 * @param      password  The password.
 * @param      hash      The hash.
 *
 * @return     - `true` the work started
 *             - `false` the inline could not be captured, and is freed
 */
forward bool:MySQL_VerifyPasswordInline(Inline:callback<i>, const password[], const hash[]);

/**
 * # Internal
 */

forward @SSI_MySQLAnswered(Inline:closure);
forward @SSI_MySQLHashed(Inline:closure, const hash[]);
forward @SSI_MySQLVerified(Inline:closure, bool:match);

/**
 * # MySQL
 */

stock bool:MySQL_ThreadedQueryInline(MySQL:handle, Inline:callback<i>, const query[], MYSQL_TAGS:...) {
    new const
        Inline:closure = callback
    ;

    if (!Inline_IsValid(closure)) {
        return false;
    }

    if (MySQL_ThreadedQuery(handle, "@SSI_MySQLAnswered", _:closure, query, ___(3))) {
        return true;
    }

    Inline_Free(closure);

    return false;
}

stock bool:MySQL_ParallelQueryInline(MySQL:handle, Inline:callback<i>, const query[], MYSQL_TAGS:...) {
    new const
        Inline:closure = callback
    ;

    if (!Inline_IsValid(closure)) {
        return false;
    }

    if (MySQL_ParallelQuery(handle, "@SSI_MySQLAnswered", _:closure, query, ___(3))) {
        return true;
    }

    Inline_Free(closure);

    return false;
}

stock bool:MySQL_SendQueryInline(Query:query, Inline:callback<i>, bool:parallel = false) {
    new const
        Inline:closure = callback
    ;

    if (!Inline_IsValid(closure)) {
        return false;
    }

    if (MySQL_SendQuery(query, "@SSI_MySQLAnswered", _:closure, parallel)) {
        return true;
    }

    Inline_Free(closure);

    return false;
}

stock bool:MySQL_ExecuteStatementInline(Statement:statement, Inline:callback<i>, MYSQL_TAGS:...) {
    new const
        Inline:closure = callback
    ;

    if (!Inline_IsValid(closure)) {
        return false;
    }

    if (MySQL_ExecuteStatement(statement, "@SSI_MySQLAnswered", _:closure, ___(2))) {
        return true;
    }

    Inline_Free(closure);

    return false;
}

stock bool:MySQL_ExecuteBatchInline(Batch:batch, Inline:callback<i>) {
    new const
        Inline:closure = callback
    ;

    if (!Inline_IsValid(closure)) {
        return false;
    }

    if (MySQL_ExecuteBatch(batch, "@SSI_MySQLAnswered", _:closure)) {
        return true;
    }

    Inline_Free(closure);

    return false;
}

/**
 * # Passwords
 */

stock bool:MySQL_HashArgon2Inline(Inline:callback<s>, const password[], memory = MYSQL_ARGON2_MEMORY, iterations = MYSQL_ARGON2_ITERATIONS, parallelism = MYSQL_ARGON2_PARALLELISM) {
    new const
        Inline:closure = callback
    ;

    if (!Inline_IsValid(closure)) {
        return false;
    }

    if (MySQL_HashArgon2(password, "@SSI_MySQLHashed", _:closure, memory, iterations, parallelism)) {
        return true;
    }

    Inline_Free(closure);

    return false;
}

stock bool:MySQL_HashBcryptInline(Inline:callback<s>, const password[], cost = MYSQL_BCRYPT_COST) {
    new const
        Inline:closure = callback
    ;

    if (!Inline_IsValid(closure)) {
        return false;
    }

    if (MySQL_HashBcrypt(password, "@SSI_MySQLHashed", _:closure, cost)) {
        return true;
    }

    Inline_Free(closure);

    return false;
}

stock bool:MySQL_VerifyPasswordInline(Inline:callback<i>, const password[], const hash[]) {
    new const
        Inline:closure = callback
    ;

    if (!Inline_IsValid(closure)) {
        return false;
    }

    if (MySQL_VerifyPassword(password, hash, "@SSI_MySQLVerified", _:closure)) {
        return true;
    }

    Inline_Free(closure);

    return false;
}

/**
 * # Calls
 */

public @SSI_MySQLAnswered(Inline:closure) {
    Inline_CallOnce(closure, MySQL_GetErrno());

    return 1;
}

public @SSI_MySQLHashed(Inline:closure, const hash[]) {
    Inline_CallOnce(closure, hash);

    return 1;
}

public @SSI_MySQLVerified(Inline:closure, bool:match) {
    Inline_CallOnce(closure, match);

    return 1;
}
