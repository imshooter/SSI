#if defined _INC_SSI_VEHICLE_PARTS
    #endinput
#endif
#define _INC_SSI_VEHICLE_PARTS

#include <open.mp>

/**
 * The parts of a vehicle one at a time: some parameters, a door, window,
 * tyre, lamp or panel is set while the others keep what the game has.
 *
 *     SetVehicleParamsState(vehicleid, VEHICLE_PARAM_ENGINE | VEHICLE_PARAM_LIGHTS, VEHICLE_PARAMS_ON);
 *     SetVehicleWindowOpen(vehicleid, VEHICLE_CORNER_FRONT_LEFT, true);
 *     SetVehicleTyrePopped(vehicleid, VEHICLE_CORNER_REAR_RIGHT, true);
 *
 * - Nothing is cached. Each call reads the state from the server and writes it
 *   back, so a native called elsewhere is never undone.
 * - Doors and windows are the four seats, named by `VEHICLE_CORNER` as tyres
 *   and wheels are. On a bike the front tyre is `VEHICLE_CORNER_FRONT_RIGHT`
 *   and the rear one `VEHICLE_CORNER_REAR_RIGHT`.
 * - The bonnet, boot and front doors break apart from the seats, so their
 *   damage is named by `VEHICLE_OPENING`.
 */

/**
 * # Header
 */

#define VEHICLE_PARAM_COUNT (7)

enum VEHICLE_PARAM: (<<= 1) {
    VEHICLE_PARAM_NONE = 0,
    VEHICLE_PARAM_ENGINE = 1,
    VEHICLE_PARAM_LIGHTS,
    VEHICLE_PARAM_ALARM,
    VEHICLE_PARAM_DOORS,
    VEHICLE_PARAM_BONNET,
    VEHICLE_PARAM_BOOT,
    VEHICLE_PARAM_OBJECTIVE
}

enum VEHICLE_CORNER {
    VEHICLE_CORNER_FRONT_LEFT,
    VEHICLE_CORNER_FRONT_RIGHT,
    VEHICLE_CORNER_REAR_LEFT,
    VEHICLE_CORNER_REAR_RIGHT
}

enum VEHICLE_OPENING {
    VEHICLE_OPENING_BONNET,
    VEHICLE_OPENING_BOOT,
    VEHICLE_OPENING_FRONT_LEFT,
    VEHICLE_OPENING_FRONT_RIGHT
}

enum VEHICLE_LAMP {
    VEHICLE_LAMP_FRONT_LEFT,
    VEHICLE_LAMP_FRONT_RIGHT,
    VEHICLE_LAMP_REAR
}

enum VEHICLE_PANEL {
    VEHICLE_PANEL_FRONT_LEFT,
    VEHICLE_PANEL_FRONT_RIGHT,
    VEHICLE_PANEL_REAR_LEFT,
    VEHICLE_PANEL_REAR_RIGHT,
    VEHICLE_PANEL_WINDSHIELD,
    VEHICLE_PANEL_FRONT_BUMPER,
    VEHICLE_PANEL_REAR_BUMPER
}

static stock const VEHICLE_TYRE_STATUS:gVehicleTyreStatus[VEHICLE_CORNER] = {
    VEHICLE_TYRE_STATUS_FRONT_LEFT_POPPED,
    VEHICLE_TYRE_STATUS_FRONT_RIGHT_POPPED,
    VEHICLE_TYRE_STATUS_REAR_LEFT_POPPED,
    VEHICLE_TYRE_STATUS_REAR_RIGHT_POPPED
};

static stock const VEHICLE_LIGHT_STATUS:gVehicleLampStatus[VEHICLE_LAMP] = {
    VEHICLE_LIGHT_STATUS_FRONT_LEFT_BROKEN,
    VEHICLE_LIGHT_STATUS_FRONT_RIGHT_BROKEN,
    VEHICLE_LIGHT_STATUS_REAR_BROKEN
};

