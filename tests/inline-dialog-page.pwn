#define SSI_TESTS
#define SSI_TEST_EXIT

#include <open.mp>
#include <SSI_Extra\inline-dialog>
#include <SSI\test>
#include <SSI\hooks>

main() {
}

static
    gBot = INVALID_PLAYER_ID,
    gCalls,
    gResponse,
    gRow,
    gText[64]
;

static Answer(response, listitem) {
    CallLocalFunction("OnDialogResponse", "iiiis", gBot, SSI_DIALOG_ID, response, listitem, "x");
}

static Body(output[], size = sizeof (output)) {
    new
        DIALOG_STYLE:style,
        title[64],
        button1[32],
        button2[32]
    ;

    GetPlayerDialogData(gBot, style, title, sizeof (title), output, size, button1, sizeof (button1), button2, sizeof (button2));
}

static ShowRows(DIALOG_STYLE:style, const header[], count, rows) {
    static
        body[1024]
    ;

    body[0] = EOS;
    strcat(body, header);

    for (new i; i != count; ++i) {
        format(body, sizeof (body), "%s%sRow %i", body, (i == 0) ? ("") : ("\n"), i);
    }

    inline OnAnswer(response, listitem, inputtext[64]) {
        ++gCalls;
        gResponse = response;
        gRow = listitem;
        gText[0] = EOS;
        strcat(gText, inputtext);
    }

    return Dialog_ShowPageInline(gBot, using inline OnAnswer, style, "Rows", body, "Pick", "Close", rows);
}

test Pages() {
    new
        body[1024]
    ;

    gBot = NPC_Create("PageBot");
    ASSERT(IsPlayerConnected(gBot));

    ASSERT(ShowRows(DIALOG_STYLE_LIST, "", 25, 10));
    ASSERT(Dialog_IsOpen(gBot));
    Body(body);
    ASSERT_EQ(strfind(body, "Row 0\nRow 1\n"), 0);
    ASSERT(strfind(body, "Row 9\n>>>") != -1);
    ASSERT_EQ(strfind(body, "<<<"), -1);

    Answer(1, 10);
    ASSERT_EQ(gCalls, 0);
    Body(body);
    ASSERT_EQ(strfind(body, "Row 10\n"), 0);
    ASSERT(strfind(body, "Row 19\n>>>\n<<<") != -1);

    Answer(1, 10);
    Body(body);
    ASSERT_EQ(strfind(body, "Row 20\n"), 0);
    ASSERT(strfind(body, "Row 24\n<<<") != -1);
    ASSERT_EQ(strfind(body, ">>>"), -1);

    Answer(1, 5);
    Body(body);
    ASSERT_EQ(strfind(body, "Row 10\n"), 0);

    Answer(1, 99);
    ASSERT_EQ(gCalls, 0);

    Answer(1, 3);
    ASSERT_EQ(gCalls, 1);
    ASSERT_EQ(gResponse, 1);
    ASSERT_EQ(gRow, 13);
    ASSERT_SAME(gText, "x");
    ASSERT_FALSE(Dialog_IsOpen(gBot));

    ASSERT(ShowRows(DIALOG_STYLE_LIST, "", 25, 10));
    Answer(0, 2);
    ASSERT_EQ(gCalls, 2);
    ASSERT_EQ(gResponse, 0);
    ASSERT_EQ(gRow, -1);
}

test Headers() {
    new
        body[1024]
    ;

    ASSERT(ShowRows(DIALOG_STYLE_TABLIST_HEADERS, "Name\tValue\n", 4, 3));
    Body(body);
    ASSERT_EQ(strfind(body, "Name\tValue\nRow 0\nRow 1\nRow 2\n>>>"), 0);

    Answer(1, 3);
    Body(body);
    ASSERT_EQ(strfind(body, "Name\tValue\nRow 3\n<<<"), 0);

    Answer(1, 0);
    ASSERT_EQ(gCalls, 3);
    ASSERT_EQ(gRow, 3);
}

test Fits() {
    ASSERT(ShowRows(DIALOG_STYLE_LIST, "", 3, 10));

    new
        body[256]
    ;

    Body(body);
    ASSERT_EQ(strfind(body, ">>>"), -1);

    Answer(1, 2);
    ASSERT_EQ(gCalls, 4);
    ASSERT_EQ(gRow, 2);
}

test Refuses() {
    inline OnAnswer(response, listitem, inputtext[64]) {
        #pragma unused response, listitem, inputtext
    }

    ASSERT_FALSE(Dialog_ShowPageInline(gBot, using inline OnAnswer, DIALOG_STYLE_INPUT, "T", "a", "b"));
    ASSERT_FALSE(Dialog_ShowPageInline(gBot, using inline OnAnswer, DIALOG_STYLE_LIST, "T", "a", "b", "", 0));
}

test PlainAfterPage() {
    ASSERT(ShowRows(DIALOG_STYLE_LIST, "", 25, 10));

    inline OnPlain(response, listitem, inputtext[64]) {
        #pragma unused inputtext
        ++gCalls;
        gResponse = response;
        gRow = listitem;
    }

    ASSERT(Dialog_ShowListInline(gBot, using inline OnPlain, "Plain", "a\nb\nc", "Pick"));
    Answer(1, 10);
    ASSERT_EQ(gCalls, 5);
    ASSERT_EQ(gRow, 10);

    NPC_Destroy(gBot);
}
