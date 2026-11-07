#if defined _INC_SSI_VEHICLE_SPEED_CAMERA
    #endinput
#endif
#define _INC_SSI_VEHICLE_SPEED_CAMERA

#include <open.mp>
#include <streamer>
#include <SSI_Vehicle\math>
#include <SSI\collection>
#include <SSI\dictionary>

#if defined SPEED_CAMERA_FLASH
    #include <SSI\inline>
    #include <SSI_Extra\inline-timers>
#endif

#include <SSI\hooks>

/**
 * Speed cameras: a pole by the road and a sphere of streamer area around it.
 * A driver who enters the sphere faster than the limit of the camera is caught,
 * and the script is told.
 *
 *     new const
 *         SpeedCamera:cameraid = CreateSpeedCamera(1363.0, -1288.3, 13.3, 180.0, 60.0)
 *     ;
 *
 *     hook OnPlayerTriggeredSpeedCamera(playerid, SpeedCamera:cameraid, Float:speed, Float:limit) {
 *         GivePlayerMoney(playerid, -100);
 *
 *         return 1;
 *     }
 *
 * - The speed is read once, as the vehicle enters, so a pass is counted once.
 * - Speeds are `GetVehicleSpeed` with the multiplier of
 *   `SetSpeedCameraMultiplier`, `VEHICLE_SPEED_MULTIPLIER` until the script
 *   sets another, and limits are written in the same unit.
 * - `OnPlayerTriggerSpeedCamera` can refuse a pass, as for a police car.
 * - With `SPEED_CAMERA_FLASH` defined before the include, the screen of a
 *   driver caught flashes white for `SPEED_CAMERA_FLASH_TIME` milliseconds.
 */

/**
 * # Header
 */

#if !defined MAX_SPEED_CAMERAS
    #define MAX_SPEED_CAMERAS (SpeedCamera:256)
#endif

#if !defined SPEED_CAMERA_MODEL
    #define SPEED_CAMERA_MODEL (18880)
#endif

#if !defined SPEED_CAMERA_RANGE
    #define SPEED_CAMERA_RANGE (12.0)
#endif

#if defined SPEED_CAMERA_FLASH
    #if !defined SPEED_CAMERA_FLASH_TIME
        #define SPEED_CAMERA_FLASH_TIME (150)
    #endif

    #if !defined SPEED_CAMERA_FLASH_COLOUR
        #define SPEED_CAMERA_FLASH_COLOUR (0xFFFFFFAA)
    #endif
#endif

#define INVALID_SPEED_CAMERA_ID (SpeedCamera:-1)

static enum E_SPEED_CAMERA_DATA {
    Float:E_SPEED_CAMERA_X,
    Float:E_SPEED_CAMERA_Y,
    Float:E_SPEED_CAMERA_Z,
    Float:E_SPEED_CAMERA_LIMIT,
    STREAMER_TAG_OBJECT:E_SPEED_CAMERA_OBJECT,
    STREAMER_TAG_AREA:E_SPEED_CAMERA_AREA
};

new
    Collection:SpeedCamera<MAX_SPEED_CAMERAS>
;

static
    gSpeedCameraData[MAX_SPEED_CAMERAS][E_SPEED_CAMERA_DATA],
    Dictionary:SpeedCameraByArea<MAX_SPEED_CAMERAS>,
    Float:gSpeedCameraMultiplier = VEHICLE_SPEED_MULTIPLIER
;

/**
 * # Functions
 */

/**
 * @brief      Put a speed camera by the road.
 *
 * @param      x           X of the pole.
 * @param      y           Y of the pole.
 * @param      z           Z of the ground at the pole.
 * @param      angle       Where the camera faces.
 * @param      limit       Speed above which a driver is caught, in the units
 *                         of `SetSpeedCameraMultiplier`.
 * @param      range       Radius of the sphere watched.
 * @param      modelid     Object of the pole.
 * @param      worldid     Virtual world, `-1` for every one.
 * @param      interiorid  Interior, `-1` for every one.
 *
 * @return     - the camera
 *             - `INVALID_SPEED_CAMERA_ID` when `MAX_SPEED_CAMERAS` already
 *               exist
 */
