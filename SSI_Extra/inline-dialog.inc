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
 * - `Dialog_ShowPageInline` splits a long list into pages, with a row for the
 *   next page and one for the page before. Turning a page shows the dialog
 *   again and keeps the inline, which gets the row of the whole list.
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

#if !defined SSI_DIALOG_PAGE_BODY
    #define SSI_DIALOG_PAGE_BODY (4096)
#endif

#if !defined SSI_DIALOG_PAGE_TITLE
    #define SSI_DIALOG_PAGE_TITLE (64)
#endif

#if !defined SSI_DIALOG_PAGE_BUTTON
    #define SSI_DIALOG_PAGE_BUTTON (32)
#endif

#if !defined SSI_DIALOG_PAGE_ROWS
    #define SSI_DIALOG_PAGE_ROWS (10)
#endif

#if !defined SSI_DIALOG_PAGE_NEXT
    #define SSI_DIALOG_PAGE_NEXT ">>>"
#endif

#if !defined SSI_DIALOG_PAGE_BACK
    #define SSI_DIALOG_PAGE_BACK "<<<"
#endif

static enum E_DIALOG_PAGE_DATA {
    bool:E_DIALOG_PAGE_SHOWN,
    DIALOG_STYLE:E_DIALOG_PAGE_STYLE,
    E_DIALOG_PAGE_ROWS,
    E_DIALOG_PAGE_LISTED,
    E_DIALOG_PAGE_PAGE,
    E_DIALOG_PAGE_HEADER,
    E_DIALOG_PAGE_START,
    E_DIALOG_PAGE_END,
    E_DIALOG_PAGE_LENGTH,
    E_DIALOG_PAGE_TITLE[SSI_DIALOG_PAGE_TITLE char],
    E_DIALOG_PAGE_BODY[SSI_DIALOG_PAGE_BODY char],
    E_DIALOG_PAGE_BUTTON_1[SSI_DIALOG_PAGE_BUTTON char],
    E_DIALOG_PAGE_BUTTON_2[SSI_DIALOG_PAGE_BUTTON char],
};

static stock
    Inline:SSI@dialog[MAX_PLAYERS] = { INVALID_INLINE, ... },
    SSI@dialogPage[MAX_PLAYERS][E_DIALOG_PAGE_DATA],
    SSI@dialogPageBody[SSI_DIALOG_PAGE_BODY]
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
 * @brief      Show a list split into pages whose answer calls an inline.
 *
 * The body is formatted with the arguments after `rows`, one row a line. With
 * `DIALOG_STYLE_TABLIST_HEADERS` the first line is the header, shown on every
 * page. The inline gets the row of the whole list, from `0`, or `-1` when the
 * dialog is cancelled.
 *
 * @param      playerid  The player.
 * @param      callback  The inline, as `using inline Name`, taking the
 *                       response, the row and its text.
 * @param      style     `DIALOG_STYLE_LIST`, `DIALOG_STYLE_TABLIST` or
 *                       `DIALOG_STYLE_TABLIST_HEADERS`.
 * @param      title     The title.
 * @param      body      The rows.
 * @param      button1   The left button.
 * @param      button2   The right button, empty for none.
 * @param      rows      Rows on each page.
 *
 * @return     - `true` it is shown
 *             - `false` the inline is freed, when:
 *                 + the player is not connected
 *                 + the inline could not be captured
 *                 + `style` is not a list style, or `rows` is below `1`
 *                 + the dialog could not be shown
 */
forward bool:Dialog_ShowPageInline(playerid, Inline:callback<iis>, DIALOG_STYLE:style, const title[], const body[], const button1[], const button2[] = "", rows = SSI_DIALOG_PAGE_ROWS, OPEN_MP_TAGS:...);

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
 * # Internal
 */

static stock SSI_DialogPageFirstInternal(playerid, const text[]) {
    if (SSI@dialogPage[playerid][E_DIALOG_PAGE_STYLE] != DIALOG_STYLE_TABLIST_HEADERS) {
        return 0;
    }

    new const
        end = strfind(text, "\n")
    ;

    return (end == -1) ? strlen(text) : end + 1;
}

