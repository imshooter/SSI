#if defined _INC_SSI_EXTRA_INLINE_PG
    #endinput
#endif
#define _INC_SSI_EXTRA_INLINE_PG

#include <open.mp>
#include <omp-postgresql>
#include <SSI\inline>
#include <SSI\collection>
#include <SSI\hooks>

/**
 * Queries of the omp-postgresql component answered by an inline, with every
 * value sent apart from the query, so nothing is ever escaped:
 *
 *     #include <SSI_Extra\inline-pg>
 *
 *     new
 *         gDatabase
 *     ;
 *
 *     public OnGameModeInit() {
 *         gDatabase = Postgres_Connect("game");
 *
 *         return 1;
 *     }
 *
 *     ShowAge(playerid, const name[]) {
 *         inline OnFound(error) {
 *             if (error != PG_ERROR_NONE) {
 *                 @return;
 *             }
 *
 *             if (Postgres_Rows() == 0) {
 *                 @return;
 *             }
 *
 *             new
 *                 days
 *             ;
 *
 *             Postgres_GetInt(0, "days", days);
 *             SendClientMessage(playerid, -1, "Registered %i days ago.", days);
 *         }
 *
 *         Postgres_QueryInline(gDatabase, using inline OnFound, "SELECT current_date - registered AS days FROM accounts WHERE name = %s", name);
 *     }
 *
 * - A query is written as for `format`, and each specifier is a parameter
 *   bound to the argument in its place: `%i` an integer, `%f` a float, `%b` a
 *   boolean, `%s` text, `%u` a UUID and `%j` JSON. `%%` is a percent sign. A
 *   specifier is never quoted. Any other type is text cast in the query, as
 *   `%s::bigint`.
 * - The queries of a connection run one after another, in the order they were
 *   sent. One sent before the connection is up, or while the component holds
 *   all the jobs it takes, waits here and goes when there is room.
 * - The inline takes the error of the query, `PG_ERROR_NONE` when it ran. It is
 *   called once, on the main thread, with the result active, so the getters
 *   read it. The result is gone once the inline returns.
 * - `Postgres_Query` sends a query that needs no answer, so a write spends no
 *   inline. A failed query of either kind calls `OnPostgresQueryFailed`.
 * - The script can run jobs of its own through the component next to these.
 *   They share its room, and closing one lets the waiting queries go.
 * - Text goes in and comes out in the code page of the clients, Windows-1252,
 *   since the component speaks UTF-8 only. Strings are unpacked.
 * - The inline keeps the arguments and locals of the function that started it,
 *   so the player id needs no passing. A player who left by then is still in
 *   it: check that the player is the same one when it matters.
 * - The connection settings come from the service file the component reads,
 *   named by `PGSERVICEFILE` in the environment of the server.
 */

/**
 * # Header
 */

#if !defined SSI_POSTGRES_QUERY_LENGTH
    #define SSI_POSTGRES_QUERY_LENGTH (2048)
#endif

#if !defined SSI_POSTGRES_TEXT_LENGTH
    #define SSI_POSTGRES_TEXT_LENGTH (4096)
#endif

#if !defined SSI_POSTGRES_REQUESTS
    #define SSI_POSTGRES_REQUESTS (PostgresRequest:512)
#endif

#define SSI_POSTGRES_PARAMETERS (64)

#define SSI_POSTGRES_CONNECTIONS (8)

#define SSI_POSTGRES_CONTEXT (0x53534900)

#define INVALID_POSTGRES_REQUEST (PostgresRequest:-1)

static enum E_POSTGRES_REQUEST_DATA {
    E_POSTGRES_REQUEST_CONNECTION,
    E_POSTGRES_REQUEST_STATEMENT,
    E_POSTGRES_REQUEST_JOB,
    Inline:E_POSTGRES_REQUEST_INLINE,
    PostgresRequest:E_POSTGRES_REQUEST_NEXT
};

static stock
    Collection:PostgresRequest<SSI_POSTGRES_REQUESTS>
;

