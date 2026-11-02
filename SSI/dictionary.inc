#if defined _INC_SSI_DICTIONARY
    #endinput
#endif
#define _INC_SSI_DICTIONARY

#include <SSI\collection>

/**
 * Dictionaries hold a value for each key. Setting, finding and removing a key
 * take about the same time with ten keys or with a hundred thousand. The
 * brackets of the declaration pick the kind of key, and every call names a
 * dictionary of text keys with `<>`:
 *
 *     #include <SSI\dictionary>
 *
 *     static
 *         Dictionary:Expiry<MAX_EXPIRY_BUCKETS>,
 *         Dictionary:Command<MAX_COMMANDS, MAX_COMMAND_LENGTH>
 *     ;
 *
 *     Dictionary_Set(Expiry, second, _:bucket);
 *     Dictionary_Set(Command<>, "help", _:COMMAND_HELP);
 *
 *     new
 *         value
 *     ;
 *
 *     if (Dictionary_Get(Command<>, "help", value)) {
 *     }
 *
 *     foreach (new entry : Command) {
 *         new
 *             name[MAX_COMMAND_LENGTH + 1]
 *         ;
 *
 *         Dictionary_Key(Command<>, entry, name);
 *         printf("%s: %d", name, Dictionary_Value(Command<>, entry));
 *     }
 *
 * - `Name<SIZE>` holds number keys: any number a cell holds.
 * - `Name<SIZE, LENGTH>` holds text keys of `LENGTH` characters at most,
 *   compared as bytes, case and all.
 *
 * The dictionary is named by its tag, which its entries carry. Keys and values
 * take any tag, as in PawnPlus.
 */

/**
 * # Header
 */

/**
 * Makes `Dictionary:dictionary<>` in the forwards below a plain parameter, so
 * the editor shows a dictionary the way it is used. The declaration takes its
 * place after them.
 */
#define Dictionary:%0<%1> %0

#if !defined SSI@value
    stock
        SSI@value
    ;
#endif

#if !defined SSI@found
    stock
        bool:SSI@found
    ;
#endif

/**
 * # Functions
 */

/**
 * @brief      Give a key a value, adding the key when it is new.
 *
 * @param      dictionary  `Name`, or `Name<>` for text keys.
 * @param      key         The key: a number, or text with `Name<>`.
 * @param      value       Its value.
 *
 * @return     - `true` the key has the value
 *             - `false` the key is new and the dictionary is full, or the text
 *               is longer than the dictionary takes
 */
forward bool:Dictionary_Set(Dictionary:dictionary<>, key, value);
#define Dictionary_Set(%0,%1,%2) SSI_DICTIONARY_A:%0<>Y|||Set|||(,%1,%2)

/**
 * @brief      The value of a key.
 *
 * @param      dictionary  `Name`, or `Name<>` for text keys.
 * @param      key         The key: a number, or text with `Name<>`.
 * @param      value       Where to write the value, when the key is there.
 *
 * @return     - `true` the key is there
 *             - `false` it is not
 */
forward bool:Dictionary_Get(Dictionary:dictionary<>, key, &value);
#define Dictionary_Get(%0,%1,%2) SSI_DICTIONARY_A:%0<>Y|||Get|||(,%1,%2)

/**
 * @brief      Whether a key is there.
 *
 * @param      dictionary  `Name`, or `Name<>` for text keys.
 * @param      key         The key: a number, or text with `Name<>`.
 *
 * @return     - `true` it is there
 *             - `false` it is not
 */
forward bool:Dictionary_Contains(Dictionary:dictionary<>, key);
#define Dictionary_Contains(%0,%1) SSI_DICTIONARY_A:%0<>Y|||Contains|||(,%1)

/**
 * @brief      Remove a key and its value.
 *
 * @param      dictionary  `Name`, or `Name<>` for text keys.
 * @param      key         The key: a number, or text with `Name<>`.
 *
 * @return     - `true` it was removed
 *             - `false` it was not there
 */
forward bool:Dictionary_Remove(Dictionary:dictionary<>, key);
#define Dictionary_Remove(%0,%1) SSI_DICTIONARY_A:%0<>Y|||Remove|||(,%1)