forward SpeedCamera:CreateSpeedCamera(Float:x, Float:y, Float:z, Float:angle, Float:limit, Float:range = SPEED_CAMERA_RANGE, modelid = SPEED_CAMERA_MODEL, worldid = -1, interiorid = -1);

/**
 * @brief      Take a speed camera away.
 *
 * @param      cameraid  The camera.
 *
 * @return     - `true` it was taken away
 *             - `false` `cameraid` is not a camera
 */
forward bool:DestroySpeedCamera(SpeedCamera:cameraid);

/**
 * @brief      Whether a speed camera exists.
 *
 * @param      cameraid  The camera.
 */
forward bool:IsValidSpeedCamera(SpeedCamera:cameraid);

/**
 * @brief      Change the limit of a speed camera.
 *
 * @param      cameraid  The camera.
 * @param      limit     The new limit.
 *
 * @return     - `true` it was changed
 *             - `false` `cameraid` is not a camera
 */
forward bool:SetSpeedCameraLimit(SpeedCamera:cameraid, Float:limit);

/**
 * @brief      The limit of a speed camera.
 *
 * @param      cameraid  The camera.
 *
 * @return     - the limit
 *             - `0.0` when `cameraid` is not a camera
 */
forward Float:GetSpeedCameraLimit(SpeedCamera:cameraid);

/**
 * @brief      Where a speed camera stands.
 *
 * @param      cameraid  The camera.
 * @param      x         Where its X goes.
 * @param      y         Where its Y goes.
 * @param      z         Where its Z goes.
 *
 * @return     - `true` it was read
 *             - `false` `cameraid` is not a camera
 */
forward bool:GetSpeedCameraPos(SpeedCamera:cameraid, &Float:x, &Float:y, &Float:z);

/**
 * @brief      Set the unit of every speed camera, as the multiplier of
 *             `GetVehicleSpeed`.
 *
 * Limits are not converted, so set it before creating cameras.
 *
 * @param      multiplier  `VEHICLE_SPEED_KMH`, `VEHICLE_SPEED_MPH`, or the
 *                         factor of any other unit.
 */
forward SetSpeedCameraMultiplier(Float:multiplier);

/**
 * @brief      The multiplier speed cameras read speeds with.
 */
forward Float:GetSpeedCameraMultiplier();

/**
 * # Events
 */

/**
 * @brief      A driver is about to be caught passing a speed camera
 *             faster than its limit.
 *
 * @param      playerid  The driver.
 * @param      cameraid  The camera.
 * @param      speed     Their speed.
 * @param      limit     The limit of the camera.
 *
 * @return     - `0` they are caught
 *             - `1` they are not
 */
event OnPlayerTriggerSpeedCamera(playerid, SpeedCamera:cameraid, Float:speed, Float:limit);

/**
 * @brief      A driver was caught by a speed camera.
 *
 * The return value is not used.
 *
 * @param      playerid  The driver.
 * @param      cameraid  The camera.
 * @param      speed     Their speed.
 * @param      limit     The limit of the camera.
 */
event OnPlayerTriggeredSpeedCamera(playerid, SpeedCamera:cameraid, Float:speed, Float:limit);

/**
 * # Speed Camera
 */

stock SpeedCamera:CreateSpeedCamera(Float:x, Float:y, Float:z, Float:angle, Float:limit, Float:range = SPEED_CAMERA_RANGE, modelid = SPEED_CAMERA_MODEL, worldid = -1, interiorid = -1) {
    new const
        SpeedCamera:cameraid = Collection_Alloc(SpeedCamera)
    ;

    if (cameraid == INVALID_SPEED_CAMERA_ID) {
        return INVALID_SPEED_CAMERA_ID;
    }

    gSpeedCameraData[cameraid][E_SPEED_CAMERA_X] = x;
    gSpeedCameraData[cameraid][E_SPEED_CAMERA_Y] = y;
    gSpeedCameraData[cameraid][E_SPEED_CAMERA_Z] = z;
    gSpeedCameraData[cameraid][E_SPEED_CAMERA_LIMIT] = limit;
    gSpeedCameraData[cameraid][E_SPEED_CAMERA_OBJECT] = CreateDynamicObject(modelid, x, y, z, 0.0, 0.0, angle, worldid, interiorid);
    gSpeedCameraData[cameraid][E_SPEED_CAMERA_AREA] = CreateDynamicSphere(x, y, z, range, worldid, interiorid);

    Dictionary_Set(SpeedCameraByArea, _:gSpeedCameraData[cameraid][E_SPEED_CAMERA_AREA], _:cameraid);

    return cameraid;
}

