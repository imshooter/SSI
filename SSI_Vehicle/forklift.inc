#if defined _INC_SSI_VEHICLE_FORKLIFT
    #endinput
#endif
#define _INC_SSI_VEHICLE_FORKLIFT

/**
 * Crates a forklift lifts, carries and stacks. A crate is a streamer object
 * with the collision of its model in 3DAndreas, so crates stack on each other
 * and none is put down inside a wall.
 *
 *     new const
 *         Crate:crateid = CreateCrate(1558, 2795.0, -2417.0, 12.55, 0.0)
 *     ;
 *
 * - The client attaches an object to a forklift by its fork carriage, which
 *   sits `FORKLIFT_FRAME_Y` ahead of the position of the vehicle and
 *   `FORKLIFT_FRAME_Z` above it with the forks down. A crate on the forks
 *   rises and falls with them once attached.
 * - The client does not report how high the forks are. The library works it
 *   out from how long the driver holds the fork keys, clamped at both ends,
 *   where the real forks stop too.
 * - A crate is lifted when the forks rise under it: centred on them, turned
 *   with the forklift, and at the height of the forks. It then sits straight
 *   against the mast. Only the top crate of a stack is lifted. It is put down
 *   when the forks lower it onto the ground or onto another crate, which it is
 *   lined up with.
 * - The game lets a vehicle push some models, which the server never learns.
 *   A crate a driven forklift touches without lifting goes back to its place
 *   once the forklift leaves it.
 * - A crate on a forklift that respawns, dies or is destroyed goes back to
 *   where it was lifted from. When something stands there now, it is put
 *   down under the forks instead.
 * - `Crate` is a collection to walk with `foreach`. Only this library changes
 *   it.
 *
 * `streamer` and `SSI_Extra\inline-timers` include `SSI\hooks` themselves, so
 * they come first.
 */
#include <open.mp>
#include <streamer>
#include <3DAndreas>
#include <SSI_Extra\inline-timers>

#include <SSI\bits>
#include <SSI\collection>
#include <SSI\dictionary>
#include <SSI\hooks>

/**
 * # Header
 */

#if !defined MAX_CRATES
    #define MAX_CRATES (Crate:1024)
#endif

#if !defined FORKLIFT_MODEL
    #define FORKLIFT_MODEL (530)
#endif

#if !defined FORKLIFT_FRAME_Y
    #define FORKLIFT_FRAME_Y (1.0)
#endif

#if !defined FORKLIFT_FRAME_Z
    #define FORKLIFT_FRAME_Z (-0.395)
#endif

#if !defined FORKLIFT_FORK_TOP
    #define FORKLIFT_FORK_TOP (-0.178)
#endif

#if !defined FORKLIFT_SEAT_X
    #define FORKLIFT_SEAT_X (-0.014)
#endif

#if !defined FORKLIFT_MAST_Y
    #define FORKLIFT_MAST_Y (1.12)
#endif

#if !defined FORKLIFT_FORK_LENGTH
    #define FORKLIFT_FORK_LENGTH (1.0)
#endif

#if !defined FORKLIFT_TRAVEL
    #define FORKLIFT_TRAVEL (1.80)
#endif

#if !defined FORKLIFT_UP_SPEED
    #define FORKLIFT_UP_SPEED (0.30)
#endif

#if !defined FORKLIFT_DOWN_SPEED
    #define FORKLIFT_DOWN_SPEED (0.64)
#endif

#if !defined FORKLIFT_REACH_SIDE
    #define FORKLIFT_REACH_SIDE (0.30)
#endif

#if !defined FORKLIFT_REACH_TURN
    #define FORKLIFT_REACH_TURN (15.0)
#endif

#if !defined FORKLIFT_REACH_HEIGHT
    #define FORKLIFT_REACH_HEIGHT (0.45)
#endif

#if !defined FORKLIFT_DROP_GAP
    #define FORKLIFT_DROP_GAP (0.20)
#endif

#if !defined FORKLIFT_STACK_SNAP
    #define FORKLIFT_STACK_SNAP (0.35)
#endif

#if !defined FORKLIFT_STEP
    #define FORKLIFT_STEP (100)
#endif

#if !defined FORKLIFT_TOUCH_STEP
    #define FORKLIFT_TOUCH_STEP (500)
#endif

#if !defined FORKLIFT_TOUCH_MARGIN
    #define FORKLIFT_TOUCH_MARGIN (0.15)
#endif

#define FORKLIFT_REACH_HITS (8)
#define FORKLIFT_TOUCH_HITS (16)

#define INVALID_CRATE_ID (Crate:-1)

