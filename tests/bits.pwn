#define SSI_TESTS
#define SSI_TEST_EXIT

#include <open.mp>
#include <SSI\bits>
#include <SSI\test>
#include <SSI\hooks>

enum E_HOLDER {
    E_HOLDER_ID,
    Bits:E_HOLDER_SEEN<70>
};

static
    Bits:One<100>,
    Bits:Other<100>,
    Bits:Rows[4]<40>,
    gHolder[3][E_HOLDER]
;

main() {
}

test Sizes() {
    ASSERT_EQ(sizeof (One), 4);
    ASSERT_EQ(sizeof (Rows), 4);
    ASSERT_EQ(sizeof (Rows[]), 2);
    ASSERT_EQ(_:E_HOLDER, 4);
}

test SetTestClear() {
    ASSERT(Bits_IsEmpty(One));
    Bits_Let(One, 0);
    Bits_Let(One, 31);
    Bits_Let(One, 32);
    Bits_Let(One, 99);
    ASSERT(Bits_Test(One, 31));
    ASSERT(Bits_Test(One, 32));
    ASSERT_FALSE(Bits_Test(One, 30));
    ASSERT_FALSE(Bits_Test(One, 33));
    ASSERT_EQ(Bits_Count(One), 4);
    ASSERT_FALSE(Bits_IsEmpty(One));

    Bits_Vet(One, 31);
    ASSERT_FALSE(Bits_Test(One, 31));
    new
        bool:on = true
    ;

    Bits_Set(One, 31, on);
    ASSERT(Bits_Test(One, 31));
    on = false;
    Bits_Set(One, 31, on);
    ASSERT_FALSE(Bits_Test(One, 31));
    ASSERT_EQ(Bits_Count(One), 3);
}

test Walk() {
    new
        seen[8],
        count
    ;

    foreach (new i : Bits(One)) {
        seen[count++] = i;
    }

    new const
        Group:tagged = Group:2
    ;

    Bits_Let(Rows[3], tagged);
    ASSERT(Bits_Test(Rows[3], tagged));
    ASSERT_FALSE(Bits_Test(Rows[3], Group:1));

    ASSERT_EQ(count, 3);
    ASSERT_EQ(seen[0], 0);
    ASSERT_EQ(seen[1], 32);
    ASSERT_EQ(seen[2], 99);

    Bits_Let(Rows[2], 39);
    Bits_Let(Rows[2], 5);
    count = 0;

    foreach (new Group:i : Bits(Rows[2])) {
        seen[count++] = _:i;
    }

    ASSERT_EQ(count, 2);
    ASSERT_EQ(seen[0], 5);
    ASSERT_EQ(seen[1], 39);

    count = 0;

    foreach (new i : Bits(Rows[1])) {
        ++count;
    }

    ASSERT_EQ(count, 0);
}

test SetOperations() {
    Bits_Clear(Other);
    ASSERT_FALSE(Bits_Intersects(One, Other));
    Bits_Let(Other, 99);
    ASSERT(Bits_Intersects(One, Other));
    Bits_Let(Other, 50);
    Bits_Or(One, Other);
    ASSERT_EQ(Bits_Count(One), 4);
    ASSERT(Bits_Test(One, 50));
    Bits_Copy(Other, One);
    ASSERT_EQ(Bits_Count(Other), 4);
    Bits_Clear(One);
    ASSERT(Bits_IsEmpty(One));
    ASSERT_EQ(Bits_Count(Other), 4);
}

test EnumField() {
    Bits_Let(gHolder[1][E_HOLDER_SEEN], 69);
    ASSERT(Bits_Test(gHolder[1][E_HOLDER_SEEN], 69));
    ASSERT_FALSE(Bits_Test(gHolder[1][E_HOLDER_SEEN], 68));
    ASSERT_EQ(gHolder[1][E_HOLDER_ID], 0);
    ASSERT_EQ(gHolder[2][E_HOLDER_ID], 0);
    ASSERT_FALSE(Bits_Test(gHolder[2][E_HOLDER_SEEN], 69));

    new
        last = -1
    ;

    foreach (new i : Bits(gHolder[1][E_HOLDER_SEEN])) {
        last = i;
    }

    ASSERT_EQ(last, 69);
}

test HighBit() {
    new
        Bits:Word<32>,
        found = -1
    ;

    Bits_Let(Word, 31);

    foreach (new i : Bits(Word)) {
        found = i;
    }

    ASSERT_EQ(found, 31);
}
