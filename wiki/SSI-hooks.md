# SSI\hooks

```pawn
#include <SSI\hooks>
```

## Requirements

- `SSI\unique`
- `SSI\amx`

## Quick Start

Hooks, as in y_hooks: any number of functions for one callback, and hooks
that replace a native or a function. Every file that hooks includes this
last, after its other includes. Each include moves on to new names, so a file
hooks the same callback once, or more often with a suffix written after the
name of the callback: `hook OnPlayerConnect@1(playerid)`.

```pawn
#include <SSI\hooks>

hook OnPlayerConnect(playerid) {
    SendClientMessage(playerid, -1, "Welcome.");

    return 1;
}
```

The hooks of a callback run in the order they were declared, from the first
include to the last, and the public of the callback, if the script has one,
runs last. The callback returns what they all returned, joined with `&` when
its default return is `1` and with `|` when it is `0`. A hook that returns
`~0` or `~1` ends the chain there: the callback returns `0` or `1` and nothing
after that hook runs. A hook can be written for a state, as a public can:
`hook OnPlayerSpawn(playerid) <round:running>`. In a state it does not name,
the hook does nothing.

The callbacks of open.mp and of the streamer, Pawn.CMD, Pawn.RakNet,
crashdetect and sscanf return `1` by default, as in y_hooks, apart from
`OnPlayerCommandText` and `OnRconCommand`. Every other callback, as the events
a script calls with `CallLocalFunction`, returns `0` by default, so a hook
returning `1` makes the callback return `1`. A callback that needs another
default sets it with `DEFINE_HOOK_RETURN__(callback, value);`, outside any
function.

`hook native` replaces a native, and `hook function` or `hook stock` a
function of the script. The hook declared last runs first. Inside a hook, a
call to the native or function it replaces calls the hook declared before
it, and in the first hook it calls the native or the function:

```pawn
hook native SetPlayerHealth(playerid, Float:health) {
    return SetPlayerHealth(playerid, health > 100.0 ? 100.0 : health);
}
```

An include holds any number of these hooks. A native or function hooked
twice in one include takes a suffix on the second, as a callback does:
`hook native SetPlayerHealth@1(playerid, Float:health)`. Only the calls made
by this script are hooked.

The chains are built the first time `OnGameModeInit` or `OnFilterScriptInit`
runs. Each chain is a few cells of code, written over a function of `nop`s
kept for them, which calls the hooks and the public one after another with
the arguments copied once, so a hook costs a call and one or two
instructions. The public of a callback is turned into its chain. A callback
with hooks and no public gets a public named after it, so the server and the
plugins find it as if it had been written. A public that only returns `0`,
as `event` writes one, in a callback whose default is `0`, is left out of its
chain and jumps to it, so calling it as a function runs the hooks. The hooks
see `-1` from `numargs`, the same as in y_hooks. Every call to a hooked
native or function is pointed at the hook declared last, and the call inside
a hook at the one declared before it, so these hooks cost a call each. When
the code of the script cannot be read, the script stops at start up with an
index out of bounds error.

## API

### `hook`

Declare a hook of a callback, with `native` a hook of a native, or with `function` or `stock` a hook of a function of the script.

```pawn
hook OnPlayerDisconnect(playerid, reason) {
    return 1;
}
```

### `DEFINE_HOOK_RETURN__`

Set the default return of a callback: `1` joins the returns of its hooks with `&`, `0` with `|`.

```pawn
DEFINE_HOOK_RETURN__(OnPlayerReachGoal, 1);
```

### `event`

Declare an event: a callback the script raises itself by calling it as a function, which runs its hooks.

```pawn
event OnPlayerReachGoal(playerid, goal);

ReachGoal(playerid, goal) {
    return call OnPlayerReachGoal(playerid, goal);
}
```

The event is a public that returns `0`, so it answers `0` until a hook
answers. Raising it costs about 1.8 us less than `CallLocalFunction`, keeps
the tags of its arguments, passes strings by reference and is checked by the
compiler. The script answers it with hooks, never with a public.

### `call`

Raise an event declared with `event`: its hooks run, and it answers what they joined. A plain call does the same, and `call` marks the call as an event.

```pawn
call OnPlayerReachGoal(playerid, goal);
```

The event's name starts with `On`, as callbacks do.