static stock
    SSI@postgresRequest[SSI_POSTGRES_REQUESTS][E_POSTGRES_REQUEST_DATA],
    PostgresRequest:SSI@postgresHead = INVALID_POSTGRES_REQUEST,
    PostgresRequest:SSI@postgresTail = INVALID_POSTGRES_REQUEST,
    SSI@postgresJob,
    SSI@postgresQuery[SSI_POSTGRES_QUERY_LENGTH],
    SSI@postgresText[SSI_POSTGRES_TEXT_LENGTH],
    SSI@postgresKind[SSI_POSTGRES_PARAMETERS],
    SSI@postgresState[6]
;

/**
 * The characters of Windows-1252 from `0x80` to `0x9F`. The five it leaves out
 * keep their own value.
 */
static stock const SSI@postgresCodePage[32] = {
    0x20AC, 0x0081, 0x201A, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021,
    0x02C6, 0x2030, 0x0160, 0x2039, 0x0152, 0x008D, 0x017D, 0x008F,
    0x0090, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
    0x02DC, 0x2122, 0x0161, 0x203A, 0x0153, 0x009D, 0x017E, 0x0178
};

/**
 * # Functions
 */

/**
 * @brief      Open a connection. The component connects on its own threads,
 *             and `OnPostgresConnected` follows.
 *
 * @param      profile  Name of the service in the service file.
 * @param      pool     Sessions of the connection.
 *
 * @return     - the connection
 *             - `0` the component refused it
 */
forward Postgres_Connect(const profile[], pool = 1);

/**
 * @brief      Close a connection. The queries still waiting here call their
 *             inline with `PG_ERROR_CONNECTION`, and the ones sent are
 *             cancelled.
 *
 * @param      connection  The connection.
 *
 * @return     - `true` it is closing
 *             - `false` it is not a connection
 */
forward bool:Postgres_Close(connection);

/**
 * @brief      Send a query, then call an inline with its error.
 *
 * @param      connection  The connection.
 * @param      callback    The inline, as `using inline Name`, taking the error,
 *                         `PG_ERROR_NONE` when the query ran.
 * @param      query       The query, with a specifier for each argument after
 *                         it.
 *
 * @return     - `true` the query is sent, or waits for room
 *             - `false` the inline is freed, when:
 *                 + it could not be captured
 *                 + a specifier is unknown or quoted
 *                 + the arguments do not match the specifiers
 *                 + the query does not fit `SSI_POSTGRES_QUERY_LENGTH`
 *                 + a text does not fit `SSI_POSTGRES_TEXT_LENGTH`
 *                 + the component refused it, or `connection` is closed
 *                 + `SSI_POSTGRES_REQUESTS` queries are waiting
 */
forward bool:Postgres_QueryInline(connection, Inline:callback<i>, const query[], OPEN_MP_TAGS:...);

/**
 * @brief      Send a query that needs no answer.
 *
 * @param      connection  The connection.
 * @param      query       The query, with a specifier for each argument after
 *                         it.
 *
 * @return     - `true` the query is sent, or waits for room
 *             - `false` for the reasons of `Postgres_QueryInline`
 */
forward bool:Postgres_Query(connection, const query[], OPEN_MP_TAGS:...);

/**
 * @brief      The rows of the active result. Called in the inline of a query,
 *             as the getters below.
 *
 * @return     - the count
 *             - `0` outside an inline, or for a query that returned none
 */
forward Postgres_Rows();

/**
 * @brief      The rows the active query changed.
 *
 * @return     - the count
 *             - `0` outside an inline, or for a query that changes none
 */
forward Postgres_AffectedRows();

/**
 * @brief      Whether a value of the active result is NULL.
 *
 * @param      row     The row, from `0`.
 * @param      column  Name of the column.
 *
 * @return     - `true` it is NULL
 *             - `false` it has a value, or the cell does not exist
 */
forward bool:Postgres_IsNull(row, const column[]);

/**
 * @brief      An integer of the active result.
 *
 * @param      row     The row, from `0`.
 * @param      column  Name of the column.
 * @param      value   Reads back the integer.
 *
 * @return     - `true` it was read
 *             - `false` when:
 *                 + the cell does not exist
 *                 + it is NULL or not an integer
 */