static stock bool:SSI_DialogPageShowInternal(playerid) {
    static
        page[SSI_DIALOG_PAGE_BODY + 16],
        piece[SSI_DIALOG_PAGE_BODY char]
    ;

    new
        title[SSI_DIALOG_PAGE_TITLE],
        button1[SSI_DIALOG_PAGE_BUTTON],
        button2[SSI_DIALOG_PAGE_BUTTON],
        position = SSI@dialogPage[playerid][E_DIALOG_PAGE_START],
        listed = 0
    ;

    strunpack(title, SSI@dialogPage[playerid][E_DIALOG_PAGE_TITLE]);
    strunpack(button1, SSI@dialogPage[playerid][E_DIALOG_PAGE_BUTTON_1]);
    strunpack(button2, SSI@dialogPage[playerid][E_DIALOG_PAGE_BUTTON_2]);

    for (; listed != SSI@dialogPage[playerid][E_DIALOG_PAGE_ROWS]; ++listed) {
        new const
            end = strfind(SSI@dialogPage[playerid][E_DIALOG_PAGE_BODY], "\n", .pos = position)
        ;

        if (end == -1) {
            listed += _:(position != SSI@dialogPage[playerid][E_DIALOG_PAGE_LENGTH]);
            position = SSI@dialogPage[playerid][E_DIALOG_PAGE_LENGTH];

            break;
        }

        position = end + 1;
    }

    new const
        header = SSI@dialogPage[playerid][E_DIALOG_PAGE_HEADER]
    ;

    strmid(piece, SSI@dialogPage[playerid][E_DIALOG_PAGE_BODY], 0, header);
    strunpack(page, piece);
    
    strmid(piece, SSI@dialogPage[playerid][E_DIALOG_PAGE_BODY], SSI@dialogPage[playerid][E_DIALOG_PAGE_START], position);
    strunpack(page[header], piece, sizeof (page) - header);

    new
        length = header + position - SSI@dialogPage[playerid][E_DIALOG_PAGE_START]
    ;

    if (length == 0 || page[length - 1] != '\n') {
        page[length++] = '\n';
        page[length] = EOS;
    }

    SSI@dialogPage[playerid][E_DIALOG_PAGE_END] = position;
    SSI@dialogPage[playerid][E_DIALOG_PAGE_LISTED] = listed;

    if (position != SSI@dialogPage[playerid][E_DIALOG_PAGE_LENGTH]) {
        strcat(page, SSI_DIALOG_PAGE_NEXT "\n");
    }

    if (SSI@dialogPage[playerid][E_DIALOG_PAGE_PAGE] > 0) {
        strcat(page, SSI_DIALOG_PAGE_BACK);
    }

    return ShowPlayerDialog(playerid, SSI_DIALOG_ID, SSI@dialogPage[playerid][E_DIALOG_PAGE_STYLE], title, page, button1, button2);
}

static stock SSI_DialogPageBackInternal(playerid, const body[]) {
    new
        position = SSI@dialogPage[playerid][E_DIALOG_PAGE_START] - 1,
        seen = 0
    ;

    while (position > SSI@dialogPage[playerid][E_DIALOG_PAGE_HEADER]) {
        if (body{position - 1} == '\n' && ++seen == SSI@dialogPage[playerid][E_DIALOG_PAGE_ROWS]) {
            break;
        }

        --position;
    }

    return position;
}

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
    SSI@dialogPage[playerid][E_DIALOG_PAGE_SHOWN] = false;

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

