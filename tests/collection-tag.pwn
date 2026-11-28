#define SSI_TESTS
#define SSI_TEST_EXIT

#include <open.mp>
#include <SSI_Extra\inline-timers>
#include <SSI\iterator>
#include <SSI\test>
#include <SSI\hooks>

static
    gTicks
;

main() {
}

test PlainCollectionStaysPlain() {
    new const
        vehicleid = CreateVehicle(411, 0.0, 0.0, 3.0, 0.0, -1, -1, -1)
    ;

    foreach (new i : Vehicle) {
        ASSERT_EQ(tagof(i), 0);
    }

    ASSERT(Collection_Contains(Vehicle, vehicleid));
    ASSERT_NE(tagof(Vehicle:), 0);

    DestroyVehicle(vehicleid);
}

test VehicleOwnerIsFreed() {
    new const
        vehicleid = CreateVehicle(411, 0.0, 0.0, 3.0, 0.0, -1, -1, -1),
        before = Inline_Count()
    ;

    inline OnTick() {
        ++gTicks;
    }

    Timer_StartInline(EBC(Vehicle:vehicleid, using inline OnTick), 100);
    ASSERT_EQ(Inline_Count(), before + 1);

    DestroyVehicle(vehicleid);
    ASSERT_EQ(Inline_Count(), before);
}
