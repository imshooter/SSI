#if defined _INC_SSI_EXTRA
    #endinput
#endif
#define _INC_SSI_EXTRA

#include <SSI\hooks>

/**
 * Extra data: values kept on the ids of something else, with a row of cells
 * for each id and a column for each name. A column has a type, which is a
 * number, a float, a boolean or a string, and a default. Reading or writing a
 * number is an array index. Columns are made by name in a hook of
 * `OnExtraInit`, and every id starts with the default of each column:
 *
 *     #include <SSI\extra>
 *
 *     new
 *         Extra:VehicleExtra<MAX_VEHICLES, 8>
 *     ;
 *
 *     static
 *         VehicleExtra:gFuelColumn,
 *         VehicleExtra:gPlateColumn
 *     ;
 *
 *     hook OnExtraInit() {
 *         gFuelColumn = Extra_Column(VehicleExtra, "fuel", EXTRA_FLOAT, 50.0);
 *         gPlateColumn = Extra_Column(VehicleExtra, "plate", EXTRA_STRING, 8);
 *
 *         return 0;
 *     }
 *
 *     Extra_Set(VehicleExtra, vehicleid, gFuelColumn, 37.5);
 *     Extra_SetString(VehicleExtra, vehicleid, gPlateColumn, "ABC 123");
 *
 *     Extra_Reset(VehicleExtra, vehicleid);
 *
 * - `Name<IDS, CELLS>` keeps a row of `CELLS` cells for each id below `IDS`.
 *   A number, a float or a boolean takes one cell. A string of `LENGTH`
 *   characters takes `(LENGTH + 1) char` cells, packed.
 * - A column is the cell it starts at, tagged `Name:`. Columns are laid out in
 *   the order they are made.
 * - A read gives the value back untagged. `Extra_Get` of a string column gives
 *   its first cell, which is `0` only when the text is empty.
 * - An id out of range is an array error, as with any array. The owner of the
 *   ids calls `Extra_Reset` when an id is made, so a reused id starts with the
 *   defaults again.
 * - `Extra_View` hands a row and its columns to a function that writes them
 *   somewhere else, such as a JSON document.
 */

/**
 * # Header
 */

#if !defined SSI_EXTRA_NAME
    #define SSI_EXTRA_NAME (32)
#endif

#if !defined SSI_EXTRA_STRING
    #define SSI_EXTRA_STRING (128)
#endif

enum E_EXTRA_TYPE {
    EXTRA_INT,
    EXTRA_FLOAT,
    EXTRA_BOOL,
    EXTRA_STRING
};

/**
 * Makes `Extra:extra<>` in the forwards below a plain parameter, so the editor
 * shows an extra the way it is used. The declaration takes its place after
 * them.
 */
#define Extra:%0<%1> %0

#if !defined SSI@column
    stock
        SSI@column
    ;
#endif

/**
 * # Functions
 */

/**
 * @brief      Make a column, or find the one made with the same name.
 *
 * Every id gets the default. Called in a hook of `OnExtraInit`.
 *
 * @param      extra  The extra.
 * @param      name   Name of the column.
 * @param      type   What it holds.
 * @param      value  The default, of any tag: a float column takes a float
 *                    such as `50.0`. For a string, the most characters it
 *                    holds. The default of a string is empty.
 *
 * @return     - the column, tagged with the extra
 *             - `-1` when:
 *                 + `name` is empty, or longer than `SSI_EXTRA_NAME`
 *                 + a column of another type has that name
 *                 + a string is shorter than a character, or longer than
 *                   `SSI_EXTRA_STRING`
 *                 + the row has no room left
 */
forward Extra_Column(Extra:extra<>, const name[], E_EXTRA_TYPE:type, value);
#define Extra_Column(%0,%1,%2,%3) %0:SSI@Extra_Column(%0@SSI_data, %0@SSI_default, %0@SSI_type, %0@SSI_size, %0@SSI_name, %0@SSI_used, sizeof %0@SSI_data, sizeof %0@SSI_default, %1, %2, _:(%3))

