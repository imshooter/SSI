#if defined _INC_SSI_EXTRA_INLINE_DIALOG
    #endinput
#endif
#define _INC_SSI_EXTRA_INLINE_DIALOG

#include <open.mp>
#include <SSI\hooks>
#include <SSI\inline>
#include <SSI\va>

/**
 * Dialogs answered by an inline:
 *
 *     #include <SSI_Extra\inline-dialog>
 *
 *     AskName(playerid) {
 *         inline OnAnswer(response, listitem, inputtext[MAX_PLAYER_NAME + 1]) {
 *             if (!response) {
 *                 @return;
 *             }
 *
 *             SetPlayerName(playerid, inputtext);
 *         }
 *
 *         Dialog_ShowInputInline(playerid, using inline OnAnswer, "Name", "Your new name:", "Save", "Cancel");
 *     }
 *
 * - The inline takes the response, the list item and the text, and is called
 *   once.
 * - A new dialog for the same player takes the place of the one waiting: the
 *   old inline is freed and never called. So is the inline of a player who
 *   leaves, or of a dialog closed with `Dialog_Close`.
 * - Every dialog shown here uses `SSI_DIALOG_ID`. A dialog with another id
 *   never reaches an inline.
 */

/**
 * # Header
 */

#if !defined SSI_DIALOG_ID
    #define SSI_DIALOG_ID (32767)
#endif

#if !defined SSI_DIALOG_INPUT_LENGTH
    #define SSI_DIALOG_INPUT_LENGTH (128)
#endif

static stock
    Inline:SSI@dialog[MAX_PLAYERS] = { INVALID_INLINE, ... }
;

/**
 * # Functions
 */

/**
 * @brief      Show a dialog whose answer calls an inline.
 *
 * The body is formatted with the arguments after `button2`, as
 * `ShowPlayerDialog` does.
 *
 * @param      playerid  The player.
 * @param      callback  The inline, as `using inline Name`, taking the
 *                       response, the list item and the text.
 * @param      style     The style.
 * @param      title     The title.
 * @param      body      The body.
 * @param      button1   The left button.
 * @param      button2   The right button, empty for none.
 *
 * @return     - `true` it is shown
 *             - `false` the inline is freed, when:
 *                 + the player is not connected
 *                 + the inline could not be captured
 *                 + the dialog could not be shown
 */
forward bool:Dialog_ShowInline(playerid, Inline:callback<iis>, DIALOG_STYLE:style, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...);

/**
 * @brief      `Dialog_ShowInline` with `DIALOG_STYLE_MSGBOX`.
 */
forward bool:Dialog_ShowMessageBoxInline(playerid, Inline:callback<iis>, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...);

/**
 * @brief      `Dialog_ShowInline` with `DIALOG_STYLE_INPUT`.
 */
forward bool:Dialog_ShowInputInline(playerid, Inline:callback<iis>, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...);

/**
 * @brief      `Dialog_ShowInline` with `DIALOG_STYLE_LIST`.
 */
forward bool:Dialog_ShowListInline(playerid, Inline:callback<iis>, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...);

/**
 * @brief      `Dialog_ShowInline` with `DIALOG_STYLE_PASSWORD`.
 */
forward bool:Dialog_ShowPasswordInline(playerid, Inline:callback<iis>, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...);

/**
 * @brief      `Dialog_ShowInline` with `DIALOG_STYLE_TABLIST`.
 */
forward bool:Dialog_ShowTabListInline(playerid, Inline:callback<iis>, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...);

/**
 * @brief      `Dialog_ShowInline` with `DIALOG_STYLE_TABLIST_HEADERS`.
 */
forward bool:Dialog_ShowTabListHeadersInline(playerid, Inline:callback<iis>, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...);

/**
 * @brief      Close the inline dialog of a player without calling its inline.
 *
 * @param      playerid  The player.
 *
 * @return     - `true` it was closed
 *             - `false` no inline dialog was waiting
 */
forward bool:Dialog_Close(playerid);

/**
 * @brief      Whether an inline dialog waits for an answer from a player.
 *
 * @param      playerid  The player.
 *
 * @return     - `true` it does
 *             - `false` it does not
 */
forward bool:Dialog_IsOpen(playerid);

/**
 * # Dialog
 */

stock bool:Dialog_ShowInline(playerid, Inline:callback<iis>, DIALOG_STYLE:style, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...) {
    new const
        Inline:closure = callback
    ;

    if (!IsPlayerConnected(playerid)) {
        Inline_Free(closure);

        return false;
    }

    if (!Inline_IsValid(closure)) {
        return false;
    }

    if (!ShowPlayerDialog(playerid, SSI_DIALOG_ID, style, title, body, button1, button2, ___(7))) {
        Inline_Free(closure);

        return false;
    }

    Inline_Free(SSI@dialog[playerid]);
    SSI@dialog[playerid] = closure;

    return true;
}

stock bool:Dialog_ShowMessageBoxInline(playerid, Inline:callback<iis>, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...) {
    return Dialog_ShowInline(playerid, callback, DIALOG_STYLE_MSGBOX, title, body, button1, button2, ___(6));
}

stock bool:Dialog_ShowInputInline(playerid, Inline:callback<iis>, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...) {
    return Dialog_ShowInline(playerid, callback, DIALOG_STYLE_INPUT, title, body, button1, button2, ___(6));
}

stock bool:Dialog_ShowListInline(playerid, Inline:callback<iis>, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...) {
    return Dialog_ShowInline(playerid, callback, DIALOG_STYLE_LIST, title, body, button1, button2, ___(6));
}

stock bool:Dialog_ShowPasswordInline(playerid, Inline:callback<iis>, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...) {
    return Dialog_ShowInline(playerid, callback, DIALOG_STYLE_PASSWORD, title, body, button1, button2, ___(6));
}

stock bool:Dialog_ShowTabListInline(playerid, Inline:callback<iis>, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...) {
    return Dialog_ShowInline(playerid, callback, DIALOG_STYLE_TABLIST, title, body, button1, button2, ___(6));
}

stock bool:Dialog_ShowTabListHeadersInline(playerid, Inline:callback<iis>, const title[], const body[], const button1[], const button2[] = "", OPEN_MP_TAGS:...) {
    return Dialog_ShowInline(playerid, callback, DIALOG_STYLE_TABLIST_HEADERS, title, body, button1, button2, ___(6));
}

stock bool:Dialog_Close(playerid) {
    if (!IsPlayerConnected(playerid)) {
        return false;
    }

    if (!Inline_Free(SSI@dialog[playerid])) {
        return false;
    }

    SSI@dialog[playerid] = INVALID_INLINE;

    if (GetPlayerDialogID(playerid) == SSI_DIALOG_ID) {
        HidePlayerDialog(playerid);
    }

    return true;
}

stock bool:Dialog_IsOpen(playerid) {
    if (!IsPlayerConnected(playerid)) {
        return false;
    }

    return Inline_IsValid(SSI@dialog[playerid]);
}

/**
 * # Calls
 */

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
    if (dialogid != SSI_DIALOG_ID) {
        return 1;
    }

    new const
        Inline:closure = SSI@dialog[playerid]
    ;

    SSI@dialog[playerid] = INVALID_INLINE;
    Inline_CallOnce(closure, response, listitem, inputtext);

    return ~1;
}

hook OnPlayerDisconnect(playerid, reason) {
    Inline_Free(SSI@dialog[playerid]);
    SSI@dialog[playerid] = INVALID_INLINE;

    return 1;
}