forward bool:Postgres_GetInt(row, const column[], &value);

/**
 * @brief      A float of the active result.
 *
 * @param      row     The row, from `0`.
 * @param      column  Name of the column.
 * @param      value   Reads back the float.
 *
 * @return     - `true` it was read
 *             - `false` when:
 *                 + the cell does not exist
 *                 + it is NULL or not a number
 */
forward bool:Postgres_GetFloat(row, const column[], &Float:value);

/**
 * @brief      A boolean of the active result.
 *
 * @param      row     The row, from `0`.
 * @param      column  Name of the column.
 * @param      value   Reads back the boolean.
 *
 * @return     - `true` it was read
 *             - `false` when:
 *                 + the cell does not exist
 *                 + it is NULL or not a boolean
 */
forward bool:Postgres_GetBool(row, const column[], &bool:value);

/**
 * @brief      A value of the active result as text, in Windows-1252. Text
 *             longer than the output is cut.
 *
 * @param      row     The row, from `0`.
 * @param      column  Name of the column.
 * @param      output  Reads back the text.
 * @param      size    Size of `output`.
 *
 * @return     - `true` it was read
 *             - `false` the output is cleared, when:
 *                 + the cell does not exist
 *                 + it is NULL
 *                 + it does not fit `SSI_POSTGRES_TEXT_LENGTH` in UTF-8
 */
forward bool:Postgres_GetString(row, const column[], output[], size = sizeof (output));

/**
 * @brief      The SQLSTATE of the active query when it failed, as `23505` for
 *             a duplicate key.
 *
 * @param      output  Reads back the five characters.
 * @param      size    Size of `output`.
 *
 * @return     - `true` it was read
 *             - `false` the output is cleared, the query did not reach the
 *               server or did not fail
 */
forward bool:Postgres_GetErrorState(output[], size = sizeof (output));

/**
 * # Events
 */

/**
 * @brief      Every session of a connection is up, the first time and after a
 *             lost connection came back.
 *
 * @param      connection  The connection.
 */
event OnPostgresConnected(connection);

/**
 * @brief      A connection gave up after its attempts. The queries waiting for
 *             it called their inline with `PG_ERROR_CONNECTION`. A new
 *             connection tries again.
 *
 * @param      connection  The connection.
 * @param      message     What the component said.
 */
event OnPostgresConnectionFailed(connection, const message[]);

/**
 * @brief      A query failed, with an inline or without.
 *
 * @param      connection  The connection.
 * @param      error       The kind of error, one of `PG_ERROR_*`.
 * @param      sqlstate    The SQLSTATE, or empty when the query did not reach
 *                         the server.
 * @param      message     What PostgreSQL or the component said. It can quote
 *                         values of the query.
 */
event OnPostgresQueryFailed(connection, error, const sqlstate[], const message[]);

/**
 * # Internal
 */

static stock bool:SSI_PostgresEncodeInternal(const text[], output[], size) {
    new
        length = 0
    ;

    for (new i; text[i] != EOS; ++i) {
        new
            code = text[i]
        ;

        if (0x80 <= code < 0xA0) {
            code = SSI@postgresCodePage[code - 0x80];
        }

        if (code < 0x80) {
            if (length + 1 >= size) {
                return false;
            }

            output[length++] = code;

            continue;
        }

        if (code < 0x800) {
            if (length + 2 >= size) {
                return false;
            }

            output[length++] = 0xC0 | (code >>> 6);
            output[length++] = 0x80 | (code & 0x3F);

            continue;
        }

        if (length + 3 >= size) {
            return false;
        }

        output[length++] = 0xE0 | (code >>> 12);
        output[length++] = 0x80 | ((code >>> 6) & 0x3F);
        output[length++] = 0x80 | (code & 0x3F);
    }

    output[length] = EOS;

    return true;
}

