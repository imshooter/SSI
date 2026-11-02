#if defined _INC_SSI_COLLECTION
    #endinput
#endif
#define _INC_SSI_COLLECTION

/**
 * Collections: the structures of these libraries under one name, as y_iterate
 * keeps every iterator under `Iterator:`. The brackets of the declaration pick
 * the structure, and every call and walk names the collection with the same
 * brackets.
 *
 *     static
 *         Collection:Business<MAX_BUSINESSES>,
 *         Collection:FactionVehicle[MAX_FACTIONS]<MAX_FACTION_VEHICLES>
 *     ;
 *
 *     new
 *         Collection:OwnedHouse<MAX_PLAYERS, MAX_HOUSES>
 *     ;
 *
 *     new const
 *         Business:businessid = Collection_Alloc(Business),
 *         FactionVehicle:slot = Collection_Alloc(FactionVehicle[factionid])
 *     ;
 *
 *     Collection_Add(OwnedHouse<playerid>, houseid);
 *     Collection_Remove(OwnedHouse<>, houseid);
 *
 *     foreach (new businessid : Business) {
 *     }
 *
 *     foreach (new House:houseid : OwnedHouse<playerid>) {
 *     }
 *
 * - `Name<SIZE>` is a handle pool: the ids from `0` to `SIZE - 1`.
 * - `Collection<Generation>:Name<SIZE>` declares a handle pool that also
 *   counts the generations of its ids, for `Collection_Generation`,
 *   `Collection_Alive`, `Collection_Ticket` and `Collection_Redeem`.
 * - `Name[COUNT]<SIZE>` is an indexed pool: a pool of `SIZE` ids for each
 *   index, so one id lives in several of them.
 * - `Name<GROUPS, SIZE>` is one range of `SIZE` values shared out among
 *   `GROUPS` groups, each value in one group at most.
 *
 * A collection either hands out its own ids with `Collection_Alloc`, or holds
 * the values given to it with `Collection_Add`. `Collection_Remove` serves both
 * cases. Using both in one collection breaks its stack of free ids.
 *
 * The ids of a pool carry the tag of the collection, and the calls check it.
 * The values of groups are plain numbers, and `Collection_Alloc` gives them the
 * tag of the collection. A collection of plain numbers, such as the players of
 * iterator.inc, defines its tag away after the declaration:
 *
 *     new
 *         Collection:Player<MAX_PLAYERS>
 *     ;
 *
 *     #define Player: _:
 *
 * `Name<>` names a group collection where the group does not matter. A group
 * is read between angle brackets, so it is a variable or an expression without
 * a comma.
 */

/**
 * # Header
 */

#if !defined SSI@id
    stock
        SSI@id
    ;
#endif

#if !defined SSI@index
    stock
        SSI@index
    ;
#endif

#if !defined SSI@whole
    const SSI@whole = 0;
#endif

/**
 * Makes `Collection:collection<>` in the forwards below a plain parameter, so
 * the editor shows a collection the way it is used. The declaration takes its
 * place after them.
 */
#define Collection%9:%0<%1> %0

/**
 * # Functions
 */

/**
 * @brief      Take a free id and put it in, last in its group.
 *
 * The id given back last, or else the lowest never used.
 *
 * @param      collection  `Name`, `Name[index]` or `Name<group>`.
 *
 * @return     - the id, with the tag of the collection
 *             - `-1` with that tag, when every id is in use, or the index or
 *               the group is out of range
 */
forward Collection_Alloc(Collection:collection<>);
#define Collection_Alloc(%0) SSI_COLLECTION_A:%0<>Y|||Alloc|||()

/**
 * @brief      Put a given value in.
 *
 * @param      collection  `Name`, `Name[index]` or `Name<group>`.
 * @param      value       The value.
 *
 * @return     - `true` it was put in
 *             - `false` when:
 *                 + it, the index or the group is out of range
 *                 + it is in already, in any group of a group collection
 */
forward bool:Collection_Add(Collection:collection<>, value);
#define Collection_Add(%0,%1) SSI_COLLECTION_A:%0<>Y|||Add|||(,%1)

/**
 * @brief      Take an id or a value out.
 *
 * @param      collection  `Name`, `Name[index]` or `Name<>`.
 * @param      value       The id or value.
 *
 * @return     - `true` it was taken out
 *             - `false` it was not in, or is out of range
 */
forward bool:Collection_Remove(Collection:collection<>, value);
#define Collection_Remove(%0,%1) SSI_COLLECTION_A:%0<>Y|||Remove|||(,%1)

/**
 * @brief      Take an id out of use, but do not hand it out again yet.
 *
 * It stays counted until `Collection_Recycle`, so it can be destroyed in two
 * steps: out of use first, free once everything that reads it is done.
 *
 * @param      collection  `Name` or `Name[index]`.
 * @param      id          The id.
 *
 * @return     - `true` it was taken out of use
 *             - `false` it was not in use, or the index is out of range
 */
forward bool:Collection_Retire(Collection:collection<>, id);
#define Collection_Retire(%0,%1) SSI_COLLECTION_A:%0<>Y|||Retire|||(,%1)

/**
 * @brief      Hand out again an id taken out of use with `Collection_Retire`.
 *
 * @param      collection  `Name` or `Name[index]`.
 * @param      id          The id.
 *
 * @return     - `true` it is free
 *             - `false` it was not retired, or the index is out of range
 */
forward bool:Collection_Recycle(Collection:collection<>, id);
#define Collection_Recycle(%0,%1) SSI_COLLECTION_A:%0<>Y|||Recycle|||(,%1)

/**
 * @brief      Whether an id or a value is in.
 *
 * @param      collection  `Name`, `Name[index]` or `Name<group>`.
 * @param      value       The id or value.
 *
 * @return     - `true` it is in, in that group for a group collection
 *             - `false` it is not, or it, the index or the group is out of
 *               range
 */
forward bool:Collection_Contains(Collection:collection<>, value);
#define Collection_Contains(%0,%1) SSI_COLLECTION_A:%0<>Y|||Contains|||(,%1)

/**
 * @brief      How many ids or values are in.
 *
 * @param      collection  `Name`, `Name[index]` or `Name<group>`.
 *
 * @return     - the count
 *             - `0` when the index or the group is out of range
 */
forward Collection_Count(Collection:collection<>);
#define Collection_Count(%0) SSI_COLLECTION_A:%0<>Y|||Count|||()

