#if defined _INC_SSI_VEHICLE_NEON
    #endinput
#endif
#define _INC_SSI_VEHICLE_NEON

#include <open.mp>
#include <streamer>
#include <SSI\hooks>

/**
 * Neon under a vehicle: two tubes of a colour along its sides, or one down the
 * middle of a model narrower than `VEHICLE_NEON_NARROW`, such as a motorbike.
 * They are attached as streamer objects, so the light follows the vehicle
 * wherever it goes.
 *
 *     SetVehicleNeon(vehicleid, VEHICLE_NEON_BLUE);
 *     SetVehicleNeon(vehicleid, VEHICLE_NEON_NONE);
 *
 * - The tubes stand `VEHICLE_NEON_SIDE` of the width out from the middle, at
 *   the height of the axles plus `VEHICLE_NEON_LIFT`, so they fit the model. A
 *   model without wheels has them `VEHICLE_NEON_LOW` of its height down.
 * - They keep the world and interior of the vehicle when the script moves it
 *   with `SetVehicleVirtualWorld` or `LinkVehicleToInterior`, and go away with
 *   it in `DestroyVehicle`.
 */

/**
 * # Header
 */

#if !defined VEHICLE_NEON_SIDE
    #define VEHICLE_NEON_SIDE (0.3)
#endif

#if !defined VEHICLE_NEON_LOW
    #define VEHICLE_NEON_LOW (0.5)
#endif

#if !defined VEHICLE_NEON_LIFT
    #define VEHICLE_NEON_LIFT (-0.35)
#endif

#if !defined VEHICLE_NEON_NARROW
    #define VEHICLE_NEON_NARROW (1.0)
#endif

#define VEHICLE_NEON_TUBES (2)

enum VEHICLE_NEON {
    VEHICLE_NEON_NONE,
    VEHICLE_NEON_RED,
    VEHICLE_NEON_BLUE,
    VEHICLE_NEON_GREEN,
    VEHICLE_NEON_YELLOW,
    VEHICLE_NEON_PINK,
    VEHICLE_NEON_WHITE
}

static enum E_VEHICLE_NEON_DATA {
    VEHICLE_NEON:E_VEHICLE_NEON_COLOUR,
    STREAMER_TAG_OBJECT:E_VEHICLE_NEON_TUBE[VEHICLE_NEON_TUBES],
    E_VEHICLE_NEON_TUBE_COUNT
};

static stock const gNeonModel[VEHICLE_NEON] = {
    0,
    18647,
    18648,
    18649,
    18650,
    18651,
    18652
};

static
    gVehicleNeon[MAX_VEHICLES][E_VEHICLE_NEON_DATA]
;

/**
 * # Functions
 */

/**
 * @brief      Put neon of a colour under a vehicle, in place of any it had.
 *
 * @param      vehicleid  The vehicle.
 * @param      neon       The colour, or `VEHICLE_NEON_NONE` to take it off.
 *
 * @return     - `true` it was set
 *             - `false` `vehicleid` is not a vehicle
 */
forward bool:SetVehicleNeon(vehicleid, VEHICLE_NEON:neon);

/**
 * @brief      The neon under a vehicle.
 *
 * @param      vehicleid  The vehicle.
 *
 * @return     - the colour
 *             - `VEHICLE_NEON_NONE` when it has none or is not a vehicle
 */
forward VEHICLE_NEON:GetVehicleNeon(vehicleid);

/**
 * # Internal
 */

static stock RemoveVehicleNeonInternal(vehicleid) {
    if (gVehicleNeon[vehicleid][E_VEHICLE_NEON_COLOUR] == VEHICLE_NEON_NONE) {
        return;
    }

    for (new i; i != gVehicleNeon[vehicleid][E_VEHICLE_NEON_TUBE_COUNT]; ++i) {
        DestroyDynamicObject(gVehicleNeon[vehicleid][E_VEHICLE_NEON_TUBE][i]);
    }

    gVehicleNeon[vehicleid][E_VEHICLE_NEON_COLOUR] = VEHICLE_NEON_NONE;
}

static stock SetVehicleNeonDataInternal(vehicleid, data, value) {
    if (gVehicleNeon[vehicleid][E_VEHICLE_NEON_COLOUR] == VEHICLE_NEON_NONE) {
        return;
    }

    for (new i; i != gVehicleNeon[vehicleid][E_VEHICLE_NEON_TUBE_COUNT]; ++i) {
        Streamer_SetIntData(STREAMER_TYPE_OBJECT, gVehicleNeon[vehicleid][E_VEHICLE_NEON_TUBE][i], data, value);
    }
}

/**
 * # External
 */

stock bool:SetVehicleNeon(vehicleid, VEHICLE_NEON:neon) {
    if (!IsValidVehicle(vehicleid)) {
        return false;
    }

    RemoveVehicleNeonInternal(vehicleid);

    if (neon == VEHICLE_NEON_NONE) {
        return true;
    }

    new
        Float:sizeX,
        Float:sizeY,
        Float:sizeZ,
        Float:wheelX,
        Float:wheelY,
        Float:wheelZ
    ;

    GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, sizeX, sizeY, sizeZ);
    GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_WHEELSFRONT, wheelX, wheelY, wheelZ);

    new const
        count = (sizeX < VEHICLE_NEON_NARROW) ? 1 : VEHICLE_NEON_TUBES,
        Float:side = (count == 1) ? 0.0 : sizeX * VEHICLE_NEON_SIDE,
        Float:low = (wheelZ < 0.0) ? wheelZ + VEHICLE_NEON_LIFT : -sizeZ * VEHICLE_NEON_LOW,
        worldid = GetVehicleVirtualWorld(vehicleid),
        interiorid = GetVehicleInterior(vehicleid)
    ;

    for (new i; i != count; ++i) {
        gVehicleNeon[vehicleid][E_VEHICLE_NEON_TUBE][i] = CreateDynamicObject(gNeonModel[neon], 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, worldid, interiorid);
        AttachDynamicObjectToVehicle(gVehicleNeon[vehicleid][E_VEHICLE_NEON_TUBE][i], vehicleid, (i == 0) ? -side : side, 0.0, low, 0.0, 0.0, 0.0);
    }

    gVehicleNeon[vehicleid][E_VEHICLE_NEON_COLOUR] = neon;
    gVehicleNeon[vehicleid][E_VEHICLE_NEON_TUBE_COUNT] = count;

    return true;
}

stock VEHICLE_NEON:GetVehicleNeon(vehicleid) {
    if (!IsValidVehicle(vehicleid)) {
        return VEHICLE_NEON_NONE;
    }

    return gVehicleNeon[vehicleid][E_VEHICLE_NEON_COLOUR];
}

/**
 * # Calls
 */

hook native bool:DestroyVehicle(vehicleid) {
    if (IsValidVehicle(vehicleid)) {
        RemoveVehicleNeonInternal(vehicleid);
    }

    return DestroyVehicle(vehicleid);
}

hook native bool:SetVehicleVirtualWorld(vehicleid, virtualWorld) {
    if (!SetVehicleVirtualWorld(vehicleid, virtualWorld)) {
        return false;
    }

    SetVehicleNeonDataInternal(vehicleid, E_STREAMER_WORLD_ID, virtualWorld);

    return true;
}

hook native bool:LinkVehicleToInterior(vehicleid, interiorid) {
    if (!LinkVehicleToInterior(vehicleid, interiorid)) {
        return false;
    }

    SetVehicleNeonDataInternal(vehicleid, E_STREAMER_INTERIOR_ID, interiorid);

    return true;
}
