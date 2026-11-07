#if defined _INC_SSI_VEHICLE_OBJECTIVE
    #endinput
#endif
#define _INC_SSI_VEHICLE_OBJECTIVE

#include <open.mp>
#include <streamer>
#include <SSI\hooks>

/**
 * Marks the vehicle a player was sent to with the yellow arrow and a radar
 * blip. The marks are hidden while the player is in it, as driver or
 * passenger, and come back when they get out. A player is sent to one vehicle
 * at a time.
 */

/**
 * # Header
 */

#if !defined VEHICLE_OBJECTIVE_ICON
    #define VEHICLE_OBJECTIVE_ICON (55)
#endif

#if !defined VEHICLE_OBJECTIVE_ICON_COLOUR
    #define VEHICLE_OBJECTIVE_ICON_COLOUR (0)
#endif

static
    gObjectiveVehicle[MAX_PLAYERS] = { INVALID_VEHICLE_ID, ... },
    STREAMER_TAG_MAP_ICON:gObjectiveIcon[MAX_PLAYERS] = { STREAMER_TAG_MAP_ICON:INVALID_STREAMER_ID, ... }
;

/**
 * # Functions
 */

/**
 * @brief      Send a player to a vehicle.
 *
 * Replaces the vehicle they were sent to before.
 *
 * @param      playerid   Player to send.
 * @param      vehicleid  Vehicle to send them to.
 *
 * @return     - `true` they are sent to it
 *             - `false` `vehicleid` is not a valid vehicle
 */
forward bool:SetPlayerObjectiveVehicle(playerid, vehicleid);

/**
 * @brief      Stop sending a player to a vehicle.
 *
 * @param      playerid  Player to change.
 *
 * @return     - `true` the marks were removed
 *             - `false` they were not sent anywhere
 */
forward bool:ClearPlayerObjectiveVehicle(playerid);

/**
 * @brief      The vehicle a player was sent to.
 *
 * A vehicle destroyed since is found here, since open.mp does not report it.
 *
 * @param      playerid  Player to read.
 *
 * @return     - the vehicle
 *             - `INVALID_VEHICLE_ID` they were not sent to one
 */
forward GetPlayerObjectiveVehicle(playerid);

/**
 * @brief      Show the arrow again.
 *
 * The client loses it when the player changes virtual world, which is not
 * reported, so call this after moving one.
 *
 * @param      playerid  Player to show it to.
 *
 * @return     - `true` it is shown again
 *             - `false` they were not sent anywhere
 */
forward bool:RefreshPlayerObjectiveVehicle(playerid);

/**
 * # Internal
 */

static stock bool:IsPlayerInObjectiveInternal(playerid) {
    return GetPlayerVehicleID(playerid) == gObjectiveVehicle[playerid];
}

static stock ClearObjectiveIconInternal(playerid) {
    if (gObjectiveIcon[playerid] == STREAMER_TAG_MAP_ICON:INVALID_STREAMER_ID) {
        return 0;
    }

    DestroyDynamicMapIcon(gObjectiveIcon[playerid]);
    gObjectiveIcon[playerid] = STREAMER_TAG_MAP_ICON:INVALID_STREAMER_ID;

    return 1;
}

static stock ShowObjectiveInternal(playerid, bool:shown) {
    new const
        vehicleid = gObjectiveVehicle[playerid]
    ;

    if (vehicleid == INVALID_VEHICLE_ID) {
        return 0;
    }

    SetVehicleParamsForPlayer(vehicleid, playerid, .objective = shown);

    return 1;
}

