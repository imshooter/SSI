# hooks

Hooks, as in y_hooks: any number of functions for one callback, and hooks that replace a native or a function. Every file that hooks includes this last, after its other includes. Each include moves on to new names, so a file hooks the same callback once, or more often with a suffix written after the name of the callback: `hook OnPlayerConnect@1(playerid)`.

## SSI

For general SSI information, see the following links:

* [Installation](../wiki/Installation.md)
* [Conventions](../wiki/Conventions.md)
* [Troubleshooting](../wiki/Troubleshooting.md)

## Documentation

* [Quick Start](../wiki/SSI-hooks.md#quick-start) shows how the library is used.
* [API](../wiki/SSI-hooks.md#api) lists every function and macro.
* [Requirements](../wiki/SSI-hooks.md#requirements) lists what it includes.
