#if defined _INC_SSI_EXTRA_INLINE_BCRYPT
    #endinput
#endif
#define _INC_SSI_EXTRA_INLINE_BCRYPT

#include <open.mp>
#include <bcrypt>
#include <SSI\inline>

/**
 * Hashing and checking passwords with bcrypt, answered by an inline:
 *
 *     #include <SSI_Extra\inline-bcrypt>
 *
 *     Register(playerid, const password[]) {
 *         inline OnHashed(hash[BCRYPT_HASH_LENGTH]) {
 *             SavePassword(playerid, hash);
 *         }
 *
 *         BCrypt_HashInline(using inline OnHashed, password);
 *     }
 *
 *     Login(playerid, const password[], const hash[]) {
 *         inline OnChecked(bool:match) {
 *             if (!match) {
 *                 @return;
 *             }
 *
 *             SpawnPlayer(playerid);
 *         }
 *
 *         BCrypt_CheckInline(using inline OnChecked, password, hash);
 *     }
 *
 * - The work runs on another thread. The inline is called once, on the main
 *   thread, when the work is done.
 * - The inline keeps the arguments and locals of the function that started
 *   it, so the player id needs no passing. A player who left by then is still
 *   in it: check `IsPlayerConnected` when it matters.
 */

/**
 * # Functions
 */

/**
 * @brief      Hash a text, then call an inline with the hash.
 *
 * @param      callback  The inline, as `using inline Name`, taking the hash.
 * @param      input     The text.
 * @param      cost      The work factor, from `4` to `31`.
 *
 * @return     - `true` the work started
 *             - `false` the inline is freed, when:
 *                 + it could not be captured
 *                 + the work could not start
 */
forward bool:BCrypt_HashInline(Inline:callback<s>, const input[], cost = BCRYPT_COST);

/**
 * @brief      Check a text against a hash, then call an inline with whether
 *             they match.
 *
 * @param      callback  The inline, as `using inline Name`, taking whether
 *                       they match.
 * @param      input     The text.
 * @param      hash      The hash.
 *
 * @return     - `true` the work started
 *             - `false` the inline is freed, when:
 *                 + it could not be captured
 *                 + the work could not start
 */
forward bool:BCrypt_CheckInline(Inline:callback<i>, const input[], const hash[]);

/**
 * # Internal
 */

forward @SSI_BCryptHashed(playerid, Inline:closure);
forward @SSI_BCryptChecked(playerid, bool:match, Inline:closure);

/**
 * # BCrypt
 */

stock bool:BCrypt_HashInline(Inline:callback<s>, const input[], cost = BCRYPT_COST) {
    new const
        Inline:closure = callback
    ;

    if (!Inline_IsValid(closure)) {
        return false;
    }

    if (!bcrypt_hash(0, "@SSI_BCryptHashed", input, cost, "i", _:closure)) {
        Inline_Free(closure);

        return false;
    }

    return true;
}

stock bool:BCrypt_CheckInline(Inline:callback<i>, const input[], const hash[]) {
    new const
        Inline:closure = callback
    ;

    if (!Inline_IsValid(closure)) {
        return false;
    }

    if (!bcrypt_verify(0, "@SSI_BCryptChecked", input, hash, "i", _:closure)) {
        Inline_Free(closure);

        return false;
    }

    return true;
}

/**
 * # Calls
 */

public @SSI_BCryptHashed(playerid, Inline:closure) {
    new
        hash[BCRYPT_HASH_LENGTH]
    ;

    #pragma unused playerid

    bcrypt_get_hash(hash);
    Inline_CallOnce(closure, hash);

    return 1;
}

public @SSI_BCryptChecked(playerid, bool:match, Inline:closure) {
    #pragma unused playerid

    Inline_CallOnce(closure, match);

    return 1;
}
