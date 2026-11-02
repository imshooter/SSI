# SSI\command

```pawn
#include <SSI\command>
```

## Requirements

- `SSI\amx`
- `SSI\bits`
- `SSI\dictionary`
- `SSI\hooks`

## Quick Start

Commands, as Pawn.CMD and y_commands keep them: a function for each command,
found by its name when a player types it.

```pawn
#include <SSI\command>

CMD:heal(playerid, params[]) {
    SetPlayerHealth(playerid, 100.0);

    return 1;
}

hook OnGameModeInit() {
    Command_AddAlias("heal", "hp", "medkit");

    return 1;
}
```

- A command is a public named `@cmd_` and its name, so `CMD:` declares one
  and the script finds every one when it starts. Names are read in any case,
  and `Command_AddAlias` gives a command more of them.
- The calls that set up a command take its name or one of its aliases, as
  Pawn.CMD takes them. `Command_GetByName` gives the id the events pass.
- The params are what follows the name, without the spaces before them. They
  are empty, never `"\1"`, when nothing follows.
- A command that returns `0` is answered as an unknown one by the server.
- Every command keeps a number of flags for the script, as Pawn.CMD keeps
  them, given to the events of the command.
- Who may use a command is decided in this order. `Command_Allow` for that
  player wins. Then the hooks of `OnPlayerCommandAccess`, where a denial
  wins over an allowance. Then the command itself: everyone may use it,
  unless it is restricted. A player who may not use a command gets
  `OnPlayerCommandDenied`, then `OnPlayerUnknownCommand` when nothing
  answered it, as if the command did not exist. An alias shares all of this
  with its command.
- This prints nothing. Messages are the script's, or another include's,
  answering the events.

Other includes connect through the same calls. A library of groups restricts
the commands it hands out and answers `OnPlayerCommandAccess` for its
members, as SSI\group does. A library
of texts would answer `OnPlayerUnknownCommand` and `OnPlayerCommandDenied` in
the language of the player. The commands walk with `N` of SSI\iterator:
`foreach (new Command:commandid : N(Command_Count()))`.

`Command_Run` runs a line as if the player typed it.

## API

### `Command_GetByName`

```pawn
forward Command:Command_GetByName(const name[]);
```

The command a name or alias calls, in any case.

| Parameter | Description |
| --- | --- |
| `name` | The name, without the slash. |

**Returns**

- the command
- `INVALID_COMMAND_ID` no command has that name

### `Command_IsValid`

```pawn
forward bool:Command_IsValid(Command:commandid);
```

Whether a command exists.

| Parameter | Description |
| --- | --- |
| `commandid` | The command. |

**Returns**

- `true` it does
- `false` it does not

### `Command_Count`

```pawn
forward Command_Count();
```

The number of commands of the script.

**Returns**

The count.

### `Command_GetName`

```pawn
forward bool:Command_GetName(Command:commandid, output[], size = sizeof (output));
```

The name of a command, in lower case.

| Parameter | Description |
| --- | --- |
| `commandid` | The command. |
| `output` | Array for the name. |
| `size` | Size of `output`. |

**Returns**

- `true` it was written
- `false` `commandid` is not a command

### `Command_AddAlias`

```pawn
forward Command_AddAlias(const command[], const alias[], ...);
```

Give a command more names.

Each alias is read in any case. One that cannot be added is skipped, when:
it is empty, has a space, is as long as `MAX_COMMAND_NAME` or longer, is the
name of a command or alias already, or `MAX_COMMAND_NAMES` names exist.

| Parameter | Description |
| --- | --- |
| `command` | The name or an alias of the command. |
| `alias` | The first new name. |
| `...` | More new names. |

**Returns**

The number of aliases added, `0` when `command` names no command.

### `Command_SetFlags`

```pawn
forward bool:Command_SetFlags(const command[], flags);
```

Set the flags of a command.

| Parameter | Description |
| --- | --- |
| `command` | The name or an alias of the command. |
| `flags` | The flags, ORed together. |

**Returns**

- `true` they were set
- `false` `command` names no command

### `Command_GetFlags`

```pawn
forward Command_GetFlags(const command[]);
```

The flags of a command.

| Parameter | Description |
| --- | --- |
| `command` | The name or an alias of the command. |