/**
 * @brief      Take everything out.
 *
 * @param      collection  `Name`, `Name[index]` or `Name<group>`.
 *
 * @return     - `true` it is empty
 *             - `false` the index or the group is out of range
 */
forward bool:Collection_Clear(Collection:collection<>);
#define Collection_Clear(%0) SSI_COLLECTION_A:%0<>Y|||Clear|||()

/**
 * @brief      The group a value is in.
 *
 * @param      collection  `Name<>`.
 * @param      value       The value.
 *
 * @return     - the group
 *             - `-1` it is in none, or is out of range
 */
forward Collection_Group(Collection:collection<>, value);
#define Collection_Group(%0,%1) SSI_COLLECTION_A:%0<>Y|||Group|||(,%1)

/**
 * @brief      The generation of an id in use.
 *
 * It changes each time the id is taken out, retired or cleared, so an id kept
 * with its generation can be checked with `Collection_Alive` before it is used
 * again. Only for a pool declared as `Collection<Generation>:Name<SIZE>`.
 *
 *     new const
 *         generation = Collection_Generation(Report, reportid)
 *     ;
 *
 *     if (Collection_Alive(Report, reportid, generation)) {
 *     }
 *
 * @param      collection  `Name`.
 * @param      id          The id.
 *
 * @return     - the generation, `0` or more
 *             - `-1` the id is not in use, or is out of range
 */
forward Collection_Generation(Collection:collection<>, id);
#define Collection_Generation(%0,%1) SSI_COLLECTION_A:%0<>Y|||Generation|||(,%1)

/**
 * @brief      Whether an id is in use and still in the generation given.
 *
 * Only for a pool declared as `Collection<Generation>:Name<SIZE>`.
 *
 * @param      collection  `Name`.
 * @param      id          The id.
 * @param      generation  Its generation, from `Collection_Generation`.
 *
 * @return     - `true` it is in use, in that generation
 *             - `false` it was taken out since, or is out of range
 */
forward bool:Collection_Alive(Collection:collection<>, id, generation);
#define Collection_Alive(%0,%1,%2) SSI_COLLECTION_A:%0<>Y|||Alive|||(,%1,%2)

/**
 * @brief      An id in use and its generation in one number.
 *
 * It is meant for places where only one number fits, such as an argument of a
 * timer. `Collection_Redeem` gives the id back while the id is still in the
 * same generation. The ticket holds the generation modulo `cellmax / SIZE`, so
 * it could pass for its id again only after that many more generations: 262143
 * for 8192 ids. Only for a pool declared as
 * `Collection<Generation>:Name<SIZE>`.
 *
 *     SetTimerEx("@Report_Expire", 300000, false, "i", Collection_Ticket(Report, reportid));
 *
 *     public @Report_Expire(ticket) {
 *         new const
 *             Report:reportid = Collection_Redeem(Report, ticket)
 *         ;
 *     }
 *
 * @param      collection  `Name`.
 * @param      id          The id.
 *
 * @return     - the ticket, `0` or more
 *             - `-1` the id is not in use, or is out of range
 */
forward Collection_Ticket(Collection:collection<>, id);
#define Collection_Ticket(%0,%1) SSI_COLLECTION_A:%0<>Y|||Ticket|||(,%1)

/**
 * @brief      The id of a ticket from `Collection_Ticket`.
 *
 * Only for a pool declared as `Collection<Generation>:Name<SIZE>`.
 *
 * @param      collection  `Name`.
 * @param      ticket      The ticket.
 *
 * @return     - the id, with the tag of the collection
 *             - `-1` with that tag, when the id was taken out since the ticket
 *               was made, or the ticket is not one
 */
forward Collection_Redeem(Collection:collection<>, ticket);
#define Collection_Redeem(%0,%1) SSI_COLLECTION_A:%0<>Y|||Redeem|||(,%1)

#define SSI_COLLECTION_A:%0<%1>%2|||%3|||(%4) SSI_COLLECTION_B%2|||%0|||(%1)|||%3|||(%4)
#define SSI_COLLECTION_B<>Y|||%0|||(%1)|||%3|||(%4) SSI_GroupPool_%3(%0,%1%4)
#define SSI_COLLECTION_BY|||%0|||(%1)|||%3|||(%4) SSI_COLLECTION_C:%0[]C|||%3|||(%4)
#define SSI_COLLECTION_C:%0[%1]%2|||%3|||(%4) SSI_COLLECTION_D%2|||%0|||(%1)|||%3|||(%4)
#define SSI_COLLECTION_D[]C|||%0|||(%1)|||%3|||(%4) SSI_IndexedPool_%3(%0,%1%4)
#define SSI_COLLECTION_DC|||%0|||(%1)|||%3|||(%4) SSI_HandlePool_%3(%0%4)

/**
 * @brief      Walk what a collection holds: all of it, one index of it, or one
 *             group of it.
 *
 * The variable takes the tag of the collection, or the tag written on it. The
 * values of a group have no tag unless one is written. Inside the loop, ids can
 * be taken and given back. The current id can be given back too, as long as it
 * is the last id given back in that pass. An id taken inside the loop may be
 * visited.
 *
 *     foreach (new businessid : Business) {
 *         Collection_Remove(Business, businessid);
 *     }
 *
 *     foreach (new slot : FactionVehicle[factionid]) {
 *     }
 *
 *     foreach (new House:houseid : OwnedHouse<playerid>) {
 *     }
 *
 * It also walks an iterator function, `Name(arguments)`, which works out each
 * value from the one before: `None`, `All`, `Empty`, `NonEmpty`, `Full` and
 * `NonFull` below, and those of iterator.inc. Its values have no tag unless one
 * is written, and its arguments are read again at every step.
 *
 *     foreach (new businessid : None(Business)) {
 *     }
 *
 * foreach.inc and y_iterate define a `foreach` of their own, and pawncc keeps
 * one macro of a name: when one of them is included before this file, theirs
 * keeps the name and this loop is `each`.
 */
#if defined foreach
    #define each%0(new%1:%2) for (new SSI_FOREACH_T:%2::|||%1|||)
#else
    #define foreach%0(new%1:%2) for (new SSI_FOREACH_T:%2::|||%1|||)
#endif

