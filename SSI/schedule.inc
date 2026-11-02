#if defined _INC_SSI_SCHEDULE
    #endinput
#endif
#define _INC_SSI_SCHEDULE

#include <SSI\collection>

/**
 * Schedules hold a time for each id. Setting, moving and removing a time take
 * the same time with ten ids or with a hundred thousand. One timer of the
 * script takes out the ids that are due, instead of one timer for each id:
 *
 *     #include <SSI\schedule>
 *
 *     static
 *         Schedule:JailRelease<MAX_PLAYERS>
 *     ;
 *
 *     Schedule_Set(JailRelease, playerid, gettime() + 300);
 *     Schedule_Remove(JailRelease, playerid);
 *
 *     foreach (new playerid : Due(JailRelease, gettime())) {
 *         ReleasePlayer(playerid);
 *     }
 *
 * An id has one time at most: setting it again moves it. Times are whole units
 * of any kind, seconds or tenths of a second, compared by their difference, so
 * a count that wraps around is fine while no time is more than half the range
 * away. Each unit is a step of the walk, so the unit is the coarsest one that is
 * precise enough. Ids and times take any tag.
 */

/**
 * # Header
 */

#if !defined SSI_SCHEDULE_SLOTS
    #define SSI_SCHEDULE_SLOTS (1024)
#endif

#if SSI_SCHEDULE_SLOTS & (SSI_SCHEDULE_SLOTS - 1)
    #error SSI_SCHEDULE_SLOTS must be a power of two.
#endif

/**
 * Makes `Schedule:schedule<>` in the forwards below a plain parameter, so the
 * editor shows a schedule the way it is used. The declaration takes its place
 * after them.
 */
#define Schedule:%0<%1> %0

/**
 * # Functions
 */

/**
 * @brief      Give an id a time, or move it to another.
 *
 * A time already past is due at the next walk.
 *
 * @param      schedule  The schedule, named by its tag.
 * @param      id        The id.
 * @param      time      Its time.
 *
 * @return     - `true` the id has the time
 *             - `false` the id is out of range
 */
forward bool:Schedule_Set(Schedule:schedule<>, id, time);
#define Schedule_Set(%0,%1,%2) SSI@Schedule_Set(%0@SSI_next, %0@SSI_prev, %0@SSI_group, %0@SSI_count, %0@SSI_free[0], %0@SSI_time, %0@SSI_tick, sizeof %0@SSI_group, _:(%1), _:(%2))

/**
 * @brief      Take an id out.
 *
 * @param      schedule  The schedule, named by its tag.
 * @param      id        The id.
 *
 * @return     - `true` it was taken out
 *             - `false` it was not in, or is out of range
 */
forward bool:Schedule_Remove(Schedule:schedule<>, id);
#define Schedule_Remove(%0,%1) SSI@Schedule_Remove(%0@SSI_next, %0@SSI_prev, %0@SSI_group, %0@SSI_count, %0@SSI_free[0], %0@SSI_tick, sizeof %0@SSI_group, _:(%1))

/**
 * @brief      Whether an id has a time.
 *
 * @param      schedule  The schedule, named by its tag.
 * @param      id        The id.
 *
 * @return     - `true` it has
 *             - `false` it has not, or is out of range
 */
forward bool:Schedule_Contains(Schedule:schedule<>, id);
#define Schedule_Contains(%0,%1) ((0 <= (SSI@index = _:(%1)) < sizeof %0@SSI_group) && %0@SSI_group[SSI@index] != -1)

/**
 * @brief      The time of an id.
 *
 * @param      schedule  The schedule, named by its tag.
 * @param      id        The id.
 *
 * @return     - the time
 *             - `0` it has none, or is out of range
 */
forward Schedule_Time(Schedule:schedule<>, id);
#define Schedule_Time(%0,%1) (((0 <= (SSI@index = _:(%1)) < sizeof %0@SSI_group) && %0@SSI_group[SSI@index] != -1) ? %0@SSI_time[SSI@index] : 0)

