#if defined _INC_SSI_BITS
    #endinput
#endif
#define _INC_SSI_BITS

#include <open.mp>
#include <SSI\collection>

/**
 * Sets of bits, as y_bit keeps them: one bit for each id up to a size, 32 to a
 * cell.
 *
 *     static
 *         Bits:Seen<MAX_VEHICLES>,
 *         Bits:PlayerGroup[MAX_PLAYERS]<MAX_GROUPS>
 *     ;
 *
 *     Bits_Let(Seen, vehicleid);
 *
 *     if (Bits_Test(PlayerGroup[playerid], groupid)) {
 *     }
 *
 *     foreach (new Group:groupid : Bits(PlayerGroup[playerid])) {
 *     }
 *
 * - `Bits:Name<SIZE>` declares a set of `SIZE` bits, and `Bits:Name[COUNT]<SIZE>`
 *   one for each of `COUNT` ids. Either is a plain array of cells, so a set is
 *   passed as `Name` or `Name[id]`, and works as a field of an enum too.
 * - A size and an index may carry a tag.
 * - The names are the ones of y_bit. `Bits_Set` turns a bit on or off, as told,
 *   `Bits_Let` turns it on, `Bits_Vet` turns it off and `Bits_Clear` turns every
 *   bit off.
 * - `Bits_Test`, `Bits_Set`, `Bits_Let` and `Bits_Vet` are macros, so the index
 *   is read twice and must have no side effect. Like any index of an array, it
 *   must be inside the set.
 * - `foreach (new i : Bits(Name))` walks the bits that are on, in order,
 *   skipping every empty cell at once.
 */

/**
 * # Header
 */

#define SSI_BITS_CELLS(%0) ((_:(%0) + 31) >>> 5)

#define Bits:%0<%1> %0[SSI_BITS_CELLS(%1)]

#define Bits@SSI_loop|||%9|||%1|||(%3)||| %9%1=%9(-1);_:(%1=%9(SSI@Bits_Next((_:%1),%3)))!=-1;

static stock const SSI@bitsDeBruijn[32] = {
    0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
    31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
};

/**
 * # Functions
 */

/**
 * @brief      Whether a bit is on.
 *
 * @param      bits   The set.
 * @param      index  The bit.
 *
 * @return     - `true` it is on
 *             - `false` it is off
 */
forward bool:Bits_Test(const bits[], index);
#define Bits_Test(%0,%1) (bool:(((%0[_:(%1) >>> 5]) >>> (_:(%1) & 31)) & 1))

/**
 * @brief      Turn a bit on or off.
 *
 * @param      bits   The set.
 * @param      index  The bit.
 * @param      set    Whether it is on.
 */
forward Bits_Set(bits[], index, bool:set);
#define Bits_Set(%0,%1,%2) (%0[_:(%1) >>> 5] = (%2) ? (%0[_:(%1) >>> 5] | (1 << (_:(%1) & 31))) : (%0[_:(%1) >>> 5] & ~(1 << (_:(%1) & 31))))

/**
 * @brief      Turn a bit on.
 *
 * @param      bits   The set.
 * @param      index  The bit.
 */
forward Bits_Let(bits[], index);
#define Bits_Let(%0,%1) (%0[_:(%1) >>> 5] |= 1 << (_:(%1) & 31))

/**
 * @brief      Turn a bit off.
 *
 * @param      bits   The set.
 * @param      index  The bit.
 */
forward Bits_Vet(bits[], index);
#define Bits_Vet(%0,%1) (%0[_:(%1) >>> 5] &= ~(1 << (_:(%1) & 31)))

/**
 * @brief      Turn every bit off.
 *
 * @param      bits  The set.
 * @param      size  Cells of the set.
 */
forward Bits_Clear(bits[], size = sizeof (bits));

/**
 * @brief      The number of bits on.
 *
 * @param      bits  The set.
 * @param      size  Cells of the set.
 *
 * @return     The count.
 */
forward Bits_Count(const bits[], size = sizeof (bits));

/**
 * @brief      Whether every bit is off.
 *
 * @param      bits  The set.
 * @param      size  Cells of the set.
 *
 * @return     - `true` every bit is off
 *             - `false` at least one is on
 */
forward bool:Bits_IsEmpty(const bits[], size = sizeof (bits));

/**
 * @brief      Turn on every bit that is on in another set.
 *
 * @param      bits   The set to change.
 * @param      other  The set to add.
 * @param      size   Cells of both sets.
 */
forward Bits_Or(bits[], const other[], size = sizeof (bits));

/**
 * @brief      Make a set the same as another.
 *
 * @param      bits   The set to change.
 * @param      other  The set to copy.
 * @param      size   Cells of both sets.
 */
forward Bits_Copy(bits[], const other[], size = sizeof (bits));

/**
 * @brief      Whether two sets have a bit on in common.
 *
 * @param      bits   One set.
 * @param      other  The other.
 * @param      size   Cells of both sets.
 *
 * @return     - `true` they do
 *             - `false` they do not
 */
forward bool:Bits_Intersects(const bits[], const other[], size = sizeof (bits));

/**
 * # Internal
 */

stock SSI@Bits_Next(previous, const bits[], size = sizeof (bits)) {
    new
        index = previous + 1,
        cell = index >>> 5
    ;

    if (cell >= size) {
        return -1;
    }

    new
        word = bits[cell] & (-1 << (index & 31))
    ;

    while (word == 0) {
        if (++cell == size) {
            return -1;
        }

        word = bits[cell];
    }

    return (cell << 5) | SSI@bitsDeBruijn[((word & -word) * 0x077CB531) >>> 27];
}

/**
 * # Bits
 */

stock Bits_Clear(bits[], size = sizeof (bits)) {
    for (new cell; cell != size; ++cell) {
        bits[cell] = 0;
    }
}

stock Bits_Count(const bits[], size = sizeof (bits)) {
    new
        count
    ;

    for (new cell; cell != size; ++cell) {
        new
            word = bits[cell]
        ;

        word = word - ((word >>> 1) & 0x55555555);
        word = (word & 0x33333333) + ((word >>> 2) & 0x33333333);
        count += (((word + (word >>> 4)) & 0x0F0F0F0F) * 0x01010101) >>> 24;
    }

    return count;
}

stock bool:Bits_IsEmpty(const bits[], size = sizeof (bits)) {
    for (new cell; cell != size; ++cell) {
        if (bits[cell] != 0) {
            return false;
        }
    }

    return true;
}

stock Bits_Or(bits[], const other[], size = sizeof (bits)) {
    for (new cell; cell != size; ++cell) {
        bits[cell] |= other[cell];
    }
}

stock Bits_Copy(bits[], const other[], size = sizeof (bits)) {
    for (new cell; cell != size; ++cell) {
        bits[cell] = other[cell];
    }
}

stock bool:Bits_Intersects(const bits[], const other[], size = sizeof (bits)) {
    for (new cell; cell != size; ++cell) {
        if (bits[cell] & other[cell]) {
            return true;
        }
    }

    return false;
}