/**
 * @brief      How many keys a dictionary holds.
 *
 * @param      dictionary  `Name`, or `Name<>` for text keys.
 *
 * @return     - the count
 */
forward Dictionary_Count(Dictionary:dictionary<>);
#define Dictionary_Count(%0) SSI_DICTIONARY_A:%0<>Y|||Count|||()

/**
 * @brief      Remove every key.
 *
 * It takes as long as the keys held, not as the size, so a dictionary filled
 * and emptied for each load costs what that load put in.
 *
 * @param      dictionary  `Name`, or `Name<>` for text keys.
 */
forward Dictionary_Clear(Dictionary:dictionary<>);
#define Dictionary_Clear(%0) SSI_DICTIONARY_A:%0<>Y|||Clear|||()

/**
 * @brief      The key of an entry, as `foreach` walks them.
 *
 * A number key is returned. A text key is copied into `key`, unpacked.
 *
 * @param      dictionary  `Name`, or `Name<>` for text keys.
 * @param      entry       The entry.
 * @param      key         Where to write a text key, an array of known size.
 *
 * @return     - the number key
 */
forward Dictionary_Key(Dictionary:dictionary<>, entry, key[] = "");
#define Dictionary_Key(%0,%1) SSI_DICTIONARY_A:%0<>Y|||Key|||(,%1)

/**
 * @brief      The value of an entry, as `foreach` walks them.
 *
 * @param      dictionary  `Name`, or `Name<>` for text keys.
 * @param      entry       The entry.
 *
 * @return     - the value
 */
forward Dictionary_Value(Dictionary:dictionary<>, entry);
#define Dictionary_Value(%0,%1) SSI_DICTIONARY_A:%0<>Y|||Value|||(,%1)

#define SSI_DICTIONARY_A:%0<%1>%2|||%3|||(%4) SSI_DICTIONARY_B%2|||%0|||%3|||(%4)
#define SSI_DICTIONARY_B<>Y|||%0|||%3|||(%4) SSI_StringMap_%3(%0%4)
#define SSI_DICTIONARY_BY|||%0|||%3|||(%4) SSI_KeyMap_%3(%0%4)

/**
 * # Declaration
 */

#undef Dictionary

/**
 * Declares the dictionary tagged `%0`, `Name<SIZE>` with number keys or
 * `Name<SIZE, LENGTH>` with text keys, static when the declaration is.
 *
 *     static
 *         Dictionary:Expiry<MAX_EXPIRY_BUCKETS>,
 *         Dictionary:Command<MAX_COMMANDS, MAX_COMMAND_LENGTH>
 *     ;
 */
#define Dictionary:%0<%1> SSI_DICTIONARY_DECLARE_A:%0|||%1,,|||

#define SSI_DICTIONARY_DECLARE_A:%0|||%1,%4,%5||| SSI_DICTIONARY_DECLARE_B%5X|||%0|||%1|||%4|||
#define SSI_DICTIONARY_DECLARE_BX|||%0|||%1|||%4||| SSI_KeyMap_Declare(%0,%1)
#define SSI_DICTIONARY_DECLARE_B,X|||%0|||%1|||%4||| SSI_StringMap_Declare(%0,%1,%4)

/**
 * # Number Keys
 */

/**
 * `Name<SIZE>` keeps its keys in a table with twice as many slots as its
 * capacity. A slot holds the entry of a key, or `-1`. A key starts at the slot
 * its hash points to and takes the next empty one. Removing a key pulls back
 * the keys after it that belong before the hole, so no slot is ever left marked
 * and a search stops at the first empty slot. The entries, which hold the key
 * and the value, form a handle pool: an entry keeps its id while it lives, and
 * `foreach` walks them.
 */
#define SSI_KeyMap_Declare(%0,%1) \
    %0@SSI_slot[_:(%1) * 2] = { -1, ... }, \
    %0@SSI_key[_:(%1)], \
    %0@SSI_value[_:(%1)], \
    %0@SSI_next[_:(%1) + 1] = { _:(%1), ... }, \
    %0@SSI_prev[_:(%1) + 1] = { _:(%1) * 2, _:(%1) * 2 - 1, ... }, \
    %0@SSI_count, \
    %0@SSI_free

