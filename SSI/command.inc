#if defined _INC_SSI_COMMAND
    #endinput
#endif
#define _INC_SSI_COMMAND

#include <open.mp>
#include <SSI\amx>
#include <SSI\bits>
#include <SSI\dictionary>
#include <SSI\hooks>

/**
 * Commands, as Pawn.CMD and y_commands keep them: a function for each command,
 * found by its name when a player types it.
 *
 *     #include <SSI\command>
 *
 *     CMD:heal(playerid, params[]) {
 *         SetPlayerHealth(playerid, 100.0);
 *
 *         return 1;
 *     }
 *
 *     hook OnGameModeInit() {
 *         Command_AddAlias("heal", "hp", "medkit");
 *
 *         return 1;
 *     }
 *
 * - A command is a public named `@cmd_` and its name, so `CMD:` declares one
 *   and the script finds every one when it starts. Names are read in any case,
 *   and `Command_AddAlias` gives a command more of them.
 * - The calls that set up a command take its name or one of its aliases, as
 *   Pawn.CMD takes them. `Command_GetByName` gives the id the events pass.
 * - The params are what follows the name, without the spaces before them. They
 *   are empty, never `"\1"`, when nothing follows.
 * - A command that returns `0` is answered as an unknown one by the server.
 * - Every command keeps a number of flags for the script, as Pawn.CMD keeps
 *   them, given to the events of the command.
 * - Who may use a command is decided in this order. `Command_Allow` for that
 *   player wins. Then the hooks of `OnPlayerCommandAccess`, where a denial
 *   wins over an allowance. Then the command itself: everyone may use it,
 *   unless it is restricted. A player who may not use a command gets
 *   `OnPlayerCommandDenied`, then `OnPlayerUnknownCommand` when nothing
 *   answered it, as if the command did not exist. An alias shares all of this
 *   with its command.
 * - This prints nothing. Messages are the script's, or another include's,
 *   answering the events.
 *
 * Other includes connect through the same calls. A library of groups restricts
 * the commands it hands out and answers `OnPlayerCommandAccess` for its
 * members, as SSI\group does. A library
 * of texts would answer `OnPlayerUnknownCommand` and `OnPlayerCommandDenied` in
 * the language of the player. The commands walk with `N` of SSI\iterator:
 * `foreach (new Command:commandid : N(Command_Count()))`.
 *
 * `Command_Run` runs a line as if the player typed it.
 */

/**
 * # Header
 */

#if !defined MAX_COMMANDS
    #define MAX_COMMANDS (Command:512)
#endif

#if !defined MAX_COMMAND_NAME
    #define MAX_COMMAND_NAME (32)
#endif

#if !defined MAX_COMMAND_NAMES
    #define MAX_COMMAND_NAMES (1024)
#endif

#define INVALID_COMMAND_ID (Command:-1)

#define CMD:%0(%1) forward @cmd_%0(%1);public @cmd_%0(%1)

#define COMMAND_ACCESS_ALLOW (1)
#define COMMAND_ACCESS_DENY (2)

static enum _:E_COMMAND_DATA {
    E_COMMAND_NAME[MAX_COMMAND_NAME],
    E_COMMAND_ADDRESS,
    E_COMMAND_FLAGS,
    bool:E_COMMAND_RESTRICTED
};

static
    Dictionary:CommandByName<MAX_COMMAND_NAMES, MAX_COMMAND_NAME>
;

static
    gCommandData[MAX_COMMANDS][E_COMMAND_DATA],
    Command:gCommandCount,
    bool:gCommandReady
;

static
    Bits:PlayerCommandAllowed[MAX_PLAYERS]<MAX_COMMANDS>,
    Bits:PlayerCommandDenied[MAX_PLAYERS]<MAX_COMMANDS>
;

/**
 * # Functions
 */

