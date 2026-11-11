#if defined _INC_SSI_VEHICLE_FREIGHT
    #endinput
#endif
#define _INC_SSI_VEHICLE_FREIGHT

/**
 * Freight that rides in the back of a vehicle, each piece in a slot of a grid
 * set for that vehicle. A slot is where the bottom of a piece stands, so
 * pieces of any model stand on the floor.
 *
 *     SetVehicleFreight(vehicleid, 2, 3, -0.500, -0.430, -0.093, 1.050, 1.050);
 *     AddVehicleFreight(vehicleid, 1558);
 *
 * - The slots go from the front left one to the right, then back row by row.
 * - A piece is a streamer object attached to the vehicle. Pieces go away when
 *   the vehicle respawns or is destroyed, and the grid stays until then.
 * - With `SSI_Vehicle\forklift` included first, a vehicle whose freight is open
 *   takes a crate a forklift lowers onto its floor: the crate goes in when
 *   its bottom comes down to the floor, from `FORKLIFT_DROP_GAP` above it to
 *   `FREIGHT_FLOOR_REACH` under it. The forklift faces a side the vehicle
 *   opens from, within `FREIGHT_FACING` degrees. Where the forks cannot pass
 *   that side the crate may stay outside the vehicle, its edge at most
 *   `FREIGHT_REACH` from the end of the vehicle model. On a flat bed the
 *   forks reach over, its centre is over the slots, as it is towards the
 *   sides it is not brought from. Brought from an end of the vehicle, the
 *   crate goes to the free slot furthest in, and from a side to the nearest.
 *   A stack of two takes two free slots of one row, side by side, or the next
 *   slot by the same rule when no row has two. `OnCrateLoad` can refuse a
 *   crate, once each time it is lowered, and the crate or the stack is then
 *   put down as usual.
 */
#include <open.mp>
#include <streamer>
#include <3DAndreas>

#include <SSI\bits>
#include <SSI\collection>
#include <SSI\hooks>

/**
 * # Header
 */

#if !defined MAX_FREIGHT_SLOTS
    #define MAX_FREIGHT_SLOTS (12)
#endif

#if !defined FREIGHT_REACH
    #define FREIGHT_REACH (0.05)
#endif

#if !defined FREIGHT_FACING
    #define FREIGHT_FACING (15.0)
#endif

#if !defined FREIGHT_FLOOR_REACH
    #define FREIGHT_FLOOR_REACH (0.05)
#endif

enum FREIGHT_SIDE: (<<= 1) {
    FREIGHT_SIDE_NONE = 0,
    FREIGHT_SIDE_BACK = 1,
    FREIGHT_SIDE_FRONT,
    FREIGHT_SIDE_LEFT,
    FREIGHT_SIDE_RIGHT
};

static enum _:E_FREIGHT_DATA {
    E_FREIGHT_COLUMNS,
    E_FREIGHT_ROWS,
    Float:E_FREIGHT_X,
    Float:E_FREIGHT_Y,
    Float:E_FREIGHT_FLOOR,
    Float:E_FREIGHT_COLUMN_GAP,
    Float:E_FREIGHT_ROW_GAP,
    Float:E_FREIGHT_RIGHT,
    Float:E_FREIGHT_BACK,
    Float:E_FREIGHT_HALF_WIDTH,
    Float:E_FREIGHT_HALF_LENGTH,
    Float:E_FREIGHT_RADIUS,
    FREIGHT_SIDE:E_FREIGHT_SIDES,
    bool:E_FREIGHT_BED,
    E_FREIGHT_COUNT,
    STREAMER_TAG_OBJECT:E_FREIGHT_OBJECT[MAX_FREIGHT_SLOTS]
};

static
    gFreightData[MAX_VEHICLES][E_FREIGHT_DATA],
    Collection:FreightOpen<MAX_VEHICLES>
;

#define FreightOpen: _:

#if defined _INC_SSI_VEHICLE_FORKLIFT
    static
        Bits:FreightRefused<MAX_CRATES>
    ;
#endif

/**
 * # Functions
 */

/**
 * @brief      Set the grid of slots in the back of a vehicle. Freight already
 *             in it goes away.
 *
 * @param      vehicleid  The vehicle.
 * @param      columns    Slots side by side.
 * @param      rows       Slots one behind the other.
 * @param      x          X of the front left slot, from the vehicle.
 * @param      y          Y of the front left slot, from the vehicle.
 * @param      floor      Height of the floor, from the vehicle.
 * @param      columnGap  Distance between columns, to the right.
 * @param      rowGap     Distance between rows, backwards.
 * @param      sides      The sides a forklift loads it from.
 * @param      bed        `true` for a flat bed the forks reach over, so a
 *                        crate is lowered over the slots.
 *
 * @return     - `true` it was set
 *             - `false` when:
 *                 + the vehicle does not exist
 *                 + `columns` or `rows` is below 1
 *                 + there are more than `MAX_FREIGHT_SLOTS` slots
 */
forward bool:SetVehicleFreight(vehicleid, columns, rows, Float:x, Float:y, Float:floor, Float:columnGap, Float:rowGap, FREIGHT_SIDE:sides = FREIGHT_SIDE_BACK, bool:bed = false);

/**
 * @brief      Put a piece of freight in the back of a vehicle.
 *
 * @param      vehicleid  The vehicle.
 * @param      modelid    Model of the piece, which stands on the floor.
 * @param      slot       The slot, or `-1` for the first free one.
 *
 * @return     - the slot
 *             - `-1` when:
 *                 + the vehicle has no grid
 *                 + the slot is taken or out of the grid
 *                 + every slot is taken
 */
forward AddVehicleFreight(vehicleid, modelid, slot = -1);

/**
 * @brief      Take a piece of freight out of the back of a vehicle.
 *
 * @param      vehicleid  The vehicle.
 * @param      slot       The slot.
 *
 * @return     - `true` it was taken out
 *             - `false` the slot is empty or out of the grid
 */
forward bool:RemoveVehicleFreight(vehicleid, slot);

/**
 * @brief      Take all the freight out of the back of a vehicle. The grid
 *             stays.
 *
 * @param      vehicleid  The vehicle.
 *
 * @return     - `true` it was emptied
 *             - `false` the vehicle has no grid
 */
forward bool:ClearVehicleFreight(vehicleid);

/**
 * @brief      How many pieces of freight a vehicle carries.
 *
 * @param      vehicleid  The vehicle.
 *
 * @return     How many.
 */
forward GetVehicleFreightCount(vehicleid);

/**
 * @brief      How many slots the grid of a vehicle has.
 *
 * @param      vehicleid  The vehicle.
 *
 * @return     - how many
 *             - `0` it has no grid
 */
forward GetVehicleFreightSlots(vehicleid);

/**
 * @brief      The object of a piece of freight.
 *
 * @param      vehicleid  The vehicle.
 * @param      slot       The slot.
 *
 * @return     - the object
 *             - `INVALID_STREAMER_ID` the slot is empty or out of the grid
 */
forward STREAMER_TAG_OBJECT:GetVehicleFreightObject(vehicleid, slot);

/**
 * @brief      Where the floor of a slot is in the world.
 *
 * @param      vehicleid  The vehicle.
 * @param      slot       The slot.
 * @param      x          Reads back the position on the X axis.
 * @param      y          Reads back the position on the Y axis.
 * @param      z          Reads back the height of the floor.
 *
 * @return     - `true` the outputs were written
 *             - `false` the slot is out of the grid
 */
forward bool:GetVehicleFreightPos(vehicleid, slot, &Float:x, &Float:y, &Float:z);