#define SSI_KeyMap_Set(%0,%1,%2) SSI@KeyMap_Set(%0@SSI_count, %0@SSI_free, %0@SSI_next, %0@SSI_prev, %0@SSI_slot, %0@SSI_key, %0@SSI_value, sizeof %0@SSI_slot, sizeof %0@SSI_key, _:(%1), _:(%2))
#define SSI_KeyMap_Get(%0,%1,%2) SSI@KeyMap_Get(%0@SSI_slot, %0@SSI_key, %0@SSI_value, sizeof %0@SSI_slot, _:(%1), _:%2)
#define SSI_KeyMap_Contains(%0,%1) (SSI@KeyMap_Slot(%0@SSI_slot, %0@SSI_key, sizeof %0@SSI_slot, _:(%1)) >= 0)
#define SSI_KeyMap_Remove(%0,%1) SSI@KeyMap_Remove(%0@SSI_count, %0@SSI_free, %0@SSI_next, %0@SSI_prev, %0@SSI_slot, %0@SSI_key, sizeof %0@SSI_slot, sizeof %0@SSI_key, _:(%1))
#define SSI_KeyMap_Count(%0) (%0@SSI_count)
#define SSI_KeyMap_Clear(%0) SSI@KeyMap_Clear(%0@SSI_count, %0@SSI_free, %0@SSI_next, %0@SSI_prev, %0@SSI_slot, %0@SSI_key, sizeof %0@SSI_slot, sizeof %0@SSI_key)
#define SSI_KeyMap_Key(%0,%1) (%0@SSI_key[_:(%1)])
#define SSI_KeyMap_Value(%0,%1) (%0@SSI_value[_:(%1)])

/**
 * # Text Keys
 */

/**
 * `Name<SIZE, LENGTH>` packs a key four characters to a cell and hashes it one
 * cell at a time. The entry keeps the packed key and its hash. The table works
 * as it does with number keys, and a search compares text only where the hash
 * matches. The packing buffer holds two cells more than `LENGTH`, so the
 * functions read `LENGTH` back with `sizeof`. A packed key uses fewer cells.
 */
#define SSI_StringMap_Declare(%0,%1,%2) \
    %0@SSI_slot[_:(%1) * 2] = { -1, ... }, \
    %0@SSI_hash[_:(%1)], \
    %0@SSI_key[_:(%1) * (((%2) + 1) char)], \
    %0@SSI_value[_:(%1)], \
    %0@SSI_next[_:(%1) + 1] = { _:(%1), ... }, \
    %0@SSI_prev[_:(%1) + 1] = { _:(%1) * 2, _:(%1) * 2 - 1, ... }, \
    %0@SSI_count, \
    %0@SSI_free, \
    %0@SSI_pack[(%2) + 2]

#define SSI_StringMap_Set(%0,%1,%2) SSI@StringMap_Set(%0@SSI_count, %0@SSI_free, %0@SSI_next, %0@SSI_prev, %0@SSI_slot, %0@SSI_hash, %0@SSI_key, %0@SSI_value, %0@SSI_pack, sizeof %0@SSI_slot, sizeof %0@SSI_hash, (sizeof %0@SSI_pack - 1) char, sizeof %0@SSI_pack - 2, %1, _:(%2))
#define SSI_StringMap_Get(%0,%1,%2) (SSI@found = SSI@StringMap_Find(%0@SSI_slot, %0@SSI_hash, %0@SSI_key, %0@SSI_value, %0@SSI_pack, sizeof %0@SSI_slot, (sizeof %0@SSI_pack - 1) char, %1, _:%2) >= 0)
#define SSI_StringMap_Contains(%0,%1) (SSI@StringMap_Find(%0@SSI_slot, %0@SSI_hash, %0@SSI_key, %0@SSI_value, %0@SSI_pack, sizeof %0@SSI_slot, (sizeof %0@SSI_pack - 1) char, %1, SSI@value) >= 0)
#define SSI_StringMap_Remove(%0,%1) SSI@StringMap_Remove(%0@SSI_count, %0@SSI_free, %0@SSI_next, %0@SSI_prev, %0@SSI_slot, %0@SSI_hash, %0@SSI_key, %0@SSI_value, %0@SSI_pack, sizeof %0@SSI_slot, sizeof %0@SSI_hash, (sizeof %0@SSI_pack - 1) char, %1)
#define SSI_StringMap_Count(%0) (%0@SSI_count)
#define SSI_StringMap_Clear(%0) SSI@StringMap_Clear(%0@SSI_count, %0@SSI_free, %0@SSI_next, %0@SSI_prev, %0@SSI_slot, %0@SSI_hash, sizeof %0@SSI_slot, sizeof %0@SSI_hash)
#define SSI_StringMap_Key(%0,%1,%2) SSI@StringMap_Key(%2, sizeof (%2), %0@SSI_key[_:(%1) * ((sizeof %0@SSI_pack - 1) char)])
#define SSI_StringMap_Value(%0,%1) (%0@SSI_value[_:(%1)])

