#define SSI_TESTS
#define SSI_TEST_EXIT

#include <open.mp>
#include <SSI\test>
#include <SSI_Extra\inline-dialog>
#include <SSI\hooks>

static
    gBot = INVALID_PLAYER_ID,
    gAnswers,
    gResponse,
    gListItem,
    gText[32]
;

main() {
}

Check(DIALOG_STYLE:want, const body[]) {
    new
        DIALOG_STYLE:style,
        title[32],
        text[64],
        button1[16],
        button2[16]
    ;

    ASSERT(GetPlayerDialogData(gBot, style, title, sizeof (title), text, sizeof (text), button1, sizeof (button1), button2, sizeof (button2)));
    ASSERT_EQ(_:style, _:want);
    ASSERT_SAME(title, "Title");
    ASSERT_SAME(text, body);
    ASSERT_SAME(button1, "Yes");
    ASSERT_SAME(button2, "No");
    ASSERT_EQ(GetPlayerDialogID(gBot), SSI_DIALOG_ID);
    ASSERT(Dialog_IsOpen(gBot));
}

Answer(response, listitem, const text[]) {
    CallLocalFunction("OnDialogResponse", "iiiis", gBot, SSI_DIALOG_ID, response, listitem, text);
}

Show(DIALOG_STYLE:style, const name[]) {
    new const
        number = 7,
        Float:value = 1.5
    ;

    inline OnAnswer(response, listitem, inputtext[32]) {
        ++gAnswers;
        gResponse = response;
        gListItem = listitem;
        strcopy(gText, inputtext);
    }

    new
        bool:shown
    ;

    switch (style) {
        case DIALOG_STYLE_MSGBOX: shown = Dialog_ShowMessageBoxInline(gBot, using inline OnAnswer, "Title", "%s %i %.1f", "Yes", "No", name, number, value);
        case DIALOG_STYLE_INPUT: shown = Dialog_ShowInputInline(gBot, using inline OnAnswer, "Title", "%s %i %.1f", "Yes", "No", name, number, value);
        case DIALOG_STYLE_LIST: shown = Dialog_ShowListInline(gBot, using inline OnAnswer, "Title", "%s %i %.1f", "Yes", "No", name, number, value);
        case DIALOG_STYLE_PASSWORD: shown = Dialog_ShowPasswordInline(gBot, using inline OnAnswer, "Title", "%s %i %.1f", "Yes", "No", name, number, value);
        case DIALOG_STYLE_TABLIST: shown = Dialog_ShowTabListInline(gBot, using inline OnAnswer, "Title", "%s %i %.1f", "Yes", "No", name, number, value);
        case DIALOG_STYLE_TABLIST_HEADERS: shown = Dialog_ShowTabListHeadersInline(gBot, using inline OnAnswer, "Title", "%s %i %.1f", "Yes", "No", name, number, value);
    }

    return shown;
}

test BotConnects() {
    Test_Async(3000);
    gBot = NPC_Create("DialogBot");
    ASSERT(IsPlayerConnected(gBot));
    Test_Done();
}

test EveryStyle() {
    new const
        DIALOG_STYLE:styles[] = {
            DIALOG_STYLE_MSGBOX,
            DIALOG_STYLE_INPUT,
            DIALOG_STYLE_LIST,
            DIALOG_STYLE_PASSWORD,
            DIALOG_STYLE_TABLIST,
            DIALOG_STYLE_TABLIST_HEADERS
        }
    ;

    for (new i; i < sizeof (styles); ++i) {
        gAnswers = 0;

        ASSERT(Show(styles[i], "ab"));
        Check(styles[i], "ab 7 1.5");

        Answer(1, i, "typed");
        ASSERT_EQ(gAnswers, 1);
        ASSERT_EQ(gResponse, 1);
        ASSERT_EQ(gListItem, i);
        ASSERT_SAME(gText, "typed");
        ASSERT_FALSE(Dialog_IsOpen(gBot));

        Answer(1, i, "again");
        ASSERT_EQ(gAnswers, 1);
    }
}

test NoArguments() {
    inline OnAnswer(response, listitem, inputtext[32]) {
        #pragma unused listitem, inputtext
        gResponse = response;
    }

    ASSERT(Dialog_ShowInputInline(gBot, using inline OnAnswer, "Title", "plain", "Yes", "No"));
    Check(DIALOG_STYLE_INPUT, "plain");
    Answer(0, 0, "");
    ASSERT_EQ(gResponse, 0);
}

test ReplacesTheWaitingOne() {
    gAnswers = 0;

    ASSERT(Show(DIALOG_STYLE_LIST, "first"));
    ASSERT(Show(DIALOG_STYLE_MSGBOX, "second"));
    Check(DIALOG_STYLE_MSGBOX, "second 7 1.5");

    Answer(1, 0, "");
    ASSERT_EQ(gAnswers, 1);
}

test NotConnected() {
    inline OnAnswer(response, listitem, inputtext[32]) {
        #pragma unused response, listitem, inputtext
    }

    ASSERT_FALSE(Dialog_ShowTabListHeadersInline(MAX_PLAYERS - 1, using inline OnAnswer, "Title", "%i", "Yes", "No", 1));
}
