#define SSI_TESTS
#define SSI_TEST_EXIT

#include <open.mp>
#include <SSI\task>
#include <SSI_Extra\inline-timers>
#include <SSI\test>
#include <SSI\hooks>

main() {
}

static
    gSpreadTick[3],
    gCounter,
    gHunger[MAX_PLAYERS],
    gSelfA,
    gSelfB,
    Timer:gSelfTimer[2],
    gBot = INVALID_PLAYER_ID
;

task SpreadAlpha[300]() {
    if (gSpreadTick[0] == 0) {
        gSpreadTick[0] = GetTickCount();
    }
}

task SpreadBeta[300]() {
    if (gSpreadTick[1] == 0) {
        gSpreadTick[1] = GetTickCount();
    }
}

task SpreadGammaLongName[600]() {
    if (gSpreadTick[2] == 0) {
        gSpreadTick[2] = GetTickCount();
    }
}

task Counter[70]() {
    ++gCounter;
}

ptask HungerForEverything[50](playerid) {
    ++gHunger[playerid];
}

static SelfStopping(index, limit) {
    new
        calls = 0
    ;

    inline OnTick() {
        ASSERT(Timer_Current() == gSelfTimer[index]);

        if (index == 0) {
            ++gSelfA;
        } else {
            ++gSelfB;
        }

        if (++calls == limit) {
            Timer_Stop(Timer_Current());
        }
    }

    gSelfTimer[index] = Timer_StartInline(using inline OnTick, 40);
}

test SelfStop() {
    ASSERT(Timer_Current() == INVALID_TIMER_ID);

    SelfStopping(0, 3);
    SelfStopping(1, 5);

    Test_Async(2000);

    inline OnEnd() {
        ASSERT_EQ(gSelfA, 3);
        ASSERT_EQ(gSelfB, 5);
        ASSERT_FALSE(Timer_IsRunning(gSelfTimer[0]));
        ASSERT_FALSE(Timer_IsRunning(gSelfTimer[1]));
        Test_Done();
    }

    Timer_StartInline(using inline OnEnd, 500, 1);
}

test Spread() {
    Test_Async(3000);

    inline OnEnd() {
        ASSERT(gSpreadTick[0] != 0 && gSpreadTick[1] != 0 && gSpreadTick[2] != 0);
        ASSERT_GE(gSpreadTick[1] - gSpreadTick[0], 70);
        ASSERT_LE(gSpreadTick[1] - gSpreadTick[0], 130);
        ASSERT_GE(gSpreadTick[2] - gSpreadTick[0], 670);
        ASSERT_LE(gSpreadTick[2] - gSpreadTick[0], 730);
        Test_Done();
    }

    Timer_StartInline(using inline OnEnd, 1400, 1);
}

test Pause() {
    ASSERT(gCounter > 0);
    ASSERT(Task_Pause(Counter));
    ASSERT_FALSE(Task_Pause(Counter));
    ASSERT_FALSE(Task_Resume(SpreadAlpha));

    new const
        frozen = gCounter
    ;

    Test_Async(2000);

    inline OnPaused() {
        ASSERT_EQ(gCounter, frozen);
        ASSERT(Task_Resume(Counter));
        ASSERT_FALSE(Task_Resume(Counter));
    }

    Timer_StartInline(using inline OnPaused, 300, 1);

    inline OnEnd() {
        ASSERT_GE(gCounter, frozen + 3);
        Test_Done();
    }

    Timer_StartInline(using inline OnEnd, 700, 1);
}

test PlayerTask() {
    gBot = NPC_Create("TaskBot");
    ASSERT(IsPlayerConnected(gBot));
    ASSERT_FALSE(PTask_ResumePlayer(HungerForEverything, gBot));

    new
        step = 0,
        last = 0
    ;

    Test_Async(4000);

    inline OnStep() {
        switch (++step) {
            case 1: {
                ASSERT_GE(gHunger[gBot], 4);
                ASSERT(PTask_PausePlayer(HungerForEverything, gBot));
                ASSERT_FALSE(PTask_PausePlayer(HungerForEverything, gBot));
                last = gHunger[gBot];
            }
            case 2: {
                ASSERT_EQ(gHunger[gBot], last);
                ASSERT(PTask_ResumePlayer(HungerForEverything, gBot));
                last = gHunger[gBot];
            }
            case 3: {
                ASSERT_GE(gHunger[gBot], last + 3);
                ASSERT(PTask_Pause(HungerForEverything));
                ASSERT_FALSE(PTask_Pause(HungerForEverything));
                ASSERT_FALSE(PTask_ResumePlayer(HungerForEverything, gBot));
                last = gHunger[gBot];
            }
            case 4: {
                ASSERT_EQ(gHunger[gBot], last);
                ASSERT(PTask_Resume(HungerForEverything));
                last = gHunger[gBot];
            }
            case 5: {
                ASSERT_GE(gHunger[gBot], last + 3);
                NPC_Destroy(gBot);
                last = gHunger[gBot];
            }
            case 6: {
                ASSERT_FALSE(IsPlayerConnected(gBot));
                last = gHunger[gBot];
            }
            case 7: {
                ASSERT_EQ(gHunger[gBot], last);
                ASSERT_FALSE(PTask_PausePlayer(HungerForEverything, gBot));
                Timer_Stop(Timer_Current());
                Test_Done();
            }
        }
    }

    Timer_StartInline(using inline OnStep, 300);
}

test CallsDirectly() {
    new const
        before = gCounter
    ;

    Counter();
    ASSERT_EQ(gCounter, before + 1);
}
