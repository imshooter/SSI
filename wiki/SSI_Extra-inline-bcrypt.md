# SSI_Extra\inline-bcrypt

```pawn
#include <SSI_Extra\inline-bcrypt>
```

## Requirements

- `SSI\inline`
- [samp-bcrypt](https://github.com/Sreyas-Sreelal/samp-bcrypt)

## Quick Start

Hashing and checking passwords with bcrypt, answered by an inline:

```pawn
#include <SSI_Extra\inline-bcrypt>

Register(playerid, const password[]) {
    inline OnHashed(hash[BCRYPT_HASH_LENGTH]) {
        SavePassword(playerid, hash);
    }

    BCrypt_HashInline(using inline OnHashed, password);
}

Login(playerid, const password[], const hash[]) {
    inline OnChecked(bool:match) {
        if (!match) {
            @return;
        }

        SpawnPlayer(playerid);
    }

    BCrypt_CheckInline(using inline OnChecked, password, hash);
}
```

- The work runs on another thread. The inline is called once, on the main
  thread, when the work is done.
- The inline keeps the arguments and locals of the function that started
  it, so the player id needs no passing. A player who left by then is still
  in it: check `IsPlayerConnected` when it matters.

## API

### `BCrypt_HashInline`

```pawn
forward bool:BCrypt_HashInline(Inline:callback<s>, const input[], cost = BCRYPT_COST);
```

Hash a text, then call an inline with the hash.

| Parameter | Description |
| --- | --- |
| `callback` | The inline, as `using inline Name`, taking the hash. |
| `input` | The text. |
| `cost` | The work factor, from `4` to `31`. |

**Returns**

- `true` the work started
- `false` the inline is freed, when:
    + it could not be captured
    + the work could not start

### `BCrypt_CheckInline`

```pawn
forward bool:BCrypt_CheckInline(Inline:callback<i>, const input[], const hash[]);
```

Check a text against a hash, then call an inline with whether they match.

| Parameter | Description |
| --- | --- |
| `callback` | The inline, as `using inline Name`, taking whether they match. |
| `input` | The text. |
| `hash` | The hash. |

**Returns**

- `true` the work started
- `false` the inline is freed, when:
    + it could not be captured
    + the work could not start
