# SSI\group

```pawn
#include <SSI\group>
```

## Requirements

- `SSI\bits`
- `SSI\collection`
- `SSI\dictionary`
- `SSI\hooks`

## Quick Start

Groups of players, as y_groups keeps them: a name, its members and what they
may do.

```pawn
#include <SSI\command>
#include <SSI\group>

new
    Group:ModeratorGroup,
    Group:JailedGroup
;

hook OnGameModeInit() {
    new const
        Group:helper = Group_Create("Helper")
    ;

    ModeratorGroup = Group_Create("Moderator");
    Group_SetParent(ModeratorGroup, helper);
    Group_AllowCommand(ModeratorGroup, "ban");

    JailedGroup = Group_Create("Jailed");
    Group_DenyCommand(JailedGroup, "help");

    return 1;
}
```

- A group has a name, read in any case by `Group_GetByName`. Groups are
  never destroyed.
- A player joins and leaves groups with `Group_AddPlayer` and
  `Group_RemovePlayer`, and leaves them all on leaving the server.
- A group may have a parent. A member of a group counts as a member of its
  parent, and of the parent of that, so ranks are a chain: an administrator
  whose group has the moderator group as parent is a moderator too.
- Every player keeps the groups they count as a member of as bits, worked out
  again only when they join or leave a group or a parent changes, so asking
  is a test of one bit.
- `foreach (new playerid : GroupMember[groupid])` walks the players who
  count as members of a group, those of the groups below it included, as
  `GroupMember` of y_groups does. Only this file changes the collection. A
  player leaves the walks when they leave the server, and
  `Group_HasPlayer` still answers for them until the hooks of
  `OnPlayerDisconnect` are over.
- With `SSI\command` included before this file, a group allows or
  denies commands. `Group_AllowCommand` restricts the command, so a player may use
  it while they count as a member of a group that allows it.
  `Group_DenyCommand` takes a command from the members of a group, and a
  denial wins over any allowance, as `DENY` does in y_groups. The groups
  answer `OnPlayerCommandAccess`, so `Command_Allow` for a player still wins.
- The bits are sets of `SSI\bits`, so `MAX_GROUPS` may be raised past
  32 and they take more cells.

## API

### `Group_Create`

```pawn
forward Group:Group_Create(const name[]);
```

Create a group.

| Parameter | Description |
| --- | --- |
| `name` | Its name, unique in any case. |

**Returns**

- the group
- `INVALID_GROUP_ID` when:
    + `MAX_GROUPS` already exist
    + `name` is empty, as long as `MAX_GROUP_NAME` or longer, or taken

### `Group_IsValid`

```pawn
forward bool:Group_IsValid(Group:groupid);
```

Whether a group exists.

| Parameter | Description |
| --- | --- |
| `groupid` | The group. |

**Returns**

- `true` it does
- `false` it does not

### `Group_Count`

```pawn
forward Group_Count();
```

The number of groups.

**Returns**

The count.

### `Group_GetByName`

```pawn
forward Group:Group_GetByName(const name[]);
```

The group with a name, in any case.

| Parameter | Description |
| --- | --- |
| `name` | The name. |

**Returns**

- the group
- `INVALID_GROUP_ID` no group has it

### `Group_GetName`

```pawn
forward bool:Group_GetName(Group:groupid, output[], size = sizeof (output));
```

The name of a group, as it was created.

| Parameter | Description |
| --- | --- |
| `groupid` | The group. |
| `output` | Array for the name. |
| `size` | Size of `output`. |

**Returns**

- `true` it was written
- `false` `groupid` is not a group

### `Group_SetParent`

```pawn
forward bool:Group_SetParent(Group:groupid, Group:parent);
```

Set the parent of a group, whose members then count as members of the parent.

| Parameter | Description |
| --- | --- |
| `groupid` | The group. |
| `parent` | The parent, or `INVALID_GROUP_ID` for none. |

**Returns**

- `true` it was set
- `false` when:
    + `groupid` is not a group
    + `parent` is neither a group nor `INVALID_GROUP_ID`
    + the group is `parent` or one of its parents

### `Group_GetParent`