#define SSI_FOREACH_T:%0:%1:%2|||%3||| SSI_FOREACH_U%2X|||%3|||(%0)|||(%1)|||
#define SSI_FOREACH_UX|||%0|||(%1)|||(%2)||| SSI_FOREACH_A:%1<>Y|||%0|||I|||
#define SSI_FOREACH_U:X|||%0|||(%1)|||(%2)||| SSI_FOREACH_A:%2<>Y|||%1|||:%0|||
#define SSI_FOREACH_A:%0<%3>%4|||%1|||%5||| SSI_FOREACH_B%4|||%0|||(%3)|||%1|||%5|||
#define SSI_FOREACH_B<>Y|||%0|||(%3)|||%1|||%5||| SSI_FOREACH_G%5|||%0|||(%3)|||%1|||
#define SSI_FOREACH_BY|||%0|||(%3)|||%1|||%5||| SSI_FOREACH_C:%0[]C|||%1|||%5|||
#define SSI_FOREACH_C:%0[%3]%4|||%1|||%5||| SSI_FOREACH_D%4|||%0|||(%3)|||%1|||%5|||
#define SSI_FOREACH_D[]C|||%0|||(%3)|||%1|||%5||| SSI_FOREACH_I%5|||%0|||(%3)|||%1|||
#define SSI_FOREACH_DC|||%0|||(%3)|||%1|||%5||| SSI_FOREACH_E:%0()F|||%1|||%5|||
#define SSI_FOREACH_E:%0(%3)%4|||%1|||%5||| SSI_FOREACH_F%4|||%0|||(%3)|||%1|||%5|||
#define SSI_FOREACH_F()F|||%0|||%3|||%1|||%5||| SSI_FOREACH_J%5|||%0|||%3|||%1|||
#define SSI_FOREACH_FF|||%0|||%3|||%1|||%5||| SSI_FOREACH_P%5|||%0|||%1|||
#define SSI_FOREACH_JI|||%0|||%3|||%1||| %0@SSI_loop|||_:|||%1|||%3|||
#define SSI_FOREACH_J:%2|||%0|||%3|||%1||| %0@SSI_loop|||%2:|||%1|||%3|||
#define SSI_FOREACH_PI|||%0|||%1||| %0:%1=%0:(sizeof %0@SSI_next-1);_:(%1=%0:%0@SSI_next[_:%1])!=sizeof %0@SSI_next-1;
#define SSI_FOREACH_P:%2|||%0|||%1||| %2:%1=%2:(sizeof %0@SSI_next-1);_:(%1=%2:%0@SSI_next[_:%1])!=sizeof %0@SSI_next-1;
#define SSI_FOREACH_II|||%0|||(%3)|||%1||| %0:%1=%0:(sizeof %0@SSI_next[]-1);_:(%1=%0:%0@SSI_next[(%3)][_:%1])!=sizeof %0@SSI_next[]-1;
#define SSI_FOREACH_I:%2|||%0|||(%3)|||%1||| %2:%1=%2:(sizeof %0@SSI_next[]-1);_:(%1=%2:%0@SSI_next[(%3)][_:%1])!=sizeof %0@SSI_next[]-1;
#define SSI_FOREACH_GI|||%0|||(%3)|||%1||| %1=sizeof %0@SSI_group+_:(%3);(%1=%0@SSI_next[%1])!=sizeof %0@SSI_group+_:(%3);
#define SSI_FOREACH_G:%2|||%0|||(%3)|||%1||| %2:%1=%2:(sizeof %0@SSI_group+_:(%3));_:(%1=%2:%0@SSI_next[_:%1])!=sizeof %0@SSI_group+_:(%3);

/**
 * # Declaration
 */

#undef Collection

/**
 * Declares the collection `%0`, with the structure picked by the brackets,
 * static when the declaration is. `Collection<Generation>:` declares a handle
 * pool that counts generations. On an indexed pool or a group collection it is
 * an error.
 *
 *     static
 *         Collection:Business<MAX_BUSINESSES>,
 *         Collection<Generation>:Report<MAX_REPORTS>,
 *         Collection:FactionVehicle[MAX_FACTIONS]<MAX_FACTION_VEHICLES>
 *     ;
 *
 *     new
 *         Collection:OwnedHouse<MAX_PLAYERS, MAX_HOUSES>
 *     ;
 */
#define Collection%9:%0<%1> SSI_COLLECTION_KIND:%9<>|||%0|||%1|||

#define SSI_COLLECTION_KIND:<%9>%8|||%0|||%1||| SSI_COLLECTION_KIND_%9|||%0|||%1|||
#define SSI_COLLECTION_KIND_|||%0|||%1||| SSI_COLLECTION_DECLARE_A:%0[]C|||%1,,|||0|||
#define SSI_COLLECTION_KIND_Generation|||%0|||%1||| SSI_COLLECTION_DECLARE_A:%0[]C|||%1,,|||1|||

#define SSI_COLLECTION_DECLARE_A:%0[%2]%3|||%1|||%6||| SSI_COLLECTION_DECLARE_B%3|||%0|||%2|||%1|||%6|||
#define SSI_COLLECTION_DECLARE_B[]C|||%0|||%2|||%1,,|||%6||| SSI_COLLECTION_HANDLE_ONLY_%6 SSI_IndexedPool_Declare(%0,%2,%1)
#define SSI_COLLECTION_DECLARE_BC|||%0|||%2|||%1,%4,%5|||%6||| SSI_COLLECTION_DECLARE_C%5X|||%0|||%1|||%4|||%6|||
#define SSI_COLLECTION_DECLARE_CX|||%0|||%1|||%4|||%6||| SSI_HandlePool_Declare(%0,%1,%6)
#define SSI_COLLECTION_DECLARE_C,X|||%0|||%1|||%4|||%6||| SSI_COLLECTION_HANDLE_ONLY_%6 SSI_GroupPool_Declare(%0,%1,%4)
#define SSI_COLLECTION_HANDLE_ONLY_0
#define SSI_COLLECTION_HANDLE_ONLY_1 SSI@generation[Generation_works_on_handle_pools_only],

/**
 * # Handle Pool
 */

/**
 * `Name<SIZE>` is a handle pool. It hands out the ids of one tag, takes them
 * back, checks them and walks them. Each of these takes the same time with ten
 * ids in use or with a hundred thousand, and a walk costs one step for each id
 * in use. The ids in use form a doubly linked list: `next` holds the id after
 * each one, and its last cell is the anchor, where a walk starts and ends.
 * `prev` holds the id before each id in use, never more than `size`. For an id
 * not in use, it holds the next free id written as `size * 2 + 1 - id`, always
 * more than `size`, so the free ids form a stack. A retired id holds
 * `size * 2 + 2`. The next id handed out is the one given back last, or else
 * the lowest never used, and it goes back in front of the id that was after it.
 * The same layout holds the ids given to it with `Collection_Add`, such as the
 * players and vehicles of iterator.inc.
 *
 * `Collection<Generation>:Name<SIZE>` has `size` more cells at the end of
 * `prev`, holding the generation of each id. A generation is counted up when
 * its id is taken out, retired or cleared. The calls on generations pass that
 * end of `prev` as an array, so on a pool without it they fail at compile time
 * on the bounds of `prev`.
 */