static enum _:E_CRATE_DATA {
    E_CRATE_MODEL,
    STREAMER_TAG_OBJECT:E_CRATE_OBJECT,
    Physic:E_CRATE_PHYSIC,
    Float:E_CRATE_X,
    Float:E_CRATE_Y,
    Float:E_CRATE_Z,
    Float:E_CRATE_ANGLE,
    E_CRATE_TOUCHED,
    E_CRATE_WORLD,
    E_CRATE_INTERIOR,
    Float:E_CRATE_BOTTOM,
    Float:E_CRATE_TOP,
    Float:E_CRATE_WIDTH,
    Float:E_CRATE_DEPTH,
    E_CRATE_VEHICLE,
    Float:E_CRATE_OFFSET_X,
    Float:E_CRATE_OFFSET_Y,
    Float:E_CRATE_TURN,
    Crate:E_CRATE_BELOW,
    Crate:E_CRATE_ABOVE
};

static enum _:E_FORKLIFT_DATA {
    Crate:E_FORKLIFT_CRATE,
    Float:E_FORKLIFT_HEIGHT,
    E_FORKLIFT_DIRECTION,
    E_FORKLIFT_MOVED,
    Timer:E_FORKLIFT_TIMER,
    Timer:E_FORKLIFT_TOUCH_TIMER
};

new
    Collection:Crate<MAX_CRATES>
;

static
    gCrateData[MAX_CRATES][E_CRATE_DATA],
    Dictionary:CrateByPhysic<MAX_CRATES>,
    Bits:CrateTouched<MAX_CRATES>,
    gForkliftData[MAX_VEHICLES][E_FORKLIFT_DATA],
    gForkliftDriven[MAX_PLAYERS]
;

/**
 * # Functions
 */

/**
 * @brief      Put a crate on the ground.
 *
 * @param      modelid     Model of the crate, which needs a collision.
 * @param      x           Centre on the X axis.
 * @param      y           Centre on the Y axis.
 * @param      z           Height of its bottom, such as the ground.
 * @param      angle       Its heading.
 * @param      worldid     Virtual world.
 * @param      interiorid  Interior.
 *
 * @return     - the crate
 *             - `INVALID_CRATE_ID` when:
 *                 + `MAX_CRATES` already exist
 *                 + the model has no collision
 */
forward Crate:CreateCrate(modelid, Float:x, Float:y, Float:z, Float:angle, worldid = 0, interiorid = 0);

/**
 * @brief      Put a crate on top of another, lined up with it.
 *
 * @param      belowid  Crate to stack on, on the ground or on a stack.
 * @param      modelid  Model of the new crate.
 *
 * @return     - the crate
 *             - `INVALID_CRATE_ID` when:
 *                 + `belowid` is not a crate, is carried or has a crate on it
 *                 + `MAX_CRATES` already exist
 *                 + the model has no collision
 */
forward Crate:StackCrate(Crate:belowid, modelid);

/**
 * @brief      Destroy a crate, also off the forks. A crate stacked on it stays
 *             where it is.
 *
 * @param      crateid  Crate to destroy.
 *
 * @return     - `true` it was destroyed
 *             - `false` `crateid` is not a crate
 */
forward bool:DestroyCrate(Crate:crateid);

/**
 * @brief      Whether a crate exists.
 *
 * @param      crateid  Crate to check.
 *
 * @return     - `true` it exists
 *             - `false` it does not
 */
forward bool:IsValidCrate(Crate:crateid);

/**
 * @brief      The streamer object of a crate. It changes each time the crate
 *             is lifted or put down.
 *
 * @param      crateid  Crate to read.
 *
 * @return     - the object
 *             - `INVALID_STREAMER_ID` `crateid` is not a crate
 */
forward STREAMER_TAG_OBJECT:GetCrateObject(Crate:crateid);

/**
 * @brief      The forklift carrying a crate.
 *
 * @param      crateid  Crate to read.
 *
 * @return     - the vehicle
 *             - `INVALID_VEHICLE_ID` it is on the ground or on another crate,
 *               or `crateid` is not a crate
 */
forward GetCrateVehicle(Crate:crateid);

/**
 * @brief      The crate a forklift carries.
 *
 * @param      vehicleid  Vehicle to read.
 *
 * @return     - the crate
 *             - `INVALID_CRATE_ID` it carries none
 */
forward Crate:GetVehicleCrate(vehicleid);

/**
 * @brief      The crate under a crate in a stack.
 *
 * @param      crateid  Crate to read.
 *
 * @return     - the crate under it
 *             - `INVALID_CRATE_ID` it is on the ground or carried, or
 *               `crateid` is not a crate
 */
forward Crate:GetCrateBelow(Crate:crateid);

/**
 * @brief      The crate on top of a crate in a stack.
 *
 * @param      crateid  Crate to read.
 *
 * @return     - the crate on it
 *             - `INVALID_CRATE_ID` nothing is on it, or `crateid` is not a
 *               crate
 */
forward Crate:GetCrateAbove(Crate:crateid);

/**
 * @brief      How high the forks of a forklift are thought to be, from how
 *             long the fork keys were held.
 *
 * @param      vehicleid  Vehicle to read.
 *
 * @return     - the height above the lowest, from `0.0` to `FORKLIFT_TRAVEL`
 */