/**
 * # Functions
 */

/**
 * @brief      Set parameters of a vehicle to one value, keeping the others.
 *
 * @param      vehicleid  The vehicle.
 * @param      params     The parameters, joined with `|`, such as
 *                        `VEHICLE_PARAM_ENGINE | VEHICLE_PARAM_LIGHTS`.
 * @param      value      `VEHICLE_PARAMS_ON`, `VEHICLE_PARAMS_OFF`, or
 *                        `VEHICLE_PARAMS_UNSET` to give them back to the game.
 *
 * @return     - `true` they were set
 *             - `false` `vehicleid` is not a vehicle
 */
forward bool:SetVehicleParamsState(vehicleid, VEHICLE_PARAM:params, value);

/**
 * @brief      One parameter of a vehicle.
 *
 * @param      vehicleid  The vehicle.
 * @param      param      The parameter, a single one.
 *
 * @return     - `VEHICLE_PARAMS_ON`, `VEHICLE_PARAMS_OFF` or
 *               `VEHICLE_PARAMS_UNSET`
 *             - `VEHICLE_PARAMS_UNSET` too when `vehicleid` is not a vehicle
 *               or `param` is not a single parameter
 */
forward GetVehicleParamState(vehicleid, VEHICLE_PARAM:param);

/**
 * @brief      Open or close the door of a seat.
 *
 * @param      vehicleid  The vehicle.
 * @param      door       The seat of the door.
 * @param      open       Whether it opens.
 *
 * @return     - `true` it was set
 *             - `false` `vehicleid` is not a vehicle
 */
forward bool:SetVehicleDoorOpen(vehicleid, VEHICLE_CORNER:door, bool:open);

/**
 * @brief      Whether the door of a seat was opened by `SetVehicleDoorOpen`.
 *
 * @param      vehicleid  The vehicle.
 * @param      door       The seat of the door.
 */
forward bool:IsVehicleDoorOpen(vehicleid, VEHICLE_CORNER:door);

/**
 * @brief      Open or close the window of a seat.
 *
 * @param      vehicleid  The vehicle.
 * @param      window     The seat of the window.
 * @param      open       Whether it opens.
 *
 * @return     - `true` it was set
 *             - `false` `vehicleid` is not a vehicle
 */
forward bool:SetVehicleWindowOpen(vehicleid, VEHICLE_CORNER:window, bool:open);

/**
 * @brief      Whether the window of a seat was opened by
 *             `SetVehicleWindowOpen`.
 *
 * @param      vehicleid  The vehicle.
 * @param      window     The seat of the window.
 */
forward bool:IsVehicleWindowOpen(vehicleid, VEHICLE_CORNER:window);

/**
 * @brief      Pop or mend a tyre.
 *
 * @param      vehicleid  The vehicle.
 * @param      tyre       The tyre.
 * @param      popped     Whether it is popped.
 *
 * @return     - `true` it was set
 *             - `false` `vehicleid` is not a vehicle
 */
forward bool:SetVehicleTyrePopped(vehicleid, VEHICLE_CORNER:tyre, bool:popped);

/**
 * @brief      Whether a tyre is popped.
 *
 * @param      vehicleid  The vehicle.
 * @param      tyre       The tyre.
 */
forward bool:IsVehicleTyrePopped(vehicleid, VEHICLE_CORNER:tyre);

/**
 * @brief      Break or mend a lamp.
 *
 * @param      vehicleid  The vehicle.
 * @param      lamp       The lamp. `VEHICLE_LAMP_REAR` is both rear lamps.
 * @param      broken     Whether it is broken.
 *
 * @return     - `true` it was set
 *             - `false` `vehicleid` is not a vehicle
 */
forward bool:SetVehicleLampBroken(vehicleid, VEHICLE_LAMP:lamp, bool:broken);

/**
 * @brief      Whether a lamp is broken.
 *
 * @param      vehicleid  The vehicle.
 * @param      lamp       The lamp.
 */