/**
 * @brief      The command a name or alias calls, in any case.
 *
 * @param      name  The name, without the slash.
 *
 * @return     - the command
 *             - `INVALID_COMMAND_ID` no command has that name
 */
forward Command:Command_GetByName(const name[]);

/**
 * @brief      Whether a command exists.
 *
 * @param      commandid  The command.
 *
 * @return     - `true` it does
 *             - `false` it does not
 */
forward bool:Command_IsValid(Command:commandid);

/**
 * @brief      The number of commands of the script.
 *
 * @return     The count.
 */
forward Command_Count();

/**
 * @brief      The name of a command, in lower case.
 *
 * @param      commandid  The command.
 * @param      output     Array for the name.
 * @param      size       Size of `output`.
 *
 * @return     - `true` it was written
 *             - `false` `commandid` is not a command
 */
forward bool:Command_GetName(Command:commandid, output[], size = sizeof (output));

/**
 * @brief      Give a command more names.
 *
 * Each alias is read in any case. One that cannot be added is skipped, when:
 * it is empty, has a space, is as long as `MAX_COMMAND_NAME` or longer, is the
 * name of a command or alias already, or `MAX_COMMAND_NAMES` names exist.
 *
 * @param      command  The name or an alias of the command.
 * @param      alias    The first new name.
 * @param      ...      More new names.
 *
 * @return     The number of aliases added, `0` when `command` names no command.
 */
forward Command_AddAlias(const command[], const alias[], ...);

/**
 * @brief      Set the flags of a command.
 *
 * @param      command  The name or an alias of the command.
 * @param      flags    The flags, ORed together.
 *
 * @return     - `true` they were set
 *             - `false` `command` names no command
 */
forward bool:Command_SetFlags(const command[], flags);

/**
 * @brief      The flags of a command.
 *
 * @param      command  The name or an alias of the command.
 *
 * @return     The flags, `0` when `command` names no command.
 */
forward Command_GetFlags(const command[]);

/**
 * @brief      Make a command only for players allowed it, or for everyone.
 *
 * A player allowed or denied it with `Command_Allow` keeps that.
 *
 * @param      command     The name or an alias of the command.
 * @param      restricted  Whether only players allowed it may use it.
 *
 * @return     - `true` it was set
 *             - `false` `command` names no command
 */
forward bool:Command_SetRestricted(const command[], bool:restricted = true);

/**
 * @brief      Whether a command is only for players allowed it.
 *
 * @param      command  The name or an alias of the command.
 *
 * @return     - `true` it is
 *             - `false` everyone may use it, or `command` names no command
 */
forward bool:Command_IsRestricted(const command[]);

/**
 * @brief      Allow a player a command, or deny it, whatever the command says.
 *
 * It lasts until the player leaves.
 *
 * @param      command   The name or an alias of the command.
 * @param      playerid  The player.
 * @param      allow     Whether they may use it.
 *
 * @return     - `true` it was set
 *             - `false` when:
 *                 + `command` names no command
 *                 + they are not connected
 */
forward bool:Command_Allow(const command[], playerid, bool:allow = true);

/**
 * @brief      Whether a player may use a command.
 *
 * @param      command   The name or an alias of the command.
 * @param      playerid  The player.
 *
 * @return     - `true` they may
 *             - `false` when:
 *                 + they may not
 *                 + `command` names no command
 *                 + they are not connected
 */
forward bool:Command_IsAllowed(const command[], playerid);

/**
 * @brief      Run a line as if a player typed it.
 *
 * @param      playerid  The player.
 * @param      text      The line, starting with the slash.
 *
 * @return     - `true` it was answered: the command ran and returned non-zero,
 *               an event refused it, or a hook answered it
 *             - `false` when:
 *                 + they are not connected
 *                 + the line does not start with a slash
 *                 + no command has that name and no hook answered
 *                 + the command returned `0`
 */
forward bool:Command_Run(playerid, const text[]);

/**
 * # Events
 */