forward Float:GetForkliftHeight(vehicleid);

/**
 * # Events
 */

/**
 * @brief      The forks of a forklift are rising under a crate.
 *
 * @param      crateid    The crate.
 * @param      vehicleid  The forklift.
 *
 * @return     - `0` it is lifted
 *             - `1` it is not
 */
event OnCrateLift(Crate:crateid, vehicleid);

/**
 * @brief      A forklift lifted a crate.
 *
 * @param      crateid    The crate.
 * @param      vehicleid  The forklift.
 */
event OnCrateLifted(Crate:crateid, vehicleid);

/**
 * @brief      A forklift is lowering a crate onto the ground or another crate.
 *             It is asked again while the forks keep going down.
 *
 * @param      crateid    The crate.
 * @param      vehicleid  The forklift.
 * @param      belowid    The crate it lands on, or `INVALID_CRATE_ID`.
 *
 * @return     - `0` it is put down
 *             - `1` it stays on the forks
 */
event OnCrateDrop(Crate:crateid, vehicleid, Crate:belowid);

/**
 * @brief      A crate came off the forks, lowered, or put down under them
 *             because the forklift is gone and its place is taken.
 *
 * @param      crateid    The crate.
 * @param      vehicleid  The forklift.
 * @param      belowid    The crate it lies on, or `INVALID_CRATE_ID`.
 */
event OnCrateDropped(Crate:crateid, vehicleid, Crate:belowid);

/**
 * @brief      A crate went back to where it was lifted from, because its
 *             forklift respawned, died or was destroyed.
 *
 * @param      crateid    The crate.
 * @param      vehicleid  The forklift.
 */
event OnCrateReturned(Crate:crateid, vehicleid);

/**
 * # Internal
 */

static stock PlaceCrateInternal(Crate:crateid, Float:x, Float:y, Float:z, Float:angle, Crate:belowid) {
    new const
        modelid = gCrateData[crateid][E_CRATE_MODEL],
        worldid = gCrateData[crateid][E_CRATE_WORLD],
        interiorid = gCrateData[crateid][E_CRATE_INTERIOR],
        Float:originZ = z - gCrateData[crateid][E_CRATE_BOTTOM],
        Physic:physicid = A3D_CreateStaticObject(modelid, x, y, originZ, 0.0, 0.0, angle, worldid, interiorid)
    ;

    gCrateData[crateid][E_CRATE_OBJECT] = CreateDynamicObject(modelid, x, y, originZ, 0.0, 0.0, angle, worldid, interiorid);
    gCrateData[crateid][E_CRATE_PHYSIC] = physicid;
    gCrateData[crateid][E_CRATE_X] = x;
    gCrateData[crateid][E_CRATE_Y] = y;
    gCrateData[crateid][E_CRATE_Z] = originZ;
    gCrateData[crateid][E_CRATE_ANGLE] = angle;
    gCrateData[crateid][E_CRATE_VEHICLE] = INVALID_VEHICLE_ID;
    gCrateData[crateid][E_CRATE_BELOW] = belowid;
    gCrateData[crateid][E_CRATE_ABOVE] = INVALID_CRATE_ID;

    Dictionary_Set(CrateByPhysic, _:physicid, _:crateid);

    if (belowid != INVALID_CRATE_ID) {
        gCrateData[belowid][E_CRATE_ABOVE] = crateid;
    }
}

static stock RestoreCrateInternal(Crate:crateid) {
    DestroyDynamicObject(gCrateData[crateid][E_CRATE_OBJECT]);

    gCrateData[crateid][E_CRATE_OBJECT] = CreateDynamicObject(gCrateData[crateid][E_CRATE_MODEL], gCrateData[crateid][E_CRATE_X], gCrateData[crateid][E_CRATE_Y], gCrateData[crateid][E_CRATE_Z], 0.0, 0.0, gCrateData[crateid][E_CRATE_ANGLE], gCrateData[crateid][E_CRATE_WORLD], gCrateData[crateid][E_CRATE_INTERIOR]);
}

static stock Crate:GetPhysicCrateInternal(hitid) {
    new
        crateid = _:INVALID_CRATE_ID
    ;

    Dictionary_Get(CrateByPhysic, hitid, crateid);

    return Crate:crateid;
}

static stock UpdateForkInternal(vehicleid) {
    new const
        now = GetTickCount(),
        direction = gForkliftData[vehicleid][E_FORKLIFT_DIRECTION],
        Float:speed = (direction > 0) ? FORKLIFT_UP_SPEED : FORKLIFT_DOWN_SPEED,
        Float:height = gForkliftData[vehicleid][E_FORKLIFT_HEIGHT] + float(direction) * speed * float(now - gForkliftData[vehicleid][E_FORKLIFT_MOVED]) / 1000.0
    ;

    gForkliftData[vehicleid][E_FORKLIFT_HEIGHT] = (height < 0.0) ? 0.0 : ((height > FORKLIFT_TRAVEL) ? FORKLIFT_TRAVEL : height);
    gForkliftData[vehicleid][E_FORKLIFT_MOVED] = now;
}