forward bool:IsVehicleLampBroken(vehicleid, VEHICLE_LAMP:lamp);

/**
 * @brief      The damage of the bonnet, the boot or a front door.
 *
 * @param      vehicleid  The vehicle.
 * @param      opening    The part.
 *
 * @return     - the flags of `VEHICLE_DOOR_STATUS_BONNET_OPEN`,
 *               `VEHICLE_DOOR_STATUS_BONNET_DAMAGED` and
 *               `VEHICLE_DOOR_STATUS_BONNET_MISSING`, whatever the part
 *             - `VEHICLE_DOOR_STATUS_NONE` when `vehicleid` is not a vehicle
 */
forward VEHICLE_DOOR_STATUS:GetVehicleOpeningDamage(vehicleid, VEHICLE_OPENING:opening);

/**
 * @brief      Set the damage of the bonnet, the boot or a front door.
 *
 * @param      vehicleid  The vehicle.
 * @param      opening    The part.
 * @param      damage     Flags of `VEHICLE_DOOR_STATUS_BONNET_OPEN`,
 *                        `VEHICLE_DOOR_STATUS_BONNET_DAMAGED` and
 *                        `VEHICLE_DOOR_STATUS_BONNET_MISSING`, whatever the
 *                        part.
 *
 * @return     - `true` it was set
 *             - `false` `vehicleid` is not a vehicle
 */
forward bool:SetVehicleOpeningDamage(vehicleid, VEHICLE_OPENING:opening, VEHICLE_DOOR_STATUS:damage);

/**
 * @brief      The damage of a panel, from `0` for whole to `3`.
 *
 * @param      vehicleid  The vehicle.
 * @param      panel      The panel.
 *
 * @return     - the damage
 *             - `0` when `vehicleid` is not a vehicle
 */
forward GetVehiclePanelDamage(vehicleid, VEHICLE_PANEL:panel);

/**
 * @brief      Set the damage of a panel.
 *
 * @param      vehicleid  The vehicle.
 * @param      panel      The panel.
 * @param      damage     From `0` for whole to `3`.
 *
 * @return     - `true` it was set
 *             - `false` `vehicleid` is not a vehicle
 */
forward bool:SetVehiclePanelDamage(vehicleid, VEHICLE_PANEL:panel, damage);

/**
 * # Params
 */

stock bool:SetVehicleParamsState(vehicleid, VEHICLE_PARAM:params, value) {
    new
        values[VEHICLE_PARAM_COUNT]
    ;

    if (!GetVehicleParamsEx(vehicleid, values[0], values[1], values[2], values[3], values[4], values[5], values[6])) {
        return false;
    }

    for (new i; i != VEHICLE_PARAM_COUNT; ++i) {
        if (params & VEHICLE_PARAM:(1 << i)) {
            values[i] = value;
        }
    }

    return SetVehicleParamsEx(vehicleid, values[0], values[1], values[2], values[3], values[4], values[5], values[6]);
}

stock GetVehicleParamState(vehicleid, VEHICLE_PARAM:param) {
    new
        values[VEHICLE_PARAM_COUNT]
    ;

    if (!GetVehicleParamsEx(vehicleid, values[0], values[1], values[2], values[3], values[4], values[5], values[6])) {
        return VEHICLE_PARAMS_UNSET;
    }

    for (new i; i != VEHICLE_PARAM_COUNT; ++i) {
        if (param == VEHICLE_PARAM:(1 << i)) {
            return values[i];
        }
    }

    return VEHICLE_PARAMS_UNSET;
}

/**
 * # Doors and windows
 */

