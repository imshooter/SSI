# Troubleshooting

## A hook never runs

* `SSI\hooks` must be the last include of the file that declares the hook. A library included after it takes the names the hook was meant to use.
* A callback whose default return is `0` joins the returns of its hooks with `|`. A hook that returns `1` there makes the callback return `1`. Set another default with `DEFINE_HOOK_RETURN__(callback, value);`.
* An earlier hook may end the chain by returning `~0` or `~1`.

## A plugin does not see a callback that only has hooks

The hooks give a callback a public when the script has none, and open.mp and the streamer find it. A plugin that looks for its callbacks when the script loads, before any code of the script runs, does not. Write the public in the script, even if it only returns:

```pawn
public OnPlayerConnect(playerid) {
    return 1;
}
```

Dynamic areas of the streamer, for example, need a public `OnPlayerConnect` in the script.

## `SSI\hooks is not compatible with y_hooks`

Both libraries rename the same callbacks. Use one of them in the script.

## `cannot read from file: "PawnPlus"`

`SSI\iterator` needs the PawnPlus include and plugin. Libraries in `SSI_Extra` need the include of the plugin or component they wrap. See [Installation](Installation.md).

## The compiler stops, hangs or runs out of memory on a macro

* A group or index in angle brackets must not hold a comma. `Name<min(a, b)>` loops the preprocessor. Store the value in a variable first.
* The compiler hangs when one expanded line passes about 4095 characters. Split a long line of macro calls into several statements.

## An inline is never called

Captured inlines come from a pool of `SSI_INLINE_CLOSURES` slots, 256 by default. When every slot is taken, the capture gives `INVALID_INLINE` and the function it was given to does nothing, so a query is never sent. A capture larger than `SSI_INLINE_CELLS` cells gives `INVALID_INLINE` too. Inlines owned by a player, vehicle or object are freed when their owner goes, and `Inline_Free` frees one by hand. Raise the pool by defining `SSI_INLINE_CLOSURES` before the first include:

```pawn
#define SSI_INLINE_CLOSURES (InlineClosure:1024)
#include <SSI\inline>
```

## A test check with a string does not compile

The text of a check is made by the compiler, so a string with a bracket and no pair, as `"a(b"`, breaks it. Put the string in a variable and check the variable.