#define SSI_HandlePool_Declare(%0,%1,%2) \
    %0@SSI_next[_:(%1) + 1] = { _:(%1), ... }, \
    %0@SSI_prev[_:(%1) * (%2 + 1) + 1] = { _:(%1) * 2, _:(%1) * 2 - 1, ... }, \
    %0@SSI_count, \
    %0@SSI_free

#define SSI_HandlePool_Alloc(%0) (%0:SSI@HandlePool_Alloc(%0@SSI_count, %0@SSI_free, %0@SSI_next, %0@SSI_prev, sizeof %0@SSI_next - 1))
#define SSI_HandlePool_Add(%0,%1) SSI@HandlePool_Add(%0@SSI_count, %0@SSI_next, %0@SSI_prev, sizeof %0@SSI_next - 1, _:(%0:SSI@id = (%1)))
#define SSI_HandlePool_Remove(%0,%1) SSI@HandlePool_Remove(%0@SSI_count, %0@SSI_free, %0@SSI_next, %0@SSI_prev, sizeof %0@SSI_next - 1, _:(%0:SSI@id = (%1)), sizeof %0@SSI_prev != sizeof %0@SSI_next)
#define SSI_HandlePool_Retire(%0,%1) SSI@HandlePool_Retire(%0@SSI_next, %0@SSI_prev, sizeof %0@SSI_next - 1, _:(%0:SSI@id = (%1)), sizeof %0@SSI_prev != sizeof %0@SSI_next)
#define SSI_HandlePool_Recycle(%0,%1) SSI@HandlePool_Recycle(%0@SSI_count, %0@SSI_free, %0@SSI_prev, sizeof %0@SSI_next - 1, _:(%0:SSI@id = (%1)))
#define SSI_HandlePool_Contains(%0,%1) SSI@HandlePool_Contains(%0@SSI_prev, sizeof %0@SSI_next - 1, _:(%0:SSI@id = (%1)))
#define SSI_HandlePool_Count(%0) (%0@SSI_count)
#define SSI_HandlePool_Clear(%0) SSI@HandlePool_Clear(%0@SSI_count, %0@SSI_free, %0@SSI_next, %0@SSI_prev, sizeof %0@SSI_next - 1, sizeof %0@SSI_prev != sizeof %0@SSI_next)
#define SSI_HandlePool_Generation(%0,%1) SSI@HandlePool_Generation(%0@SSI_prev, %0@SSI_prev[sizeof %0@SSI_next], sizeof %0@SSI_next - 1, _:(%0:SSI@id = (%1)))
#define SSI_HandlePool_Alive(%0,%1,%2) SSI@HandlePool_Alive(%0@SSI_prev, %0@SSI_prev[sizeof %0@SSI_next], sizeof %0@SSI_next - 1, _:(%0:SSI@id = (%1)), %2)
#define SSI_HandlePool_Ticket(%0,%1) SSI@HandlePool_Ticket(%0@SSI_prev, %0@SSI_prev[sizeof %0@SSI_next], sizeof %0@SSI_next - 1, _:(%0:SSI@id = (%1)))
#define SSI_HandlePool_Redeem(%0,%1) (%0:SSI@HandlePool_Redeem(%0@SSI_prev, %0@SSI_prev[sizeof %0@SSI_next], sizeof %0@SSI_next - 1, %1))

/**
 * # Indexed Pool
 */

/**
 * `Name[COUNT]<SIZE>` is an indexed pool: a handle pool for each index, kept
 * in rows of the same arrays, so the functions of a handle pool run on a row.
 * When the number of indexes is tagged, the index must carry that tag. Every
 * call checks the index and answers as an empty pool when the index is out of
 * range. `foreach` does not check it, so walk only a valid index.
 */
#define SSI_IndexedPool_Declare(%0,%1,%2) \
    %0@SSI_next[%1][_:(%2) + 1] = { { _:(%2), ... }, ... }, \
    %0@SSI_prev[%1][_:(%2) + 1] = { { _:(%2) * 2, _:(%2) * 2 - 1, ... }, ... }, \
    %0@SSI_count[%1], \
    %0@SSI_free[%1]

#define SSI_IndexedPool_Alloc(%0,%1) (%0:((0 <= (SSI@index = _:(%1)) < sizeof %0@SSI_count) ? SSI@HandlePool_Alloc(%0@SSI_count[(%1)], %0@SSI_free[(%1)], %0@SSI_next[(%1)], %0@SSI_prev[(%1)], sizeof %0@SSI_next[] - 1) : -1))
#define SSI_IndexedPool_Add(%0,%1,%2) ((0 <= (SSI@index = _:(%1)) < sizeof %0@SSI_count) && SSI@HandlePool_Add(%0@SSI_count[(%1)], %0@SSI_next[(%1)], %0@SSI_prev[(%1)], sizeof %0@SSI_next[] - 1, _:(%0:SSI@id = (%2))))
#define SSI_IndexedPool_Remove(%0,%1,%2) ((0 <= (SSI@index = _:(%1)) < sizeof %0@SSI_count) && SSI@HandlePool_Remove(%0@SSI_count[(%1)], %0@SSI_free[(%1)], %0@SSI_next[(%1)], %0@SSI_prev[(%1)], sizeof %0@SSI_next[] - 1, _:(%0:SSI@id = (%2)), false))
#define SSI_IndexedPool_Retire(%0,%1,%2) ((0 <= (SSI@index = _:(%1)) < sizeof %0@SSI_count) && SSI@HandlePool_Retire(%0@SSI_next[(%1)], %0@SSI_prev[(%1)], sizeof %0@SSI_next[] - 1, _:(%0:SSI@id = (%2)), false))
#define SSI_IndexedPool_Recycle(%0,%1,%2) ((0 <= (SSI@index = _:(%1)) < sizeof %0@SSI_count) && SSI@HandlePool_Recycle(%0@SSI_count[(%1)], %0@SSI_free[(%1)], %0@SSI_prev[(%1)], sizeof %0@SSI_prev[] - 1, _:(%0:SSI@id = (%2))))
#define SSI_IndexedPool_Contains(%0,%1,%2) ((0 <= (SSI@index = _:(%1)) < sizeof %0@SSI_count) && SSI@HandlePool_Contains(%0@SSI_prev[(%1)], sizeof %0@SSI_prev[] - 1, _:(%0:SSI@id = (%2))))
#define SSI_IndexedPool_Count(%0,%1) ((0 <= (SSI@index = _:(%1)) < sizeof %0@SSI_count) ? %0@SSI_count[(%1)] : 0)
#define SSI_IndexedPool_Clear(%0,%1) ((0 <= (SSI@index = _:(%1)) < sizeof %0@SSI_count) && SSI@HandlePool_Clear(%0@SSI_count[(%1)], %0@SSI_free[(%1)], %0@SSI_next[(%1)], %0@SSI_prev[(%1)], sizeof %0@SSI_next[] - 1, false))

