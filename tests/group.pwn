#define SSI_TESTS
#define SSI_TEST_EXIT

#include <open.mp>
#include <SSI\iterator>
#include <SSI\command>
#include <SSI\group>
#include <SSI\test>
#include <SSI\hooks>

static
    gBot = INVALID_PLAYER_ID,
    Group:HelperGroup,
    Group:ModeratorGroup,
    Group:AdministratorGroup,
    Group:OtherGroup,
    gJoined,
    gLeft,
    bool:gRefuse
;

main() {
}

CMD:report(playerid, params[]) {
    return 1;
}

CMD:kick(playerid, params[]) {
    return 1;
}

CMD:ban(playerid, params[]) {
    return 1;
}

CMD:setrank(playerid, params[]) {
    return 1;
}

CMD:help(playerid, params[]) {
    return 1;
}

hook OnPlayerJoinGroup(playerid, Group:groupid) {
    return gRefuse;
}

hook OnPlayerJoinedGroup(playerid, Group:groupid) {
    ++gJoined;

    return 0;
}

hook OnPlayerLeftGroup(playerid, Group:groupid) {
    ++gLeft;

    return 0;
}

test BotConnects() {
    gBot = NPC_Create("GroupBot");
    ASSERT(IsPlayerConnected(gBot));
}

test Creates() {
    new
        name[MAX_GROUP_NAME]
    ;

    HelperGroup = Group_Create("Helper");
    ModeratorGroup = Group_Create("Moderator");
    AdministratorGroup = Group_Create("Administrator");
    OtherGroup = Group_Create("Other");

    ASSERT_EQ(Group_Count(), 4);
    ASSERT(Group_Create("HELPER") == INVALID_GROUP_ID);
    ASSERT(Group_Create("") == INVALID_GROUP_ID);
    ASSERT(Group_GetByName("moderator") == ModeratorGroup);
    ASSERT(Group_GetByName("nothing") == INVALID_GROUP_ID);
    ASSERT(Group_GetName(AdministratorGroup, name));
    ASSERT_SAME(name, "Administrator");
}

test Parents() {
    ASSERT(Group_SetParent(ModeratorGroup, HelperGroup));
    ASSERT(Group_SetParent(AdministratorGroup, ModeratorGroup));
    ASSERT(Group_GetParent(AdministratorGroup) == ModeratorGroup);
    ASSERT_FALSE(Group_SetParent(HelperGroup, AdministratorGroup));
    ASSERT_FALSE(Group_SetParent(HelperGroup, HelperGroup));
    ASSERT_FALSE(Group_SetParent(HelperGroup, Group:99));
}

test Commands() {
    ASSERT(Group_AllowCommand(HelperGroup, "report"));
    ASSERT(Group_AllowCommand(ModeratorGroup, "kick"));
    ASSERT(Group_AllowCommand(ModeratorGroup, "ban"));
    ASSERT(Group_AllowCommand(AdministratorGroup, "setrank"));
    ASSERT(Group_AllowCommand(OtherGroup, "ban"));
    ASSERT_FALSE(Group_AllowCommand(HelperGroup, "nothing"));

    ASSERT(Group_IsCommandAllowed(ModeratorGroup, "ban"));
    ASSERT_FALSE(Group_IsCommandAllowed(AdministratorGroup, "ban"));
    ASSERT(Command_IsRestricted("ban"));
    ASSERT_FALSE(Command_IsRestricted("help"));

    ASSERT_FALSE(Command_Run(gBot, "/report"));
    ASSERT_FALSE(Command_Run(gBot, "/ban"));
    ASSERT(Command_Run(gBot, "/help"));
}

test Ranks() {
    ASSERT(Group_AddPlayer(ModeratorGroup, gBot));
    ASSERT_EQ(gJoined, 1);
    ASSERT_FALSE(Group_AddPlayer(ModeratorGroup, gBot));

    ASSERT(Group_HasPlayer(ModeratorGroup, gBot));
    ASSERT(Group_HasPlayer(HelperGroup, gBot));
    ASSERT_FALSE(Group_HasPlayer(HelperGroup, gBot, false));
    ASSERT_FALSE(Group_HasPlayer(AdministratorGroup, gBot));

    ASSERT(Command_Run(gBot, "/report"));
    ASSERT(Command_Run(gBot, "/kick"));
    ASSERT(Command_Run(gBot, "/ban"));
    ASSERT_FALSE(Command_Run(gBot, "/setrank"));

    ASSERT(Group_RemovePlayer(ModeratorGroup, gBot));
    ASSERT_EQ(gLeft, 1);
    ASSERT_FALSE(Group_RemovePlayer(ModeratorGroup, gBot));
    ASSERT_FALSE(Command_Run(gBot, "/kick"));
    ASSERT_FALSE(Command_Run(gBot, "/report"));

    ASSERT(Group_AddPlayer(AdministratorGroup, gBot));
    ASSERT(Command_Run(gBot, "/setrank"));
    ASSERT(Command_Run(gBot, "/kick"));
    ASSERT(Command_Run(gBot, "/report"));
    ASSERT(Group_RemovePlayer(AdministratorGroup, gBot));
}

