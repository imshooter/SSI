#define SSI_TESTS
#define SSI_TEST_EXIT

#include <open.mp>
#include <streamer>
#include <SSI_Vehicle\parts>
#include <SSI_Vehicle\math>
#include <SSI_Vehicle\neon>
#include <SSI\test>

main() {
}

static
    gVehicle = INVALID_VEHICLE_ID
;

static Vehicle(Float:angle = 0.0) {
    if (gVehicle != INVALID_VEHICLE_ID) {
        DestroyVehicle(gVehicle);
    }

    gVehicle = CreateVehicle(411, 100.0, 200.0, 10.0, angle, 1, 1, -1);

    return gVehicle;
}

test Params() {
    new const
        vehicleid = Vehicle()
    ;

    ASSERT(SetVehicleParamsState(vehicleid, VEHICLE_PARAM_ENGINE, VEHICLE_PARAMS_ON));
    ASSERT(SetVehicleParamsState(vehicleid, VEHICLE_PARAM_LIGHTS, VEHICLE_PARAMS_ON));
    ASSERT(SetVehicleParamsState(vehicleid, VEHICLE_PARAM_BOOT, VEHICLE_PARAMS_OFF));
    ASSERT_EQ(GetVehicleParamState(vehicleid, VEHICLE_PARAM_ENGINE), VEHICLE_PARAMS_ON);
    ASSERT_EQ(GetVehicleParamState(vehicleid, VEHICLE_PARAM_LIGHTS), VEHICLE_PARAMS_ON);
    ASSERT_EQ(GetVehicleParamState(vehicleid, VEHICLE_PARAM_BOOT), VEHICLE_PARAMS_OFF);
    ASSERT_EQ(GetVehicleParamState(vehicleid, VEHICLE_PARAM_ALARM), VEHICLE_PARAMS_UNSET);
    ASSERT(SetVehicleParamsState(vehicleid, VEHICLE_PARAM_ENGINE, VEHICLE_PARAMS_UNSET));
    ASSERT_EQ(GetVehicleParamState(vehicleid, VEHICLE_PARAM_ENGINE), VEHICLE_PARAMS_UNSET);
    ASSERT_EQ(GetVehicleParamState(vehicleid, VEHICLE_PARAM_LIGHTS), VEHICLE_PARAMS_ON);
    ASSERT(SetVehicleParamsState(vehicleid, VEHICLE_PARAM_ALARM | VEHICLE_PARAM_DOORS | VEHICLE_PARAM_OBJECTIVE, VEHICLE_PARAMS_ON));
    ASSERT_EQ(GetVehicleParamState(vehicleid, VEHICLE_PARAM_ALARM), VEHICLE_PARAMS_ON);
    ASSERT_EQ(GetVehicleParamState(vehicleid, VEHICLE_PARAM_DOORS), VEHICLE_PARAMS_ON);
    ASSERT_EQ(GetVehicleParamState(vehicleid, VEHICLE_PARAM_OBJECTIVE), VEHICLE_PARAMS_ON);
    ASSERT_EQ(GetVehicleParamState(vehicleid, VEHICLE_PARAM_BONNET), VEHICLE_PARAMS_UNSET);
    ASSERT_EQ(GetVehicleParamState(vehicleid, VEHICLE_PARAM_BOOT), VEHICLE_PARAMS_OFF);
    ASSERT_EQ(GetVehicleParamState(vehicleid, VEHICLE_PARAM_ALARM | VEHICLE_PARAM_DOORS), VEHICLE_PARAMS_UNSET);
    ASSERT_FALSE(SetVehicleParamsState(1999, VEHICLE_PARAM_ENGINE, VEHICLE_PARAMS_ON));
    ASSERT_EQ(GetVehicleParamState(1999, VEHICLE_PARAM_ENGINE), VEHICLE_PARAMS_UNSET);
}

test DoorsAndWindows() {
    new const
        vehicleid = Vehicle()
    ;

    ASSERT_FALSE(IsVehicleDoorOpen(vehicleid, VEHICLE_CORNER_REAR_LEFT));
    ASSERT(SetVehicleDoorOpen(vehicleid, VEHICLE_CORNER_REAR_LEFT, true));
    ASSERT(IsVehicleDoorOpen(vehicleid, VEHICLE_CORNER_REAR_LEFT));
    ASSERT_FALSE(IsVehicleDoorOpen(vehicleid, VEHICLE_CORNER_FRONT_LEFT));

    new
        frontLeft,
        frontRight,
        rearLeft,
        rearRight
    ;

    GetVehicleParamsCarDoors(vehicleid, frontLeft, frontRight, rearLeft, rearRight);
    ASSERT_EQ(rearLeft, 1);
    ASSERT_NE(frontLeft, 1);

    ASSERT_FALSE(IsVehicleWindowOpen(vehicleid, VEHICLE_CORNER_FRONT_RIGHT));
    ASSERT(SetVehicleWindowOpen(vehicleid, VEHICLE_CORNER_FRONT_RIGHT, true));
    ASSERT(IsVehicleWindowOpen(vehicleid, VEHICLE_CORNER_FRONT_RIGHT));
    GetVehicleParamsCarWindows(vehicleid, frontLeft, frontRight, rearLeft, rearRight);
    ASSERT_EQ(frontRight, 0);
    ASSERT(SetVehicleWindowOpen(vehicleid, VEHICLE_CORNER_FRONT_RIGHT, false));
    ASSERT_FALSE(IsVehicleWindowOpen(vehicleid, VEHICLE_CORNER_FRONT_RIGHT));
    ASSERT(IsVehicleDoorOpen(vehicleid, VEHICLE_CORNER_REAR_LEFT));
}