stock bool:SetVehicleDoorOpen(vehicleid, VEHICLE_CORNER:door, bool:open) {
    new
        doors[VEHICLE_CORNER]
    ;

    if (!GetVehicleParamsCarDoors(vehicleid, doors[VEHICLE_CORNER_FRONT_LEFT], doors[VEHICLE_CORNER_FRONT_RIGHT], doors[VEHICLE_CORNER_REAR_LEFT], doors[VEHICLE_CORNER_REAR_RIGHT])) {
        return false;
    }

    doors[door] = open ? 1 : 0;

    return SetVehicleParamsCarDoors(vehicleid, doors[VEHICLE_CORNER_FRONT_LEFT], doors[VEHICLE_CORNER_FRONT_RIGHT], doors[VEHICLE_CORNER_REAR_LEFT], doors[VEHICLE_CORNER_REAR_RIGHT]);
}

stock bool:IsVehicleDoorOpen(vehicleid, VEHICLE_CORNER:door) {
    new
        doors[VEHICLE_CORNER]
    ;

    if (!GetVehicleParamsCarDoors(vehicleid, doors[VEHICLE_CORNER_FRONT_LEFT], doors[VEHICLE_CORNER_FRONT_RIGHT], doors[VEHICLE_CORNER_REAR_LEFT], doors[VEHICLE_CORNER_REAR_RIGHT])) {
        return false;
    }

    return doors[door] == 1;
}

stock bool:SetVehicleWindowOpen(vehicleid, VEHICLE_CORNER:window, bool:open) {
    new
        windows[VEHICLE_CORNER]
    ;

    if (!GetVehicleParamsCarWindows(vehicleid, windows[VEHICLE_CORNER_FRONT_LEFT], windows[VEHICLE_CORNER_FRONT_RIGHT], windows[VEHICLE_CORNER_REAR_LEFT], windows[VEHICLE_CORNER_REAR_RIGHT])) {
        return false;
    }

    windows[window] = open ? 0 : 1;

    return SetVehicleParamsCarWindows(vehicleid, windows[VEHICLE_CORNER_FRONT_LEFT], windows[VEHICLE_CORNER_FRONT_RIGHT], windows[VEHICLE_CORNER_REAR_LEFT], windows[VEHICLE_CORNER_REAR_RIGHT]);
}

stock bool:IsVehicleWindowOpen(vehicleid, VEHICLE_CORNER:window) {
    new
        windows[VEHICLE_CORNER]
    ;

    if (!GetVehicleParamsCarWindows(vehicleid, windows[VEHICLE_CORNER_FRONT_LEFT], windows[VEHICLE_CORNER_FRONT_RIGHT], windows[VEHICLE_CORNER_REAR_LEFT], windows[VEHICLE_CORNER_REAR_RIGHT])) {
        return false;
    }

    return windows[window] == 0;
}

/**
 * # Damage
 */

stock bool:SetVehicleTyrePopped(vehicleid, VEHICLE_CORNER:tyre, bool:popped) {
    new
        VEHICLE_PANEL_STATUS:panels,
        VEHICLE_DOOR_STATUS:doors,
        VEHICLE_LIGHT_STATUS:lights,
        VEHICLE_TYRE_STATUS:tyres
    ;

    if (!GetVehicleDamageStatus(vehicleid, panels, doors, lights, tyres)) {
        return false;
    }

    return UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, popped ? (tyres | gVehicleTyreStatus[tyre]) : (tyres & ~gVehicleTyreStatus[tyre]));
}

stock bool:IsVehicleTyrePopped(vehicleid, VEHICLE_CORNER:tyre) {
    new
        VEHICLE_PANEL_STATUS:panels,
        VEHICLE_DOOR_STATUS:doors,
        VEHICLE_LIGHT_STATUS:lights,
        VEHICLE_TYRE_STATUS:tyres
    ;

    if (!GetVehicleDamageStatus(vehicleid, panels, doors, lights, tyres)) {
        return false;
    }

    return (tyres & gVehicleTyreStatus[tyre]) != VEHICLE_TYRE_STATUS_NONE;
}

