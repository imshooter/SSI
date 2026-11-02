#if defined _INC_SSI_GROUP
    #endinput
#endif
#define _INC_SSI_GROUP

#include <open.mp>
#include <SSI\bits>
#include <SSI\collection>
#include <SSI\dictionary>
#include <SSI\hooks>

/**
 * Groups of players, as y_groups keeps them: a name, its members and what they
 * may do.
 *
 *     #include <SSI\command>
 *     #include <SSI\group>
 *
 *     new
 *         Group:ModeratorGroup,
 *         Group:JailedGroup
 *     ;
 *
 *     hook OnGameModeInit() {
 *         new const
 *             Group:helper = Group_Create("Helper")
 *         ;
 *
 *         ModeratorGroup = Group_Create("Moderator");
 *         Group_SetParent(ModeratorGroup, helper);
 *         Group_AllowCommand(ModeratorGroup, "ban");
 *
 *         JailedGroup = Group_Create("Jailed");
 *         Group_DenyCommand(JailedGroup, "help");
 *
 *         return 1;
 *     }
 *
 * - A group has a name, read in any case by `Group_GetByName`. Groups are
 *   never destroyed.
 * - A player joins and leaves groups with `Group_AddPlayer` and
 *   `Group_RemovePlayer`, and leaves them all on leaving the server.
 * - A group may have a parent. A member of a group counts as a member of its
 *   parent, and of the parent of that, so ranks are a chain: an administrator
 *   whose group has the moderator group as parent is a moderator too.
 * - Every player keeps the groups they count as a member of as bits, worked out
 *   again only when they join or leave a group or a parent changes, so asking
 *   is a test of one bit.
 * - `foreach (new playerid : GroupMember[groupid])` walks the players who
 *   count as members of a group, those of the groups below it included, as
 *   `GroupMember` of y_groups does. Only this file changes the collection. A
 *   player leaves the walks when they leave the server, and
 *   `Group_HasPlayer` still answers for them until the hooks of
 *   `OnPlayerDisconnect` are over.
 * - With `SSI\command` included before this file, a group allows or
 *   denies commands. `Group_AllowCommand` restricts the command, so a player may use
 *   it while they count as a member of a group that allows it.
 *   `Group_DenyCommand` takes a command from the members of a group, and a
 *   denial wins over any allowance, as `DENY` does in y_groups. The groups
 *   answer `OnPlayerCommandAccess`, so `Command_Allow` for a player still wins.
 * - The bits are sets of `SSI\bits`, so `MAX_GROUPS` may be raised past
 *   32 and they take more cells.
 */

/**
 * # Header
 */

#if !defined MAX_GROUPS
    #define MAX_GROUPS (Group:32)
#endif

#if !defined MAX_GROUP_NAME
    #define MAX_GROUP_NAME (24)
#endif

#define INVALID_GROUP_ID (Group:-1)

static enum _:E_GROUP_DATA {
    E_GROUP_NAME[MAX_GROUP_NAME],
    Group:E_GROUP_PARENT
};

static
    Dictionary:GroupByName<MAX_GROUPS, MAX_GROUP_NAME>
;

new
    Collection:GroupMember[MAX_GROUPS]<MAX_PLAYERS>
;

#define GroupMember: _:

static
    gGroupData[MAX_GROUPS][E_GROUP_DATA],
    Group:gGroupCount
;

static
    Bits:GroupClosure[MAX_GROUPS]<MAX_GROUPS>,
    Bits:PlayerDirectGroup[MAX_PLAYERS]<MAX_GROUPS>,
    Bits:PlayerMemberGroup[MAX_PLAYERS]<MAX_GROUPS>
;

#if defined _INC_SSI_COMMAND
    static
        Bits:CommandAllowGroup[MAX_COMMANDS]<MAX_GROUPS>,
        Bits:CommandDenyGroup[MAX_COMMANDS]<MAX_GROUPS>
    ;
#endif

/**
 * # Functions
 */

/**
 * @brief      Create a group.
 *
 * @param      name  Its name, unique in any case.
 *
 * @return     - the group
 *             - `INVALID_GROUP_ID` when:
 *                 + `MAX_GROUPS` already exist
 *                 + `name` is empty, as long as `MAX_GROUP_NAME` or longer, or taken
 */
forward Group:Group_Create(const name[]);

/**
 * @brief      Whether a group exists.
 *
 * @param      groupid  The group.
 *
 * @return     - `true` it does
 *             - `false` it does not
 */
forward bool:Group_IsValid(Group:groupid);

/**
 * @brief      The number of groups.
 *
 * @return     The count.
 */