static stock bool:LiftCrateInternal(vehicleid) {
    new
        Float:angle,
        Float:x,
        Float:y,
        Float:z,
        A3D_HIT:types[FORKLIFT_REACH_HITS],
        hits[FORKLIFT_REACH_HITS]
    ;

    GetVehicleZAngle(vehicleid, angle);

    new const
        Float:forkTop = FORKLIFT_FRAME_Z + FORKLIFT_FORK_TOP + gForkliftData[vehicleid][E_FORKLIFT_HEIGHT]
    ;

    A3D_GetVehicleOffsetPosition(vehicleid, 0.0, FORKLIFT_MAST_Y + FORKLIFT_FORK_LENGTH * 0.5, forkTop + 0.5, x, y, z);

    new const
        count = A3D_OverlapBox(1.0, FORKLIFT_FORK_LENGTH, 1.0, x, y, z, 0.0, 0.0, angle, types, hits, .worldid = GetVehicleVirtualWorld(vehicleid), .flags = A3D_COLLIDE_STATIC, .interiorid = GetVehicleInterior(vehicleid))
    ;

    for (new i; i != count; ++i) {
        new const
            Crate:crateid = GetPhysicCrateInternal(hits[i])
        ;

        if (crateid == INVALID_CRATE_ID) {
            continue;
        }

        if (gCrateData[crateid][E_CRATE_ABOVE] != INVALID_CRATE_ID) {
            continue;
        }

        new
            Float:offsetX,
            Float:offsetY,
            Float:offsetZ
        ;

        A3D_GetVehiclePositionOffset(vehicleid, gCrateData[crateid][E_CRATE_X], gCrateData[crateid][E_CRATE_Y], gCrateData[crateid][E_CRATE_Z], offsetX, offsetY, offsetZ);

        new const
            Float:turn = gCrateData[crateid][E_CRATE_ANGLE] - angle,
            quarter = floatround(turn / 90.0),
            Float:depth = (quarter & 1) ? gCrateData[crateid][E_CRATE_WIDTH] : gCrateData[crateid][E_CRATE_DEPTH],
            Float:rear = offsetY - depth,
            Float:bottom = offsetZ + gCrateData[crateid][E_CRATE_BOTTOM]
        ;

        if (floatabs(turn - float(quarter) * 90.0) > FORKLIFT_REACH_TURN) {
            continue;
        }

        if (floatabs(offsetX) > FORKLIFT_REACH_SIDE) {
            continue;
        }

        if (!(FORKLIFT_MAST_Y - 0.15 <= rear <= FORKLIFT_MAST_Y + FORKLIFT_FORK_LENGTH * 0.5)) {
            continue;
        }

        if (!(bottom - 0.25 <= forkTop <= bottom + FORKLIFT_REACH_HEIGHT)) {
            continue;
        }

        if (call OnCrateLift(crateid, vehicleid)) {
            return false;
        }

        new const
            Crate:belowid = gCrateData[crateid][E_CRATE_BELOW],
            Float:seatY = FORKLIFT_MAST_Y + depth,
            Float:seatTurn = float(quarter) * 90.0
        ;

        if (belowid != INVALID_CRATE_ID) {
            gCrateData[belowid][E_CRATE_ABOVE] = INVALID_CRATE_ID;
        }

        Bits_Vet(CrateTouched, crateid);
        Dictionary_Remove(CrateByPhysic, _:gCrateData[crateid][E_CRATE_PHYSIC]);
        A3D_DestroyObject(gCrateData[crateid][E_CRATE_PHYSIC]);
        AttachDynamicObjectToVehicle(gCrateData[crateid][E_CRATE_OBJECT], vehicleid, FORKLIFT_SEAT_X, seatY - FORKLIFT_FRAME_Y, FORKLIFT_FORK_TOP - gCrateData[crateid][E_CRATE_BOTTOM], 0.0, 0.0, seatTurn);

        gCrateData[crateid][E_CRATE_PHYSIC] = INVALID_PHYSIC_ID;
        gCrateData[crateid][E_CRATE_VEHICLE] = vehicleid;
        gCrateData[crateid][E_CRATE_OFFSET_X] = FORKLIFT_SEAT_X;
        gCrateData[crateid][E_CRATE_OFFSET_Y] = seatY;
        gCrateData[crateid][E_CRATE_TURN] = seatTurn;
        gCrateData[crateid][E_CRATE_BELOW] = INVALID_CRATE_ID;
        gForkliftData[vehicleid][E_FORKLIFT_CRATE] = crateid;

        call OnCrateLifted(crateid, vehicleid);

        return true;
    }

    return false;
}

