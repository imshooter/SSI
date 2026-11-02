# SSI_Extra\inline-argon2

```pawn
#include <SSI_Extra\inline-argon2>
```

## Requirements

- `SSI\inline`
- [async-crypto](https://github.com/roseeast/async-crypto)

## Quick Start

Hashing and checking passwords with Argon2id through the async_crypto plugin,
answered by an inline:

```pawn
#include <SSI_Extra\inline-argon2>

Register(playerid, const password[]) {
    inline OnHashed(hash[SSI_ARGON2_HASH_LENGTH]) {
        if (hash[0] == EOS) {
            @return;
        }

        SavePassword(playerid, hash);
    }

    Argon2_HashInline(using inline OnHashed, password);
}

Login(playerid, const password[], const hash[]) {
    inline OnChecked(bool:match) {
        if (!match) {
            @return;
        }

        SpawnPlayer(playerid);
    }

    Argon2_CheckInline(using inline OnChecked, password, hash);
}
```

- The work runs on the threads of the plugin. The inline is called once, on
  the main thread, when the work is done.
- A hash keeps the costs it was made with, so a check costs what its hash
  cost, whatever the defaults are now.
- The defaults are the least OWASP recommends for Argon2id: 19 MiB, two
  passes, one lane. A login takes about 100 ms with them, against 235 ms
  with bcrypt at cost 12 and 450 ms with the plugin's own 64 MiB and three
  passes.
- The inline keeps the arguments and locals of the function that started
  it, so the player id needs no passing. A player who left by then is still
  in it: check `IsPlayerConnected` when it matters.

## API

### `Argon2_HashInline`

```pawn
forward bool:Argon2_HashInline(Inline:callback<s>, const password[], memory = SSI_ARGON2_MEMORY, iterations = SSI_ARGON2_ITERATIONS, parallelism = SSI_ARGON2_PARALLELISM, length = SSI_ARGON2_LENGTH);
```

Hash a password, then call an inline with the hash.

| Parameter | Description |
| --- | --- |
| `callback` | The inline, as `using inline Name`, taking the hash, empty when the plugin failed. |
| `password` | The password. |
| `memory` | Memory, in KiB, from `8192` to `1048576`. |
| `iterations` | Passes, from `1` to `16`. |
| `parallelism` | Lanes, from `1` to `8`. |
| `length` | Bytes of the hash, from `16` to `128`. |

**Returns**

- `true` the work started
- `false` the inline is freed, when:
    + it could not be captured
    + the plugin refused the costs or its queue is full
    + `SSI_ARGON2_PENDING` requests already wait

### `Argon2_CheckInline`

```pawn
forward bool:Argon2_CheckInline(Inline:callback<i>, const password[], const hash[]);
```

Check a password against a hash, then call an inline with whether they match.

| Parameter | Description |
| --- | --- |
| `callback` | The inline, as `using inline Name`, taking whether they match. A hash that the plugin cannot read never matches. |
| `password` | The password. |
| `hash` | The hash. |

**Returns**

- `true` the work started
- `false` the inline is freed, when:
    + it could not be captured
    + the plugin refused it or its queue is full
    + `SSI_ARGON2_PENDING` requests already wait