static stock SSI_PostgresByteInternal(code) {
    if (code < 0x80) {
        return code;
    }

    if (0xA0 <= code <= 0xFF) {
        return code;
    }

    for (new i; i != sizeof (SSI@postgresCodePage); ++i) {
        if (SSI@postgresCodePage[i] == code) {
            return 0x80 + i;
        }
    }

    return '?';
}

static stock SSI_PostgresDecodeInternal(const text[], output[], size) {
    new
        length = 0,
        i = 0
    ;

    while (text[i] != EOS && length + 1 < size) {
        new
            code = text[i++]
        ;

        if (code >= 0xF0) {
            code = '?';

            while (0x80 <= text[i] < 0xC0) {
                ++i;
            }
        } else if (code >= 0xE0) {
            code = ((code & 0x0F) << 12) | ((text[i] & 0x3F) << 6) | (text[i + 1] & 0x3F);
            i += 2;
        } else if (code >= 0xC0) {
            code = ((code & 0x1F) << 6) | (text[i++] & 0x3F);
        }

        output[length++] = SSI_PostgresByteInternal(code);
    }

    output[length] = EOS;
}

static stock bool:SSI_PostgresBindTextInternal(statement, index, const text[], type) {
    for (new i; text[i] != EOS; ++i) {
        if (text[i] < 0x80) {
            continue;
        }

        if (!SSI_PostgresEncodeInternal(text, SSI@postgresText, sizeof (SSI@postgresText))) {
            return false;
        }

        return pg_bind_string(statement, index, SSI@postgresText, type);
    }

    return pg_bind_string(statement, index, text, type);
}

static stock bool:SSI_PostgresBindAddressInternal(statement, index, address, type) {
    __emit(
        push.s type,
        push.s address,
        push.s index,
        push.s statement,
        push.c 16,
        call SSI_PostgresBindTextInternal,
        retn
    );

    return false;
}

static stock bool:SSI_PostgresBindInternal(statement, index, kind, address) {
    switch (kind) {
        case 'i': {
            return pg_bind_int(statement, index, SSI@Amx_Read(address));
        }
        case 'f': {
            return pg_bind_float(statement, index, Float:SSI@Amx_Read(address));
        }
        case 'b': {
            return pg_bind_bool(statement, index, bool:SSI@Amx_Read(address));
        }
        case 's': {
            return SSI_PostgresBindAddressInternal(statement, index, address, PG_TEXT);
        }
        case 'u': {
            return SSI_PostgresBindAddressInternal(statement, index, address, PG_UUID);
        }
        case 'j': {
            return SSI_PostgresBindAddressInternal(statement, index, address, PG_JSONB);
        }
    }

    return false;
}

static stock SSI_PostgresPrepareInternal(connection, const query[], frame, first) {
    if (strlen(query) >= sizeof (SSI@postgresQuery) - SSI_POSTGRES_PARAMETERS) {
        return 0;
    }

    strcopy(SSI@postgresQuery, query);

    new const
        arguments = SSI@Amx_Read(frame + 8) / 4 - first
    ;

    new
        count = 0,
        position = 0
    ;

    while ((position = strfind(SSI@postgresQuery, "%", false, position)) != -1) {
        new const
            kind = SSI@postgresQuery[position + 1]
        ;

        if (kind == '%') {
            strdel(SSI@postgresQuery, position, position + 1);
            ++position;

            continue;
        }

        switch (kind) {
            case 'i', 'f', 'b', 's', 'u', 'j': {}
            default: {
                return 0;
            }
        }

        if (count == arguments) {
            return 0;
        }

        if (count == SSI_POSTGRES_PARAMETERS) {
            return 0;
        }

        if (position != 0 && SSI@postgresQuery[position - 1] == '\'') {
            return 0;
        }

        SSI@postgresKind[count++] = kind;
        SSI@postgresQuery[position] = '$';

        if (count < 10) {
            SSI@postgresQuery[position + 1] = '0' + count;
            position += 2;

            continue;
        }

        SSI@postgresQuery[position + 1] = '0' + count / 10;
        strins(SSI@postgresQuery, "0", position + 2);
        SSI@postgresQuery[position + 2] = '0' + count % 10;
        position += 3;
    }

    if (count != arguments) {
        return 0;
    }

    new const
        statement = pg_prepare(connection, SSI@postgresQuery, count)
    ;

    if (!statement) {
        return 0;
    }

    for (new i; i != count; ++i) {
        if (!SSI_PostgresBindInternal(statement, i + 1, SSI@postgresKind[i], SSI@Amx_Read(frame + 12 + (first + i) * 4))) {
            pg_statement_close(statement);

            return 0;
        }
    }

    if (!pg_add(statement)) {
        pg_statement_close(statement);

        return 0;
    }

    return statement;
}

