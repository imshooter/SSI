#define SSI_TESTS
#define SSI_TEST_EXIT

#include <open.mp>
#include <SSI\iterator>
#include <SSI\command>
#include <SSI\test>
#include <SSI\hooks>

static
    gBot = INVALID_PLAYER_ID,
    gRan,
    gParams[64],
    gUnknown,
    gUnknownName[32],
    gDenied,
    gPerformed,
    gPerformedResult,
    bool:gAnswerUnknown,
    bool:gAnswerDenied
;

main() {
}

CMD:Heal(playerid, params[]) {
    ++gRan;
    strcopy(gParams, params);

    return 1;
}

CMD:fail(playerid, params[]) {
    ++gRan;

    return 0;
}

CMD:secret(playerid, params[]) {
    ++gRan;

    return 1;
}

CMD:guarded(playerid, params[]) {
    ++gRan;

    return 1;
}

hook OnPlayerUnknownCommand(playerid, const name[], const params[]) {
    ++gUnknown;
    strcopy(gUnknownName, name);

    return gAnswerUnknown;
}

hook OnPlayerCommandDenied(playerid, Command:commandid, const params[]) {
    ++gDenied;

    return gAnswerDenied;
}

hook OnPlayerUseCommand(playerid, Command:commandid, const params[], flags) {
    return flags & 1;
}

hook OnPlayerUsedCommand(playerid, Command:commandid, const params[], result, flags) {
    ++gPerformed;
    gPerformedResult = result;

    return 0;
}

Reset() {
    gRan = 0;
    gParams[0] = EOS;
    gUnknown = 0;
    gUnknownName[0] = EOS;
    gDenied = 0;
    gPerformed = 0;
    gPerformedResult = -1;
    gAnswerUnknown = false;
    gAnswerDenied = false;
}

test BotConnects() {
    gBot = NPC_Create("CommandBot");
    ASSERT(IsPlayerConnected(gBot));
}

test Registers() {
    new
        name[32]
    ;

    ASSERT_EQ(Command_Count(), 4);
    ASSERT(Command_GetByName("heal") != INVALID_COMMAND_ID);
    ASSERT(Command_GetByName("HEAL") == Command_GetByName("heal"));
    ASSERT(Command_GetByName("nothing") == INVALID_COMMAND_ID);
    ASSERT(Command_GetByName("") == INVALID_COMMAND_ID);
    ASSERT(Command_GetName(Command_GetByName("Heal"), name));
    ASSERT_SAME(name, "heal");

    foreach (new Command:commandid : N(Command_Count())) {
        ASSERT(Command_IsValid(commandid));
    }

    ASSERT_FALSE(Command_IsValid(Command:4));
}

test Aliases() {
    ASSERT_EQ(Command_AddAlias("heal", "Cure", "remedy"), 2);
    ASSERT(Command_GetByName("cure") == Command_GetByName("heal"));
    ASSERT(Command_GetByName("REMEDY") == Command_GetByName("heal"));
    ASSERT_EQ(Command_AddAlias("cure", "fail", "cure", "two words", "", "abcdefghijklmnopqrstuvwxyzabcdefg", "mend"), 1);
    ASSERT(Command_GetByName("mend") == Command_GetByName("heal"));
    ASSERT_EQ(Command_AddAlias("nothing", "x"), 0);
}

test Runs() {
    Reset();
    ASSERT(Command_Run(gBot, "/HEAL   10 20"));
    ASSERT_EQ(gRan, 1);
    ASSERT_SAME(gParams, "10 20");
    ASSERT_EQ(gPerformed, 1);
    ASSERT_EQ(gPerformedResult, 1);

    Reset();
    ASSERT(Command_Run(gBot, "/cure"));
    ASSERT_EQ(gRan, 1);
    ASSERT_EQ(gParams[0], EOS);

    Reset();
    ASSERT_FALSE(Command_Run(gBot, "/fail"));
    ASSERT_EQ(gRan, 1);
    ASSERT_EQ(gPerformedResult, 0);

    Reset();
    ASSERT_FALSE(Command_Run(gBot, "heal"));
    ASSERT_FALSE(Command_Run(INVALID_PLAYER_ID, "/heal"));
    ASSERT_EQ(gRan, 0);
}

test Unknown() {
    Reset();
    ASSERT_FALSE(Command_Run(gBot, "/Nothing here"));
    ASSERT_EQ(gUnknown, 1);
    ASSERT_SAME(gUnknownName, "nothing");

    Reset();
    gAnswerUnknown = true;
    ASSERT(Command_Run(gBot, "/nothing"));

    Reset();
    ASSERT_FALSE(Command_Run(gBot, "/healabcdefghijklmnopqrstuvwxyzabcdefg"));
    ASSERT_EQ(gUnknown, 1);
    ASSERT_EQ(gRan, 0);

    Reset();
    ASSERT_FALSE(Command_Run(gBot, "/"));
    ASSERT_EQ(gUnknown, 1);
}

test Refused() {
    ASSERT(Command_SetFlags("guarded", 1));
    ASSERT_EQ(Command_GetFlags("GUARDED"), 1);
    ASSERT_FALSE(Command_SetFlags("nothing", 1));

    Reset();
    ASSERT(Command_Run(gBot, "/guarded"));
    ASSERT_EQ(gRan, 0);
    ASSERT_EQ(gPerformed, 0);

    ASSERT(Command_SetFlags("guarded", 0));
    Reset();
    ASSERT(Command_Run(gBot, "/guarded"));
    ASSERT_EQ(gRan, 1);
}

test Access() {
    ASSERT(Command_SetRestricted("secret"));
    ASSERT(Command_IsRestricted("secret"));
    ASSERT_FALSE(Command_IsAllowed("secret", gBot));

    Reset();
    ASSERT_FALSE(Command_Run(gBot, "/secret"));
    ASSERT_EQ(gRan, 0);
    ASSERT_EQ(gDenied, 1);
    ASSERT_EQ(gUnknown, 1);
    ASSERT_SAME(gUnknownName, "secret");

    Reset();
    gAnswerDenied = true;
    ASSERT(Command_Run(gBot, "/secret"));
    ASSERT_EQ(gUnknown, 0);

    ASSERT(Command_Allow("secret", gBot));
    ASSERT(Command_IsAllowed("secret", gBot));
    Reset();
    ASSERT(Command_Run(gBot, "/secret"));
    ASSERT_EQ(gRan, 1);

    ASSERT(Command_Allow("cure", gBot, false));
    ASSERT_FALSE(Command_IsAllowed("heal", gBot));
    Reset();
    ASSERT_FALSE(Command_Run(gBot, "/heal"));
    ASSERT_EQ(gDenied, 1);
    ASSERT_EQ(gRan, 0);

    ASSERT_FALSE(Command_Allow("heal", INVALID_PLAYER_ID));
    ASSERT_FALSE(Command_Allow("nothing", gBot));
}

test ThroughTheCallback() {
    Reset();
    ASSERT_EQ(CallLocalFunction("OnPlayerCommandText", "is", gBot, "/cure 5"), 0);
    ASSERT_EQ(gRan, 0);
    ASSERT_EQ(gDenied, 1);
    ASSERT_EQ(gUnknown, 1);

    ASSERT(Command_Allow("heal", gBot));
    Reset();
    ASSERT_EQ(CallLocalFunction("OnPlayerCommandText", "is", gBot, "/cure 5"), 1);
    ASSERT_EQ(gRan, 1);
    ASSERT_SAME(gParams, "5");

    Reset();
    ASSERT_EQ(CallLocalFunction("OnPlayerCommandText", "is", gBot, "/nothing"), 0);
}
