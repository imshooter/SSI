#if defined _INC_SSI_ITERATOR
    #endinput
#endif
#define _INC_SSI_ITERATOR

#include <open.mp>
#include <PawnPlus>
#include <SSI\hooks>
#include <SSI\collection>

/**
 * The ids the server hands out, in collections this script walks with
 * `foreach`, as y_foreach keeps its iterators:
 *
 *     #include <SSI\iterator>
 *
 *     foreach (new playerid : Player) {
 *     }
 *
 *     foreach (new vehicleid : StreamedVehicle[playerid]) {
 *     }
 *
 * - `Player`: the connected players who are not NPCs.
 * - `Bot`, also `NPC`: the connected NPCs.
 * - `Character`: both.
 * - `RconAdmin`: the players logged in to RCON.
 * - `Vehicle` and `Actor`: every one on the server.
 * - `LocalVehicle` and `LocalActor`: the ones made by this script.
 * - `StreamedPlayer[playerid]`, `StreamedBot[playerid]`,
 *   `StreamedCharacter[playerid]`, `StreamedVehicle[playerid]` and
 *   `StreamedActor[playerid]`: what that player has streamed in. Each is a
 *   collection per player, about 48 MB in all with the default 1000 players and
 *   2000 vehicles, so they exist only when `SSI_ITERATOR_STREAMED` is defined
 *   before this file.
 *
 * A player is added on `OnPlayerConnect` and removed after every hook and the
 * public of `OnPlayerDisconnect` have run, so all of them still walk the
 * player who is leaving. Vehicles and actors are tracked by PawnPlus filters
 * that run after the natives that create and destroy them, whichever script
 * calls them. Those that already exist when the script starts are counted too.
 * The ids are plain numbers, so the loop variable has no tag.
 * `Collection_Count`, `Collection_Contains` and the other calls read these
 * collections, and only this file changes them.
 *
 * It also has the iterator functions of y_foreach, walked the same way:
 * `Range`, `N`, `Powers`, `Fib`, `Random`, `Null`, `NonNull`, `Until`,
 * `Filter`, `VehicleOccupant`, `VehicleDriver` and `VehiclePassenger`.
 *
 *     foreach (new i : Range(10, 100, 2)) {
 *     }
 *
 *     foreach (new playerid : VehicleOccupant(vehicleid)) {
 *     }
 */

/**
 * # Header
 */

new
    Collection:Player<MAX_PLAYERS>,
    Collection:Bot<MAX_PLAYERS>,
    Collection:Character<MAX_PLAYERS>,
    Collection:RconAdmin<MAX_PLAYERS>,
    Collection:Vehicle<MAX_VEHICLES>,
    Collection:LocalVehicle<MAX_VEHICLES>,
    Collection:Actor<MAX_ACTORS>,
    Collection:LocalActor<MAX_ACTORS>
;

#define Player: _:
#define Bot: _:
#define Character: _:
#define RconAdmin: _:
#define Vehicle: _:
#define LocalVehicle: _:
#define Actor: _:
#define LocalActor: _:

#define NPC@SSI_next Bot@SSI_next
#define NPC@SSI_prev Bot@SSI_prev
#define NPC@SSI_count Bot@SSI_count
#define NPC@SSI_free Bot@SSI_free
#define NPC: _:

#if defined SSI_ITERATOR_STREAMED
    new
        Collection:StreamedPlayer[MAX_PLAYERS]<MAX_PLAYERS>,
        Collection:StreamedBot[MAX_PLAYERS]<MAX_PLAYERS>,
        Collection:StreamedCharacter[MAX_PLAYERS]<MAX_PLAYERS>,
        Collection:StreamedVehicle[MAX_PLAYERS]<MAX_VEHICLES>,
        Collection:StreamedActor[MAX_PLAYERS]<MAX_ACTORS>
    ;

    #define StreamedPlayer: _:
    #define StreamedBot: _:
    #define StreamedCharacter: _:
    #define StreamedVehicle: _:
    #define StreamedActor: _:
#endif

#if !defined SSI@carry
    stock
        SSI@carry
    ;
#endif

/**
 * # Iterator Functions
 */

/**
 * @brief      Walk the numbers from `0` up to `count`, `count` left out.
 *
 *     foreach (new i : N(6)) {
 *     }
 *
 * @param      count  How many numbers.
 */