stock bool:DestroySpeedCamera(SpeedCamera:cameraid) {
    if (!Collection_Contains(SpeedCamera, cameraid)) {
        return false;
    }

    Dictionary_Remove(SpeedCameraByArea, _:gSpeedCameraData[cameraid][E_SPEED_CAMERA_AREA]);
    DestroyDynamicArea(gSpeedCameraData[cameraid][E_SPEED_CAMERA_AREA]);
    DestroyDynamicObject(gSpeedCameraData[cameraid][E_SPEED_CAMERA_OBJECT]);
    Collection_Remove(SpeedCamera, cameraid);

    return true;
}

stock bool:IsValidSpeedCamera(SpeedCamera:cameraid) {
    return Collection_Contains(SpeedCamera, cameraid);
}

stock bool:SetSpeedCameraLimit(SpeedCamera:cameraid, Float:limit) {
    if (!Collection_Contains(SpeedCamera, cameraid)) {
        return false;
    }

    gSpeedCameraData[cameraid][E_SPEED_CAMERA_LIMIT] = limit;

    return true;
}

stock Float:GetSpeedCameraLimit(SpeedCamera:cameraid) {
    if (!Collection_Contains(SpeedCamera, cameraid)) {
        return 0.0;
    }

    return gSpeedCameraData[cameraid][E_SPEED_CAMERA_LIMIT];
}

stock bool:GetSpeedCameraPos(SpeedCamera:cameraid, &Float:x, &Float:y, &Float:z) {
    if (!Collection_Contains(SpeedCamera, cameraid)) {
        return false;
    }

    x = gSpeedCameraData[cameraid][E_SPEED_CAMERA_X];
    y = gSpeedCameraData[cameraid][E_SPEED_CAMERA_Y];
    z = gSpeedCameraData[cameraid][E_SPEED_CAMERA_Z];

    return true;
}

stock SetSpeedCameraMultiplier(Float:multiplier) {
    gSpeedCameraMultiplier = multiplier;
}

stock Float:GetSpeedCameraMultiplier() {
    return gSpeedCameraMultiplier;
}

/**
 * # Calls
 */

hook OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid) {
    new
        SpeedCamera:cameraid
    ;

    if (!Dictionary_Get(SpeedCameraByArea, _:areaid, cameraid)) {
        return 1;
    }

    if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
        return 1;
    }

    new const
        Float:speed = GetVehicleSpeed(GetPlayerVehicleID(playerid), gSpeedCameraMultiplier),
        Float:limit = gSpeedCameraData[cameraid][E_SPEED_CAMERA_LIMIT]
    ;

    if (speed <= limit) {
        return 1;
    }

    if (call OnPlayerTriggerSpeedCamera(playerid, cameraid, speed, limit)) {
        return 1;
    }

    #if defined SPEED_CAMERA_FLASH
        new const
            PlayerText:pt = CreatePlayerTextDraw(playerid, 0.0, 0.0, "_")
        ;

        PlayerTextDrawLetterSize(playerid, pt, 0.0, 50.0);
        PlayerTextDrawTextSize(playerid, pt, 640.0, 0.0);
        PlayerTextDrawUseBox(playerid, pt, true);
        PlayerTextDrawBoxColour(playerid, pt, SPEED_CAMERA_FLASH_COLOUR);
        PlayerTextDrawShow(playerid, pt);

        inline OnFlashed() {
            PlayerTextDrawDestroy(playerid, pt);
        }

        Timer_StartInline(EBC(playerid, using inline OnFlashed), SPEED_CAMERA_FLASH_TIME, 1);
    #endif

    call OnPlayerTriggeredSpeedCamera(playerid, cameraid, speed, limit);

    return 1;
}