static stock ShowObjectiveIconInternal(playerid) {
    new const
        vehicleid = gObjectiveVehicle[playerid]
    ;

    if (vehicleid == INVALID_VEHICLE_ID) {
        return 0;
    }

    if (gObjectiveIcon[playerid] != STREAMER_TAG_MAP_ICON:INVALID_STREAMER_ID) {
        return 1;
    }

    new
        Float:x,
        Float:y,
        Float:z
    ;

    GetVehiclePos(vehicleid, x, y, z);

    gObjectiveIcon[playerid] = CreateDynamicMapIcon(x, y, z,
        VEHICLE_OBJECTIVE_ICON, VEHICLE_OBJECTIVE_ICON_COLOUR,
        .playerid = playerid, .style = MAPICON_GLOBAL
    );

    Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, gObjectiveIcon[playerid], E_STREAMER_ATTACHED_VEHICLE, vehicleid);

    return 1;
}

/**
 * # Vehicle Objective
 */

stock bool:SetPlayerObjectiveVehicle(playerid, vehicleid) {
    if (!IsValidVehicle(vehicleid)) {
        return false;
    }

    ClearPlayerObjectiveVehicle(playerid);

    gObjectiveVehicle[playerid] = vehicleid;

    ShowObjectiveInternal(playerid, !IsPlayerInObjectiveInternal(playerid));

    return true;
}

stock bool:ClearPlayerObjectiveVehicle(playerid) {
    if (gObjectiveVehicle[playerid] == INVALID_VEHICLE_ID) {
        return false;
    }

    ShowObjectiveInternal(playerid, false);
    ClearObjectiveIconInternal(playerid);

    gObjectiveVehicle[playerid] = INVALID_VEHICLE_ID;

    return true;
}

stock GetPlayerObjectiveVehicle(playerid) {
    if (gObjectiveVehicle[playerid] == INVALID_VEHICLE_ID) {
        return INVALID_VEHICLE_ID;
    }

    if (!IsValidVehicle(gObjectiveVehicle[playerid])) {
        ClearPlayerObjectiveVehicle(playerid);

        return INVALID_VEHICLE_ID;
    }

    return gObjectiveVehicle[playerid];
}

stock bool:RefreshPlayerObjectiveVehicle(playerid) {
    if (gObjectiveVehicle[playerid] == INVALID_VEHICLE_ID) {
        return false;
    }

    ShowObjectiveInternal(playerid, !IsPlayerInObjectiveInternal(playerid));

    return true;
}

/**
 * # Calls
 */

hook OnPlayerConnect(playerid) {
    gObjectiveVehicle[playerid] = INVALID_VEHICLE_ID;
    gObjectiveIcon[playerid] = STREAMER_TAG_MAP_ICON:INVALID_STREAMER_ID;

    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    ClearPlayerObjectiveVehicle(playerid);

    return 1;
}

/**
 * Getting in hides the marks and getting out shows them.
 */
hook OnPlayerStateChange(playerid, PLAYER_STATE:newstate, PLAYER_STATE:oldstate) {
    if (gObjectiveVehicle[playerid] == INVALID_VEHICLE_ID) {
        return 1;
    }

    ShowObjectiveInternal(playerid, !IsPlayerInObjectiveInternal(playerid));

    return 1;
}

/**
 * The arrow is lost when the player changes world, which has no callback, so
 * it is shown again when the interior changes with it.
 */
hook OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid) {
    RefreshPlayerObjectiveVehicle(playerid);

    return 1;
}

/**
 * The arrow can only be set on a vehicle the client has, so it is set when the
 * vehicle streams in, and the blip is removed.
 */
hook OnVehicleStreamIn(vehicleid, forplayerid) {
    if (gObjectiveVehicle[forplayerid] != vehicleid) {
        return 1;
    }

    ClearObjectiveIconInternal(forplayerid);
    ShowObjectiveInternal(forplayerid, !IsPlayerInObjectiveInternal(forplayerid));

    return 1;
}

/**
 * The arrow is gone with the vehicle, so the blip takes its place.
 */
hook OnVehicleStreamOut(vehicleid, forplayerid) {
    if (gObjectiveVehicle[forplayerid] != vehicleid) {
        return 1;
    }

    if (IsPlayerInObjectiveInternal(forplayerid)) {
        return 1;
    }

    ShowObjectiveIconInternal(forplayerid);

    return 1;
}