static stock bool:SSI_PostgresAliveInternal(connection) {
    new const
        status = pg_connection_state(connection)
    ;

    return status == PG_CONNECTING || status == PG_CONNECTED || status == PG_RECONNECTING;
}

static stock bool:SSI_PostgresWaitingInternal(connection) {
    for (new PostgresRequest:request = SSI@postgresHead; request != INVALID_POSTGRES_REQUEST; request = SSI@postgresRequest[request][E_POSTGRES_REQUEST_NEXT]) {
        if (SSI@postgresRequest[request][E_POSTGRES_REQUEST_CONNECTION] == connection) {
            return true;
        }
    }

    return false;
}

static stock SSI_PostgresWaitInternal(PostgresRequest:request) {
    SSI@postgresRequest[request][E_POSTGRES_REQUEST_NEXT] = INVALID_POSTGRES_REQUEST;

    if (SSI@postgresTail == INVALID_POSTGRES_REQUEST) {
        SSI@postgresHead = request;
    } else {
        SSI@postgresRequest[SSI@postgresTail][E_POSTGRES_REQUEST_NEXT] = request;
    }

    SSI@postgresTail = request;
}

static stock SSI_PostgresUnlinkInternal(PostgresRequest:previous, PostgresRequest:request) {
    new const
        PostgresRequest:next = SSI@postgresRequest[request][E_POSTGRES_REQUEST_NEXT]
    ;

    if (previous == INVALID_POSTGRES_REQUEST) {
        SSI@postgresHead = next;
    } else {
        SSI@postgresRequest[previous][E_POSTGRES_REQUEST_NEXT] = next;
    }

    if (SSI@postgresTail == request) {
        SSI@postgresTail = previous;
    }
}

static stock bool:SSI_PostgresExecuteInternal(PostgresRequest:request) {
    new const
        statement = SSI@postgresRequest[request][E_POSTGRES_REQUEST_STATEMENT],
        job = pg_execute(statement, 0, 0, SSI_POSTGRES_CONTEXT + _:request)
    ;

    if (!job) {
        return false;
    }

    pg_statement_close(statement);

    SSI@postgresRequest[request][E_POSTGRES_REQUEST_STATEMENT] = 0;
    SSI@postgresRequest[request][E_POSTGRES_REQUEST_JOB] = job;

    return true;
}

static stock bool:SSI_PostgresListedInternal(const list[], count, value) {
    for (new i; i != count; ++i) {
        if (list[i] == value) {
            return true;
        }
    }

    return false;
}

static stock SSI_PostgresFlushInternal() {
    new
        blocked[SSI_POSTGRES_CONNECTIONS],
        count,
        PostgresRequest:previous = INVALID_POSTGRES_REQUEST,
        PostgresRequest:request = SSI@postgresHead
    ;

    while (request != INVALID_POSTGRES_REQUEST) {
        new const
            PostgresRequest:next = SSI@postgresRequest[request][E_POSTGRES_REQUEST_NEXT],
            connection = SSI@postgresRequest[request][E_POSTGRES_REQUEST_CONNECTION]
        ;

        if (SSI_PostgresListedInternal(blocked, count, connection)) {
            previous = request;
            request = next;

            continue;
        }

        if (!SSI_PostgresExecuteInternal(request)) {
            if (count == sizeof (blocked)) {
                return;
            }

            blocked[count++] = connection;
            previous = request;
            request = next;

            continue;
        }

        SSI_PostgresUnlinkInternal(previous, request);
        request = next;
    }
}