/**
 * # Internal
 */

static stock
    SSI@slot,
    SSI@entry,
    SSI@after,
    SSI@before,
    SSI@hole,
    SSI@home,
    SSI@hash,
    SSI@cells,
    SSI@cell,
    SSI@at,
    SSI@from,
    SSI@loop,
    SSI@step
;

stock SSI@KeyMap_Slot(const slot[], const keys[], slots, key) {
    __emit(
        load.s.pri key,
        smul.c -1640531535,
        move.alt,
        shr.c.pri 16,
        xor,
        shr.c.pri 1,
        load.s.alt slots,
        xchg,
        sdiv.alt,
        move.pri,
        stor.pri SSI@slot,
        load.s.alt slot,
        lidx,
        const.alt -1,
        jeq key_map_empty,
        load.s.alt keys,
        lidx,
        load.s.alt key,
        jneq key_map_next,
        load.pri SSI@slot,
        retn
    );

key_map_next:
    __emit(
        load.pri SSI@slot,
        add.c 1,
        load.s.alt slots,
        xchg,
        sdiv.alt,
        move.pri,
        stor.pri SSI@slot,
        load.s.alt slot,
        lidx,
        const.alt -1,
        jeq key_map_empty,
        load.s.alt keys,
        lidx,
        load.s.alt key,
        jneq key_map_next,
        load.pri SSI@slot,
        retn
    );

key_map_empty:
    return -2 - SSI@slot;
}

stock bool:SSI@KeyMap_Get(const slot[], const keys[], const values[], slots, key, &value) {
    __emit(
        load.s.pri key,
        smul.c -1640531535,
        move.alt,
        shr.c.pri 16,
        xor,
        shr.c.pri 1,
        load.s.alt slots,
        xchg,
        sdiv.alt,
        move.pri,
        stor.pri SSI@slot,
        load.s.alt slot,
        lidx,
        stor.pri SSI@entry,
        const.alt -1,
        jeq key_map_absent,
        load.s.alt keys,
        lidx,
        load.s.alt key,
        jneq key_map_next,
        load.pri SSI@entry,
        load.s.alt values,
        lidx,
        sref.s.pri value,
        const.pri 1,
        retn
    );

key_map_next:
    __emit(
        load.pri SSI@slot,
        add.c 1,
        load.s.alt slots,
        xchg,
        sdiv.alt,
        move.pri,
        stor.pri SSI@slot,
        load.s.alt slot,
        lidx,
        stor.pri SSI@entry,
        const.alt -1,
        jeq key_map_absent,
        load.s.alt keys,
        lidx,
        load.s.alt key,
        jneq key_map_next,
        load.pri SSI@entry,
        load.s.alt values,
        lidx,
        sref.s.pri value,
        const.pri 1,
        retn
    );

key_map_absent:
    return false;
}