test Damage() {
    new const
        vehicleid = Vehicle()
    ;

    new
        VEHICLE_PANEL_STATUS:panels,
        VEHICLE_DOOR_STATUS:doors,
        VEHICLE_LIGHT_STATUS:lights,
        VEHICLE_TYRE_STATUS:tyres
    ;

    ASSERT(SetVehicleTyrePopped(vehicleid, VEHICLE_CORNER_FRONT_LEFT, true));
    ASSERT(SetVehicleTyrePopped(vehicleid, VEHICLE_CORNER_REAR_RIGHT, true));
    ASSERT(IsVehicleTyrePopped(vehicleid, VEHICLE_CORNER_FRONT_LEFT));
    ASSERT_FALSE(IsVehicleTyrePopped(vehicleid, VEHICLE_CORNER_FRONT_RIGHT));
    GetVehicleDamageStatus(vehicleid, panels, doors, lights, tyres);
    ASSERT_EQ(_:tyres, 8 | 1);
    ASSERT(SetVehicleTyrePopped(vehicleid, VEHICLE_CORNER_FRONT_LEFT, false));
    ASSERT_FALSE(IsVehicleTyrePopped(vehicleid, VEHICLE_CORNER_FRONT_LEFT));
    ASSERT(IsVehicleTyrePopped(vehicleid, VEHICLE_CORNER_REAR_RIGHT));

    ASSERT(SetVehicleLampBroken(vehicleid, VEHICLE_LAMP_REAR, true));
    ASSERT(IsVehicleLampBroken(vehicleid, VEHICLE_LAMP_REAR));
    ASSERT_FALSE(IsVehicleLampBroken(vehicleid, VEHICLE_LAMP_FRONT_LEFT));
    GetVehicleDamageStatus(vehicleid, panels, doors, lights, tyres);
    ASSERT_EQ(_:lights, 64);

    ASSERT(SetVehicleOpeningDamage(vehicleid, VEHICLE_OPENING_BOOT, VEHICLE_DOOR_STATUS_BONNET_MISSING));
    ASSERT(SetVehicleOpeningDamage(vehicleid, VEHICLE_OPENING_FRONT_RIGHT, VEHICLE_DOOR_STATUS_BONNET_DAMAGED | VEHICLE_DOOR_STATUS_BONNET_OPEN));
    ASSERT(GetVehicleOpeningDamage(vehicleid, VEHICLE_OPENING_BOOT) == VEHICLE_DOOR_STATUS_BONNET_MISSING);
    ASSERT(GetVehicleOpeningDamage(vehicleid, VEHICLE_OPENING_BONNET) == VEHICLE_DOOR_STATUS_NONE);
    GetVehicleDamageStatus(vehicleid, panels, doors, lights, tyres);
    ASSERT(doors == (VEHICLE_DOOR_STATUS_BOOT_MISSING | VEHICLE_DOOR_STATUS_PASSENGER_DAMAGED | VEHICLE_DOOR_STATUS_PASSENGER_OPEN));
    ASSERT(SetVehicleOpeningDamage(vehicleid, VEHICLE_OPENING_BOOT, VEHICLE_DOOR_STATUS_NONE));
    GetVehicleDamageStatus(vehicleid, panels, doors, lights, tyres);
    ASSERT(doors == (VEHICLE_DOOR_STATUS_PASSENGER_DAMAGED | VEHICLE_DOOR_STATUS_PASSENGER_OPEN));

    ASSERT(SetVehiclePanelDamage(vehicleid, VEHICLE_PANEL_FRONT_BUMPER, 3));
    ASSERT(SetVehiclePanelDamage(vehicleid, VEHICLE_PANEL_WINDSHIELD, 1));
    ASSERT_EQ(GetVehiclePanelDamage(vehicleid, VEHICLE_PANEL_FRONT_BUMPER), 3);
    ASSERT_EQ(GetVehiclePanelDamage(vehicleid, VEHICLE_PANEL_REAR_BUMPER), 0);
    GetVehicleDamageStatus(vehicleid, panels, doors, lights, tyres);
    ASSERT_EQ(_:panels, (3 << 20) | (1 << 16));
    ASSERT(IsVehicleTyrePopped(vehicleid, VEHICLE_CORNER_REAR_RIGHT));
    ASSERT(IsVehicleLampBroken(vehicleid, VEHICLE_LAMP_REAR));
}