```pawn
forward Group:Group_GetParent(Group:groupid);
```

The parent of a group.

| Parameter | Description |
| --- | --- |
| `groupid` | The group. |

**Returns**

- the parent
- `INVALID_GROUP_ID` it has none, or `groupid` is not a group

### `Group_AddPlayer`

```pawn
forward bool:Group_AddPlayer(Group:groupid, playerid);
```

Add a player to a group.

| Parameter | Description |
| --- | --- |
| `groupid` | The group. |
| `playerid` | The player. |

**Returns**

- `true` they are in it
- `false` when:
    + `groupid` is not a group
    + they are not connected
    + they are in it already
    + `OnPlayerJoinGroup` refused

### `Group_RemovePlayer`

```pawn
forward bool:Group_RemovePlayer(Group:groupid, playerid);
```

Take a player out of a group.

| Parameter | Description |
| --- | --- |
| `groupid` | The group. |
| `playerid` | The player. |

**Returns**

- `true` they left it
- `false` when:
    + `groupid` is not a group
    + they are not connected
    + they were not in it

### `Group_HasPlayer`

```pawn
forward bool:Group_HasPlayer(Group:groupid, playerid, bool:inherited = true);
```

Whether a player counts as a member of a group.

| Parameter | Description |
| --- | --- |
| `groupid` | The group. |
| `playerid` | The player. |
| `inherited` | Whether a member of a group whose parent, or a parent above, is this one counts. |

**Returns**

- `true` they do
- `false` when:
    + they do not
    + `groupid` is not a group
    + they are not connected

### `Group_AllowCommand`

```pawn
forward bool:Group_AllowCommand(Group:groupid, const command[]);
```

Let the members of a group use a command.

The command becomes restricted, so only players a group allows it to
may use it. A denial of the same group is lifted.

| Parameter | Description |
| --- | --- |
| `groupid` | The group. |
| `command` | The name or an alias of the command. |

**Returns**

- `true` the group allows it
- `false` when:
    + `groupid` is not a group
    + `command` names no command

### `Group_DenyCommand`

```pawn
forward bool:Group_DenyCommand(Group:groupid, const command[]);
```

Take a command from the members of a group.

A denial wins over the allowance of any other group. An allowance of the
same group is lifted.

| Parameter | Description |
| --- | --- |
| `groupid` | The group. |
| `command` | The name or an alias of the command. |

**Returns**

- `true` the group denies it
- `false` when:
    + `groupid` is not a group
    + `command` names no command

### `Group_IsCommandAllowed`

```pawn
forward bool:Group_IsCommandAllowed(Group:groupid, const command[]);
```

Whether a group allows a command.

Only the group itself, not its parents.

| Parameter | Description |
| --- | --- |
| `groupid` | The group. |
| `command` | The name or an alias of the command. |

**Returns**

- `true` it does
- `false` it does not, or either is unknown

### `Group_IsCommandDenied`

```pawn
forward bool:Group_IsCommandDenied(Group:groupid, const command[]);
```

Whether a group denies a command.

Only the group itself, not its parents.

| Parameter | Description |
| --- | --- |
| `groupid` | The group. |
| `command` | The name or an alias of the command. |

**Returns**

- `true` it does
- `false` it does not, or either is unknown

## Events

### `OnPlayerJoinGroup`

```pawn
event OnPlayerJoinGroup(playerid, Group:groupid);
```

A player is about to join a group.

| Parameter | Description |
| --- | --- |
| `playerid` | The player. |
| `groupid` | The group. |

**Returns**

- `0` they join it
- `1` they do not

### `OnPlayerJoinedGroup`

```pawn
event OnPlayerJoinedGroup(playerid, Group:groupid);
```

A player joined a group.

The return value is not used.

| Parameter | Description |
| --- | --- |
| `playerid` | The player. |
| `groupid` | The group. |

### `OnPlayerLeftGroup`

```pawn
event OnPlayerLeftGroup(playerid, Group:groupid);
```

A player left a group.

Not called when they leave the server. The return value is not used.

| Parameter | Description |
| --- | --- |
| `playerid` | The player. |
| `groupid` | The group. |