/**
 * @brief      A player is about to run a command.
 *
 * @param      playerid   The player.
 * @param      commandid  The command.
 * @param      params     What follows its name.
 * @param      flags      Its flags.
 *
 * @return     - `0` it runs
 *             - `1` it does not, and the hook that refused tells them why
 */
event OnPlayerUseCommand(playerid, Command:commandid, const params[], flags);

/**
 * @brief      A player ran a command.
 *
 * The return value is not used.
 *
 * @param      playerid   The player.
 * @param      commandid  The command.
 * @param      params     What followed its name.
 * @param      result     What the command returned.
 * @param      flags      Its flags.
 */
event OnPlayerUsedCommand(playerid, Command:commandid, const params[], result, flags);

/**
 * @brief      Whether a player may use a command, asked when `Command_Allow`
 *             was not called for them.
 *
 * Asked each time they type it, so a hook answers from what it already knows.
 *
 * @param      playerid   The player.
 * @param      commandid  The command.
 *
 * @return     `COMMAND_ACCESS_ALLOW`, `COMMAND_ACCESS_DENY`, both ORed, or `0`
 *             for no opinion. A denial wins, and with no opinion the command
 *             decides.
 */
event OnPlayerCommandAccess(playerid, Command:commandid);

/**
 * @brief      A player typed a command they may not use.
 *
 * @param      playerid   The player.
 * @param      commandid  The command.
 * @param      params     What followed its name.
 *
 * @return     - `0` it goes on as an unknown command
 *             - `1` a hook told them
 */
event OnPlayerCommandDenied(playerid, Command:commandid, const params[]);

/**
 * @brief      A player typed a name no command has.
 *
 * @param      playerid  The player.
 * @param      name      The name, in lower case.
 * @param      params    What followed it.
 *
 * @return     - `0` the server answers that the command is unknown
 *             - `1` a hook told them
 */
event OnPlayerUnknownCommand(playerid, const name[], const params[]);

/**
 * # Internal
 */

static stock SSI@Command_Call(address, playerid, const params[]) {
    #pragma unused address, playerid, params

    __emit(
        push.s 20,
        push.s 16,
        push.c 8,
        lctrl 6,
        add.c 28,
        push.pri,
        load.s.pri 12,
        sctrl 6,
        retn
    );

    return 0;
}

static stock bool:SSI@Command_Key(const name[], key[], size = sizeof (key)) {
    new
        length,
        c
    ;

    while ((c = name[length]) > ' ') {
        if (length == size - 1) {
            key[length] = EOS;

            return false;
        }

        key[length++] = ('A' <= c <= 'Z') ? (c | 0x20) : c;
    }

    key[length] = EOS;

    return length != 0;
}

static stock bool:SSI@Command_Public(name) {
    new const
        prefix[] = "@cmd_"
    ;

    for (new i; i != sizeof (prefix) - 1; ++i) {
        if (SSI@Amx_ReadByte(name + i) != prefix[i]) {
            return false;
        }
    }

    return true;
}

static stock SSI@Command_Ready() {
    if (gCommandReady) {
        return;
    }

    gCommandReady = true;

    if (!SSI@Amx_Ready()) {
        return;
    }

    new const
        publics = SSI@Amx_Header(32),
        size = (SSI@Amx_Header(8) >>> 16) & 0xFFFF,
        count = (SSI@Amx_Header(36) - publics) / size
    ;

    new
        key[MAX_COMMAND_NAME]
    ;

    for (new index; index != count; ++index) {
        new const
            entry = SSI@amxBase + publics + index * size,
            name = SSI@amxBase + SSI@Amx_Read(entry + 4)
        ;

        if (!SSI@Command_Public(name)) {
            continue;
        }

        if (gCommandCount == MAX_COMMANDS) {
            return;
        }

        new
            length,
            c
        ;

        while ((c = SSI@Amx_ReadByte(name + 5 + length)) != EOS && length != MAX_COMMAND_NAME - 1) {
            key[length++] = ('A' <= c <= 'Z') ? (c | 0x20) : c;
        }

        key[length] = EOS;

        if (c != EOS) {
            continue;
        }

        if (Dictionary_Contains(CommandByName<>, key)) {
            continue;
        }

        new const
            Command:commandid = gCommandCount++
        ;

        strcopy(gCommandData[commandid][E_COMMAND_NAME], key, MAX_COMMAND_NAME);
        gCommandData[commandid][E_COMMAND_ADDRESS] = SSI@Amx_Read(entry);
        gCommandData[commandid][E_COMMAND_FLAGS] = 0;
        gCommandData[commandid][E_COMMAND_RESTRICTED] = false;

        Dictionary_Set(CommandByName<>, key, commandid);
    }
}