stock bool:Dialog_ShowPageInline(playerid, Inline:callback<iis>, DIALOG_STYLE:style, const title[], const body[], const button1[], const button2[] = "", rows = SSI_DIALOG_PAGE_ROWS, OPEN_MP_TAGS:...) {
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

    if (style != DIALOG_STYLE_LIST && style != DIALOG_STYLE_TABLIST && style != DIALOG_STYLE_TABLIST_HEADERS) {
        Inline_Free(closure);

        return false;
    }

    if (rows < 1) {
        Inline_Free(closure);

        return false;
    }

    if (numargs() == 8) {
        SSI@dialogPageBody[0] = EOS;
        strcat(SSI@dialogPageBody, body);
    } else {
        Format(SSI@dialogPageBody, sizeof (SSI@dialogPageBody), body, ___(8));
    }

    strpack(SSI@dialogPage[playerid][E_DIALOG_PAGE_BODY], SSI@dialogPageBody, SSI_DIALOG_PAGE_BODY char);
    strpack(SSI@dialogPage[playerid][E_DIALOG_PAGE_TITLE], title, SSI_DIALOG_PAGE_TITLE char);
    strpack(SSI@dialogPage[playerid][E_DIALOG_PAGE_BUTTON_1], button1, SSI_DIALOG_PAGE_BUTTON char);
    strpack(SSI@dialogPage[playerid][E_DIALOG_PAGE_BUTTON_2], button2, SSI_DIALOG_PAGE_BUTTON char);

    SSI@dialogPage[playerid][E_DIALOG_PAGE_STYLE]  = style;
    SSI@dialogPage[playerid][E_DIALOG_PAGE_ROWS]   = rows;
    SSI@dialogPage[playerid][E_DIALOG_PAGE_PAGE]   = 0;
    SSI@dialogPage[playerid][E_DIALOG_PAGE_HEADER] = SSI_DialogPageFirstInternal(playerid, SSI@dialogPageBody);
    SSI@dialogPage[playerid][E_DIALOG_PAGE_START]  = SSI@dialogPage[playerid][E_DIALOG_PAGE_HEADER];
    SSI@dialogPage[playerid][E_DIALOG_PAGE_LENGTH] = strlen(SSI@dialogPage[playerid][E_DIALOG_PAGE_BODY]);

    if (!SSI_DialogPageShowInternal(playerid)) {
        Inline_Free(closure);

        return false;
    }

    Inline_Free(SSI@dialog[playerid]);
    SSI@dialog[playerid] = closure;
    SSI@dialogPage[playerid][E_DIALOG_PAGE_SHOWN] = true;

    return true;
}

stock bool:Dialog_Close(playerid) {
    if (!IsPlayerConnected(playerid)) {
        return false;
    }

    if (!Inline_Free(SSI@dialog[playerid])) {
        return false;
    }

    SSI@dialog[playerid] = INVALID_INLINE;
    SSI@dialogPage[playerid][E_DIALOG_PAGE_SHOWN] = false;

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

    if (!SSI@dialogPage[playerid][E_DIALOG_PAGE_SHOWN]) {
        SSI@dialog[playerid] = INVALID_INLINE;
        Inline_CallOnce(closure, response, listitem, inputtext);

        return ~1;
    }

    new const
        current = SSI@dialogPage[playerid][E_DIALOG_PAGE_PAGE],
        first = current * SSI@dialogPage[playerid][E_DIALOG_PAGE_ROWS],
        count = SSI@dialogPage[playerid][E_DIALOG_PAGE_LISTED],
        bool:next = SSI@dialogPage[playerid][E_DIALOG_PAGE_END] != SSI@dialogPage[playerid][E_DIALOG_PAGE_LENGTH]
    ;

    if (response && next && listitem == count) {
        ++SSI@dialogPage[playerid][E_DIALOG_PAGE_PAGE];
        SSI@dialogPage[playerid][E_DIALOG_PAGE_START] = SSI@dialogPage[playerid][E_DIALOG_PAGE_END];
        SSI_DialogPageShowInternal(playerid);

        return ~1;
    }

    if (response && current > 0 && listitem == count + _:next) {
        --SSI@dialogPage[playerid][E_DIALOG_PAGE_PAGE];
        SSI@dialogPage[playerid][E_DIALOG_PAGE_START] = SSI_DialogPageBackInternal(playerid, SSI@dialogPage[playerid][E_DIALOG_PAGE_BODY]);
        SSI_DialogPageShowInternal(playerid);

        return ~1;
    }

    if (response && !(0 <= listitem < count)) {
        SSI_DialogPageShowInternal(playerid);

        return ~1;
    }

    SSI@dialog[playerid] = INVALID_INLINE;
    SSI@dialogPage[playerid][E_DIALOG_PAGE_SHOWN] = false;
    Inline_CallOnce(closure, response, response ? first + listitem : -1, inputtext);

    return ~1;
}

hook OnPlayerDisconnect(playerid, reason) {
    Inline_Free(SSI@dialog[playerid]);
    SSI@dialog[playerid] = INVALID_INLINE;
    SSI@dialogPage[playerid][E_DIALOG_PAGE_SHOWN] = false;

    return 1;
}