static stock bool:LowerCrateInternal(vehicleid, bool:forced) {
    new const
        Crate:crateid = gForkliftData[vehicleid][E_FORKLIFT_CRATE],
        worldid = gCrateData[crateid][E_CRATE_WORLD],
        interiorid = gCrateData[crateid][E_CRATE_INTERIOR],
        Float:height = gForkliftData[vehicleid][E_FORKLIFT_HEIGHT]
    ;

    new
        Float:angle,
        Float:x,
        Float:y,
        Float:z,
        Float:hitX,
        Float:hitY,
        Float:hitZ,
        A3D_HIT:type,
        hitid
    ;

    GetVehicleZAngle(vehicleid, angle);
    A3D_GetVehicleOffsetPosition(vehicleid, gCrateData[crateid][E_CRATE_OFFSET_X], gCrateData[crateid][E_CRATE_OFFSET_Y], FORKLIFT_FRAME_Z + FORKLIFT_FORK_TOP + height, x, y, z);

    if (!A3D_RayCast(x, y, z + 0.05, x, y, z - FORKLIFT_TRAVEL - 2.0, hitX, hitY, hitZ, type, hitid, .worldid = worldid, .flags = A3D_COLLIDE_MAP | A3D_COLLIDE_STATIC, .interiorid = interiorid)) {
        if (!forced) {
            return false;
        }

        hitZ = z;
    }

    if (!forced && z - hitZ > FORKLIFT_DROP_GAP && height > 0.0) {
        return false;
    }

    new const
        Crate:belowid = (type == A3D_HIT_STATIC) ? GetPhysicCrateInternal(hitid) : INVALID_CRATE_ID,
        Float:turned = angle + gCrateData[crateid][E_CRATE_TURN],
        bool:lined = belowid != INVALID_CRATE_ID && VectorSize(gCrateData[belowid][E_CRATE_X] - x, gCrateData[belowid][E_CRATE_Y] - y, 0.0) <= FORKLIFT_STACK_SNAP,
        Float:crateX = lined ? gCrateData[belowid][E_CRATE_X] : x,
        Float:crateY = lined ? gCrateData[belowid][E_CRATE_Y] : y,
        Float:crateAngle = lined ? gCrateData[belowid][E_CRATE_ANGLE] + float(floatround((turned - gCrateData[belowid][E_CRATE_ANGLE]) / 90.0)) * 90.0 : turned
    ;

    if (!forced && A3D_IsModelColliding(gCrateData[crateid][E_CRATE_MODEL], crateX, crateY, hitZ - gCrateData[crateid][E_CRATE_BOTTOM] + 0.03, 0.0, 0.0, crateAngle, worldid, A3D_COLLIDE_MAP | A3D_COLLIDE_STATIC, interiorid)) {
        return false;
    }

    if (!forced && call OnCrateDrop(crateid, vehicleid, belowid)) {
        return false;
    }

    DestroyDynamicObject(gCrateData[crateid][E_CRATE_OBJECT]);
    PlaceCrateInternal(crateid, crateX, crateY, hitZ, crateAngle, belowid);

    gForkliftData[vehicleid][E_FORKLIFT_CRATE] = INVALID_CRATE_ID;

    call OnCrateDropped(crateid, vehicleid, belowid);

    return true;
}

static stock StepForkliftInternal(vehicleid) {
    UpdateForkInternal(vehicleid);

    new const
        direction = gForkliftData[vehicleid][E_FORKLIFT_DIRECTION],
        bool:carrying = gForkliftData[vehicleid][E_FORKLIFT_CRATE] != INVALID_CRATE_ID
    ;

    if (direction > 0 && !carrying) {
        LiftCrateInternal(vehicleid);
    }

    if (direction < 0 && carrying) {
        LowerCrateInternal(vehicleid, false);
    }
}

static stock MoveForkInternal(vehicleid, direction) {
    inline OnStep() {
        StepForkliftInternal(vehicleid);
    }

    UpdateForkInternal(vehicleid);
    Timer_Stop(gForkliftData[vehicleid][E_FORKLIFT_TIMER]);

    gForkliftData[vehicleid][E_FORKLIFT_DIRECTION] = direction;
    gForkliftData[vehicleid][E_FORKLIFT_TIMER] = (direction == 0)
        ? INVALID_TIMER_ID
        : Timer_StartInline(EBC(Vehicle:vehicleid, using inline OnStep), FORKLIFT_STEP);

    if (direction != 0) {
        StepForkliftInternal(vehicleid);
    }
}

static stock ClearForkliftInternal(vehicleid) {
    if (vehicleid == INVALID_VEHICLE_ID) {
        return;
    }

    gForkliftData[vehicleid][E_FORKLIFT_CRATE] = INVALID_CRATE_ID;
    gForkliftData[vehicleid][E_FORKLIFT_HEIGHT] = 0.0;
    gForkliftData[vehicleid][E_FORKLIFT_DIRECTION] = 0;
    gForkliftData[vehicleid][E_FORKLIFT_MOVED] = 0;
    gForkliftData[vehicleid][E_FORKLIFT_TIMER] = INVALID_TIMER_ID;
    gForkliftData[vehicleid][E_FORKLIFT_TOUCH_TIMER] = INVALID_TIMER_ID;
}