stock bool:SSI@KeyMap_Set(&count, &free, next[], prev[], slot[], keys[], values[], slots, size, key, value) {
    __emit(
        load.s.pri key,
        smul.c -1640531535,
        move.alt,
        shr.c.pri 16,
        xor,
        shr.c.pri 1,
        load.s.alt slots,
        xchg,
        sdiv.alt,
        move.pri,
        stor.pri SSI@slot,
        load.s.alt slot,
        lidx,
        stor.pri SSI@entry,
        const.alt -1,
        jeq key_map_insert,
        load.s.alt keys,
        lidx,
        load.s.alt key,
        jneq key_map_next,
        load.pri SSI@entry,
        load.s.alt values,
        idxaddr,
        move.alt,
        load.s.pri value,
        stor.i,
        const.pri 1,
        retn
    );

key_map_next:
    __emit(
        load.pri SSI@slot,
        add.c 1,
        load.s.alt slots,
        xchg,
        sdiv.alt,
        move.pri,
        stor.pri SSI@slot,
        load.s.alt slot,
        lidx,
        stor.pri SSI@entry,
        const.alt -1,
        jeq key_map_insert,
        load.s.alt keys,
        lidx,
        load.s.alt key,
        jneq key_map_next,
        load.pri SSI@entry,
        load.s.alt values,
        idxaddr,
        move.alt,
        load.s.pri value,
        stor.i,
        const.pri 1,
        retn
    );

key_map_insert:
    __emit(
        lref.s.pri free,
        load.s.alt size,
        jeq key_map_full,
        stor.pri SSI@entry,
        load.s.alt next,
        lidx,
        stor.pri SSI@after,
        load.s.alt prev,
        lidx,
        stor.pri SSI@before,
        load.pri SSI@entry,
        load.s.alt prev,
        lidx,
        move.alt,
        load.s.pri size,
        shl.c.pri 1,
        add.c 1,
        sub,
        sref.s.pri free,
        load.pri SSI@before,
        load.s.alt next,
        idxaddr,
        move.alt,
        load.pri SSI@entry,
        stor.i,
        load.pri SSI@after,
        load.s.alt prev,
        idxaddr,
        move.alt,
        load.pri SSI@entry,
        stor.i,
        load.pri SSI@entry,
        load.s.alt prev,
        idxaddr,
        move.alt,
        load.pri SSI@before,
        stor.i,
        load.s.pri count,
        inc.i,
        load.pri SSI@slot,
        load.s.alt slot,
        idxaddr,
        move.alt,
        load.pri SSI@entry,
        stor.i,
        load.pri SSI@entry,
        load.s.alt keys,
        idxaddr,
        move.alt,
        load.s.pri key,
        stor.i,
        load.pri SSI@entry,
        load.s.alt values,
        idxaddr,
        move.alt,
        load.s.pri value,
        stor.i,
        const.pri 1,
        retn
    );

key_map_full:
    return false;
}