/**
 * @brief      How many ids have a time.
 *
 * @param      schedule  The schedule, named by its tag.
 *
 * @return     - the count
 */
forward Schedule_Count(Schedule:schedule<>);
#define Schedule_Count(%0) (%0@SSI_tick[2])

/**
 * @brief      Take every id out.
 *
 * @param      schedule  The schedule, named by its tag.
 */
forward Schedule_Clear(Schedule:schedule<>);
#define Schedule_Clear(%0) SSI@Schedule_Clear(%0@SSI_next, %0@SSI_prev, %0@SSI_group, %0@SSI_count, %0@SSI_free[0], %0@SSI_tick, sizeof %0@SSI_group)

/**
 * # Iterator Functions
 */

/**
 * @brief      Walk the ids due at `now`, taking each out.
 *
 * Earlier units come first, and the ids of one unit come in any order. An id
 * given a time that the walks have already passed comes with the next unit. An
 * id set again inside the loop to a time not after `now` comes back in the
 * same walk. A `break` leaves the remaining ids in.
 *
 *     foreach (new playerid : Due(JailRelease, gettime())) {
 *     }
 *
 * @param      schedule  The schedule, named by its tag.
 * @param      now       The current time, read once before the walk.
 */
#define Due@SSI_loop|||%9|||%1|||(%0,%2)||| %9%1,SSI@state%1=_:(%2);_:(%1=%9(SSI@Schedule_Due(%0@SSI_next, %0@SSI_prev, %0@SSI_group, %0@SSI_count, %0@SSI_time, %0@SSI_tick, sizeof %0@SSI_group, SSI@state%1)))!=-1;

/**
 * # Declaration
 */

#undef Schedule

/**
 * Declares the schedule tagged `%0`, for the ids from `0` to `%1 - 1`, static
 * when the declaration is. It is a wheel: the group layout of collections with
 * one group for each slot, the slot of an id being its time masked by the
 * slots. `time` holds the time of each id, and `tick` the last unit walked,
 * the id the walk of the next slot goes on from, the count, and the time that
 * id was passed over at.
 *
 *     static
 *         Schedule:JailRelease<MAX_PLAYERS>
 *     ;
 */
#define Schedule:%0<%1> \
    SSI_GroupPool_Declare(%0,SSI_SCHEDULE_SLOTS,%1), \
    %0@SSI_time[_:(%1)], \
    %0@SSI_tick[4] = { 0, -1, 0, 0 }

/**
 * # Internal
 */

const SSI@scheduleSlots = SSI_SCHEDULE_SLOTS;
const SSI@scheduleMask = SSI_SCHEDULE_SLOTS - 1;

static stock
    SSI@slot,
    SSI@anchor,
    SSI@cursor,
    SSI@member,
    SSI@before,
    SSI@after,
    SSI@loop
;

stock bool:SSI@Schedule_Set(next[], prev[], group[], count[], &free, time[], tick[], size, id, at) {
    if (id < 0) {
        return false;
    }

    if (id >= size) {
        return false;
    }

    if (group[id] == -1) {
        ++tick[2];
    } else {
        SSI@GroupPool_Remove(next, prev, group, count, free, size, id);
    }

    if (tick[1] == id) {
        tick[1] = -1;
    }

    time[id] = at;

    new const
        slot = ((at - tick[0] > 0) ? at : tick[0] + 1) & (SSI_SCHEDULE_SLOTS - 1)
    ;

    SSI@GroupPool_Add(next, prev, group, count, size, SSI_SCHEDULE_SLOTS, slot, id);

    return true;
}

stock bool:SSI@Schedule_Remove(next[], prev[], group[], count[], &free, tick[], size, id) {
    if (id < 0) {
        return false;
    }

    if (id >= size) {
        return false;
    }

    if (!SSI@GroupPool_Remove(next, prev, group, count, free, size, id)) {
        return false;
    }

    if (tick[1] == id) {
        tick[1] = -1;
    }

    --tick[2];

    return true;
}