/**
 * @brief      The value of an id in a number, float or boolean column.
 *
 * @param      extra   The extra.
 * @param      id      The id.
 * @param      column  The column.
 *
 * @return     - the value, untagged
 */
forward Extra_Get(Extra:extra<>, id, column);
#define Extra_Get(%0,%1,%2) (%0@SSI_data[_:(%1)][_:(%0:SSI@column = (%2))])

/**
 * @brief      Give an id a value in a number, float or boolean column.
 *
 * @param      extra   The extra.
 * @param      id      The id.
 * @param      column  The column.
 * @param      value   The value, of any tag.
 *
 * @return     - the value
 */
forward Extra_Set(Extra:extra<>, id, column, value);
#define Extra_Set(%0,%1,%2,%3) (%0@SSI_data[_:(%1)][_:(%0:SSI@column = (%2))] = _:(%3))

/**
 * @brief      The text of an id in a string column.
 *
 * @param      extra   The extra.
 * @param      id      The id.
 * @param      column  The column.
 * @param      output  Reads back the text.
 * @param      size    Size of `output`.
 *
 * @return     - `true` the text was written
 *             - `false` the column holds no string, and the output is cleared
 */
forward bool:Extra_GetString(Extra:extra<>, id, column, output[], size = sizeof (output));
#define Extra_GetString(%0,%1,%2,%3) SSI@Extra_GetString(%0@SSI_data[_:(%1)], %0@SSI_type, _:(%0:SSI@column = (%2)), %3)

/**
 * @brief      Give an id a text in a string column.
 *
 * Text longer than the cells of the column hold is cut. The cells are whole,
 * so a column of 8 characters holds 11.
 *
 * @param      extra   The extra.
 * @param      id      The id.
 * @param      column  The column.
 * @param      text    The text.
 *
 * @return     - `true` the text is written
 *             - `false` the column holds no string
 */
forward bool:Extra_SetString(Extra:extra<>, id, column, const text[]);
#define Extra_SetString(%0,%1,%2,%3) SSI@Extra_SetString(%0@SSI_data[_:(%1)], %0@SSI_type, %0@SSI_size, _:(%0:SSI@column = (%2)), %3)

/**
 * @brief      Give an id the default of every column.
 *
 * @param      extra  The extra.
 * @param      id     The id.
 */
forward Extra_Reset(Extra:extra<>, id);
#define Extra_Reset(%0,%1) %0@SSI_data[_:(%1)] = %0@SSI_default

/**
 * @brief      What a column holds.
 *
 * @param      extra   The extra.
 * @param      column  The column.
 *
 * @return     - the type
 */
forward E_EXTRA_TYPE:Extra_Type(Extra:extra<>, column);
#define Extra_Type(%0,%1) (%0@SSI_type[_:(%0:SSI@column = (%1))])

/**
 * @brief      The name of a column.
 *
 * @param      extra   The extra.
 * @param      column  The column.
 * @param      name    Reads back the name, an array of known size.
 *
 * @return     - `true` the name was written
 *             - `false` the column is not made, and the name is cleared
 */
forward bool:Extra_Name(Extra:extra<>, column, name[]);
#define Extra_Name(%0,%1,%2) SSI@Extra_Name(%0@SSI_name, %0@SSI_used, _:(%0:SSI@column = (%1)), %2)

/**
 * The row of an id and its columns, as the arguments of a function that
 * writes them somewhere else: the row, the defaults, the types, the sizes and
 * the names, each read at the cell a column starts, and the cells in use.
 *
 *     stock WriteRow(const row[], const defaults[], const E_EXTRA_TYPE:types[], const sizes[], const names[][], used) {
 *         for (new cell; cell < used; cell += sizes[cell]) {
 *         }
 *     }
 *
 *     WriteRow(Extra_View(VehicleExtra, vehicleid));
 */