/**
 * # Group
 */

/**
 * `Name<GROUPS, SIZE>` shares one range of values out among groups, each value
 * in one group at most, as y_iterate's `Iterator:Name<GROUPS, SIZE>`. Each
 * group is a ring through its anchor, the cell `size + group`: `next` holds the
 * value after each one and `prev` the one before, so a value comes out in
 * place, keeping its `next`. `group` holds the group of each value, `-1` while
 * it is in none, and `count` the size of each group. A value goes last in its
 * group. The ids it hands out itself come from a stack held in the `prev` of
 * the ids given back, with `free` holding the top of that stack and the lowest
 * id never used.
 */
#define SSI_GroupPool_Declare(%0,%1,%2) \
    %0@SSI_next[_:(%2) + _:(%1)] = { 0, 1, ... }, \
    %0@SSI_prev[_:(%2) + _:(%1)] = { 0, 1, ... }, \
    %0@SSI_group[_:(%2)] = { -1, ... }, \
    %0@SSI_count[_:(%1)], \
    %0@SSI_free[2] = { -1, 0 }

#define SSI_GroupPool_Alloc(%0,%1) (%0:SSI@GroupPool_Alloc(%0@SSI_next, %0@SSI_prev, %0@SSI_group, %0@SSI_count, %0@SSI_free[0], %0@SSI_free[1], sizeof %0@SSI_group, sizeof %0@SSI_count, _:(%1)))
#define SSI_GroupPool_Add(%0,%1,%2) SSI@GroupPool_Add(%0@SSI_next, %0@SSI_prev, %0@SSI_group, %0@SSI_count, sizeof %0@SSI_group, sizeof %0@SSI_count, _:(%1), _:(%2))
#define SSI_GroupPool_Remove(%0,%1,%2) SSI@GroupPool_Remove(%0@SSI_next, %0@SSI_prev, %0@SSI_group, %0@SSI_count, %0@SSI_free[0], sizeof %0@SSI_group, _:(%2))
#define SSI_GroupPool_Clear(%0,%1) SSI@GroupPool_Clear(%0@SSI_next, %0@SSI_prev, %0@SSI_group, %0@SSI_count, %0@SSI_free[0], sizeof %0@SSI_group, sizeof %0@SSI_count, _:(%1))
#define SSI_GroupPool_Group(%0,%1,%2) SSI@GroupPool_Group(%0@SSI_group, sizeof %0@SSI_group, _:(%2))
#define SSI_GroupPool_Contains(%0,%1,%2) SSI@GroupPool_Contains(%0@SSI_group, sizeof %0@SSI_group, sizeof %0@SSI_count, _:(%1), _:(%2))
#define SSI_GroupPool_Count(%0,%1) ((0 <= (SSI@index = _:(%1)) < sizeof %0@SSI_count) ? %0@SSI_count[SSI@index] : 0)

/**
 * # Iterator Functions
 */

/**
 * Makes `SSI@state` and the name of a loop variable one symbol: the state an
 * iterator function keeps for that loop.
 */
#define SSI@state%0\32; SSI@state

/**
 * @brief      Walk the values a collection does not hold, lowest first.
 *
 * The free ids of a pool or of one index, the values of a group collection in
 * no group with `Name<>`, or the values not in one group with `Name<group>`.
 *
 *     foreach (new Business:businessid : None(Business)) {
 *     }
 *
 * @param      collection  `Name`, `Name[index]`, `Name<>` or `Name<group>`.
 */
#define None@SSI_loop|||%9|||%1|||(%3)||| SSI_COLLECTION_WALK|||None|||%9|||%1|||%3|||

/**
 * @brief      Walk the values a collection holds, lowest first.
 *
 * The values a walk of the collection gives, in order of value instead of the
 * order they went in. `Name<>` gives the values in any group.
 *
 *     foreach (new value : All(OwnedHouse<>)) {
 *     }
 *
 * @param      collection  `Name`, `Name[index]`, `Name<>` or `Name<group>`.
 */
#define All@SSI_loop|||%9|||%1|||(%3)||| SSI_COLLECTION_WALK|||All|||%9|||%1|||%3|||

/**
 * @brief      Walk the indexes of an indexed pool, or the groups of a group
 *             collection, that hold nothing.
 *
 *     foreach (new factionid : Empty(FactionVehicle[])) {
 *     }
 *
 *     foreach (new playerid : Empty(OwnedHouse<>)) {
 *     }
 *
 * @param      collection  `Name[]` or `Name<>`.
 */
#define Empty@SSI_loop|||%9|||%1|||(%3)||| SSI_COLLECTION_WALK|||Empty|||%9|||%1|||%3|||

/**
 * @brief      Walk the indexes, or the groups, that hold something.
 *
 * @param      collection  `Name[]` or `Name<>`.
 */
#define NonEmpty@SSI_loop|||%9|||%1|||(%3)||| SSI_COLLECTION_WALK|||NonEmpty|||%9|||%1|||%3|||

/**
 * @brief      Walk the indexes, or the groups, that hold as many values as there
 *             is room for.
 *
 * @param      collection  `Name[]` or `Name<>`.
 */
#define Full@SSI_loop|||%9|||%1|||(%3)||| SSI_COLLECTION_WALK|||Full|||%9|||%1|||%3|||

/**
 * @brief      Walk the indexes, or the groups, that have room for one more
 *             value.
 *
 * @param      collection  `Name[]` or `Name<>`.
 */
#define NonFull@SSI_loop|||%9|||%1|||(%3)||| SSI_COLLECTION_WALK|||NonFull|||%9|||%1|||%3|||