stock bool:SetVehicleLampBroken(vehicleid, VEHICLE_LAMP:lamp, bool:broken) {
    new
        VEHICLE_PANEL_STATUS:panels,
        VEHICLE_DOOR_STATUS:doors,
        VEHICLE_LIGHT_STATUS:lights,
        VEHICLE_TYRE_STATUS:tyres
    ;

    if (!GetVehicleDamageStatus(vehicleid, panels, doors, lights, tyres)) {
        return false;
    }

    return UpdateVehicleDamageStatus(vehicleid, panels, doors, broken ? (lights | gVehicleLampStatus[lamp]) : (lights & ~gVehicleLampStatus[lamp]), tyres);
}

stock bool:IsVehicleLampBroken(vehicleid, VEHICLE_LAMP:lamp) {
    new
        VEHICLE_PANEL_STATUS:panels,
        VEHICLE_DOOR_STATUS:doors,
        VEHICLE_LIGHT_STATUS:lights,
        VEHICLE_TYRE_STATUS:tyres
    ;

    if (!GetVehicleDamageStatus(vehicleid, panels, doors, lights, tyres)) {
        return false;
    }

    return (lights & gVehicleLampStatus[lamp]) != VEHICLE_LIGHT_STATUS_NONE;
}

stock VEHICLE_DOOR_STATUS:GetVehicleOpeningDamage(vehicleid, VEHICLE_OPENING:opening) {
    new
        VEHICLE_PANEL_STATUS:panels,
        VEHICLE_DOOR_STATUS:doors,
        VEHICLE_LIGHT_STATUS:lights,
        VEHICLE_TYRE_STATUS:tyres
    ;

    if (!GetVehicleDamageStatus(vehicleid, panels, doors, lights, tyres)) {
        return VEHICLE_DOOR_STATUS_NONE;
    }

    return VEHICLE_DOOR_STATUS:((_:doors >>> (_:opening * 8)) & 0x7);
}

stock bool:SetVehicleOpeningDamage(vehicleid, VEHICLE_OPENING:opening, VEHICLE_DOOR_STATUS:damage) {
    new
        VEHICLE_PANEL_STATUS:panels,
        VEHICLE_DOOR_STATUS:doors,
        VEHICLE_LIGHT_STATUS:lights,
        VEHICLE_TYRE_STATUS:tyres
    ;

    if (!GetVehicleDamageStatus(vehicleid, panels, doors, lights, tyres)) {
        return false;
    }

    new const
        shift = _:opening * 8
    ;

    return UpdateVehicleDamageStatus(vehicleid, panels, VEHICLE_DOOR_STATUS:((_:doors & ~(0x7 << shift)) | ((_:damage & 0x7) << shift)), lights, tyres);
}

stock GetVehiclePanelDamage(vehicleid, VEHICLE_PANEL:panel) {
    new
        VEHICLE_PANEL_STATUS:panels,
        VEHICLE_DOOR_STATUS:doors,
        VEHICLE_LIGHT_STATUS:lights,
        VEHICLE_TYRE_STATUS:tyres
    ;

    if (!GetVehicleDamageStatus(vehicleid, panels, doors, lights, tyres)) {
        return 0;
    }

    return (_:panels >>> (_:panel * 4)) & 0xF;
}

stock bool:SetVehiclePanelDamage(vehicleid, VEHICLE_PANEL:panel, damage) {
    new
        VEHICLE_PANEL_STATUS:panels,
        VEHICLE_DOOR_STATUS:doors,
        VEHICLE_LIGHT_STATUS:lights,
        VEHICLE_TYRE_STATUS:tyres
    ;

    if (!GetVehicleDamageStatus(vehicleid, panels, doors, lights, tyres)) {
        return false;
    }

    new const
        shift = _:panel * 4
    ;

    return UpdateVehicleDamageStatus(vehicleid, VEHICLE_PANEL_STATUS:((_:panels & ~(0xF << shift)) | ((damage & 0xF) << shift)), doors, lights, tyres);
}