static stock SSI_PostgresAbandonInternal(connection) {
    new
        PostgresRequest:previous = INVALID_POSTGRES_REQUEST,
        PostgresRequest:request = SSI@postgresHead
    ;

    while (request != INVALID_POSTGRES_REQUEST) {
        new const
            PostgresRequest:next = SSI@postgresRequest[request][E_POSTGRES_REQUEST_NEXT],
            Inline:closure = SSI@postgresRequest[request][E_POSTGRES_REQUEST_INLINE]
        ;

        if (SSI@postgresRequest[request][E_POSTGRES_REQUEST_CONNECTION] != connection) {
            previous = request;
            request = next;

            continue;
        }

        SSI_PostgresUnlinkInternal(previous, request);
        pg_statement_close(SSI@postgresRequest[request][E_POSTGRES_REQUEST_STATEMENT]);
        Collection_Remove(PostgresRequest, request);
        Inline_CallOnce(closure, PG_ERROR_CONNECTION);

        request = next;
    }
}

static stock bool:SSI_PostgresSendInternal(connection, Inline:closure, const query[], first) {
    new
        frame
    ;

    __emit(
        load.s.pri 0,
        stor.s.pri frame
    );

    new const
        statement = SSI_PostgresPrepareInternal(connection, query, frame, first)
    ;

    if (!statement) {
        Inline_Free(closure);

        return false;
    }

    new const
        PostgresRequest:request = Collection_Alloc(PostgresRequest)
    ;

    if (request == INVALID_POSTGRES_REQUEST) {
        pg_statement_close(statement);
        Inline_Free(closure);

        return false;
    }

    SSI@postgresRequest[request][E_POSTGRES_REQUEST_CONNECTION] = connection;
    SSI@postgresRequest[request][E_POSTGRES_REQUEST_STATEMENT] = statement;
    SSI@postgresRequest[request][E_POSTGRES_REQUEST_JOB] = 0;
    SSI@postgresRequest[request][E_POSTGRES_REQUEST_INLINE] = closure;

    if (SSI_PostgresWaitingInternal(connection)) {
        SSI_PostgresFlushInternal();
    }

    if (!SSI_PostgresWaitingInternal(connection) && SSI_PostgresExecuteInternal(request)) {
        return true;
    }

    if (!SSI_PostgresAliveInternal(connection)) {
        Collection_Remove(PostgresRequest, request);
        pg_statement_close(statement);
        Inline_Free(closure);

        return false;
    }

    SSI_PostgresWaitInternal(request);

    return true;
}

static stock SSI_PostgresErrorInternal(job) {
    if (pg_job_status(job) == PG_CONFIRMED) {
        return PG_ERROR_NONE;
    }

    new const
        error = pg_job_error(job)
    ;

    return (error == PG_ERROR_NONE) ? PG_ERROR_INTERNAL : error;
}

static stock SSI_PostgresFailedInternal(connection, job, error) {
    if (!pg_result_sqlstate(job, 0, SSI@postgresState)) {
        SSI@postgresState[0] = EOS;
    }

    if (!pg_result_message(job, 0, SSI@postgresText) && !pg_job_message(job, SSI@postgresText)) {
        SSI@postgresText[0] = EOS;
    }

    SSI_PostgresDecodeInternal(SSI@postgresText, SSI@postgresText, sizeof (SSI@postgresText));

    call OnPostgresQueryFailed(connection, error, SSI@postgresState, SSI@postgresText);
}

/**
 * # Postgres
 */

stock Postgres_Connect(const profile[], pool = 1) {
    return pg_connect(profile, pool);
}

stock bool:Postgres_Close(connection) {
    if (!pg_connection_close(connection)) {
        return false;
    }

    SSI_PostgresAbandonInternal(connection);

    return true;
}