stock bool:SSI@KeyMap_Remove(&count, &free, next[], prev[], slot[], const keys[], slots, size, key) {
    __emit(
        load.s.pri key,
        smul.c -1640531535,
        move.alt,
        shr.c.pri 16,
        xor,
        shr.c.pri 1,
        load.s.alt slots,
        xchg,
        sdiv.alt,
        move.pri,
        stor.pri SSI@hole,
        load.s.alt slot,
        lidx,
        stor.pri SSI@entry,
        const.alt -1,
        jeq key_map_absent,
        load.s.alt keys,
        lidx,
        load.s.alt key,
        jeq key_map_found,
        jump key_map_next
    );

key_map_next:
    __emit(
        load.pri SSI@hole,
        add.c 1,
        load.s.alt slots,
        xchg,
        sdiv.alt,
        move.pri,
        stor.pri SSI@hole,
        load.s.alt slot,
        lidx,
        stor.pri SSI@entry,
        const.alt -1,
        jeq key_map_absent,
        load.s.alt keys,
        lidx,
        load.s.alt key,
        jneq key_map_next,
        jump key_map_found
    );

key_map_found:
    __emit(
        load.pri SSI@entry,
        load.s.alt prev,
        lidx,
        stor.pri SSI@before,
        load.pri SSI@entry,
        load.s.alt next,
        lidx,
        stor.pri SSI@after,
        load.pri SSI@before,
        load.s.alt next,
        idxaddr,
        move.alt,
        load.pri SSI@after,
        stor.i,
        load.pri SSI@after,
        load.s.alt prev,
        idxaddr,
        move.alt,
        load.pri SSI@before,
        stor.i,
        load.pri SSI@entry,
        load.s.alt prev,
        idxaddr,
        push.pri,
        lref.s.alt free,
        load.s.pri size,
        shl.c.pri 1,
        add.c 1,
        sub,
        pop.alt,
        stor.i,
        load.pri SSI@entry,
        sref.s.pri free,
        load.s.pri count,
        dec.i,
        load.pri SSI@hole,
        stor.pri SSI@slot,
        lctrl 6,
        stor.pri SSI@loop,
        load.pri SSI@slot,
        add.c 1,
        load.s.alt slots,
        xchg,
        sdiv.alt,
        move.pri,
        stor.pri SSI@slot,
        load.s.alt slot,
        lidx,
        stor.pri SSI@entry,
        const.alt -1,
        jeq key_map_done,
        load.s.alt keys,
        lidx,
        smul.c -1640531535,
        move.alt,
        shr.c.pri 16,
        xor,
        shr.c.pri 1,
        load.s.alt slots,
        xchg,
        sdiv.alt,
        move.pri,
        stor.pri SSI@home,
        load.pri SSI@hole,
        load.s.alt slot,
        idxaddr,
        move.alt,
        load.pri SSI@entry,
        stor.i,
        load.pri SSI@hole,
        load.alt SSI@home,
        sless,
        push.pri,
        load.pri SSI@home,
        load.alt SSI@slot,
        sleq,
        pop.alt,
        add,
        push.pri,
        load.pri SSI@hole,
        load.alt SSI@slot,
        sleq,
        pop.alt,
        sgeq,
        push.pri,
        load.pri SSI@slot,
        load.alt SSI@hole,
        sub,
        pop.alt,
        smul,
        load.alt SSI@hole,
        add,
        stor.pri SSI@hole,
        load.pri SSI@loop,
        sctrl 6
    );

key_map_done:
    __emit(
        load.pri SSI@hole,
        load.s.alt slot,
        idxaddr,
        move.alt,
        const.pri -1,
        stor.i,
        const.pri 1,
        retn
    );

key_map_absent:
    return false;
}

stock SSI@StringMap_Find(const slot[], const hashes[], const keys[], const values[], pack[], slots, cells, const key[], &value) {
    strpack(pack, key, cells + 1);

    __emit(
        zero.pri,
        stor.pri SSI@hash,
        stor.pri SSI@cells,
        lctrl 6,
        stor.pri SSI@loop,
        load.pri SSI@cells,
        load.s.alt pack,
        lidx,
        inc SSI@cells,
        stor.pri SSI@cell,
        load.alt SSI@hash,
        xor,
        smul.c -1640531535,
        move.alt,
        shr.c.pri 15,
        xor,
        stor.pri SSI@hash,
        load.pri SSI@cell,
        shl.c.pri 24,
        jzer string_map_hashed,
        load.pri SSI@loop,
        sctrl 6
    );

string_map_hashed:
    __emit(
        load.pri SSI@cells,
        load.s.alt cells,
        jsgrtr string_map_long,
        load.pri SSI@hash,
        shr.c.pri 1,
        load.s.alt slots,
        xchg,
        sdiv.alt,
        move.pri,
        add.c -1,
        stor.pri SSI@slot,
        lctrl 6,
        stor.pri SSI@loop,
        load.pri SSI@slot,
        add.c 1,
        load.s.alt slots,
        xchg,
        sdiv.alt,
        move.pri,
        stor.pri SSI@slot,
        load.s.alt slot,
        lidx,
        stor.pri SSI@entry,
        const.alt -1,
        jeq string_map_absent,
        load.s.alt hashes,
        lidx,
        load.alt SSI@hash,
        jeq string_map_compare,
        load.pri SSI@loop,
        sctrl 6
    );

string_map_compare:
    __emit(
        load.pri SSI@entry,
        load.s.alt cells,
        smul,
        shl.c.pri 2,
        load.s.alt keys,
        add,
        stor.pri SSI@at,
        load.s.pri pack,
        stor.pri SSI@from,
        lctrl 6,
        stor.pri SSI@step,
        load.pri SSI@at,
        load.i,
        move.alt,
        load.pri SSI@from,
        load.i,
        jneq string_map_differ,
        shl.c.pri 24,
        jzer string_map_found,
        load.pri SSI@at,
        add.c 4,
        stor.pri SSI@at,
        load.pri SSI@from,
        add.c 4,
        stor.pri SSI@from,
        load.pri SSI@step,
        sctrl 6
    );

string_map_differ:
    __emit(
        load.pri SSI@loop,
        sctrl 6
    );

string_map_found:
    __emit(
        load.pri SSI@entry,
        load.s.alt values,
        lidx,
        sref.s.pri value,
        load.pri SSI@slot,
        retn
    );

string_map_absent:
    return -2 - SSI@slot;

string_map_long:
    return -1;
}