#define N@SSI_loop|||%9|||%1|||(%3)||| %9%1=%9(0);_:%1<_:(%3);%1++

/**
 * @brief      Walk the numbers from `min` towards `max`, `max` left out.
 *
 *     foreach (new i : Range(10, 100, 2)) {
 *     }
 *
 * @param      min   The first number.
 * @param      max   The number the walk stops at.
 * @param      step  What is added each time, negative to count down, or `1`
 *                   when left out. A step of `0` never ends the walk.
 */
#define Range@SSI_loop|||%9|||%1|||(%3)||| SSI_RANGE|||%9|||%1|||(%3,1,)|||
#define SSI_RANGE|||%9|||%1|||(%0,%2,%4,%5)||| %9%1=%9(%0),SSI@state%1=_:((%4)>0);SSI@state%1?(_:%1<(%2)):(_:%1>(%2));%1+=%9(%4)

/**
 * @brief      Walk the powers of `base` that fit in a cell, from `1`.
 *
 *     foreach (new i : Powers(3)) {
 *     }
 *
 * @param      base  The number raised.
 */
#define Powers@SSI_loop|||%9|||%1|||(%3)||| %9%1=%9(1);_:%1!=0;%1=%9(SSI@Powers((_:%1),%3))

/**
 * @brief      Walk the Fibonacci numbers that fit in a cell, from `0`.
 *
 *     foreach (new i : Fib()) {
 *     }
 */
#define Fib@SSI_loop|||%9|||%1|||()||| %9%1=%9(0),SSI@state%1=1;_:%1>=0;SSI@state%1+=_:%1,%1=%9(SSI@state%1-_:%1)

/**
 * @brief      Walk `count` random numbers.
 *
 * With one number after `count`, the numbers range from `0` up to that
 * number, which is left out. With two, they range from the first up to the
 * second, which is left out.
 *
 *     foreach (new i : Random(12, 10)) {
 *     }
 *
 * @param      count  How many numbers.
 * @param      min    The lowest number, or with no `max` the number they stay
 *                    under.
 * @param      max    The number they stay under.
 */
#define Random@SSI_loop|||%9|||%1|||(%3)||| SSI_RANDOM|||%9|||%1|||(%3)|||(%3,)|||
#define SSI_RANDOM|||%9|||%1|||(%3)|||(%0,%2)||| %9%1=%9(0),SSI@state%1=0;SSI@state%1++<(%0)&&((%1=%9(SSI@Random(%3))),true);

/**
 * @brief      Walk the indexes of an array that hold `0`.
 *
 *     foreach (new i : Null(array)) {
 *     }
 *
 * @param      array  The array.
 * @param      size   How many of its cells to walk, or all of them when left
 *                    out.
 */
#define Null@SSI_loop|||%9|||%1|||(%3)||| SSI_SEARCH|||SSI@Null|||%9|||%1|||(%3)|||

/**
 * @brief      Walk the indexes of an array that hold anything but `0`.
 *
 * @param      array  The array.
 * @param      size   How many of its cells to walk, or all of them when left
 *                    out.
 */
#define NonNull@SSI_loop|||%9|||%1|||(%3)||| SSI_SEARCH|||SSI@NonNull|||%9|||%1|||(%3)|||

/**
 * @brief      Walk the indexes of an array up to the first that holds `value`,
 *             which is left out.
 *
 *     foreach (new i : Until(5, array)) {
 *     }
 *
 * @param      value  The value the walk stops at.
 * @param      array  The array.
 * @param      size   How many of its cells to walk, or all of them when left
 *                    out.
 */
#define Until@SSI_loop|||%9|||%1|||(%3)||| SSI_SEARCH|||SSI@Until|||%9|||%1|||(%3)|||

/**
 * @brief      Walk the indexes of an array that hold `value`.
 *
 * @param      value  The value looked for.
 * @param      array  The array.
 * @param      size   How many of its cells to walk, or all of them when left
 *                    out.
 */
#define Filter@SSI_loop|||%9|||%1|||(%3)||| SSI_SEARCH|||SSI@Filter|||%9|||%1|||(%3)|||

#define SSI_SEARCH|||%8|||%9|||%1|||(%3)||| %9%1=%9(-1);_:(%1=%9(%8((_:%1),%3)))!=-1;