forward Group_Count();

/**
 * @brief      The group with a name, in any case.
 *
 * @param      name  The name.
 *
 * @return     - the group
 *             - `INVALID_GROUP_ID` no group has it
 */
forward Group:Group_GetByName(const name[]);

/**
 * @brief      The name of a group, as it was created.
 *
 * @param      groupid  The group.
 * @param      output   Array for the name.
 * @param      size     Size of `output`.
 *
 * @return     - `true` it was written
 *             - `false` `groupid` is not a group
 */
forward bool:Group_GetName(Group:groupid, output[], size = sizeof (output));

/**
 * @brief      Set the parent of a group, whose members then count as members of
 *             the parent.
 *
 * @param      groupid  The group.
 * @param      parent   The parent, or `INVALID_GROUP_ID` for none.
 *
 * @return     - `true` it was set
 *             - `false` when:
 *                 + `groupid` is not a group
 *                 + `parent` is neither a group nor `INVALID_GROUP_ID`
 *                 + the group is `parent` or one of its parents
 */
forward bool:Group_SetParent(Group:groupid, Group:parent);

/**
 * @brief      The parent of a group.
 *
 * @param      groupid  The group.
 *
 * @return     - the parent
 *             - `INVALID_GROUP_ID` it has none, or `groupid` is not a group
 */
forward Group:Group_GetParent(Group:groupid);

/**
 * @brief      Add a player to a group.
 *
 * @param      groupid   The group.
 * @param      playerid  The player.
 *
 * @return     - `true` they are in it
 *             - `false` when:
 *                 + `groupid` is not a group
 *                 + they are not connected
 *                 + they are in it already
 *                 + `OnPlayerJoinGroup` refused
 */
forward bool:Group_AddPlayer(Group:groupid, playerid);

/**
 * @brief      Take a player out of a group.
 *
 * @param      groupid   The group.
 * @param      playerid  The player.
 *
 * @return     - `true` they left it
 *             - `false` when:
 *                 + `groupid` is not a group
 *                 + they are not connected
 *                 + they were not in it
 */
forward bool:Group_RemovePlayer(Group:groupid, playerid);

/**
 * @brief      Whether a player counts as a member of a group.
 *
 * @param      groupid    The group.
 * @param      playerid   The player.
 * @param      inherited  Whether a member of a group whose parent, or a parent
 *                        above, is this one counts.
 *
 * @return     - `true` they do
 *             - `false` when:
 *                 + they do not
 *                 + `groupid` is not a group
 *                 + they are not connected
 */
forward bool:Group_HasPlayer(Group:groupid, playerid, bool:inherited = true);

#if defined _INC_SSI_COMMAND
    /**
     * @brief      Let the members of a group use a command.
     *
     * The command becomes restricted, so only players a group allows it to
     * may use it. A denial of the same group is lifted.
     *
     * @param      groupid  The group.
     * @param      command  The name or an alias of the command.
     *
     * @return     - `true` the group allows it
     *             - `false` when:
     *                 + `groupid` is not a group
     *                 + `command` names no command
     */
    forward bool:Group_AllowCommand(Group:groupid, const command[]);

    /**
     * @brief      Take a command from the members of a group.
     *
     * A denial wins over the allowance of any other group. An allowance of the
     * same group is lifted.
     *
     * @param      groupid  The group.
     * @param      command  The name or an alias of the command.
     *
     * @return     - `true` the group denies it
     *             - `false` when:
     *                 + `groupid` is not a group
     *                 + `command` names no command
     */
    forward bool:Group_DenyCommand(Group:groupid, const command[]);

    /**
     * @brief      Whether a group allows a command.
     *
     * Only the group itself, not its parents.
     *
     * @param      groupid  The group.
     * @param      command  The name or an alias of the command.
     *
     * @return     - `true` it does
     *             - `false` it does not, or either is unknown
     */
    forward bool:Group_IsCommandAllowed(Group:groupid, const command[]);

    /**
     * @brief      Whether a group denies a command.
     *
     * Only the group itself, not its parents.
     *
     * @param      groupid  The group.
     * @param      command  The name or an alias of the command.
     *
     * @return     - `true` it does
     *             - `false` it does not, or either is unknown
     */
    forward bool:Group_IsCommandDenied(Group:groupid, const command[]);
#endif

/**
 * # Events
 */

/**
 * @brief      A player is about to join a group.
 *
 * @param      playerid  The player.
 * @param      groupid   The group.
 *
 * @return     - `0` they join it
 *             - `1` they do not
 */
event OnPlayerJoinGroup(playerid, Group:groupid);