static stock bool:SSI@Command_Alias(Command:commandid, const alias[]) {
    new
        key[MAX_COMMAND_NAME]
    ;

    if (!SSI@Command_Key(alias, key)) {
        return false;
    }

    if (alias[strlen(key)] != EOS) {
        return false;
    }

    if (Dictionary_Contains(CommandByName<>, key)) {
        return false;
    }

    return Dictionary_Set(CommandByName<>, key, commandid);
}

static stock bool:SSI@Command_Allowed(playerid, Command:commandid) {
    if (Bits_Test(PlayerCommandAllowed[playerid], commandid)) {
        return true;
    }

    if (Bits_Test(PlayerCommandDenied[playerid], commandid)) {
        return false;
    }

    new const
        access = call OnPlayerCommandAccess(playerid, commandid)
    ;

    if (access & COMMAND_ACCESS_DENY) {
        return false;
    }

    if (access & COMMAND_ACCESS_ALLOW) {
        return true;
    }

    return !gCommandData[commandid][E_COMMAND_RESTRICTED];
}

/**
 * # Command
 */

stock Command:Command_GetByName(const name[]) {
    SSI@Command_Ready();

    new
        key[MAX_COMMAND_NAME],
        Command:commandid
    ;

    if (!SSI@Command_Key(name, key)) {
        return INVALID_COMMAND_ID;
    }

    if (!Dictionary_Get(CommandByName<>, key, commandid)) {
        return INVALID_COMMAND_ID;
    }

    return commandid;
}

stock bool:Command_IsValid(Command:commandid) {
    SSI@Command_Ready();

    return (0 <= _:commandid < _:gCommandCount);
}

stock Command_Count() {
    SSI@Command_Ready();

    return _:gCommandCount;
}

stock bool:Command_GetName(Command:commandid, output[], size = sizeof (output)) {
    if (!Command_IsValid(commandid)) {
        return false;
    }

    strcopy(output, gCommandData[commandid][E_COMMAND_NAME], size);

    return true;
}

stock Command_AddAlias(const command[], const alias[], ...) {
    new const
        Command:commandid = Command_GetByName(command)
    ;

    if (commandid == INVALID_COMMAND_ID) {
        return 0;
    }

    new
        added
    ;

    if (SSI@Command_Alias(commandid, alias)) {
        ++added;
    }

    new
        extra[MAX_COMMAND_NAME + 1]
    ;

    for (new arg = 2, args = numargs(); arg != args; ++arg) {
        new
            length
        ;

        while (length != sizeof (extra) - 1 && (extra[length] = getarg(arg, length)) != EOS) {
            ++length;
        }

        extra[length] = EOS;

        if (getarg(arg, length) != EOS) {
            continue;
        }

        if (SSI@Command_Alias(commandid, extra)) {
            ++added;
        }
    }

    return added;
}

stock bool:Command_SetFlags(const command[], flags) {
    new const
        Command:commandid = Command_GetByName(command)
    ;

    if (commandid == INVALID_COMMAND_ID) {
        return false;
    }

    gCommandData[commandid][E_COMMAND_FLAGS] = flags;

    return true;
}