static stock ResetForkliftInternal(vehicleid) {
    new const
        Crate:crateid = gForkliftData[vehicleid][E_FORKLIFT_CRATE]
    ;

    if (crateid != INVALID_CRATE_ID) {
        new const
            worldid = gCrateData[crateid][E_CRATE_WORLD],
            interiorid = gCrateData[crateid][E_CRATE_INTERIOR],
            Float:x = gCrateData[crateid][E_CRATE_X],
            Float:y = gCrateData[crateid][E_CRATE_Y],
            Float:bottom = gCrateData[crateid][E_CRATE_Z] + gCrateData[crateid][E_CRATE_BOTTOM]
        ;

        if (A3D_IsModelColliding(gCrateData[crateid][E_CRATE_MODEL], x, y, gCrateData[crateid][E_CRATE_Z] + 0.03, 0.0, 0.0, gCrateData[crateid][E_CRATE_ANGLE], worldid, A3D_COLLIDE_MAP | A3D_COLLIDE_STATIC, interiorid)) {
            LowerCrateInternal(vehicleid, true);
        } else {
            new
                Float:hitX,
                Float:hitY,
                Float:hitZ,
                A3D_HIT:type,
                hitid
            ;

            new const
                bool:hit = A3D_RayCast(x, y, bottom + 0.05, x, y, bottom - 0.3, hitX, hitY, hitZ, type, hitid, .worldid = worldid, .flags = A3D_COLLIDE_MAP | A3D_COLLIDE_STATIC, .interiorid = interiorid),
                Crate:belowid = (hit && type == A3D_HIT_STATIC) ? GetPhysicCrateInternal(hitid) : INVALID_CRATE_ID
            ;

            DestroyDynamicObject(gCrateData[crateid][E_CRATE_OBJECT]);
            PlaceCrateInternal(crateid, x, y, bottom, gCrateData[crateid][E_CRATE_ANGLE], belowid);

            gForkliftData[vehicleid][E_FORKLIFT_CRATE] = INVALID_CRATE_ID;

            call OnCrateReturned(crateid, vehicleid);
        }
    }

    Timer_Stop(gForkliftData[vehicleid][E_FORKLIFT_TIMER]);

    gForkliftData[vehicleid][E_FORKLIFT_TIMER] = INVALID_TIMER_ID;
    gForkliftData[vehicleid][E_FORKLIFT_DIRECTION] = 0;
    gForkliftData[vehicleid][E_FORKLIFT_HEIGHT] = 0.0;
}

static stock TouchCratesInternal(vehicleid, bool:leaving) {
    new
        Float:sizeX,
        Float:sizeY,
        Float:sizeZ,
        Float:angle,
        Float:x,
        Float:y,
        Float:z,
        A3D_HIT:types[FORKLIFT_TOUCH_HITS],
        hits[FORKLIFT_TOUCH_HITS]
    ;

    GetVehicleModelInfo(FORKLIFT_MODEL, VEHICLE_MODEL_INFO_SIZE, sizeX, sizeY, sizeZ);
    GetVehicleZAngle(vehicleid, angle);
    A3D_GetVehicleOffsetPosition(vehicleid, 0.0, FORKLIFT_FORK_LENGTH * 0.5, 0.0, x, y, z);

    new const
        now = GetTickCount(),
        count = A3D_OverlapBox(sizeX + FORKLIFT_TOUCH_MARGIN * 2.0, sizeY + FORKLIFT_FORK_LENGTH + FORKLIFT_TOUCH_MARGIN * 2.0, sizeZ + FORKLIFT_TOUCH_MARGIN * 2.0, x, y, z, 0.0, 0.0, angle, types, hits, .worldid = GetVehicleVirtualWorld(vehicleid), .flags = A3D_COLLIDE_STATIC, .interiorid = GetVehicleInterior(vehicleid))
    ;

    for (new i; i != count; ++i) {
        new const
            Crate:crateid = GetPhysicCrateInternal(hits[i])
        ;

        if (crateid != INVALID_CRATE_ID) {
            gCrateData[crateid][E_CRATE_TOUCHED] = now;
            Bits_Let(CrateTouched, crateid);
        }
    }

    foreach (new Crate:crateid : Bits(CrateTouched)) {
        if (leaving || now - gCrateData[crateid][E_CRATE_TOUCHED] > FORKLIFT_TOUCH_STEP * 2) {
            Bits_Vet(CrateTouched, crateid);
            RestoreCrateInternal(crateid);
        }
    }
}