**Returns**

The flags, `0` when `command` names no command.

### `Command_SetRestricted`

```pawn
forward bool:Command_SetRestricted(const command[], bool:restricted = true);
```

Make a command only for players allowed it, or for everyone.

A player allowed or denied it with `Command_Allow` keeps that.

| Parameter | Description |
| --- | --- |
| `command` | The name or an alias of the command. |
| `restricted` | Whether only players allowed it may use it. |

**Returns**

- `true` it was set
- `false` `command` names no command

### `Command_IsRestricted`

```pawn
forward bool:Command_IsRestricted(const command[]);
```

Whether a command is only for players allowed it.

| Parameter | Description |
| --- | --- |
| `command` | The name or an alias of the command. |

**Returns**

- `true` it is
- `false` everyone may use it, or `command` names no command

### `Command_Allow`

```pawn
forward bool:Command_Allow(const command[], playerid, bool:allow = true);
```

Allow a player a command, or deny it, whatever the command says.

It lasts until the player leaves.

| Parameter | Description |
| --- | --- |
| `command` | The name or an alias of the command. |
| `playerid` | The player. |
| `allow` | Whether they may use it. |

**Returns**

- `true` it was set
- `false` when:
    + `command` names no command
    + they are not connected

### `Command_IsAllowed`

```pawn
forward bool:Command_IsAllowed(const command[], playerid);
```

Whether a player may use a command.

| Parameter | Description |
| --- | --- |
| `command` | The name or an alias of the command. |
| `playerid` | The player. |

**Returns**

- `true` they may
- `false` when:
    + they may not
    + `command` names no command
    + they are not connected

### `Command_Run`

```pawn
forward bool:Command_Run(playerid, const text[]);
```

Run a line as if a player typed it.

| Parameter | Description |
| --- | --- |
| `playerid` | The player. |
| `text` | The line, starting with the slash. |

**Returns**

- `true` it was answered: the command ran and returned non-zero,
  an event refused it, or a hook answered it
- `false` when:
    + they are not connected
    + the line does not start with a slash
    + no command has that name and no hook answered
    + the command returned `0`

## Events

### `OnPlayerUseCommand`

```pawn
event OnPlayerUseCommand(playerid, Command:commandid, const params[], flags);
```

A player is about to run a command.

| Parameter | Description |
| --- | --- |
| `playerid` | The player. |
| `commandid` | The command. |
| `params` | What follows its name. |
| `flags` | Its flags. |

**Returns**

- `0` it runs
- `1` it does not, and the hook that refused tells them why

### `OnPlayerUsedCommand`

```pawn
event OnPlayerUsedCommand(playerid, Command:commandid, const params[], result, flags);
```

A player ran a command.

The return value is not used.

| Parameter | Description |
| --- | --- |
| `playerid` | The player. |
| `commandid` | The command. |
| `params` | What followed its name. |
| `result` | What the command returned. |
| `flags` | Its flags. |

### `OnPlayerCommandAccess`

```pawn
event OnPlayerCommandAccess(playerid, Command:commandid);
```

Whether a player may use a command, asked when `Command_Allow` was not called for them.

Asked each time they type it, so a hook answers from what it already knows.

| Parameter | Description |
| --- | --- |
| `playerid` | The player. |
| `commandid` | The command. |

**Returns**

`COMMAND_ACCESS_ALLOW`, `COMMAND_ACCESS_DENY`, both ORed, or `0`
for no opinion. A denial wins, and with no opinion the command
decides.

### `OnPlayerCommandDenied`

```pawn
event OnPlayerCommandDenied(playerid, Command:commandid, const params[]);
```

A player typed a command they may not use.

| Parameter | Description |
| --- | --- |
| `playerid` | The player. |
| `commandid` | The command. |
| `params` | What followed its name. |

**Returns**

- `0` it goes on as an unknown command
- `1` a hook told them

### `OnPlayerUnknownCommand`

```pawn
event OnPlayerUnknownCommand(playerid, const name[], const params[]);
```

A player typed a name no command has.

| Parameter | Description |
| --- | --- |
| `playerid` | The player. |
| `name` | The name, in lower case. |
| `params` | What followed it. |

**Returns**

- `0` the server answers that the command is unknown
- `1` a hook told them