test Positions() {
    new
        vehicleid = Vehicle(),
        Float:x,
        Float:y,
        Float:z
    ;

    ASSERT(GetVehicleOffsetPos(vehicleid, 1.0, 2.0, 3.0, x, y, z));
    ASSERT_NEAR(x, 101.0, 0.01);
    ASSERT_NEAR(y, 202.0, 0.01);
    ASSERT_NEAR(z, 13.0, 0.01);

    vehicleid = Vehicle(90.0);
    ASSERT(GetVehicleOffsetPos(vehicleid, 0.0, 1.0, 0.0, x, y, z));
    ASSERT_NEAR(x, 99.0, 0.01);
    ASSERT_NEAR(y, 200.0, 0.01);
    ASSERT(GetVehicleOffsetPos(vehicleid, 1.0, 0.0, 0.0, x, y, z));
    ASSERT_NEAR(x, 100.0, 0.01);
    ASSERT_NEAR(y, 201.0, 0.01);

    vehicleid = Vehicle();

    new
        Float:leftX,
        Float:leftY,
        Float:leftZ,
        Float:rightX,
        Float:rightY,
        Float:rightZ,
        Float:rearX,
        Float:rearY,
        Float:rearZ
    ;

    ASSERT(GetVehicleWheelPos(vehicleid, VEHICLE_CORNER_FRONT_LEFT, leftX, leftY, leftZ));
    ASSERT(GetVehicleWheelPos(vehicleid, VEHICLE_CORNER_FRONT_RIGHT, rightX, rightY, rightZ));
    ASSERT(GetVehicleWheelPos(vehicleid, VEHICLE_CORNER_REAR_LEFT, rearX, rearY, rearZ));
    ASSERT(leftX < 100.0 && rightX > 100.0);
    ASSERT_NEAR(leftX - 100.0, 100.0 - rightX, 0.01);
    ASSERT(leftY > 200.0 && rearY < 200.0);
    ASSERT(leftZ < 10.0);
    ASSERT_FALSE(GetVehicleWheelPos(1999, VEHICLE_CORNER_FRONT_LEFT, x, y, z));
}

test SpeedAndOrientation() {
    new const
        vehicleid = Vehicle()
    ;

    ASSERT_NEAR(GetVehicleSpeed(vehicleid, 180.0), 0.0, 0.01);
    ASSERT_NEAR(GetVehicleSpeed(1999, 180.0), 0.0, 0.01);
    ASSERT_FALSE(IsVehicleUpsideDown(vehicleid));
    ASSERT_FALSE(IsVehicleUpsideDown(1999));
}

test Neon() {
    new const
        vehicleid = Vehicle(),
        before = CountDynamicObjects()
    ;

    ASSERT(GetVehicleNeon(vehicleid) == VEHICLE_NEON_NONE);
    ASSERT(SetVehicleNeon(vehicleid, VEHICLE_NEON_BLUE));
    ASSERT(GetVehicleNeon(vehicleid) == VEHICLE_NEON_BLUE);
    ASSERT_EQ(CountDynamicObjects(), before + 2);
    ASSERT(SetVehicleNeon(vehicleid, VEHICLE_NEON_RED));
    ASSERT_EQ(CountDynamicObjects(), before + 2);

    new
        models,
        worlds
    ;

    for (new STREAMER_TAG_OBJECT:objectid = STREAMER_TAG_OBJECT:1; _:objectid <= Streamer_GetUpperBound(STREAMER_TYPE_OBJECT); ++objectid) {
        if (!IsValidDynamicObject(objectid)) {
            continue;
        }

        if (Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_ATTACHED_VEHICLE) != vehicleid) {
            continue;
        }

        models += _:(Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_MODEL_ID) == 18647);

        SetVehicleVirtualWorld(vehicleid, 7);
        worlds += Streamer_IsInArrayData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_WORLD_ID, 7);
    }

    ASSERT_EQ(models, 2);
    ASSERT_EQ(worlds, 2);

    ASSERT(SetVehicleNeon(vehicleid, VEHICLE_NEON_NONE));
    ASSERT_EQ(CountDynamicObjects(), before);
    ASSERT(SetVehicleNeon(vehicleid, VEHICLE_NEON_GREEN));
    DestroyVehicle(vehicleid);
    gVehicle = INVALID_VEHICLE_ID;
    ASSERT_EQ(CountDynamicObjects(), before);
    ASSERT_FALSE(SetVehicleNeon(vehicleid, VEHICLE_NEON_GREEN));
}