/**
 * @brief      Open or close the back of a vehicle to forklifts.
 *
 * @param      vehicleid  The vehicle.
 * @param      open       `true` takes crates.
 *
 * @return     - `true` it was set
 *             - `false` the vehicle has no grid
 */
forward bool:SetVehicleFreightOpen(vehicleid, bool:open);

/**
 * @brief      Whether the back of a vehicle takes crates from forklifts.
 *
 * @param      vehicleid  The vehicle.
 *
 * @return     - `true` it does
 *             - `false` it does not
 */
forward bool:IsVehicleFreightOpen(vehicleid);

/**
 * # Events
 */

#if defined _INC_SSI_VEHICLE_FORKLIFT
    /**
     * @brief      A forklift is lowering a crate into the back of a vehicle.
     *             A stack gives a call for the bottom crate, then one for the
     *             top crate, and either refuses both.
     *
     * @param      crateid      The crate.
     * @param      forkliftid   The forklift.
     * @param      vehicleid    The vehicle.
     * @param      slot         The slot it goes to.
     *
     * @return     - `0` it is loaded
     *             - `1` it is not
     */
    event OnCrateLoad(Crate:crateid, forkliftid, vehicleid, slot);

    /**
     * @brief      A crate is in the back of a vehicle as freight. The crate
     *             still exists here and is destroyed after, unless a handler
     *             destroyed it. A stack gives a call for the bottom crate,
     *             then one for the top crate.
     *
     * @param      crateid      The crate.
     * @param      forkliftid   The forklift.
     * @param      vehicleid    The vehicle.
     * @param      slot         Its slot.
     */
    event OnCrateLoaded(Crate:crateid, forkliftid, vehicleid, slot);
#endif

/**
 * # Internal
 */

static stock ResetFreightInternal(vehicleid) {
    gFreightData[vehicleid][E_FREIGHT_COLUMNS] = 0;
    gFreightData[vehicleid][E_FREIGHT_ROWS] = 0;
    gFreightData[vehicleid][E_FREIGHT_COUNT] = 0;

    for (new i; i != MAX_FREIGHT_SLOTS; ++i) {
        gFreightData[vehicleid][E_FREIGHT_OBJECT][i] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
    }

    Collection_Remove(FreightOpen, vehicleid);
}

/**
 * # Freight
 */

stock bool:SetVehicleFreight(vehicleid, columns, rows, Float:x, Float:y, Float:floor, Float:columnGap, Float:rowGap, FREIGHT_SIDE:sides = FREIGHT_SIDE_BACK, bool:bed = false) {
    if (!IsValidVehicle(vehicleid)) {
        return false;
    }

    if (columns < 1) {
        return false;
    }

    if (rows < 1) {
        return false;
    }

    if (columns * rows > MAX_FREIGHT_SLOTS) {
        return false;
    }

    new
        Float:width,
        Float:length,
        Float:height
    ;

    GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, width, length, height);
    ClearVehicleFreight(vehicleid);

    gFreightData[vehicleid][E_FREIGHT_COLUMNS] = columns;
    gFreightData[vehicleid][E_FREIGHT_ROWS] = rows;
    gFreightData[vehicleid][E_FREIGHT_X] = x;
    gFreightData[vehicleid][E_FREIGHT_Y] = y;
    gFreightData[vehicleid][E_FREIGHT_FLOOR] = floor;
    gFreightData[vehicleid][E_FREIGHT_COLUMN_GAP] = columnGap;
    gFreightData[vehicleid][E_FREIGHT_ROW_GAP] = rowGap;
    gFreightData[vehicleid][E_FREIGHT_RIGHT] = x + float(columns - 1) * columnGap;
    gFreightData[vehicleid][E_FREIGHT_BACK] = y - float(rows - 1) * rowGap;
    gFreightData[vehicleid][E_FREIGHT_HALF_WIDTH] = width * 0.5;
    gFreightData[vehicleid][E_FREIGHT_HALF_LENGTH] = length * 0.5;
    gFreightData[vehicleid][E_FREIGHT_RADIUS] = VectorSize(width * 0.5, length * 0.5, 0.0) + FREIGHT_REACH;
    gFreightData[vehicleid][E_FREIGHT_SIDES] = sides;
    gFreightData[vehicleid][E_FREIGHT_BED] = bed;

    return true;
}

