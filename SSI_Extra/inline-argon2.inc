#if defined _INC_SSI_EXTRA_INLINE_ARGON2
    #endinput
#endif
#define _INC_SSI_EXTRA_INLINE_ARGON2

#include <open.mp>
#include <async_crypto>
#include <SSI\inline>

/**
 * Hashing and checking passwords with Argon2id through the async_crypto plugin,
 * answered by an inline:
 *
 *     #include <SSI_Extra\inline-argon2>
 *
 *     Register(playerid, const password[]) {
 *         inline OnHashed(hash[SSI_ARGON2_HASH_LENGTH]) {
 *             if (hash[0] == EOS) {
 *                 @return;
 *             }
 *
 *             SavePassword(playerid, hash);
 *         }
 *
 *         Argon2_HashInline(using inline OnHashed, password);
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
 *         Argon2_CheckInline(using inline OnChecked, password, hash);
 *     }
 *
 * - The work runs on the threads of the plugin. The inline is called once, on
 *   the main thread, when the work is done.
 * - A hash keeps the costs it was made with, so a check costs what its hash
 *   cost, whatever the defaults are now.
 * - The defaults are the least OWASP recommends for Argon2id: 19 MiB, two
 *   passes, one lane. A login takes about 100 ms with them, against 235 ms
 *   with bcrypt at cost 12 and 450 ms with the plugin's own 64 MiB and three
 *   passes.
 * - The inline keeps the arguments and locals of the function that started
 *   it, so the player id needs no passing. A player who left by then is still
 *   in it: check `IsPlayerConnected` when it matters.
 */

/**
 * # Header
 */

#if !defined SSI_ARGON2_MEMORY
    #define SSI_ARGON2_MEMORY (19456)
#endif

#if !defined SSI_ARGON2_ITERATIONS
    #define SSI_ARGON2_ITERATIONS (2)
#endif

#if !defined SSI_ARGON2_PARALLELISM
    #define SSI_ARGON2_PARALLELISM (1)
#endif

#if !defined SSI_ARGON2_LENGTH
    #define SSI_ARGON2_LENGTH (32)
#endif

#if !defined SSI_ARGON2_HASH_LENGTH
    #define SSI_ARGON2_HASH_LENGTH (128)
#endif

#if !defined SSI_ARGON2_PENDING
    #define SSI_ARGON2_PENDING (256)
#endif

static stock
    Inline:SSI@argon2[SSI_ARGON2_PENDING] = { INVALID_INLINE, ... },
    SSI@argon2Request[SSI_ARGON2_PENDING]
;

/**
 * # Functions
 */

/**
 * @brief      Hash a password, then call an inline with the hash.
 *
 * @param      callback     The inline, as `using inline Name`, taking the hash,
 *                          empty when the plugin failed.
 * @param      password     The password.
 * @param      memory       Memory, in KiB, from `8192` to `1048576`.
 * @param      iterations   Passes, from `1` to `16`.
 * @param      parallelism  Lanes, from `1` to `8`.
 * @param      length       Bytes of the hash, from `16` to `128`.
 *
 * @return     - `true` the work started
 *             - `false` the inline is freed, when:
 *                 + it could not be captured
 *                 + the plugin refused the costs or its queue is full
 *                 + `SSI_ARGON2_PENDING` requests already wait
 */
forward bool:Argon2_HashInline(Inline:callback<s>, const password[], memory = SSI_ARGON2_MEMORY, iterations = SSI_ARGON2_ITERATIONS, parallelism = SSI_ARGON2_PARALLELISM, length = SSI_ARGON2_LENGTH);

/**
 * @brief      Check a password against a hash, then call an inline with
 *             whether they match.
 *
 * @param      callback  The inline, as `using inline Name`, taking whether
 *                       they match. A hash that the plugin cannot read never
 *                       matches.
 * @param      password  The password.
 * @param      hash      The hash.
 *
 * @return     - `true` the work started
 *             - `false` the inline is freed, when:
 *                 + it could not be captured
 *                 + the plugin refused it or its queue is full
 *                 + `SSI_ARGON2_PENDING` requests already wait
 */
forward bool:Argon2_CheckInline(Inline:callback<i>, const password[], const hash[]);

/**
 * # Internal
 */

forward @SSI_Argon2Hashed(requestid, status, const result[]);
forward @SSI_Argon2Checked(requestid, status, const result[]);

static stock bool:SSI_Argon2WaitInternal(requestid, Inline:closure) {
    if (requestid <= 0) {
        Inline_Free(closure);

        return false;
    }

    new const
        slot = requestid % SSI_ARGON2_PENDING
    ;

    if (SSI@argon2[slot] != INVALID_INLINE) {
        Inline_Free(closure);

        return false;
    }

    SSI@argon2[slot] = closure;
    SSI@argon2Request[slot] = requestid;

    return true;
}

static stock Inline:SSI_Argon2TakeInternal(requestid) {
    new const
        slot = requestid % SSI_ARGON2_PENDING
    ;

    if (SSI@argon2Request[slot] != requestid) {
        return INVALID_INLINE;
    }

    new const
        Inline:closure = SSI@argon2[slot]
    ;

    SSI@argon2[slot] = INVALID_INLINE;
    SSI@argon2Request[slot] = 0;

    return closure;
}

/**
 * # Argon2
 */

stock bool:Argon2_HashInline(Inline:callback<s>, const password[], memory = SSI_ARGON2_MEMORY, iterations = SSI_ARGON2_ITERATIONS, parallelism = SSI_ARGON2_PARALLELISM, length = SSI_ARGON2_LENGTH) {
    new const
        Inline:closure = callback
    ;

    if (!Inline_IsValid(closure)) {
        return false;
    }

    return SSI_Argon2WaitInternal(Crypto_Argon2Hash(password, "@SSI_Argon2Hashed", memory, iterations, parallelism, length), closure);
}

stock bool:Argon2_CheckInline(Inline:callback<i>, const password[], const hash[]) {
    new const
        Inline:closure = callback
    ;

    if (!Inline_IsValid(closure)) {
        return false;
    }

    return SSI_Argon2WaitInternal(Crypto_Argon2Verify(password, hash, "@SSI_Argon2Checked"), closure);
}

/**
 * # Calls
 */

public @SSI_Argon2Hashed(requestid, status, const result[]) {
    new const
        Inline:closure = SSI_Argon2TakeInternal(requestid)
    ;

    if (status != CRYPTO_STATUS_OK) {
        Inline_CallOnce(closure, "");

        return 1;
    }

    Inline_CallOnce(closure, result);

    return 1;
}

public @SSI_Argon2Checked(requestid, status, const result[]) {
    new const
        Inline:closure = SSI_Argon2TakeInternal(requestid)
    ;

    Inline_CallOnce(closure, status == CRYPTO_STATUS_OK && result[0] == '1');

    return 1;
}