stock bool:SSI@StringMap_Set(&count, &free, next[], prev[], slot[], hashes[], keys[], values[], pack[], slots, size, cells, length, const key[], value) {
    SSI@hole = SSI@StringMap_Find(slot, hashes, keys, values, pack, slots, cells, key, SSI@value);

    __emit(
        load.pri SSI@hole,
        const.alt -1,
        jeq string_map_refuse,
        jsgrtr string_map_update,
        load.s.pri length,
        const.alt 3,
        and,
        shl.c.pri 3,
        move.alt,
        const.pri -1,
        shr,
        load.alt SSI@cell,
        and,
        zero.alt,
        neq,
        move.alt,
        load.pri SSI@cells,
        shl.c.pri 1,
        add,
        push.pri,
        load.s.pri length,
        shr.c.pri 2,
        add.c 1,
        shl.c.pri 1,
        pop.alt,
        jsless string_map_refuse,
        lref.s.pri free,
        load.s.alt size,
        jeq string_map_refuse,
        stor.pri SSI@entry,
        load.s.alt next,
        lidx,
        stor.pri SSI@after,
        load.s.alt prev,
        lidx,
        stor.pri SSI@before,
        load.pri SSI@entry,
        load.s.alt prev,
        lidx,
        move.alt,
        load.s.pri size,
        shl.c.pri 1,
        add.c 1,
        sub,
        sref.s.pri free,
        load.pri SSI@before,
        load.s.alt next,
        idxaddr,
        move.alt,
        load.pri SSI@entry,
        stor.i,
        load.pri SSI@after,
        load.s.alt prev,
        idxaddr,
        move.alt,
        load.pri SSI@entry,
        stor.i,
        load.pri SSI@entry,
        load.s.alt prev,
        idxaddr,
        move.alt,
        load.pri SSI@before,
        stor.i,
        load.s.pri count,
        inc.i,
        load.pri SSI@slot,
        load.s.alt slot,
        idxaddr,
        move.alt,
        load.pri SSI@entry,
        stor.i,
        load.pri SSI@entry,
        load.s.alt hashes,
        idxaddr,
        move.alt,
        load.pri SSI@hash,
        stor.i,
        load.pri SSI@entry,
        load.s.alt values,
        idxaddr,
        move.alt,
        load.s.pri value,
        stor.i,
        push.s cells,
        push.s pack,
        load.pri SSI@entry,
        load.s.alt cells,
        smul,
        shl.c.pri 2,
        load.s.alt keys,
        add,
        push.pri,
        push.c 12,
        sysreq.c strpack,
        stack 16,
        const.pri 1,
        retn
    );

string_map_update:
    __emit(
        load.pri SSI@entry,
        load.s.alt values,
        idxaddr,
        move.alt,
        load.s.pri value,
        stor.i,
        const.pri 1,
        retn
    );

string_map_refuse:
    return false;
}