static stock StopDrivingInternal(playerid) {
    new const
        vehicleid = gForkliftDriven[playerid]
    ;

    if (vehicleid == INVALID_VEHICLE_ID) {
        return;
    }

    MoveForkInternal(vehicleid, 0);
    Timer_Stop(gForkliftData[vehicleid][E_FORKLIFT_TOUCH_TIMER]);
    TouchCratesInternal(vehicleid, true);

    gForkliftData[vehicleid][E_FORKLIFT_TOUCH_TIMER] = INVALID_TIMER_ID;
    gForkliftDriven[playerid] = INVALID_VEHICLE_ID;
}

/**
 * # Crate
 */

static stock Crate:AllocCrateInternal(modelid, worldid, interiorid) {
    new
        Float:minX,
        Float:minY,
        Float:minZ,
        Float:maxX,
        Float:maxY,
        Float:maxZ
    ;

    if (!A3D_GetModelBoundingBox(modelid, minX, minY, minZ, maxX, maxY, maxZ)) {
        return INVALID_CRATE_ID;
    }

    new const
        Crate:crateid = Collection_Alloc(Crate)
    ;

    if (crateid == INVALID_CRATE_ID) {
        return INVALID_CRATE_ID;
    }

    gCrateData[crateid][E_CRATE_MODEL] = modelid;
    gCrateData[crateid][E_CRATE_WORLD] = worldid;
    gCrateData[crateid][E_CRATE_INTERIOR] = interiorid;
    gCrateData[crateid][E_CRATE_BOTTOM] = minZ;
    gCrateData[crateid][E_CRATE_TOP] = maxZ;
    gCrateData[crateid][E_CRATE_WIDTH] = (maxX - minX) * 0.5;
    gCrateData[crateid][E_CRATE_DEPTH] = (maxY - minY) * 0.5;

    return crateid;
}

stock Crate:CreateCrate(modelid, Float:x, Float:y, Float:z, Float:angle, worldid = 0, interiorid = 0) {
    new const
        Crate:crateid = AllocCrateInternal(modelid, worldid, interiorid)
    ;

    if (crateid == INVALID_CRATE_ID) {
        return INVALID_CRATE_ID;
    }

    PlaceCrateInternal(crateid, x, y, z, angle, INVALID_CRATE_ID);

    return crateid;
}

stock Crate:StackCrate(Crate:belowid, modelid) {
    if (!Collection_Contains(Crate, belowid)) {
        return INVALID_CRATE_ID;
    }

    if (gCrateData[belowid][E_CRATE_VEHICLE] != INVALID_VEHICLE_ID) {
        return INVALID_CRATE_ID;
    }

    if (gCrateData[belowid][E_CRATE_ABOVE] != INVALID_CRATE_ID) {
        return INVALID_CRATE_ID;
    }

    new const
        Crate:crateid = AllocCrateInternal(modelid, gCrateData[belowid][E_CRATE_WORLD], gCrateData[belowid][E_CRATE_INTERIOR])
    ;

    if (crateid == INVALID_CRATE_ID) {
        return INVALID_CRATE_ID;
    }

    PlaceCrateInternal(crateid, gCrateData[belowid][E_CRATE_X], gCrateData[belowid][E_CRATE_Y], gCrateData[belowid][E_CRATE_Z] + gCrateData[belowid][E_CRATE_TOP], gCrateData[belowid][E_CRATE_ANGLE], belowid);

    return crateid;
}

stock bool:DestroyCrate(Crate:crateid) {
    if (!Collection_Contains(Crate, crateid)) {
        return false;
    }

    new const
        vehicleid = gCrateData[crateid][E_CRATE_VEHICLE],
        Crate:belowid = gCrateData[crateid][E_CRATE_BELOW],
        Crate:aboveid = gCrateData[crateid][E_CRATE_ABOVE]
    ;

    if (vehicleid != INVALID_VEHICLE_ID) {
        gForkliftData[vehicleid][E_FORKLIFT_CRATE] = INVALID_CRATE_ID;
    }

    if (belowid != INVALID_CRATE_ID) {
        gCrateData[belowid][E_CRATE_ABOVE] = INVALID_CRATE_ID;
    }

    if (aboveid != INVALID_CRATE_ID) {
        gCrateData[aboveid][E_CRATE_BELOW] = INVALID_CRATE_ID;
    }

    if (gCrateData[crateid][E_CRATE_PHYSIC] != INVALID_PHYSIC_ID) {
        Dictionary_Remove(CrateByPhysic, _:gCrateData[crateid][E_CRATE_PHYSIC]);
        A3D_DestroyObject(gCrateData[crateid][E_CRATE_PHYSIC]);
    }

    Bits_Vet(CrateTouched, crateid);
    DestroyDynamicObject(gCrateData[crateid][E_CRATE_OBJECT]);
    Collection_Remove(Crate, crateid);

    return true;
}

stock bool:IsValidCrate(Crate:crateid) {
    return Collection_Contains(Crate, crateid);
}