#define Extra_View(%0,%1) %0@SSI_data[_:(%1)], %0@SSI_default, %0@SSI_type, %0@SSI_size, %0@SSI_name, %0@SSI_used

/**
 * # Events
 */

/**
 * @brief      The columns can be made.
 *
 * Called when the script starts, from a hook of `OnGameModeInit`, or of
 * `OnFilterScriptInit` in a filterscript. The hooks of those callbacks run in
 * the order of the includes, so the ones declared before `SSI\extra` run
 * first. Include it before any file that reads or writes extra data when the
 * script starts. Modules make their columns here.
 */
event OnExtraInit();

/**
 * # Declaration
 */

#undef Extra

/**
 * Declares the extra tagged `%0`, `Name<IDS, CELLS>`, static when the
 * declaration is.
 *
 *     static
 *         Extra:VehicleExtra<MAX_VEHICLES, 8>
 *     ;
 */
#define Extra:%0<%1,%2> %0@SSI_data[_:(%1)][(%2)], %0@SSI_default[(%2)], E_EXTRA_TYPE:%0@SSI_type[(%2)], %0@SSI_size[(%2)], %0@SSI_name[(%2)][SSI_EXTRA_NAME + 1], %0@SSI_used

/**
 * # Internal
 */

stock SSI@Extra_Column(data[][], defaults[], E_EXTRA_TYPE:types[], sizes[], names[][], &used, ids, cells, const name[], E_EXTRA_TYPE:type, value) {
    if (name[0] == EOS) {
        return -1;
    }

    if (strlen(name) > SSI_EXTRA_NAME) {
        return -1;
    }

    for (new cell; cell < used; cell += sizes[cell]) {
        if (!strequal(names[cell], name)) {
            continue;
        }

        if (types[cell] != type) {
            return -1;
        }

        return cell;
    }

    if (type == EXTRA_STRING && !(0 < value <= SSI_EXTRA_STRING)) {
        return -1;
    }

    new const
        size = (type == EXTRA_STRING) ? ((value + 1) char) : 1
    ;

    if (used + size > cells) {
        return -1;
    }

    new const
        column = used
    ;

    strcopy(names[column], name, SSI_EXTRA_NAME + 1);

    types[column] = type;
    sizes[column] = size;
    used += size;

    if (type == EXTRA_STRING) {
        return column;
    }

    defaults[column] = value;

    for (new i; i != ids; ++i) {
        data[i][column] = value;
    }

    return column;
}

stock bool:SSI@Extra_GetString(const row[], const E_EXTRA_TYPE:types[], column, output[], size = sizeof (output)) {
    output[0] = EOS;

    if (types[column] != EXTRA_STRING) {
        return false;
    }

    __emit(
        push.s size,
        load.s.pri row,
        load.s.alt column,
        shl.c.alt 2,
        add,
        push.pri,
        push.s output,
        push.c 12,
        sysreq.c strunpack,
        stack 16
    );

    return true;
}

stock bool:SSI@Extra_SetString(row[], const E_EXTRA_TYPE:types[], const sizes[], column, const text[]) {
    if (types[column] != EXTRA_STRING) {
        return false;
    }

    new const
        size = sizes[column]
    ;

    __emit(
        push.s size,
        push.s text,
        load.s.pri row,
        load.s.alt column,
        shl.c.alt 2,
        add,
        push.pri,
        push.c 12,
        sysreq.c strpack,
        stack 16
    );

    return true;
}

stock bool:SSI@Extra_Name(const names[][], used, column, name[], size = sizeof (name)) {
    name[0] = EOS;

    if (!(0 <= column < used)) {
        return false;
    }

    strcopy(name, names[column], size);

    return name[0] != EOS;
}

/**
 * # Calls
 */

#if defined FILTERSCRIPT
    hook OnFilterScriptInit() {
        call OnExtraInit();

        return 1;
    }
#else
    hook OnGameModeInit() {
        call OnExtraInit();

        return 1;
    }
#endif