#define SSI_COLLECTION_WALK|||%0|||%9|||%1|||%3||| %9%1=%9(-1);_:(%1=%9(SSI_COLLECTION_A:%3<>Y|||%0|||(,(_:%1))))!=-1;

#define SSI_HandlePool_None(%0,%1) SSI@HandlePool_Next(%0@SSI_prev, sizeof %0@SSI_next - 1, %1, false)
#define SSI_HandlePool_All(%0,%1) SSI@HandlePool_Next(%0@SSI_prev, sizeof %0@SSI_next - 1, %1, true)
#define SSI_IndexedPool_None(%0,%1,%2) ((0 <= (SSI@index = _:(%1)) < sizeof %0@SSI_count) ? SSI@HandlePool_Next(%0@SSI_prev[(%1)], sizeof %0@SSI_prev[] - 1, %2, false) : -1)
#define SSI_IndexedPool_All(%0,%1,%2) ((0 <= (SSI@index = _:(%1)) < sizeof %0@SSI_count) ? SSI@HandlePool_Next(%0@SSI_prev[(%1)], sizeof %0@SSI_prev[] - 1, %2, true) : -1)
#define SSI_IndexedPool_Empty(%0,%1,%2) SSI@Count_Next(%0@SSI_count, sizeof %0@SSI_count, %2 + SSI@whole%1, 0, 0)
#define SSI_IndexedPool_NonEmpty(%0,%1,%2) SSI@Count_Next(%0@SSI_count, sizeof %0@SSI_count, %2 + SSI@whole%1, 1, cellmax)
#define SSI_IndexedPool_Full(%0,%1,%2) SSI@Count_Next(%0@SSI_count, sizeof %0@SSI_count, %2 + SSI@whole%1, sizeof %0@SSI_next[] - 1, cellmax)
#define SSI_IndexedPool_NonFull(%0,%1,%2) SSI@Count_Next(%0@SSI_count, sizeof %0@SSI_count, %2 + SSI@whole%1, 0, sizeof %0@SSI_next[] - 2)
#define SSI_GroupPool_None(%0,%1,%2) SSI@GroupPool_Next(%0@SSI_group, sizeof %0@SSI_group, %2, SSI@GroupPool_Pick(%1), false)
#define SSI_GroupPool_All(%0,%1,%2) SSI@GroupPool_Next(%0@SSI_group, sizeof %0@SSI_group, %2, SSI@GroupPool_Pick(%1), true)
#define SSI_GroupPool_Empty(%0,%1,%2) SSI@Count_Next(%0@SSI_count, sizeof %0@SSI_count, %2 + SSI@whole%1, 0, 0)
#define SSI_GroupPool_NonEmpty(%0,%1,%2) SSI@Count_Next(%0@SSI_count, sizeof %0@SSI_count, %2 + SSI@whole%1, 1, cellmax)
#define SSI_GroupPool_Full(%0,%1,%2) SSI@Count_Next(%0@SSI_count, sizeof %0@SSI_count, %2 + SSI@whole%1, sizeof %0@SSI_group, cellmax)
#define SSI_GroupPool_NonFull(%0,%1,%2) SSI@Count_Next(%0@SSI_count, sizeof %0@SSI_count, %2 + SSI@whole%1, 0, sizeof %0@SSI_group - 1)

/**
 * # Internal
 */

static stock
    SSI@anchor,
    SSI@before,
    SSI@after,
    SSI@member,
    SSI@cell,
    SSI@loop
;

stock SSI@HandlePool_Alloc(&count, &free, next[], prev[], size) {
    __emit(
        lref.s.pri free,
        load.s.alt size,
        jeq handle_pool_full,
        push.pri,
        load.s.alt next,
        lidx,
        push.pri,
        load.s.alt prev,
        lidx,
        load.s.alt size,
        jsgrtr handle_pool_last,
        push.pri,
        load.s.alt next,
        idxaddr,
        move.alt,
        load.s.pri -4,
        stor.i,
        load.s.pri -8,
        load.s.alt prev,
        idxaddr,
        move.alt,
        load.s.pri -4,
        stor.i,
        load.s.pri -4,
        load.s.alt prev,
        idxaddr,
        push.pri,
        load.i,
        move.alt,
        load.s.pri size,
        shl.c.pri 1,
        add.c 1,
        sub,
        sref.s.pri free,
        pop.alt,
        load.s.pri -12,
        stor.i,
        load.s.pri count,
        inc.i,
        load.s.pri -4,
        stack 12,
        retn
    );

handle_pool_last:
    new const
        id = free,
        before = prev[size]
    ;

    free = size * 2 + 1 - prev[id];
    next[before] = id;
    next[id] = size;
    prev[id] = before;
    prev[size] = id;
    count += 1;

    return id;

handle_pool_full:
    return -1;
}

stock bool:SSI@HandlePool_Remove(&count, &free, next[], prev[], size, id, bool:generations) {
    __emit(
        load.s.pri id,
        zero.alt,
        jsless handle_pool_refused,
        load.s.alt size,
        jsgeq handle_pool_refused,
        load.s.alt prev,
        lidx,
        load.s.alt size,
        jsgrtr handle_pool_refused,
        push.pri,
        load.s.pri id,
        load.s.alt next,
        lidx,
        push.pri,
        load.s.pri -4,
        load.s.alt next,
        idxaddr,
        move.alt,
        load.s.pri -8,
        stor.i,
        load.s.pri -8,
        load.s.alt prev,
        idxaddr,
        move.alt,
        load.s.pri -4,
        stor.i,
        load.s.pri id,
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
        load.s.pri id,
        sref.s.pri free,
        load.s.pri count,
        dec.i,
        load.s.pri generations,
        jnz handle_pool_generation,
        const.pri 1,
        stack 8,
        retn
    );

handle_pool_generation:
    __emit(
        load.s.pri id,
        load.s.alt size,
        add,
        add.c 1,
        load.s.alt prev,
        idxaddr,
        inc.i,
        const.pri 1,
        retn
    );

handle_pool_refused:
    return false;
}