stock STREAMER_TAG_OBJECT:GetCrateObject(Crate:crateid) {
    if (!Collection_Contains(Crate, crateid)) {
        return STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
    }

    return gCrateData[crateid][E_CRATE_OBJECT];
}

stock GetCrateVehicle(Crate:crateid) {
    if (!Collection_Contains(Crate, crateid)) {
        return INVALID_VEHICLE_ID;
    }

    return gCrateData[crateid][E_CRATE_VEHICLE];
}

stock Crate:GetVehicleCrate(vehicleid) {
    if (!(0 <= vehicleid < MAX_VEHICLES)) {
        return INVALID_CRATE_ID;
    }

    return gForkliftData[vehicleid][E_FORKLIFT_CRATE];
}

stock Crate:GetCrateBelow(Crate:crateid) {
    if (!Collection_Contains(Crate, crateid)) {
        return INVALID_CRATE_ID;
    }

    return gCrateData[crateid][E_CRATE_BELOW];
}

stock Crate:GetCrateAbove(Crate:crateid) {
    if (!Collection_Contains(Crate, crateid)) {
        return INVALID_CRATE_ID;
    }

    return gCrateData[crateid][E_CRATE_ABOVE];
}

stock Float:GetForkliftHeight(vehicleid) {
    if (!(0 <= vehicleid < MAX_VEHICLES)) {
        return 0.0;
    }

    return gForkliftData[vehicleid][E_FORKLIFT_HEIGHT];
}

/**
 * # Calls
 */

hook OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys) {
    new const
        vehicleid = gForkliftDriven[playerid]
    ;

    if (vehicleid == INVALID_VEHICLE_ID) {
        return 1;
    }

    new const
        bool:up = (newkeys & KEY_ANALOG_UP) != KEY:0,
        bool:down = (newkeys & KEY_ANALOG_DOWN) != KEY:0,
        direction = (up == down) ? 0 : (up ? 1 : -1)
    ;

    if (direction == gForkliftData[vehicleid][E_FORKLIFT_DIRECTION]) {
        return 1;
    }

    MoveForkInternal(vehicleid, direction);

    return 1;
}

hook OnPlayerStateChange(playerid, PLAYER_STATE:newstate, PLAYER_STATE:oldstate) {
    StopDrivingInternal(playerid);

    if (newstate != PLAYER_STATE_DRIVER) {
        return 1;
    }

    new const
        vehicleid = GetPlayerVehicleID(playerid)
    ;

    if (GetVehicleModel(vehicleid) != FORKLIFT_MODEL) {
        return 1;
    }

    inline OnTouch() {
        TouchCratesInternal(vehicleid, false);
    }

    gForkliftDriven[playerid] = vehicleid;
    gForkliftData[vehicleid][E_FORKLIFT_TOUCH_TIMER] = Timer_StartInline(EBC(Vehicle:vehicleid, using inline OnTouch), FORKLIFT_TOUCH_STEP);

    return 1;
}

hook OnPlayerConnect(playerid) {
    gForkliftDriven[playerid] = INVALID_VEHICLE_ID;

    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    StopDrivingInternal(playerid);

    return 1;
}

hook OnVehicleDeath(vehicleid, killerid) {
    ResetForkliftInternal(vehicleid);

    return 1;
}

hook OnVehicleSpawn(vehicleid) {
    ResetForkliftInternal(vehicleid);

    return 1;
}

hook native CreateVehicle(modelid, Float:spawnX, Float:spawnY, Float:spawnZ, Float:angle, colour1, colour2, respawnDelay, bool:addSiren = false) {
    new const
        vehicleid = CreateVehicle(modelid, spawnX, spawnY, spawnZ, angle, colour1, colour2, respawnDelay, addSiren)
    ;

    ClearForkliftInternal(vehicleid);

    return vehicleid;
}

hook native AddStaticVehicle(modelid, Float:spawnX, Float:spawnY, Float:spawnZ, Float:angle, colour1, colour2) {
    new const
        vehicleid = AddStaticVehicle(modelid, spawnX, spawnY, spawnZ, angle, colour1, colour2)
    ;

    ClearForkliftInternal(vehicleid);

    return vehicleid;
}

hook native AddStaticVehicleEx(modelid, Float:spawnX, Float:spawnY, Float:spawnZ, Float:angle, colour1, colour2, respawnDelay, bool:addSiren = false) {
    new const
        vehicleid = AddStaticVehicleEx(modelid, spawnX, spawnY, spawnZ, angle, colour1, colour2, respawnDelay, addSiren)
    ;

    ClearForkliftInternal(vehicleid);

    return vehicleid;
}

hook native bool:DestroyVehicle(vehicleid) {
    if (0 <= vehicleid < MAX_VEHICLES) {
        ResetForkliftInternal(vehicleid);
    }

    return DestroyVehicle(vehicleid);
}