stock bool:Postgres_QueryInline(connection, Inline:callback<i>, const query[], OPEN_MP_TAGS:...) {
    new const
        Inline:closure = callback
    ;

    if (!Inline_IsValid(closure)) {
        return false;
    }

    return SSI_PostgresSendInternal(connection, closure, query, 3);
}

stock bool:Postgres_Query(connection, const query[], OPEN_MP_TAGS:...) {
    return SSI_PostgresSendInternal(connection, INVALID_INLINE, query, 2);
}

stock Postgres_Rows() {
    return pg_result_rows(SSI@postgresJob, 0);
}

stock Postgres_AffectedRows() {
    new
        count[24]
    ;

    if (!pg_result_affected(SSI@postgresJob, 0, count)) {
        return 0;
    }

    return strval(count);
}

stock bool:Postgres_IsNull(row, const column[]) {
    return pg_result_is_null(SSI@postgresJob, 0, row, pg_result_column(SSI@postgresJob, 0, column));
}

stock bool:Postgres_GetInt(row, const column[], &value) {
    return pg_result_int(SSI@postgresJob, 0, row, pg_result_column(SSI@postgresJob, 0, column), value);
}

stock bool:Postgres_GetFloat(row, const column[], &Float:value) {
    return pg_result_float(SSI@postgresJob, 0, row, pg_result_column(SSI@postgresJob, 0, column), value);
}

stock bool:Postgres_GetBool(row, const column[], &bool:value) {
    return pg_result_bool(SSI@postgresJob, 0, row, pg_result_column(SSI@postgresJob, 0, column), value);
}

stock bool:Postgres_GetString(row, const column[], output[], size = sizeof (output)) {
    output[0] = EOS;

    if (!pg_result_string(SSI@postgresJob, 0, row, pg_result_column(SSI@postgresJob, 0, column), SSI@postgresText)) {
        return false;
    }

    SSI_PostgresDecodeInternal(SSI@postgresText, output, size);

    return true;
}

stock bool:Postgres_GetErrorState(output[], size = sizeof (output)) {
    output[0] = EOS;

    return pg_result_sqlstate(SSI@postgresJob, 0, output, size);
}

/**
 * # Calls
 */

hook OnPgConnection(connection, connection_state) {
    switch (connection_state) {
        case PG_CONNECTED: {
            SSI_PostgresFlushInternal();

            call OnPostgresConnected(connection);
        }
        case PG_CONNECTION_FAILED: {
            SSI_PostgresAbandonInternal(connection);

            if (!pg_connection_message(connection, 0, SSI@postgresText)) {
                SSI@postgresText[0] = EOS;
            }

            SSI_PostgresDecodeInternal(SSI@postgresText, SSI@postgresText, sizeof (SSI@postgresText));

            call OnPostgresConnectionFailed(connection, SSI@postgresText);
        }
        case PG_DISCONNECTED: {
            SSI_PostgresAbandonInternal(connection);
        }
    }

    return 0;
}

hook OnPgComplete(job, context) {
    new const
        PostgresRequest:request = PostgresRequest:(context - SSI_POSTGRES_CONTEXT)
    ;

    if (!Collection_Contains(PostgresRequest, request)) {
        return 0;
    }

    if (SSI@postgresRequest[request][E_POSTGRES_REQUEST_JOB] != job) {
        return 0;
    }

    new const
        connection = SSI@postgresRequest[request][E_POSTGRES_REQUEST_CONNECTION],
        Inline:closure = SSI@postgresRequest[request][E_POSTGRES_REQUEST_INLINE],
        error = SSI_PostgresErrorInternal(job)
    ;

    Collection_Remove(PostgresRequest, request);

    if (error != PG_ERROR_NONE) {
        SSI_PostgresFailedInternal(connection, job, error);
    }

    SSI@postgresJob = job;
    Inline_CallOnce(closure, error);
    SSI@postgresJob = 0;

    pg_job_close(job);

    return ~0;
}

/**
 * A job closed anywhere in the script makes room, so the waiting queries go.
 */
hook native bool:pg_job_close(job) {
    if (!pg_job_close(job)) {
        return false;
    }

    SSI_PostgresFlushInternal();

    return true;
}