test SharedCommand() {
    ASSERT(Group_AddPlayer(OtherGroup, gBot));
    ASSERT(Command_Run(gBot, "/ban"));
    ASSERT_FALSE(Command_Run(gBot, "/kick"));
    ASSERT(Group_RemovePlayer(OtherGroup, gBot));
    ASSERT_FALSE(Command_Run(gBot, "/ban"));
}

test LateCommand() {
    ASSERT(Group_AddPlayer(HelperGroup, gBot));
    ASSERT(Command_Run(gBot, "/help"));
    ASSERT(Group_AllowCommand(AdministratorGroup, "help"));
    ASSERT_FALSE(Command_Run(gBot, "/help"));
    ASSERT(Group_RemovePlayer(HelperGroup, gBot));
}

test LateParent() {
    ASSERT(Group_AddPlayer(OtherGroup, gBot));
    ASSERT_FALSE(Command_Run(gBot, "/report"));
    ASSERT(Group_SetParent(OtherGroup, HelperGroup));
    ASSERT(Command_Run(gBot, "/report"));
    ASSERT(Group_SetParent(OtherGroup, INVALID_GROUP_ID));
    ASSERT_FALSE(Command_Run(gBot, "/report"));
    ASSERT(Group_RemovePlayer(OtherGroup, gBot));
}

test Refused() {
    gRefuse = true;
    ASSERT_FALSE(Group_AddPlayer(HelperGroup, gBot));
    ASSERT_FALSE(Group_HasPlayer(HelperGroup, gBot));
    gRefuse = false;
    ASSERT_FALSE(Group_AddPlayer(HelperGroup, INVALID_PLAYER_ID));
    ASSERT_FALSE(Group_AddPlayer(Group:99, gBot));
}

test Deny() {
    new const
        Group:jailed = Group_Create("Jailed")
    ;

    ASSERT(Group_DenyCommand(jailed, "help"));
    ASSERT(Group_IsCommandDenied(jailed, "help"));
    ASSERT_FALSE(Group_IsCommandAllowed(jailed, "help"));

    ASSERT(Group_AddPlayer(AdministratorGroup, gBot));
    ASSERT(Command_Run(gBot, "/help"));
    ASSERT(Group_AddPlayer(jailed, gBot));
    ASSERT_FALSE(Command_Run(gBot, "/help"));

    ASSERT(Group_DenyCommand(jailed, "kick"));
    ASSERT_FALSE(Command_Run(gBot, "/kick"));
    ASSERT(Command_Run(gBot, "/ban"));

    ASSERT(Command_Allow("kick", gBot));
    ASSERT(Command_Run(gBot, "/kick"));

    ASSERT(Group_AllowCommand(jailed, "help"));
    ASSERT_FALSE(Group_IsCommandDenied(jailed, "help"));
    ASSERT(Command_Run(gBot, "/help"));

    ASSERT(Group_RemovePlayer(jailed, gBot));
    ASSERT(Group_RemovePlayer(AdministratorGroup, gBot));
}

test Members() {
    new
        count
    ;

    foreach (new i : GroupMember[HelperGroup]) {
        ++count;
    }

    ASSERT_EQ(count, 0);

    ASSERT(Group_AddPlayer(AdministratorGroup, gBot));

    count = 0;

    foreach (new i : GroupMember[HelperGroup]) {
        ASSERT_EQ(i, gBot);
        ++count;
    }

    ASSERT_EQ(count, 1);
    ASSERT_EQ(Collection_Count(GroupMember[ModeratorGroup]), 1);
    ASSERT_EQ(Collection_Count(GroupMember[AdministratorGroup]), 1);
    ASSERT_EQ(Collection_Count(GroupMember[OtherGroup]), 0);

    ASSERT(Group_RemovePlayer(AdministratorGroup, gBot));
    ASSERT_EQ(Collection_Count(GroupMember[HelperGroup]), 0);
    ASSERT_EQ(Collection_Count(GroupMember[AdministratorGroup]), 0);

    ASSERT(Group_AddPlayer(OtherGroup, gBot));
    ASSERT(Group_SetParent(OtherGroup, ModeratorGroup));
    ASSERT_EQ(Collection_Count(GroupMember[HelperGroup]), 1);
    ASSERT(Group_SetParent(OtherGroup, INVALID_GROUP_ID));
    ASSERT_EQ(Collection_Count(GroupMember[HelperGroup]), 0);
    ASSERT_EQ(Collection_Count(GroupMember[OtherGroup]), 1);
    ASSERT(Group_RemovePlayer(OtherGroup, gBot));
}