/**
 * @brief      Walk the players in a vehicle, seat by seat from the driver, or
 *             the players in any vehicle.
 *
 * A player who leaves the vehicle inside the loop does not stop the walk.
 *
 *     foreach (new playerid : VehicleOccupant(vehicleid)) {
 *     }
 *
 * @param      vehicleid  The vehicle, or every vehicle when left out.
 * @param      driver     Whether the driver is walked.
 * @param      passenger  Whether the passengers are walked.
 */
#define VehicleOccupant@SSI_loop|||%9|||%1|||(%3)||| SSI_OCCUPANT|||SSI@VehicleOccupant|||%9|||%1|||(%3)|||

/**
 * @brief      Walk the driver of a vehicle, or the drivers of every vehicle.
 *
 * @param      vehicleid  The vehicle, or every vehicle when left out.
 */
#define VehicleDriver@SSI_loop|||%9|||%1|||(%3)||| SSI_OCCUPANT|||SSI@VehicleDriver|||%9|||%1|||(%3)|||

/**
 * @brief      Walk the passengers of a vehicle, or of every vehicle.
 *
 * @param      vehicleid  The vehicle, or every vehicle when left out.
 */
#define VehiclePassenger@SSI_loop|||%9|||%1|||(%3)||| SSI_OCCUPANT|||SSI@VehiclePassenger|||%9|||%1|||(%3)|||

#define SSI_OCCUPANT|||%8|||%9|||%1|||(%3)||| %9%1,SSI@state%1=-1;(SSI@carry=SSI@state%1,%1=%9(%8(%3)),SSI@state%1=SSI@carry,_:%1)!=INVALID_PLAYER_ID;

/**
 * # Internal
 */

forward @SSI_RconLogin();
forward @SSI_AdminSet(&bool:set, &playerid, &bool:admin);
forward @SSI_VehicleCreated(&vehicleid);
forward @SSI_VehicleDestroyed(&bool:destroyed, &vehicleid);
forward @SSI_ActorCreated(&actorid);
forward @SSI_ActorDestroyed(&bool:destroyed, &actorid);

forward _pp@on_init@SSI_Iterator();

static stock ForgetCharacterInternal(playerid) {
    Collection_Remove(Character, playerid);
    Collection_Remove(Player, playerid);
    Collection_Remove(Bot, playerid);
    Collection_Remove(RconAdmin, playerid);

    #if defined SSI_ITERATOR_STREAMED
        foreach (new forplayerid : Character) {
            Collection_Remove(StreamedCharacter[forplayerid], playerid);
            Collection_Remove(StreamedPlayer[forplayerid], playerid);
            Collection_Remove(StreamedBot[forplayerid], playerid);
        }

        Collection_Clear(StreamedCharacter[playerid]);
        Collection_Clear(StreamedPlayer[playerid]);
        Collection_Clear(StreamedBot[playerid]);
        Collection_Clear(StreamedVehicle[playerid]);
        Collection_Clear(StreamedActor[playerid]);
    #endif
}

static stock AddCharacterInternal(playerid) {
    Collection_Add(Character, playerid);

    if (IsPlayerNPC(playerid)) {
        Collection_Add(Bot, playerid);

        return;
    }

    Collection_Add(Player, playerid);

    if (IsPlayerAdmin(playerid)) {
        Collection_Add(RconAdmin, playerid);
    }
}

#if defined SSI_ITERATOR_STREAMED
    static stock AddStreamedCharacterInternal(playerid, forplayerid) {
        Collection_Add(StreamedCharacter[forplayerid], playerid);

        if (IsPlayerNPC(playerid)) {
            Collection_Add(StreamedBot[forplayerid], playerid);

            return;
        }

        Collection_Add(StreamedPlayer[forplayerid], playerid);
    }

    static stock CollectStreamedIdsInternal() {
        foreach (new forplayerid : Character) {
            foreach (new playerid : Character) {
                if (playerid == forplayerid) {
                    continue;
                }

                if (!IsPlayerStreamedIn(playerid, forplayerid)) {
                    continue;
                }

                AddStreamedCharacterInternal(playerid, forplayerid);
            }

            foreach (new vehicleid : Vehicle) {
                if (!IsVehicleStreamedIn(vehicleid, forplayerid)) {
                    continue;
                }

                Collection_Add(StreamedVehicle[forplayerid], vehicleid);
            }

            foreach (new actorid : Actor) {
                if (!IsActorStreamedIn(actorid, forplayerid)) {
                    continue;
                }

                Collection_Add(StreamedActor[forplayerid], actorid);
            }
        }
    }