stock bool:SSI@HandlePool_Retire(next[], prev[], size, id, bool:generations) {
    __emit(
        load.s.pri id,
        zero.alt,
        jsless handle_pool_refused,
        load.s.alt size,
        jsgeq handle_pool_refused,
        load.s.alt prev,
        lidx,
        load.s.alt size,
        jsgrtr handle_pool_refused,
        push.pri,
        load.s.pri id,
        load.s.alt next,
        lidx,
        push.pri,
        load.s.pri -4,
        load.s.alt next,
        idxaddr,
        move.alt,
        load.s.pri -8,
        stor.i,
        load.s.pri -8,
        load.s.alt prev,
        idxaddr,
        move.alt,
        load.s.pri -4,
        stor.i,
        load.s.pri id,
        load.s.alt prev,
        idxaddr,
        move.alt,
        load.s.pri size,
        shl.c.pri 1,
        add.c 2,
        stor.i,
        load.s.pri generations,
        jnz handle_pool_generation,
        const.pri 1,
        stack 8,
        retn
    );

handle_pool_generation:
    __emit(
        load.s.pri id,
        load.s.alt size,
        add,
        add.c 1,
        load.s.alt prev,
        idxaddr,
        inc.i,
        const.pri 1,
        retn
    );

handle_pool_refused:
    return false;
}

stock bool:SSI@HandlePool_Recycle(&count, &free, prev[], size, id) {
    __emit(
        load.s.pri id,
        zero.alt,
        jsless handle_pool_refused,
        load.s.alt size,
        jsgeq handle_pool_refused,
        load.s.alt prev,
        idxaddr,
        push.pri,
        load.i,
        move.alt,
        load.s.pri size,
        shl.c.pri 1,
        add.c 2,
        jneq handle_pool_refused,
        lref.s.alt free,
        load.s.pri size,
        shl.c.pri 1,
        add.c 1,
        sub,
        pop.alt,
        stor.i,
        load.s.pri id,
        sref.s.pri free,
        load.s.pri count,
        dec.i,
        const.pri 1,
        retn
    );

handle_pool_refused:
    return false;
}

stock bool:SSI@HandlePool_Contains(const prev[], size, id) {
    __emit(
        load.s.pri id,
        zero.alt,
        jsless handle_pool_absent,
        load.s.alt size,
        jsgeq handle_pool_absent,
        load.s.alt prev,
        lidx,
        load.s.alt size,
        sleq,
        retn
    );

handle_pool_absent:
    return false;
}

stock SSI@HandlePool_Generation(const prev[], const generations[], size, id) {
    __emit(
        load.s.pri id,
        zero.alt,
        jsless handle_pool_absent,
        load.s.alt size,
        jsgeq handle_pool_absent,
        load.s.alt prev,
        lidx,
        load.s.alt size,
        jsgrtr handle_pool_absent,
        load.s.pri id,
        load.s.alt generations,
        lidx,
        const.alt cellmax,
        and,
        retn
    );

handle_pool_absent:
    return -1;
}

stock bool:SSI@HandlePool_Alive(const prev[], const generations[], size, id, generation) {
    __emit(
        load.s.pri id,
        zero.alt,
        jsless handle_pool_absent,
        load.s.alt size,
        jsgeq handle_pool_absent,
        load.s.alt prev,
        lidx,
        load.s.alt size,
        jsgrtr handle_pool_absent,
        load.s.pri id,
        load.s.alt generations,
        lidx,
        const.alt cellmax,
        and,
        load.s.alt generation,
        eq,
        retn
    );

handle_pool_absent:
    return false;
}

stock SSI@HandlePool_Ticket(const prev[], const generations[], size, id) {
    __emit(
        load.s.pri id,
        zero.alt,
        jsless handle_pool_absent,
        load.s.alt size,
        jsgeq handle_pool_absent,
        load.s.alt prev,
        lidx,
        load.s.alt size,
        jsgrtr handle_pool_absent,
        const.pri cellmax,
        load.s.alt size,
        xchg,
        sdiv.alt,
        push.pri,
        load.s.pri id,
        load.s.alt generations,
        lidx,
        const.alt cellmax,
        and,
        pop.alt,
        xchg,
        sdiv.alt,
        load.s.pri size,
        smul,
        load.s.alt id,
        add,
        retn
    );

handle_pool_absent:
    return -1;
}

stock SSI@HandlePool_Redeem(const prev[], const generations[], size, ticket) {
    __emit(
        load.s.pri ticket,
        zero.alt,
        jsless handle_pool_absent,
        load.s.alt size,
        xchg,
        sdiv.alt,
        push.alt,
        push.pri,
        move.pri,
        load.s.alt prev,
        lidx,
        load.s.alt size,
        jsgrtr handle_pool_absent,
        const.pri cellmax,
        load.s.alt size,
        xchg,
        sdiv.alt,
        push.pri,
        load.s.pri -4,
        load.s.alt generations,
        lidx,
        const.alt cellmax,
        and,
        pop.alt,
        xchg,
        sdiv.alt,
        load.s.pri -8,
        jneq handle_pool_absent,
        load.s.pri -4,
        stack 8,
        retn
    );

handle_pool_absent:
    return -1;
}

stock bool:SSI@HandlePool_Clear(&count, &free, next[], prev[], size, bool:generations) {
    if (generations) {
        for (new id = next[size]; id != size; id = next[id]) {
            prev[size + 1 + id] += 1;
        }
    }

    for (new id = next[size]; id != size; id = next[id]) {
        prev[id] = size * 2 + 1 - free;
        free = id;
        count -= 1;
    }

    next[size] = size;
    prev[size] = size;

    return true;
}

stock bool:SSI@HandlePool_Add(&count, next[], prev[], size, id) {
    if (id < 0) {
        return false;
    }

    if (id >= size) {
        return false;
    }

    if (prev[id] <= size) {
        return false;
    }

    new const
        after = (prev[next[id]] <= size) ? next[id] : size,
        before = prev[after]
    ;

    next[before] = id;
    next[id] = after;
    prev[id] = before;
    prev[after] = id;
    count += 1;

    return true;
}

stock bool:SSI@GroupPool_Add(next[], prev[], group[], count[], size, groups, groupid, value) {
    __emit(
        load.s.pri value,
        load.s.alt size,
        jgeq group_set_refuse,
        load.s.pri groupid,
        load.s.alt groups,
        jgeq group_set_refuse,
        load.s.pri value,
        load.s.alt group,
        lidx,
        const.alt -1,
        jneq group_set_refuse,
        load.s.pri size,
        load.s.alt groupid,
        add,
        stor.pri SSI@anchor,
        load.s.alt prev,
        lidx,
        stor.pri SSI@before,
        load.s.alt next,
        idxaddr,
        move.alt,
        load.s.pri value,
        stor.i,
        load.s.pri value,
        load.s.alt prev,
        idxaddr,
        move.alt,
        load.pri SSI@before,
        stor.i,
        load.s.pri value,
        load.s.alt next,
        idxaddr,
        move.alt,
        load.pri SSI@anchor,
        stor.i,
        load.pri SSI@anchor,
        load.s.alt prev,
        idxaddr,
        move.alt,
        load.s.pri value,
        stor.i,
        load.s.pri value,
        load.s.alt group,
        idxaddr,
        move.alt,
        load.s.pri groupid,
        stor.i,
        load.s.pri groupid,
        load.s.alt count,
        idxaddr,
        inc.i,
        const.pri 1,
        retn
    );

group_set_refuse:
    return false;
}