stock SSI@Schedule_Due(next[], prev[], group[], count[], const time[], tick[], size, now) {
    __emit(
        load.s.pri tick,
        load.i,
        load.s.alt now,
        sub,
        zero.alt,
        jsgeq schedule_none,
        load.s.pri tick,
        load.i,
        move.alt,
        load.s.pri now,
        sub,
        const.alt SSI@scheduleSlots,
        jsleq schedule_slot,
        load.s.pri now,
        const.alt SSI@scheduleSlots,
        sub,
        sref.s.pri tick,
        load.s.pri tick,
        add.c 4,
        move.alt,
        const.pri -1,
        stor.i,
        jump schedule_slot
    );

schedule_slot:
    __emit(
        load.s.pri tick,
        load.i,
        add.c 1,
        const.alt SSI@scheduleMask,
        and,
        stor.pri SSI@slot,
        load.s.alt size,
        add,
        stor.pri SSI@anchor,
        load.s.pri tick,
        add.c 4,
        load.i,
        stor.pri SSI@cursor,
        const.alt -1,
        jeq schedule_head,
        load.s.alt group,
        lidx,
        load.alt SSI@slot,
        jneq schedule_head,
        load.s.pri tick,
        add.c 12,
        load.i,
        load.s.alt now,
        jneq schedule_head,
        load.pri SSI@cursor,
        load.s.alt next,
        lidx,
        stor.pri SSI@member,
        jump schedule_walk
    );

schedule_head:
    __emit(
        const.pri -1,
        stor.pri SSI@cursor,
        load.pri SSI@anchor,
        load.s.alt next,
        lidx,
        stor.pri SSI@member,
        jump schedule_walk
    );

schedule_walk:
    __emit(
        lctrl 6,
        stor.pri SSI@loop,
        load.pri SSI@member,
        load.alt SSI@anchor,
        jeq schedule_slot_done,
        load.s.alt time,
        lidx,
        load.s.alt now,
        sub,
        zero.alt,
        jsleq schedule_due,
        load.pri SSI@member,
        stor.pri SSI@cursor,
        load.s.alt next,
        lidx,
        stor.pri SSI@member,
        load.pri SSI@loop,
        sctrl 6
    );

schedule_due:
    __emit(
        load.s.pri tick,
        add.c 4,
        move.alt,
        load.pri SSI@cursor,
        stor.i,
        load.s.pri tick,
        add.c 12,
        move.alt,
        load.s.pri now,
        stor.i,
        load.pri SSI@member,
        load.s.alt prev,
        lidx,
        stor.pri SSI@before,
        load.pri SSI@member,
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
        load.pri SSI@slot,
        load.s.alt count,
        idxaddr,
        dec.i,
        load.pri SSI@member,
        load.s.alt group,
        idxaddr,
        move.alt,
        const.pri -1,
        stor.i,
        load.s.pri tick,
        add.c 8,
        dec.i,
        load.pri SSI@member,
        retn
    );

schedule_slot_done:
    __emit(
        load.s.pri tick,
        add.c 4,
        move.alt,
        const.pri -1,
        stor.i,
        load.s.pri tick,
        inc.i,
        load.s.pri tick,
        load.i,
        load.s.alt now,
        sub,
        zero.alt,
        jsgeq schedule_none,
        jump schedule_slot
    );

schedule_none:
    return -1;
}

stock SSI@Schedule_Clear(next[], prev[], group[], count[], &free, tick[], size) {
    for (new slot; slot != SSI_SCHEDULE_SLOTS; ++slot) {
        SSI@GroupPool_Clear(next, prev, group, count, free, size, SSI_SCHEDULE_SLOTS, slot);
    }

    tick[1] = -1;
    tick[2] = 0;
}