#endif

static stock CollectServerIdsInternal() {
    for (new i; i != MAX_PLAYERS; ++i) {
        if (!IsPlayerConnected(i)) {
            continue;
        }

        AddCharacterInternal(i);
    }

    for (new i = 1; i != MAX_VEHICLES; ++i) {
        if (!IsValidVehicle(i)) {
            continue;
        }

        Collection_Add(Vehicle, i);
    }

    for (new i; i != MAX_ACTORS; ++i) {
        if (!IsValidActor(i)) {
            continue;
        }

        Collection_Add(Actor, i);
    }

    #if defined SSI_ITERATOR_STREAMED
        CollectStreamedIdsInternal();
    #endif
}

public @SSI_RconLogin() {
    foreach (new playerid : Player) {
        if (!IsPlayerAdmin(playerid)) {
            continue;
        }

        Collection_Add(RconAdmin, playerid);
    }

    return 1;
}

stock SSI@Powers(value, base) {
    if (base <= 1) {
        return 0;
    }

    if (value > cellmax / base) {
        return 0;
    }

    return value * base;
}

stock SSI@Random(count, min = cellmax, max = 0) {
    #pragma unused count

    if (min >= max) {
        return random(min);
    }

    return random(max - min) + min;
}

stock SSI@Null(index, const array[], size = sizeof (array)) {
    while (++index < size) {
        if (!array[index]) {
            return index;
        }
    }

    return -1;
}

stock SSI@NonNull(index, const array[], size = sizeof (array)) {
    while (++index < size) {
        if (array[index]) {
            return index;
        }
    }

    return -1;
}

stock SSI@Until(index, value, const array[], size = sizeof (array)) {
    if (++index >= size) {
        return -1;
    }

    if (array[index] == value) {
        return -1;
    }

    return index;
}

stock SSI@Filter(index, value, const array[], size = sizeof (array)) {
    while (++index < size) {
        if (array[index] == value) {
            return index;
        }
    }

    return -1;
}

stock SSI@VehicleOccupant(vehicleid = INVALID_VEHICLE_ID, bool:driver = true, bool:passenger = true) {
    if (vehicleid == INVALID_VEHICLE_ID) {
        new const
            anchor = sizeof (Character@SSI_next) - 1
        ;

        for (new playerid = Character@SSI_next[(SSI@carry == -1) ? anchor : SSI@carry]; playerid != anchor; playerid = Character@SSI_next[playerid]) {
            new const
                PLAYER_STATE:status = GetPlayerState(playerid),
                bool:seated = (status == PLAYER_STATE_DRIVER) ? driver : (passenger && status == PLAYER_STATE_PASSENGER)
            ;

            if (!seated) {
                continue;
            }

            SSI@carry = playerid;

            return playerid;
        }

        return INVALID_PLAYER_ID;
    }

    new const
        model = GetVehicleModel(vehicleid)
    ;

    if (!model) {
        return INVALID_PLAYER_ID;
    }

    new const
        last = passenger ? GetVehicleSeats(model) : 0
    ;

    for (new seat = (SSI@carry == -1) ? (driver ? 0 : 1) : SSI@carry + 1; seat <= last; ++seat) {
        new const
            playerid = GetVehicleOccupant(vehicleid, seat)
        ;

        if (playerid == INVALID_PLAYER_ID) {
            continue;
        }

        SSI@carry = seat;

        return playerid;
    }

    return INVALID_PLAYER_ID;
}

stock SSI@VehicleDriver(vehicleid = INVALID_VEHICLE_ID) {
    return SSI@VehicleOccupant(vehicleid, true, false);
}

stock SSI@VehiclePassenger(vehicleid = INVALID_VEHICLE_ID) {
    return SSI@VehicleOccupant(vehicleid, false, true);
}

/**
 * # Calls
 */

#if defined FILTERSCRIPT
    hook OnFilterScriptInit() {
        CollectServerIdsInternal();

        return 1;
    }
#else
    hook OnGameModeInit() {
        CollectServerIdsInternal();

        return 1;
    }
#endif

hook OnPlayerConnect(playerid) {
    ForgetCharacterInternal(playerid);
    AddCharacterInternal(playerid);

    return 1;
}