/**
 * @brief      A player joined a group.
 *
 * The return value is not used.
 *
 * @param      playerid  The player.
 * @param      groupid   The group.
 */
event OnPlayerJoinedGroup(playerid, Group:groupid);

/**
 * @brief      A player left a group.
 *
 * Not called when they leave the server. The return value is not used.
 *
 * @param      playerid  The player.
 * @param      groupid   The group.
 */
event OnPlayerLeftGroup(playerid, Group:groupid);

/**
 * # Internal
 */

static stock bool:SSI@Group_Key(const name[], key[], size = sizeof (key)) {
    new
        length,
        c
    ;

    while ((c = name[length]) != EOS) {
        if (length == size - 1) {
            return false;
        }

        key[length++] = ('A' <= c <= 'Z') ? (c | 0x20) : c;
    }

    key[length] = EOS;

    return length != 0;
}

static stock SSI@Group_Close() {
    for (new Group:groupid; groupid != gGroupCount; ++groupid) {
        Bits_Clear(GroupClosure[groupid]);

        for (new Group:above = groupid; above != INVALID_GROUP_ID; above = gGroupData[above][E_GROUP_PARENT]) {
            Bits_Let(GroupClosure[groupid], above);
        }
    }
}

static stock SSI@Group_Members(playerid) {
    new
        Bits:member<MAX_GROUPS>
    ;

    foreach (new Group:groupid : Bits(PlayerDirectGroup[playerid])) {
        Bits_Or(member, GroupClosure[groupid]);
    }

    for (new Group:groupid; groupid != gGroupCount; ++groupid) {
        new const
            bool:was = Bits_Test(PlayerMemberGroup[playerid], groupid),
            bool:now = Bits_Test(member, groupid)
        ;

        if (was == now) {
            continue;
        }

        if (now) {
            Collection_Add(GroupMember[groupid], playerid);
        } else {
            Collection_Remove(GroupMember[groupid], playerid);
        }
    }

    Bits_Copy(PlayerMemberGroup[playerid], member);
}

static stock SSI@Group_Rebuild() {
    SSI@Group_Close();

    for (new playerid; playerid != MAX_PLAYERS; ++playerid) {
        if (IsPlayerConnected(playerid)) {
            SSI@Group_Members(playerid);
        }
    }
}

/**
 * # Group
 */

stock Group:Group_Create(const name[]) {
    if (gGroupCount == MAX_GROUPS) {
        return INVALID_GROUP_ID;
    }

    new
        key[MAX_GROUP_NAME]
    ;

    if (!SSI@Group_Key(name, key)) {
        return INVALID_GROUP_ID;
    }

    if (Dictionary_Contains(GroupByName<>, key)) {
        return INVALID_GROUP_ID;
    }

    new const
        Group:groupid = gGroupCount++
    ;

    strcopy(gGroupData[groupid][E_GROUP_NAME], name, MAX_GROUP_NAME);
    gGroupData[groupid][E_GROUP_PARENT] = INVALID_GROUP_ID;
    Bits_Let(GroupClosure[groupid], groupid);
    Dictionary_Set(GroupByName<>, key, groupid);

    return groupid;
}

stock bool:Group_IsValid(Group:groupid) {
    return (0 <= _:groupid < _:gGroupCount);
}

stock Group_Count() {
    return _:gGroupCount;
}

stock Group:Group_GetByName(const name[]) {
    new
        key[MAX_GROUP_NAME],
        Group:groupid
    ;

    if (!SSI@Group_Key(name, key)) {
        return INVALID_GROUP_ID;
    }

    if (!Dictionary_Get(GroupByName<>, key, groupid)) {
        return INVALID_GROUP_ID;
    }

    return groupid;
}

stock bool:Group_GetName(Group:groupid, output[], size = sizeof (output)) {
    if (!Group_IsValid(groupid)) {
        return false;
    }

    strcopy(output, gGroupData[groupid][E_GROUP_NAME], size);

    return true;
}

stock bool:Group_SetParent(Group:groupid, Group:parent) {
    if (!Group_IsValid(groupid)) {
        return false;
    }

    if (parent == INVALID_GROUP_ID) {
        gGroupData[groupid][E_GROUP_PARENT] = INVALID_GROUP_ID;
        SSI@Group_Rebuild();

        return true;
    }

    if (!Group_IsValid(parent)) {
        return false;
    }

    for (new Group:above = parent; above != INVALID_GROUP_ID; above = gGroupData[above][E_GROUP_PARENT]) {
        if (above == groupid) {
            return false;
        }
    }

    gGroupData[groupid][E_GROUP_PARENT] = parent;
    SSI@Group_Rebuild();

    return true;
}