stock AddVehicleFreight(vehicleid, modelid, slot = -1) {
    if (!(0 <= vehicleid < MAX_VEHICLES)) {
        return -1;
    }

    new const
        columns = gFreightData[vehicleid][E_FREIGHT_COLUMNS],
        slots = columns * gFreightData[vehicleid][E_FREIGHT_ROWS]
    ;

    if (slot == -1) {
        while (++slot != slots && gFreightData[vehicleid][E_FREIGHT_OBJECT][slot] != STREAMER_TAG_OBJECT:INVALID_STREAMER_ID) {}
    }

    if (!(0 <= slot < slots) || gFreightData[vehicleid][E_FREIGHT_OBJECT][slot] != STREAMER_TAG_OBJECT:INVALID_STREAMER_ID) {
        return -1;
    }

    new
        Float:minX,
        Float:minY,
        Float:minZ,
        Float:maxX,
        Float:maxY,
        Float:maxZ
    ;

    A3D_GetModelBoundingBox(modelid, minX, minY, minZ, maxX, maxY, maxZ);

    new const
        STREAMER_TAG_OBJECT:objectid = CreateDynamicObject(modelid, 0.0, 0.0, -50.0, 0.0, 0.0, 0.0)
    ;

    AttachDynamicObjectToVehicle(objectid, vehicleid,
        gFreightData[vehicleid][E_FREIGHT_X] + float(slot % columns) * gFreightData[vehicleid][E_FREIGHT_COLUMN_GAP],
        gFreightData[vehicleid][E_FREIGHT_Y] - float(slot / columns) * gFreightData[vehicleid][E_FREIGHT_ROW_GAP],
        gFreightData[vehicleid][E_FREIGHT_FLOOR] - minZ,
        0.0, 0.0, 0.0
    );

    gFreightData[vehicleid][E_FREIGHT_OBJECT][slot] = objectid;
    ++gFreightData[vehicleid][E_FREIGHT_COUNT];

    return slot;
}

stock bool:RemoveVehicleFreight(vehicleid, slot) {
    if (!(0 <= vehicleid < MAX_VEHICLES) || !(0 <= slot < MAX_FREIGHT_SLOTS)) {
        return false;
    }

    if (gFreightData[vehicleid][E_FREIGHT_OBJECT][slot] == STREAMER_TAG_OBJECT:INVALID_STREAMER_ID) {
        return false;
    }

    DestroyDynamicObject(gFreightData[vehicleid][E_FREIGHT_OBJECT][slot]);

    gFreightData[vehicleid][E_FREIGHT_OBJECT][slot] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
    --gFreightData[vehicleid][E_FREIGHT_COUNT];

    return true;
}

stock bool:ClearVehicleFreight(vehicleid) {
    if (!(0 <= vehicleid < MAX_VEHICLES) || gFreightData[vehicleid][E_FREIGHT_COLUMNS] == 0) {
        return false;
    }

    for (new i; i != MAX_FREIGHT_SLOTS; ++i) {
        if (gFreightData[vehicleid][E_FREIGHT_OBJECT][i] != STREAMER_TAG_OBJECT:INVALID_STREAMER_ID) {
            DestroyDynamicObject(gFreightData[vehicleid][E_FREIGHT_OBJECT][i]);
            gFreightData[vehicleid][E_FREIGHT_OBJECT][i] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
        }
    }

    gFreightData[vehicleid][E_FREIGHT_COUNT] = 0;

    return true;
}

stock GetVehicleFreightCount(vehicleid) {
    return (0 <= vehicleid < MAX_VEHICLES) ? gFreightData[vehicleid][E_FREIGHT_COUNT] : 0;
}