public OnPlayerDisconnect(playerid, reason) {
    #if defined SSI@Iterator_OnPlayerDisconnect
        new const
            result = SSI@Iterator_OnPlayerDisconnect(playerid, reason)
        ;
    #else
        new const
            result = 1
        ;
    #endif

    ForgetCharacterInternal(playerid);

    return result;
}

#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect SSI@Iterator_OnPlayerDisconnect

#if defined SSI@Iterator_OnPlayerDisconnect
    forward SSI@Iterator_OnPlayerDisconnect(playerid, reason);
#endif

hook OnRconLoginAttempt(ip[], password[], success) {
    if (success) {
        SetTimer("@SSI_RconLogin", 0, false);
    }

    return 1;
}

public _pp@on_init@SSI_Iterator() {
    pawn_add_filter("SetPlayerAdmin", "-", "@SSI_AdminSet", filter_out);
    pawn_add_filter("CreateVehicle", "-", "@SSI_VehicleCreated", filter_out);
    pawn_add_filter("AddStaticVehicle", "-", "@SSI_VehicleCreated", filter_out);
    pawn_add_filter("AddStaticVehicleEx", "-", "@SSI_VehicleCreated", filter_out);
    pawn_add_filter("DestroyVehicle", "-", "@SSI_VehicleDestroyed", filter_out);
    pawn_add_filter("CreateActor", "-", "@SSI_ActorCreated", filter_out);
    pawn_add_filter("DestroyActor", "-", "@SSI_ActorDestroyed", filter_out);

    return 1;
}

public @SSI_AdminSet(&bool:set, &playerid, &bool:admin) {
    if (!set) {
        return 1;
    }

    if (admin && Collection_Contains(Player, playerid)) {
        Collection_Add(RconAdmin, playerid);
    } else {
        Collection_Remove(RconAdmin, playerid);
    }

    return 1;
}

public @SSI_VehicleCreated(&vehicleid) {
    if (!IsValidVehicle(vehicleid)) {
        return 1;
    }

    Collection_Add(Vehicle, vehicleid);

    if (amx_source() == amx_this()) {
        Collection_Add(LocalVehicle, vehicleid);
    }

    return 1;
}

public @SSI_VehicleDestroyed(&bool:destroyed, &vehicleid) {
    if (!destroyed) {
        return 1;
    }

    Collection_Remove(Vehicle, vehicleid);
    Collection_Remove(LocalVehicle, vehicleid);

    #if defined SSI_ITERATOR_STREAMED
        foreach (new forplayerid : Character) {
            Collection_Remove(StreamedVehicle[forplayerid], vehicleid);
        }
    #endif

    return 1;
}

public @SSI_ActorCreated(&actorid) {
    if (!IsValidActor(actorid)) {
        return 1;
    }

    Collection_Add(Actor, actorid);

    if (amx_source() == amx_this()) {
        Collection_Add(LocalActor, actorid);
    }

    return 1;
}

public @SSI_ActorDestroyed(&bool:destroyed, &actorid) {
    if (!destroyed) {
        return 1;
    }

    Collection_Remove(Actor, actorid);
    Collection_Remove(LocalActor, actorid);

    #if defined SSI_ITERATOR_STREAMED
        foreach (new forplayerid : Character) {
            Collection_Remove(StreamedActor[forplayerid], actorid);
        }
    #endif

    return 1;
}

#if defined SSI_ITERATOR_STREAMED
    hook OnPlayerStreamIn(playerid, forplayerid) {
        AddStreamedCharacterInternal(playerid, forplayerid);

        return 1;
    }

    hook OnPlayerStreamOut(playerid, forplayerid) {
        Collection_Remove(StreamedCharacter[forplayerid], playerid);
        Collection_Remove(StreamedPlayer[forplayerid], playerid);
        Collection_Remove(StreamedBot[forplayerid], playerid);

        return 1;
    }

    hook OnVehicleStreamIn(vehicleid, forplayerid) {
        Collection_Add(StreamedVehicle[forplayerid], vehicleid);

        return 1;
    }

    hook OnVehicleStreamOut(vehicleid, forplayerid) {
        Collection_Remove(StreamedVehicle[forplayerid], vehicleid);

        return 1;
    }

    hook OnActorStreamIn(actorid, forplayerid) {
        Collection_Add(StreamedActor[forplayerid], actorid);

        return 1;
    }

    hook OnActorStreamOut(actorid, forplayerid) {
        Collection_Remove(StreamedActor[forplayerid], actorid);

        return 1;
    }
#endif