stock Group:Group_GetParent(Group:groupid) {
    if (!Group_IsValid(groupid)) {
        return INVALID_GROUP_ID;
    }

    return gGroupData[groupid][E_GROUP_PARENT];
}

/**
 * # Members
 */

stock bool:Group_AddPlayer(Group:groupid, playerid) {
    if (!Group_IsValid(groupid)) {
        return false;
    }

    if (!IsPlayerConnected(playerid)) {
        return false;
    }

    if (Bits_Test(PlayerDirectGroup[playerid], groupid)) {
        return false;
    }

    if (call OnPlayerJoinGroup(playerid, groupid)) {
        return false;
    }

    Bits_Let(PlayerDirectGroup[playerid], groupid);
    SSI@Group_Members(playerid);

    call OnPlayerJoinedGroup(playerid, groupid);

    return true;
}

stock bool:Group_RemovePlayer(Group:groupid, playerid) {
    if (!Group_IsValid(groupid)) {
        return false;
    }

    if (!IsPlayerConnected(playerid)) {
        return false;
    }

    if (!Bits_Test(PlayerDirectGroup[playerid], groupid)) {
        return false;
    }

    Bits_Vet(PlayerDirectGroup[playerid], groupid);
    SSI@Group_Members(playerid);

    call OnPlayerLeftGroup(playerid, groupid);

    return true;
}

stock bool:Group_HasPlayer(Group:groupid, playerid, bool:inherited = true) {
    if (!Group_IsValid(groupid)) {
        return false;
    }

    if (!IsPlayerConnected(playerid)) {
        return false;
    }

    if (inherited) {
        return Bits_Test(PlayerMemberGroup[playerid], groupid);
    }

    return Bits_Test(PlayerDirectGroup[playerid], groupid);
}

#if defined _INC_SSI_COMMAND
    /**
     * # Commands
     */

    stock bool:Group_AllowCommand(Group:groupid, const command[]) {
        if (!Group_IsValid(groupid)) {
            return false;
        }

        new const
            Command:commandid = Command_GetByName(command)
        ;

        if (commandid == INVALID_COMMAND_ID) {
            return false;
        }

        Bits_Let(CommandAllowGroup[commandid], groupid);
        Bits_Vet(CommandDenyGroup[commandid], groupid);
        Command_SetRestricted(command);

        return true;
    }

    stock bool:Group_DenyCommand(Group:groupid, const command[]) {
        if (!Group_IsValid(groupid)) {
            return false;
        }

        new const
            Command:commandid = Command_GetByName(command)
        ;

        if (commandid == INVALID_COMMAND_ID) {
            return false;
        }

        Bits_Let(CommandDenyGroup[commandid], groupid);
        Bits_Vet(CommandAllowGroup[commandid], groupid);

        return true;
    }

    stock bool:Group_IsCommandAllowed(Group:groupid, const command[]) {
        if (!Group_IsValid(groupid)) {
            return false;
        }

        new const
            Command:commandid = Command_GetByName(command)
        ;

        if (commandid == INVALID_COMMAND_ID) {
            return false;
        }

        return Bits_Test(CommandAllowGroup[commandid], groupid);
    }

    stock bool:Group_IsCommandDenied(Group:groupid, const command[]) {
        if (!Group_IsValid(groupid)) {
            return false;
        }

        new const
            Command:commandid = Command_GetByName(command)
        ;

        if (commandid == INVALID_COMMAND_ID) {
            return false;
        }

        return Bits_Test(CommandDenyGroup[commandid], groupid);
    }
#endif

/**
 * # Calls
 */

hook OnPlayerConnect(playerid) {
    Bits_Clear(PlayerDirectGroup[playerid]);
    Bits_Clear(PlayerMemberGroup[playerid]);

    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    foreach (new Group:groupid : Bits(PlayerMemberGroup[playerid])) {
        Collection_Remove(GroupMember[groupid], playerid);
    }

    return 1;
}

#if defined _INC_SSI_COMMAND
    hook OnPlayerCommandAccess(playerid, Command:commandid) {
        new
            access
        ;

        if (Bits_Intersects(PlayerMemberGroup[playerid], CommandDenyGroup[commandid])) {
            access |= COMMAND_ACCESS_DENY;
        }

        if (Bits_Intersects(PlayerMemberGroup[playerid], CommandAllowGroup[commandid])) {
            access |= COMMAND_ACCESS_ALLOW;
        }

        return access;
    }
#endif