stock GetVehicleFreightSlots(vehicleid) {
    return (0 <= vehicleid < MAX_VEHICLES) ? gFreightData[vehicleid][E_FREIGHT_COLUMNS] * gFreightData[vehicleid][E_FREIGHT_ROWS] : 0;
}

stock STREAMER_TAG_OBJECT:GetVehicleFreightObject(vehicleid, slot) {
    if (!(0 <= slot < GetVehicleFreightSlots(vehicleid))) {
        return STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
    }

    return gFreightData[vehicleid][E_FREIGHT_OBJECT][slot];
}

stock bool:GetVehicleFreightPos(vehicleid, slot, &Float:x, &Float:y, &Float:z) {
    if (!(0 <= slot < GetVehicleFreightSlots(vehicleid))) {
        return false;
    }

    new const
        columns = gFreightData[vehicleid][E_FREIGHT_COLUMNS]
    ;

    return A3D_GetVehicleOffsetPosition(vehicleid,
        gFreightData[vehicleid][E_FREIGHT_X] + float(slot % columns) * gFreightData[vehicleid][E_FREIGHT_COLUMN_GAP],
        gFreightData[vehicleid][E_FREIGHT_Y] - float(slot / columns) * gFreightData[vehicleid][E_FREIGHT_ROW_GAP],
        gFreightData[vehicleid][E_FREIGHT_FLOOR],
        x, y, z
    );
}

stock bool:SetVehicleFreightOpen(vehicleid, bool:open) {
    if (!(0 <= vehicleid < MAX_VEHICLES) || gFreightData[vehicleid][E_FREIGHT_COLUMNS] == 0) {
        return false;
    }

    if (open) {
        Collection_Add(FreightOpen, vehicleid);
    } else {
        Collection_Remove(FreightOpen, vehicleid);
    }

    return true;
}

stock bool:IsVehicleFreightOpen(vehicleid) {
    return (0 <= vehicleid < MAX_VEHICLES) && Collection_Contains(FreightOpen, vehicleid);
}

/**
 * # Calls
 */

