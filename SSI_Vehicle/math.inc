#if defined _INC_SSI_VEHICLE_MATH
    #endinput
#endif
#define _INC_SSI_VEHICLE_MATH

#include <open.mp>
#include <SSI_Vehicle\parts>

/**
 * The geometry of a vehicle in the world: its speed, whether it lies on its
 * roof, and where a point of its body, its bonnet, boot or a wheel is as it
 * leans and turns.
 *
 *     new const
 *         Float:kmh = GetVehicleSpeed(vehicleid),
 *         Float:mph = GetVehicleSpeed(vehicleid, VEHICLE_SPEED_MPH)
 *     ;
 *
 *     GetVehicleBootPos(vehicleid, x, y, z);
 *
 * - The speed is the velocity of the game times a factor,
 *   `VEHICLE_SPEED_MULTIPLIER` unless one is given. It is kilometres an hour
 *   unless the script defines it before the include, as
 *   `#define VEHICLE_SPEED_MULTIPLIER VEHICLE_SPEED_MPH`. `VEHICLE_SPEED_KMH`
 *   and `VEHICLE_SPEED_MPH` can be defined before the include too.
 * - Points use the matrix of the vehicle, so they follow it on a slope or on
 *   its side.
 */

/**
 * # Header
 */

#if !defined VEHICLE_SPEED_KMH
    #define VEHICLE_SPEED_KMH (180.0)
#endif

#if !defined VEHICLE_SPEED_MPH
    #define VEHICLE_SPEED_MPH (111.846814)
#endif

#if !defined VEHICLE_SPEED_MULTIPLIER
    #define VEHICLE_SPEED_MULTIPLIER (VEHICLE_SPEED_KMH)
#endif

/**
 * # Functions
 */

/**
 * @brief      The speed of a vehicle: the length of its velocity times
 *             `multiplier`.
 *
 * @param      vehicleid   The vehicle.
 * @param      multiplier  Factor of the unit wanted, `VEHICLE_SPEED_KMH`,
 *                         `VEHICLE_SPEED_MPH`, or `1.0` for the velocity
 *                         of the game.
 *
 * @return     - the speed
 *             - `0.0` when `vehicleid` is not a vehicle
 */
forward Float:GetVehicleSpeed(vehicleid, Float:multiplier = VEHICLE_SPEED_MULTIPLIER);

/**
 * @brief      Whether a vehicle lies on its roof: its up points below the
 *             horizon.
 *
 * @param      vehicleid  The vehicle.
 *
 * @return     - `true` it is upside down
 *             - `false` it is not, or `vehicleid` is not a vehicle
 */
forward bool:IsVehicleUpsideDown(vehicleid);

/**
 * @brief      The world position of a point given in the frame of a vehicle,
 *             right, forward and up, as it leans and turns.
 *
 * @param      vehicleid  The vehicle.
 * @param      offsetX    To the right.
 * @param      offsetY    Forward.
 * @param      offsetZ    Up.
 * @param      x          Where the world X goes.
 * @param      y          Where the world Y goes.
 * @param      z          Where the world Z goes.
 *
 * @return     - `true` it was found
 *             - `false` `vehicleid` is not a vehicle
 */
forward bool:GetVehicleOffsetPos(vehicleid, Float:offsetX, Float:offsetY, Float:offsetZ, &Float:x, &Float:y, &Float:z);

/**
 * @brief      Distance from the middle of a vehicle to its bonnet.
 *
 * Half the length of its model plus `margin`, along the Y of the vehicle. Used
 * as the `offsetY` of `GetVehicleOffsetPos`.
 *
 * @param      vehicleid  The vehicle.
 * @param      margin     Distance past the bumper.
 *
 * @return     - the offset
 *             - `margin` when `vehicleid` is not a vehicle
 */
forward Float:GetVehicleBonnetOffset(vehicleid, Float:margin = 0.1);

/**
 * @brief      Distance from the middle of a vehicle to its boot, negative.
 *
 * @param      vehicleid  The vehicle.
 * @param      margin     Distance past the bumper.
 *
 * @return     - the offset
 *             - `-margin` when `vehicleid` is not a vehicle
 */
forward Float:GetVehicleBootOffset(vehicleid, Float:margin = 0.1);

/**
 * @brief      The world position of the bonnet of a vehicle, at the height of
 *             its middle.
 *
 * @param      vehicleid  The vehicle.
 * @param      x          Where the world X goes.
 * @param      y          Where the world Y goes.
 * @param      z          Where the world Z goes.
 * @param      margin     Distance past the bumper.
 *
 * @return     - `true` it was found
 *             - `false` `vehicleid` is not a vehicle
 */
forward bool:GetVehicleBonnetPos(vehicleid, &Float:x, &Float:y, &Float:z, Float:margin = 0.1);

