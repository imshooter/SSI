#define SSI_TESTS
#define SSI_TEST_EXIT

#include <open.mp>
#include <SSI\string>
#include <SSI\test>

Djb2(const string[], bool:ignorecase = false) {
    new
        hash = 5381
    ;

    for (new i; string[i] != EOS; ++i) {
        new
            character = string[i]
        ;

        if (ignorecase && 'A' <= character <= 'Z') {
            character += 'a' - 'A';
        }

        hash = hash * 33 ^ character;
    }

    return hash;
}

#define SAME_HASH(%0) ASSERT(Hash<%0> == Djb2(#%0) && String_Hash(#%0) == Djb2(#%0))
#define SAME_HASHI(%0) ASSERT(HashI<%0> == Djb2(#%0, true) && String_Hash(#%0, true) == Djb2(#%0, true))

Pick(const command[]) {
    switch (String_Hash(command, true)) {
        case HashI<gun>: {
            return 1;
        }
        case HashI<health>: {
            return 2;
        }
        case HashI<hood collect>: {
            return 3;
        }
    }

    return 0;
}

test Hashes() {
    SAME_HASH(gun);
    SAME_HASH(abba);
    SAME_HASH(bca);
    SAME_HASH(Hello World);
    SAME_HASH(GAN1);
    SAME_HASH(x_y@z-1.5);
    SAME_HASH(0123456789);
    SAME_HASH(abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ);
    SAME_HASH(the quick brown fox jumps over the lazy dog 0123456789 THE QUICK BROWN FOX);
    SAME_HASHI(HeLLo);
    SAME_HASHI(GAN1);
    ASSERT_EQ(Hash<>, 5381);
    ASSERT_EQ(String_Hash(""), 5381);
    ASSERT_NE(Hash<Gun>, Hash<gun>);
    ASSERT_EQ(HashI<Gun>, HashI<gun>);
    ASSERT_EQ(Pick("gun"), 1);
    ASSERT_EQ(Pick("HEALTH"), 2);
    ASSERT_EQ(Pick("Hood Collect"), 3);
    ASSERT_EQ(Pick("car"), 0);
}

test Cases() {
    new
        text[32] = "Grove St. 4"
    ;

    String_ToUpper(text);
    ASSERT_SAME(text, "GROVE ST. 4");
    String_ToLower(text);
    ASSERT_SAME(text, "grove st. 4");
}

test Trims() {
    new
        text[32] = " \t grove \n "
    ;

    ASSERT_EQ(String_Trim(text), 5);
    ASSERT_SAME(text, "grove");

    text = "--grove--";
    ASSERT_EQ(String_Trim(text, "-", STRING_EDGE_LEFT), 7);
    ASSERT_SAME(text, "grove--");
    ASSERT_EQ(String_Trim(text, "-", STRING_EDGE_RIGHT), 5);
    ASSERT_SAME(text, "grove");

    text = "   ";
    ASSERT_EQ(String_Trim(text), 0);
    ASSERT_SAME(text, "");
}

test Pads() {
    new
        text[8] = "ab"
    ;

    ASSERT_EQ(String_Pad(text, 5), 5);
    ASSERT_SAME(text, "ab   ");

    text = "ab";
    ASSERT_EQ(String_Pad(text, 5, "0", STRING_EDGE_LEFT), 5);
    ASSERT_SAME(text, "000ab");

    text = "ab";
    ASSERT_EQ(String_Pad(text, 5, "*", STRING_EDGE_BOTH), 5);
    ASSERT_SAME(text, "*ab**");

    text = "ab";
    ASSERT_EQ(String_Pad(text, 20, "xy"), 7);
    ASSERT_SAME(text, "abxyxyx");

    text = "abcdef";
    ASSERT_EQ(String_Pad(text, 3), 6);
    ASSERT_SAME(text, "abcdef");
}

test Replaces() {
    new
        text[16] = "a-b-c-d"
    ;

    ASSERT_EQ(String_Replace(text, "-", ", "), 3);
    ASSERT_SAME(text, "a, b, c, d");

    text = "aXbxc";
    ASSERT_EQ(String_Replace(text, "x", "", true), 2);
    ASSERT_SAME(text, "abc");

    text = "aaaa";
    ASSERT_EQ(String_Replace(text, "a", "aa", false, 2), 2);
    ASSERT_SAME(text, "aaaaaa");

    text = "abc";
    ASSERT_EQ(String_Replace(text, "", "x"), 0);

    new
        small[6] = "a.b"
    ;

    ASSERT_EQ(String_Replace(small, ".", "1234"), 1);
    ASSERT_SAME(small, "a1234");
}

test Counts() {
    ASSERT_EQ(String_Count("aaaa", "aa"), 2);
    ASSERT_EQ(String_Count("Gun gun GUN", "gun", true), 3);
    ASSERT_EQ(String_Count("abc", ""), 0);
    ASSERT(String_StartsWith("hoodcollect", "hood"));
    ASSERT(String_StartsWith("HoodCollect", "hood", true));
    ASSERT_FALSE(String_StartsWith("ho", "hood"));
    ASSERT_FALSE(String_StartsWith("", "hood"));
    ASSERT(String_StartsWith("", ""));
    ASSERT(String_EndsWith("GAN1", "N1"));
    ASSERT_FALSE(String_EndsWith("1", "N1"));
    ASSERT(String_EndsWith("gan1", "N1", true));
}

test Splits() {
    new
        parts[3][8],
        joined[32]
    ;

    ASSERT_EQ(String_Split("a,,b", ",", parts), 3);
    ASSERT_SAME(parts[0], "a");
    ASSERT_SAME(parts[1], "");
    ASSERT_SAME(parts[2], "b");

    ASSERT_EQ(String_Split("a, b, c, d", ", ", parts), 3);
    ASSERT_SAME(parts[2], "c, d");

    ASSERT_EQ(String_Split("abc", "", parts), 1);
    ASSERT_SAME(parts[0], "abc");

    ASSERT_EQ(String_Split("aXbxc", "x", parts, true), 3);
    ASSERT_SAME(parts[1], "b");

    ASSERT_EQ(String_Join(joined, " | ", parts), 9);
    ASSERT_SAME(joined, "a | b | c");
    ASSERT_EQ(String_Join(joined, ",", parts, 0), 0);
    ASSERT_SAME(joined, "");
}

test Distances() {
    ASSERT_EQ(String_Distance("kitten", "sitting"), 3);
    ASSERT_EQ(String_Distance("hoodcolect", "hoodcollect"), 1);
    ASSERT_EQ(String_Distance("", "abc"), 3);
    ASSERT_EQ(String_Distance("abc", ""), 3);
    ASSERT_EQ(String_Distance("Gun", "gun"), 1);
    ASSERT_EQ(String_Distance("Gun", "gun", true), 0);
    ASSERT_EQ(String_Distance("flaw", "lawn"), 2);
}

test Urls() {
    new
        encoded[64],
        decoded[64]
    ;

    ASSERT_EQ(String_UrlEncode(encoded, "a b&c=d/~"), 17);
    ASSERT_SAME(encoded, "a%20b%26c%3Dd%2F~");
    ASSERT_EQ(String_UrlDecode(decoded, encoded), 9);
    ASSERT_SAME(decoded, "a b&c=d/~");
    String_UrlDecode(decoded, "a+b%zz%4");
    ASSERT_SAME(decoded, "a b%zz%4");

    new
        small[5]
    ;

    ASSERT_EQ(String_UrlEncode(small, "ab c"), 2);
    ASSERT_SAME(small, "ab");
}