#if defined _INC_SSI_VEHICLE_FORKLIFT
    hook OnCrateLower(Crate:crateid, vehicleid, Float:x, Float:y, Float:z) {
        if (Bits_Test(FreightRefused, crateid) || Collection_Count(FreightOpen) == 0) {
            return 0;
        }

        new
            Float:width,
            Float:depth
        ;

        GetCrateSize(crateid, width, depth);

        new
            Float:heading
        ;

        GetVehicleZAngle(vehicleid, heading);

        new const
            Crate:aboveid = GetCrateAbove(crateid),
            worldid = GetVehicleVirtualWorld(vehicleid),
            Float:size = (width > depth) ? width : depth,
            Float:half = size * 0.5
        ;

        foreach (new freightid : FreightOpen) {
            if (GetVehicleVirtualWorld(freightid) != worldid) {
                continue;
            }

            new
                Float:offsetX,
                Float:offsetY,
                Float:offsetZ,
                Float:angle
            ;

            GetVehiclePos(freightid, offsetX, offsetY, offsetZ);

            if (VectorSize(x - offsetX, y - offsetY, 0.0) > gFreightData[freightid][E_FREIGHT_RADIUS] + size) {
                continue;
            }

            GetVehicleZAngle(freightid, angle);

            new const
                Float:turn = heading - angle - 360.0 * float(floatround((heading - angle) / 360.0)),
                FREIGHT_SIDE:from = (floatabs(turn) <= FREIGHT_FACING) ? FREIGHT_SIDE_BACK
                    : (floatabs(turn + 90.0) <= FREIGHT_FACING) ? FREIGHT_SIDE_LEFT
                    : (floatabs(turn - 90.0) <= FREIGHT_FACING) ? FREIGHT_SIDE_RIGHT
                    : (floatabs(turn) >= 180.0 - FREIGHT_FACING) ? FREIGHT_SIDE_FRONT
                    : FREIGHT_SIDE_NONE
            ;

            if (!(gFreightData[freightid][E_FREIGHT_SIDES] & from)) {
                continue;
            }

            A3D_GetVehiclePositionOffset(freightid, x, y, z, offsetX, offsetY, offsetZ);

            if (!(gFreightData[freightid][E_FREIGHT_FLOOR] - FREIGHT_FLOOR_REACH <= offsetZ <= gFreightData[freightid][E_FREIGHT_FLOOR] + FORKLIFT_DROP_GAP)) {
                continue;
            }

            new const
                Float:left = gFreightData[freightid][E_FREIGHT_X],
                Float:front = gFreightData[freightid][E_FREIGHT_Y],
                Float:columnGap = gFreightData[freightid][E_FREIGHT_COLUMN_GAP],
                Float:rowGap = gFreightData[freightid][E_FREIGHT_ROW_GAP],
                Float:sideGap = (columnGap * 0.5 > half) ? columnGap * 0.5 : half,
                Float:endGap = (rowGap * 0.5 > half) ? rowGap * 0.5 : half,
                Float:outsideX = gFreightData[freightid][E_FREIGHT_HALF_WIDTH] + half + FREIGHT_REACH,
                Float:outsideY = gFreightData[freightid][E_FREIGHT_HALF_LENGTH] + half + FREIGHT_REACH,
                FREIGHT_SIDE:outside = gFreightData[freightid][E_FREIGHT_BED] ? FREIGHT_SIDE_NONE : from
            ;

            if (!(((outside == FREIGHT_SIDE_LEFT) ? -outsideX : left - sideGap) <= offsetX <= ((outside == FREIGHT_SIDE_RIGHT) ? outsideX : gFreightData[freightid][E_FREIGHT_RIGHT] + sideGap))) {
                continue;
            }

            if (!(((outside == FREIGHT_SIDE_BACK) ? -outsideY : gFreightData[freightid][E_FREIGHT_BACK] - endGap) <= offsetY <= ((outside == FREIGHT_SIDE_FRONT) ? outsideY : front + endGap))) {
                continue;
            }

            new const
                columns = gFreightData[freightid][E_FREIGHT_COLUMNS],
                rows = gFreightData[freightid][E_FREIGHT_ROWS],
                bool:end = from == FREIGHT_SIDE_BACK || from == FREIGHT_SIDE_FRONT,
                Float:inward = (from == FREIGHT_SIDE_FRONT) ? -100.0 : 100.0
            ;

            new
                Float:best,
                Float:nextBest,
                Float:pairBest,
                found = -1,
                next = -1,
                pairFound = -1,
                pairNext = -1
            ;

            for (new row, i, Float:slotY = front; row != rows; ++row, slotY -= rowGap) {
                new
                    Float:rowBest,
                    Float:rowNextBest,
                    rowFound = -1,
                    rowNext = -1
                ;

                for (new column, Float:slotX = left; column != columns; ++column, ++i, slotX += columnGap) {
                    if (gFreightData[freightid][E_FREIGHT_OBJECT][i] != STREAMER_TAG_OBJECT:INVALID_STREAMER_ID) {
                        continue;
                    }

                    new const
                        Float:score = end ? slotY * inward - floatabs(slotX - offsetX) : -VectorSize(offsetX - slotX, offsetY - slotY, 0.0)
                    ;

                    if (found == -1 || score > best) {
                        nextBest = best;
                        next = found;
                        best = score;
                        found = i;
                    } else if (next == -1 || score > nextBest) {
                        nextBest = score;
                        next = i;
                    }

                    if (rowFound == -1 || score > rowBest) {
                        rowNextBest = rowBest;
                        rowNext = rowFound;
                        rowBest = score;
                        rowFound = i;
                    } else if (rowNext == -1 || score > rowNextBest) {
                        rowNextBest = score;
                        rowNext = i;
                    }
                }

                if (rowNext != -1 && (pairFound == -1 || rowBest > pairBest)) {
                    pairBest = rowBest;
                    pairFound = rowFound;
                    pairNext = rowNext;
                }
            }

            if (found == -1) {
                continue;
            }

            if (aboveid != INVALID_CRATE_ID && pairFound != -1) {
                found = pairFound;
                next = pairNext;
            }

            if (aboveid != INVALID_CRATE_ID && next == -1) {
                continue;
            }

            if (call OnCrateLoad(crateid, vehicleid, freightid, found) || (aboveid != INVALID_CRATE_ID && call OnCrateLoad(aboveid, vehicleid, freightid, next))) {
                Bits_Let(FreightRefused, crateid);

                return 0;
            }

            AddVehicleFreight(freightid, GetCrateModel(crateid), found);

            if (aboveid != INVALID_CRATE_ID) {
                AddVehicleFreight(freightid, GetCrateModel(aboveid), next);
            }

            call OnCrateLoaded(crateid, vehicleid, freightid, found);

            if (aboveid != INVALID_CRATE_ID) {
                call OnCrateLoaded(aboveid, vehicleid, freightid, next);
            }

            if (aboveid != INVALID_CRATE_ID && IsValidCrate(aboveid)) {
                DestroyCrate(aboveid);
            }

            if (IsValidCrate(crateid)) {
                DestroyCrate(crateid);
            }

            return ~1;
        }

        return 0;
    }

    hook OnCrateLifted(Crate:crateid, vehicleid) {
        Bits_Vet(FreightRefused, crateid);

        return 0;
    }

    hook OnCrateDropped(Crate:crateid, vehicleid, Crate:belowid) {
        Bits_Vet(FreightRefused, crateid);

        return 0;
    }

    hook OnCrateReturned(Crate:crateid, vehicleid) {
        Bits_Vet(FreightRefused, crateid);

        return 0;
    }