/**
 * @brief      The world position of the boot of a vehicle, at the height of its
 *             middle.
 *
 * @param      vehicleid  The vehicle.
 * @param      x          Where the world X goes.
 * @param      y          Where the world Y goes.
 * @param      z          Where the world Z goes.
 * @param      margin     Distance past the bumper.
 *
 * @return     - `true` it was found
 *             - `false` `vehicleid` is not a vehicle
 */
forward bool:GetVehicleBootPos(vehicleid, &Float:x, &Float:y, &Float:z, Float:margin = 0.1);

/**
 * @brief      The world position of the centre of a wheel.
 *
 * @param      vehicleid  The vehicle.
 * @param      wheel      The wheel.
 * @param      x          Where the world X goes.
 * @param      y          Where the world Y goes.
 * @param      z          Where the world Z goes.
 *
 * @return     - `true` it was found
 *             - `false` `vehicleid` is not a vehicle
 */
forward bool:GetVehicleWheelPos(vehicleid, VEHICLE_CORNER:wheel, &Float:x, &Float:y, &Float:z);

/**
 * # Speed
 */

stock Float:GetVehicleSpeed(vehicleid, Float:multiplier = VEHICLE_SPEED_MULTIPLIER) {
    new
        Float:vx,
        Float:vy,
        Float:vz
    ;

    if (!GetVehicleVelocity(vehicleid, vx, vy, vz)) {
        return 0.0;
    }

    return VectorSize(vx, vy, vz) * multiplier;
}

/**
 * # Orientation
 */

stock bool:IsVehicleUpsideDown(vehicleid) {
    new
        Float:unused,
        Float:upZ
    ;

    if (!GetVehicleMatrix(vehicleid, unused, unused, unused, unused, unused, unused, unused, unused, upZ)) {
        return false;
    }

    return upZ < 0.0;
}

/**
 * # Positions
 */

stock bool:GetVehicleOffsetPos(vehicleid, Float:offsetX, Float:offsetY, Float:offsetZ, &Float:x, &Float:y, &Float:z) {
    new
        Float:rightX,
        Float:rightY,
        Float:rightZ,
        Float:forwardX,
        Float:forwardY,
        Float:forwardZ,
        Float:upX,
        Float:upY,
        Float:upZ
    ;

    if (!GetVehiclePos(vehicleid, x, y, z)) {
        return false;
    }

    GetVehicleMatrix(vehicleid, rightX, rightY, rightZ, forwardX, forwardY, forwardZ, upX, upY, upZ);

    x += offsetX * rightX + offsetY * forwardX + offsetZ * upX;
    y += offsetX * rightY + offsetY * forwardY + offsetZ * upY;
    z += offsetX * rightZ + offsetY * forwardZ + offsetZ * upZ;

    return true;
}

stock Float:GetVehicleBonnetOffset(vehicleid, Float:margin = 0.1) {
    new
        Float:sizeX,
        Float:sizeY,
        Float:sizeZ
    ;

    GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, sizeX, sizeY, sizeZ);

    return sizeY / 2.0 + margin;
}

stock Float:GetVehicleBootOffset(vehicleid, Float:margin = 0.1) {
    return -GetVehicleBonnetOffset(vehicleid, margin);
}

stock bool:GetVehicleBonnetPos(vehicleid, &Float:x, &Float:y, &Float:z, Float:margin = 0.1) {
    return GetVehicleOffsetPos(vehicleid, 0.0, GetVehicleBonnetOffset(vehicleid, margin), 0.0, x, y, z);
}

stock bool:GetVehicleBootPos(vehicleid, &Float:x, &Float:y, &Float:z, Float:margin = 0.1) {
    return GetVehicleOffsetPos(vehicleid, 0.0, GetVehicleBootOffset(vehicleid, margin), 0.0, x, y, z);
}

stock bool:GetVehicleWheelPos(vehicleid, VEHICLE_CORNER:wheel, &Float:x, &Float:y, &Float:z) {
    new
        Float:offsetX,
        Float:offsetY,
        Float:offsetZ
    ;

    if (!GetVehicleModelInfo(GetVehicleModel(vehicleid), (wheel == VEHICLE_CORNER_FRONT_LEFT || wheel == VEHICLE_CORNER_FRONT_RIGHT) ? VEHICLE_MODEL_INFO_WHEELS_FRONT : VEHICLE_MODEL_INFO_WHEELS_REAR, offsetX, offsetY, offsetZ)) {
        return false;
    }

    new const
        Float:side = floatabs(offsetX)
    ;

    return GetVehicleOffsetPos(vehicleid, (wheel == VEHICLE_CORNER_FRONT_LEFT || wheel == VEHICLE_CORNER_REAR_LEFT) ? -side : side, offsetY, offsetZ, x, y, z);
}