stock SSI@GroupPool_Group(const group[], size, value) {
    __emit(
        load.s.pri value,
        load.s.alt size,
        jgeq group_set_none,
        load.s.pri value,
        load.s.alt group,
        lidx,
        retn
    );

group_set_none:
    return -1;
}

stock bool:SSI@GroupPool_Contains(const group[], size, groups, groupid, value) {
    __emit(
        load.s.pri value,
        load.s.alt size,
        jgeq group_set_refuse,
        load.s.pri groupid,
        load.s.alt groups,
        jgeq group_set_refuse,
        load.s.pri value,
        load.s.alt group,
        lidx,
        load.s.alt groupid,
        eq,
        retn
    );

group_set_refuse:
    return false;
}

stock SSI@GroupPool_Alloc(next[], prev[], group[], count[], &free, &fresh, size, groups, groupid) {
    __emit(
        load.s.pri groupid,
        load.s.alt groups,
        jgeq group_pool_refuse,
        lref.s.pri free,
        const.alt -1,
        jeq group_pool_fresh,
        stor.pri SSI@member,
        load.s.alt prev,
        lidx,
        sref.s.pri free,
        jump group_pool_link
    );

group_pool_fresh:
    __emit(
        lref.s.pri fresh,
        load.s.alt size,
        jeq group_pool_refuse,
        stor.pri SSI@member,
        add.c 1,
        sref.s.pri fresh,
        jump group_pool_link
    );

group_pool_link:
    __emit(
        load.s.pri size,
        load.s.alt groupid,
        add,
        stor.pri SSI@anchor,
        load.s.alt prev,
        lidx,
        stor.pri SSI@before,
        load.s.alt next,
        idxaddr,
        move.alt,
        load.pri SSI@member,
        stor.i,
        load.pri SSI@member,
        load.s.alt prev,
        idxaddr,
        move.alt,
        load.pri SSI@before,
        stor.i,
        load.pri SSI@member,
        load.s.alt next,
        idxaddr,
        move.alt,
        load.pri SSI@anchor,
        stor.i,
        load.pri SSI@anchor,
        load.s.alt prev,
        idxaddr,
        move.alt,
        load.pri SSI@member,
        stor.i,
        load.pri SSI@member,
        load.s.alt group,
        idxaddr,
        move.alt,
        load.s.pri groupid,
        stor.i,
        load.s.pri groupid,
        load.s.alt count,
        idxaddr,
        inc.i,
        load.pri SSI@member,
        retn
    );

group_pool_refuse:
    return -1;
}

stock bool:SSI@GroupPool_Remove(next[], prev[], group[], count[], &free, size, id) {
    __emit(
        load.s.pri id,
        load.s.alt size,
        jgeq group_pool_refuse,
        load.s.pri id,
        load.s.alt group,
        idxaddr,
        stor.pri SSI@cell,
        load.i,
        const.alt -1,
        jeq group_pool_refuse,
        load.s.alt count,
        idxaddr,
        dec.i,
        load.pri SSI@cell,
        move.alt,
        const.pri -1,
        stor.i,
        load.s.pri id,
        load.s.alt prev,
        lidx,
        stor.pri SSI@before,
        load.s.pri id,
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
        load.s.pri id,
        load.s.alt prev,
        idxaddr,
        move.alt,
        lref.s.pri free,
        stor.i,
        load.s.pri id,
        sref.s.pri free,
        const.pri 1,
        retn
    );

group_pool_refuse:
    return false;
}

stock bool:SSI@GroupPool_Clear(next[], prev[], group[], count[], &free, size, groups, groupid) {
    __emit(
        load.s.pri groupid,
        load.s.alt groups,
        jgeq group_pool_refuse,
        load.s.pri size,
        load.s.alt groupid,
        add,
        stor.pri SSI@anchor,
        load.s.alt next,
        lidx,
        stor.pri SSI@member,
        lctrl 6,
        stor.pri SSI@loop,
        load.pri SSI@member,
        load.alt SSI@anchor,
        jeq group_pool_cleared,
        load.s.alt group,
        idxaddr,
        move.alt,
        const.pri -1,
        stor.i,
        load.pri SSI@member,
        load.s.alt prev,
        idxaddr,
        move.alt,
        lref.s.pri free,
        stor.i,
        load.pri SSI@member,
        sref.s.pri free,
        load.s.alt next,
        lidx,
        stor.pri SSI@member,
        load.pri SSI@loop,
        sctrl 6
    );

group_pool_cleared:
    __emit(
        load.pri SSI@anchor,
        load.s.alt next,
        idxaddr,
        move.alt,
        load.pri SSI@anchor,
        stor.i,
        load.pri SSI@anchor,
        load.s.alt prev,
        idxaddr,
        move.alt,
        load.pri SSI@anchor,
        stor.i,
        load.s.pri groupid,
        load.s.alt count,
        idxaddr,
        move.alt,
        zero.pri,
        stor.i,
        const.pri 1,
        retn
    );

group_pool_refuse:
    return false;
}

stock SSI@HandlePool_Next(const prev[], size, id, bool:used) {
    while (++id < size) {
        if ((prev[id] <= size) == used) {
            return id;
        }
    }

    return -1;
}

stock SSI@GroupPool_Pick(groupid = -1) {
    return groupid;
}

stock SSI@GroupPool_Next(const group[], size, value, groupid, bool:used) {
    if (groupid == -1) {
        while (++value < size) {
            if ((group[value] != -1) == used) {
                return value;
            }
        }

        return -1;
    }

    while (++value < size) {
        if ((group[value] == groupid) == used) {
            return value;
        }
    }

    return -1;
}

stock SSI@Count_Next(const count[], length, index, low, high) {
    while (++index < length) {
        if (low <= count[index] <= high) {
            return index;
        }
    }

    return -1;
}