#endif

hook OnVehicleSpawn(vehicleid) {
    ClearVehicleFreight(vehicleid);

    return 1;
}

hook native CreateVehicle(modelid, Float:spawnX, Float:spawnY, Float:spawnZ, Float:angle, colour1, colour2, respawnDelay, bool:addSiren = false) {
    new const
        vehicleid = CreateVehicle(modelid, spawnX, spawnY, spawnZ, angle, colour1, colour2, respawnDelay, addSiren)
    ;

    if (vehicleid != INVALID_VEHICLE_ID) {
        ResetFreightInternal(vehicleid);
    }

    return vehicleid;
}

hook native AddStaticVehicle(modelid, Float:spawnX, Float:spawnY, Float:spawnZ, Float:angle, colour1, colour2) {
    new const
        vehicleid = AddStaticVehicle(modelid, spawnX, spawnY, spawnZ, angle, colour1, colour2)
    ;

    if (vehicleid != INVALID_VEHICLE_ID) {
        ResetFreightInternal(vehicleid);
    }

    return vehicleid;
}

hook native AddStaticVehicleEx(modelid, Float:spawnX, Float:spawnY, Float:spawnZ, Float:angle, colour1, colour2, respawnDelay, bool:addSiren = false) {
    new const
        vehicleid = AddStaticVehicleEx(modelid, spawnX, spawnY, spawnZ, angle, colour1, colour2, respawnDelay, addSiren)
    ;

    if (vehicleid != INVALID_VEHICLE_ID) {
        ResetFreightInternal(vehicleid);
    }

    return vehicleid;
}

hook native bool:DestroyVehicle(vehicleid) {
    if (0 <= vehicleid < MAX_VEHICLES) {
        ClearVehicleFreight(vehicleid);
        ResetFreightInternal(vehicleid);
    }

    return DestroyVehicle(vehicleid);
}