stock Command_GetFlags(const command[]) {
    new const
        Command:commandid = Command_GetByName(command)
    ;

    if (commandid == INVALID_COMMAND_ID) {
        return 0;
    }

    return gCommandData[commandid][E_COMMAND_FLAGS];
}

stock bool:Command_SetRestricted(const command[], bool:restricted = true) {
    new const
        Command:commandid = Command_GetByName(command)
    ;

    if (commandid == INVALID_COMMAND_ID) {
        return false;
    }

    gCommandData[commandid][E_COMMAND_RESTRICTED] = restricted;

    return true;
}

stock bool:Command_IsRestricted(const command[]) {
    new const
        Command:commandid = Command_GetByName(command)
    ;

    if (commandid == INVALID_COMMAND_ID) {
        return false;
    }

    return gCommandData[commandid][E_COMMAND_RESTRICTED];
}

/**
 * # Access
 */

stock bool:Command_Allow(const command[], playerid, bool:allow = true) {
    new const
        Command:commandid = Command_GetByName(command)
    ;

    if (commandid == INVALID_COMMAND_ID) {
        return false;
    }

    if (!IsPlayerConnected(playerid)) {
        return false;
    }

    Bits_Set(PlayerCommandAllowed[playerid], commandid, allow);
    Bits_Set(PlayerCommandDenied[playerid], commandid, !allow);

    return true;
}

stock bool:Command_IsAllowed(const command[], playerid) {
    new const
        Command:commandid = Command_GetByName(command)
    ;

    if (commandid == INVALID_COMMAND_ID) {
        return false;
    }

    if (!IsPlayerConnected(playerid)) {
        return false;
    }

    return SSI@Command_Allowed(playerid, commandid);
}

/**
 * # Run
 */

stock bool:Command_Run(playerid, const text[]) {
    if (!IsPlayerConnected(playerid)) {
        return false;
    }

    if (text[0] != '/') {
        return false;
    }

    SSI@Command_Ready();

    new
        key[MAX_COMMAND_NAME],
        at = 1
    ;

    SSI@Command_Key(text[1], key);

    while (text[at] > ' ') {
        ++at;
    }

    while (text[at] == ' ') {
        ++at;
    }

    new
        Command:commandid
    ;

    if (text[strlen(key) + 1] > ' ') {
        return call OnPlayerUnknownCommand(playerid, key, text[at]) != 0;
    }

    if (!Dictionary_Get(CommandByName<>, key, commandid)) {
        return call OnPlayerUnknownCommand(playerid, key, text[at]) != 0;
    }

    if (!SSI@Command_Allowed(playerid, commandid)) {
        if (call OnPlayerCommandDenied(playerid, commandid, text[at])) {
            return true;
        }

        return call OnPlayerUnknownCommand(playerid, key, text[at]) != 0;
    }

    new const
        flags = gCommandData[commandid][E_COMMAND_FLAGS]
    ;

    if (call OnPlayerUseCommand(playerid, commandid, text[at], flags)) {
        return true;
    }

    new const
        result = SSI@Command_Call(gCommandData[commandid][E_COMMAND_ADDRESS], playerid, text[at])
    ;

    call OnPlayerUsedCommand(playerid, commandid, text[at], result, flags);

    return result != 0;
}

/**
 * # Calls
 */

hook OnGameModeInit() {
    SSI@Command_Ready();

    return 1;
}

hook OnFilterScriptInit() {
    SSI@Command_Ready();

    return 1;
}

hook OnPlayerConnect(playerid) {
    Bits_Clear(PlayerCommandAllowed[playerid]);
    Bits_Clear(PlayerCommandDenied[playerid]);

    return 1;
}

hook OnPlayerCommandText(playerid, cmdtext[]) {
    return Command_Run(playerid, cmdtext) ? ~1 : 0;
}