stock bool:SSI@StringMap_Remove(&count, &free, next[], prev[], slot[], const hashes[], const keys[], const values[], pack[], slots, size, cells, const key[]) {
    SSI@hole = SSI@StringMap_Find(slot, hashes, keys, values, pack, slots, cells, key, SSI@value);

    __emit(
        load.pri SSI@hole,
        const.alt 0,
        jsless string_map_absent,
        load.pri SSI@entry,
        load.s.alt prev,
        lidx,
        stor.pri SSI@before,
        load.pri SSI@entry,
        load.s.alt next,
        lidx,
        stor.pri SSI@after,
        load.pri SSI@before,
        load.s.alt next,
        idxaddr,
        move.alt,
        load.pri SSI@after,
        stor.i,
        load.pri SSI@after,
        load.s.alt prev,
        idxaddr,
        move.alt,
        load.pri SSI@before,
        stor.i,
        load.pri SSI@entry,
        load.s.alt prev,
        idxaddr,
        push.pri,
        lref.s.alt free,
        load.s.pri size,
        shl.c.pri 1,
        add.c 1,
        sub,
        pop.alt,
        stor.i,
        load.pri SSI@entry,
        sref.s.pri free,
        load.s.pri count,
        dec.i,
        load.pri SSI@hole,
        stor.pri SSI@slot,
        lctrl 6,
        stor.pri SSI@loop,
        load.pri SSI@slot,
        add.c 1,
        load.s.alt slots,
        xchg,
        sdiv.alt,
        move.pri,
        stor.pri SSI@slot,
        load.s.alt slot,
        lidx,
        stor.pri SSI@entry,
        const.alt -1,
        jeq string_map_done,
        load.s.alt hashes,
        lidx,
        shr.c.pri 1,
        load.s.alt slots,
        xchg,
        sdiv.alt,
        move.pri,
        stor.pri SSI@home,
        load.pri SSI@hole,
        load.s.alt slot,
        idxaddr,
        move.alt,
        load.pri SSI@entry,
        stor.i,
        load.pri SSI@hole,
        load.alt SSI@home,
        sless,
        push.pri,
        load.pri SSI@home,
        load.alt SSI@slot,
        sleq,
        pop.alt,
        add,
        push.pri,
        load.pri SSI@hole,
        load.alt SSI@slot,
        sleq,
        pop.alt,
        sgeq,
        push.pri,
        load.pri SSI@slot,
        load.alt SSI@hole,
        sub,
        pop.alt,
        smul,
        load.alt SSI@hole,
        add,
        stor.pri SSI@hole,
        load.pri SSI@loop,
        sctrl 6
    );

string_map_done:
    __emit(
        load.pri SSI@hole,
        load.s.alt slot,
        idxaddr,
        move.alt,
        const.pri -1,
        stor.i,
        const.pri 1,
        retn
    );

string_map_absent:
    return false;
}

stock SSI@StringMap_Key(key[], size, &first) {
    __emit(
        push.s size,
        push.s first,
        push.s key,
        push.c 12,
        sysreq.c strunpack,
        stack 16
    );
}

stock SSI@KeyMap_Clear(&count, &free, next[], prev[], slot[], const keys[], slots, size) {
    for (new entry = next[size]; entry != size; entry = next[entry]) {
        new
            mixed = keys[entry] * -1640531535,
            at = ((mixed ^ (mixed >>> 16)) >>> 1) % slots
        ;

        while (slot[at] != entry) {
            if (++at == slots) {
                at = 0;
            }
        }

        slot[at] = -1;
        prev[entry] = size * 2 + 1 - free;
        free = entry;
    }

    count = 0;
    next[size] = size;
    prev[size] = size;
}

stock SSI@StringMap_Clear(&count, &free, next[], prev[], slot[], const hashes[], slots, size) {
    for (new entry = next[size]; entry != size; entry = next[entry]) {
        new
            at = (hashes[entry] >>> 1) % slots
        ;

        while (slot[at] != entry) {
            if (++at == slots) {
                at = 0;
            }
        }

        slot[at] = -1;
        prev[entry] = size * 2 + 1 - free;
        free = entry;
    }

    count = 0;
    next[size] = size;
    prev[size] = size;
}
