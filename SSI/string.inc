#if defined _INC_SSI_STRING
    #endinput
#endif
#define _INC_SSI_STRING

#include <open.mp>

/**
 * Strings changed in place and compared, beyond the natives of open.mp:
 *
 *     new
 *         name[32] = "  grove street  "
 *     ;
 *
 *     String_Trim(name);
 *     String_ToUpper(name);
 *
 *     switch (String_Hash(params, true)) {
 *         case HashI<gun>: {
 *         }
 *         case HashI<health>: {
 *         }
 *     }
 *
 * - Each function writes into the array it is given and takes its size last,
 *   `sizeof` by default. None returns a string.
 * - `Hash<text>` is the hash of a text written without quotes, worked out by
 *   the compiler, so it is a constant a `case` takes. `String_Hash` gives the
 *   same number for a string at run time. `HashI<text>` and
 *   `String_Hash(string, true)` ignore case. Two cases with the same hash do
 *   not compile, so a collision between them is never silent.
 * - A hashed text holds letters, digits, single spaces and `_ @ - .`. Any
 *   other character does not compile or gives another number.
 */

/**
 * # Header
 */

#if !defined SSI_STRING_DISTANCE_MAX
    #define SSI_STRING_DISTANCE_MAX (128)
#endif

enum STRING_EDGE {
    STRING_EDGE_LEFT = 1,
    STRING_EDGE_RIGHT,
    STRING_EDGE_BOTH
}

/**
 * `Hash<text>` is djb2 worked out by the preprocessor. Each character macro
 * below turns every copy of its character into its character literal and a
 * `>`, in place, since the compiler skips literals when it matches a pattern.
 * Numbers are written as literals too, so no digit macro reads them. Once the
 * characters are done `SSI@hf` folds the list from the left, and `SSI@hz` is
 * the result. The macros before it stay behind as tags, which `_:` drops.
 */
#define Hash<%0> (_:SSI@hc0:SSI@hc1:SSI@hc2:SSI@hc3:SSI@hc4:SSI@hc5:SSI@hc6:SSI@hc7:SSI@hc8:SSI@hc9:SSI@hca:SSI@hcb:SSI@hcc:SSI@hcd:SSI@hce:SSI@hcf:SSI@hcg:SSI@hch:SSI@hci:SSI@hcj:SSI@hck:SSI@hcl:SSI@hcm:SSI@hcn:SSI@hco:SSI@hcp:SSI@hcq:SSI@hcr:SSI@hcs:SSI@hct:SSI@hcu:SSI@hcv:SSI@hcw:SSI@hcx:SSI@hcy:SSI@hcz:SSI@hcA:SSI@hcB:SSI@hcC:SSI@hcD:SSI@hcE:SSI@hcF:SSI@hcG:SSI@hcH:SSI@hcI:SSI@hcJ:SSI@hcK:SSI@hcL:SSI@hcM:SSI@hcN:SSI@hcO:SSI@hcP:SSI@hcQ:SSI@hcR:SSI@hcS:SSI@hcT:SSI@hcU:SSI@hcV:SSI@hcW:SSI@hcX:SSI@hcY:SSI@hcZ:SSI@hpu:SSI@hpa:SSI@hpm:SSI@hpd:SSI@hps:SSI@hf:SSI@hz:$(('\255;'*'\21;'+'\26;')>%0)$)
#define HashI<%0> (_:SSI@hlA:SSI@hlB:SSI@hlC:SSI@hlD:SSI@hlE:SSI@hlF:SSI@hlG:SSI@hlH:SSI@hlI:SSI@hlJ:SSI@hlK:SSI@hlL:SSI@hlM:SSI@hlN:SSI@hlO:SSI@hlP:SSI@hlQ:SSI@hlR:SSI@hlS:SSI@hlT:SSI@hlU:SSI@hlV:SSI@hlW:SSI@hlX:SSI@hlY:SSI@hlZ:SSI@hc0:SSI@hc1:SSI@hc2:SSI@hc3:SSI@hc4:SSI@hc5:SSI@hc6:SSI@hc7:SSI@hc8:SSI@hc9:SSI@hca:SSI@hcb:SSI@hcc:SSI@hcd:SSI@hce:SSI@hcf:SSI@hcg:SSI@hch:SSI@hci:SSI@hcj:SSI@hck:SSI@hcl:SSI@hcm:SSI@hcn:SSI@hco:SSI@hcp:SSI@hcq:SSI@hcr:SSI@hcs:SSI@hct:SSI@hcu:SSI@hcv:SSI@hcw:SSI@hcx:SSI@hcy:SSI@hcz:SSI@hcA:SSI@hcB:SSI@hcC:SSI@hcD:SSI@hcE:SSI@hcF:SSI@hcG:SSI@hcH:SSI@hcI:SSI@hcJ:SSI@hcK:SSI@hcL:SSI@hcM:SSI@hcN:SSI@hcO:SSI@hcP:SSI@hcQ:SSI@hcR:SSI@hcS:SSI@hcT:SSI@hcU:SSI@hcV:SSI@hcW:SSI@hcX:SSI@hcY:SSI@hcZ:SSI@hpu:SSI@hpa:SSI@hpm:SSI@hpd:SSI@hps:SSI@hf:SSI@hz:$(('\255;'*'\21;'+'\26;')>%0)$)

#define SSI@hf:%9$(%0>%1>%2)$ SSI@hf:%9$((%0)*'\33;'^%1>%2)$
#define SSI@hz:%9$(%0>)$ (%0)

#define SSI@hc0:%9$(%10%0)$ SSI@hc0:%9$(%1'0'>%0)$
#define SSI@hc1:%9$(%11%0)$ SSI@hc1:%9$(%1'1'>%0)$
#define SSI@hc2:%9$(%12%0)$ SSI@hc2:%9$(%1'2'>%0)$
#define SSI@hc3:%9$(%13%0)$ SSI@hc3:%9$(%1'3'>%0)$
#define SSI@hc4:%9$(%14%0)$ SSI@hc4:%9$(%1'4'>%0)$
#define SSI@hc5:%9$(%15%0)$ SSI@hc5:%9$(%1'5'>%0)$
#define SSI@hc6:%9$(%16%0)$ SSI@hc6:%9$(%1'6'>%0)$
#define SSI@hc7:%9$(%17%0)$ SSI@hc7:%9$(%1'7'>%0)$
#define SSI@hc8:%9$(%18%0)$ SSI@hc8:%9$(%1'8'>%0)$
#define SSI@hc9:%9$(%19%0)$ SSI@hc9:%9$(%1'9'>%0)$
#define SSI@hca:%9$(%1a%0)$ SSI@hca:%9$(%1'a'>%0)$
#define SSI@hcb:%9$(%1b%0)$ SSI@hcb:%9$(%1'b'>%0)$
#define SSI@hcc:%9$(%1c%0)$ SSI@hcc:%9$(%1'c'>%0)$
#define SSI@hcd:%9$(%1d%0)$ SSI@hcd:%9$(%1'd'>%0)$
#define SSI@hce:%9$(%1e%0)$ SSI@hce:%9$(%1'e'>%0)$
#define SSI@hcf:%9$(%1f%0)$ SSI@hcf:%9$(%1'f'>%0)$
#define SSI@hcg:%9$(%1g%0)$ SSI@hcg:%9$(%1'g'>%0)$
#define SSI@hch:%9$(%1h%0)$ SSI@hch:%9$(%1'h'>%0)$
#define SSI@hci:%9$(%1i%0)$ SSI@hci:%9$(%1'i'>%0)$
#define SSI@hcj:%9$(%1j%0)$ SSI@hcj:%9$(%1'j'>%0)$
#define SSI@hck:%9$(%1k%0)$ SSI@hck:%9$(%1'k'>%0)$
#define SSI@hcl:%9$(%1l%0)$ SSI@hcl:%9$(%1'l'>%0)$
#define SSI@hcm:%9$(%1m%0)$ SSI@hcm:%9$(%1'm'>%0)$
#define SSI@hcn:%9$(%1n%0)$ SSI@hcn:%9$(%1'n'>%0)$
#define SSI@hco:%9$(%1o%0)$ SSI@hco:%9$(%1'o'>%0)$
#define SSI@hcp:%9$(%1p%0)$ SSI@hcp:%9$(%1'p'>%0)$
#define SSI@hcq:%9$(%1q%0)$ SSI@hcq:%9$(%1'q'>%0)$
#define SSI@hcr:%9$(%1r%0)$ SSI@hcr:%9$(%1'r'>%0)$
#define SSI@hcs:%9$(%1s%0)$ SSI@hcs:%9$(%1's'>%0)$
#define SSI@hct:%9$(%1t%0)$ SSI@hct:%9$(%1't'>%0)$
#define SSI@hcu:%9$(%1u%0)$ SSI@hcu:%9$(%1'u'>%0)$
#define SSI@hcv:%9$(%1v%0)$ SSI@hcv:%9$(%1'v'>%0)$
#define SSI@hcw:%9$(%1w%0)$ SSI@hcw:%9$(%1'w'>%0)$
#define SSI@hcx:%9$(%1x%0)$ SSI@hcx:%9$(%1'x'>%0)$
#define SSI@hcy:%9$(%1y%0)$ SSI@hcy:%9$(%1'y'>%0)$
#define SSI@hcz:%9$(%1z%0)$ SSI@hcz:%9$(%1'z'>%0)$
#define SSI@hcA:%9$(%1A%0)$ SSI@hcA:%9$(%1'A'>%0)$
#define SSI@hcB:%9$(%1B%0)$ SSI@hcB:%9$(%1'B'>%0)$
#define SSI@hcC:%9$(%1C%0)$ SSI@hcC:%9$(%1'C'>%0)$
#define SSI@hcD:%9$(%1D%0)$ SSI@hcD:%9$(%1'D'>%0)$
#define SSI@hcE:%9$(%1E%0)$ SSI@hcE:%9$(%1'E'>%0)$
#define SSI@hcF:%9$(%1F%0)$ SSI@hcF:%9$(%1'F'>%0)$
#define SSI@hcG:%9$(%1G%0)$ SSI@hcG:%9$(%1'G'>%0)$
#define SSI@hcH:%9$(%1H%0)$ SSI@hcH:%9$(%1'H'>%0)$
#define SSI@hcI:%9$(%1I%0)$ SSI@hcI:%9$(%1'I'>%0)$
#define SSI@hcJ:%9$(%1J%0)$ SSI@hcJ:%9$(%1'J'>%0)$
#define SSI@hcK:%9$(%1K%0)$ SSI@hcK:%9$(%1'K'>%0)$
#define SSI@hcL:%9$(%1L%0)$ SSI@hcL:%9$(%1'L'>%0)$
#define SSI@hcM:%9$(%1M%0)$ SSI@hcM:%9$(%1'M'>%0)$
#define SSI@hcN:%9$(%1N%0)$ SSI@hcN:%9$(%1'N'>%0)$
#define SSI@hcO:%9$(%1O%0)$ SSI@hcO:%9$(%1'O'>%0)$
#define SSI@hcP:%9$(%1P%0)$ SSI@hcP:%9$(%1'P'>%0)$
#define SSI@hcQ:%9$(%1Q%0)$ SSI@hcQ:%9$(%1'Q'>%0)$
#define SSI@hcR:%9$(%1R%0)$ SSI@hcR:%9$(%1'R'>%0)$
#define SSI@hcS:%9$(%1S%0)$ SSI@hcS:%9$(%1'S'>%0)$
#define SSI@hcT:%9$(%1T%0)$ SSI@hcT:%9$(%1'T'>%0)$
#define SSI@hcU:%9$(%1U%0)$ SSI@hcU:%9$(%1'U'>%0)$
#define SSI@hcV:%9$(%1V%0)$ SSI@hcV:%9$(%1'V'>%0)$
#define SSI@hcW:%9$(%1W%0)$ SSI@hcW:%9$(%1'W'>%0)$
#define SSI@hcX:%9$(%1X%0)$ SSI@hcX:%9$(%1'X'>%0)$
#define SSI@hcY:%9$(%1Y%0)$ SSI@hcY:%9$(%1'Y'>%0)$
#define SSI@hcZ:%9$(%1Z%0)$ SSI@hcZ:%9$(%1'Z'>%0)$
#define SSI@hpu:%9$(%1_%0)$ SSI@hpu:%9$(%1'_'>%0)$
#define SSI@hpa:%9$(%1@%0)$ SSI@hpa:%9$(%1'@'>%0)$
#define SSI@hpm:%9$(%1-%0)$ SSI@hpm:%9$(%1'-'>%0)$
#define SSI@hpd:%9$(%1.%0)$ SSI@hpd:%9$(%1'.'>%0)$
#define SSI@hps:%9$(%1\32;%0)$ SSI@hps:%9$(%1'\32;'>%0)$
#define SSI@hlA:%9$(%1A%0)$ SSI@hlA:%9$(%1'a'>%0)$
#define SSI@hlB:%9$(%1B%0)$ SSI@hlB:%9$(%1'b'>%0)$
#define SSI@hlC:%9$(%1C%0)$ SSI@hlC:%9$(%1'c'>%0)$
#define SSI@hlD:%9$(%1D%0)$ SSI@hlD:%9$(%1'd'>%0)$
#define SSI@hlE:%9$(%1E%0)$ SSI@hlE:%9$(%1'e'>%0)$
#define SSI@hlF:%9$(%1F%0)$ SSI@hlF:%9$(%1'f'>%0)$
#define SSI@hlG:%9$(%1G%0)$ SSI@hlG:%9$(%1'g'>%0)$
#define SSI@hlH:%9$(%1H%0)$ SSI@hlH:%9$(%1'h'>%0)$
#define SSI@hlI:%9$(%1I%0)$ SSI@hlI:%9$(%1'i'>%0)$
#define SSI@hlJ:%9$(%1J%0)$ SSI@hlJ:%9$(%1'j'>%0)$
#define SSI@hlK:%9$(%1K%0)$ SSI@hlK:%9$(%1'k'>%0)$
#define SSI@hlL:%9$(%1L%0)$ SSI@hlL:%9$(%1'l'>%0)$
#define SSI@hlM:%9$(%1M%0)$ SSI@hlM:%9$(%1'm'>%0)$
#define SSI@hlN:%9$(%1N%0)$ SSI@hlN:%9$(%1'n'>%0)$
#define SSI@hlO:%9$(%1O%0)$ SSI@hlO:%9$(%1'o'>%0)$
#define SSI@hlP:%9$(%1P%0)$ SSI@hlP:%9$(%1'p'>%0)$
#define SSI@hlQ:%9$(%1Q%0)$ SSI@hlQ:%9$(%1'q'>%0)$
#define SSI@hlR:%9$(%1R%0)$ SSI@hlR:%9$(%1'r'>%0)$
#define SSI@hlS:%9$(%1S%0)$ SSI@hlS:%9$(%1's'>%0)$
#define SSI@hlT:%9$(%1T%0)$ SSI@hlT:%9$(%1't'>%0)$
#define SSI@hlU:%9$(%1U%0)$ SSI@hlU:%9$(%1'u'>%0)$
#define SSI@hlV:%9$(%1V%0)$ SSI@hlV:%9$(%1'v'>%0)$
#define SSI@hlW:%9$(%1W%0)$ SSI@hlW:%9$(%1'w'>%0)$
#define SSI@hlX:%9$(%1X%0)$ SSI@hlX:%9$(%1'x'>%0)$
#define SSI@hlY:%9$(%1Y%0)$ SSI@hlY:%9$(%1'y'>%0)$
#define SSI@hlZ:%9$(%1Z%0)$ SSI@hlZ:%9$(%1'z'>%0)$

/**
 * # Functions
 */

/**
 * @brief      The hash of a string, the number `Hash<>` gives for the same text.
 *
 * @param      string      The string.
 * @param      ignorecase  Whether upper case letters count as lower case, as
 *                         `HashI<>` does.
 *
 * @return     - the hash
 */
forward String_Hash(const string[], bool:ignorecase = false);

/**
 * @brief      Turn every letter of a string to upper case.
 *
 * @param      string  The string.
 */
forward String_ToUpper(string[]);

/**
 * @brief      Turn every letter of a string to lower case.
 *
 * @param      string  The string.
 */
forward String_ToLower(string[]);

/**
 * @brief      Remove characters from the edges of a string.
 *
 * @param      string  The string.
 * @param      chars   The characters to remove, or empty for spaces, tabs and
 *                     line breaks.
 * @param      edge    The edges to trim.
 *
 * @return     - the new length
 */
forward String_Trim(string[], const chars[] = "", STRING_EDGE:edge = STRING_EDGE_BOTH);

/**
 * @brief      Lengthen a string to `length` with copies of `pad`.
 *
 * Padding both edges puts the odd character on the right.
 *
 * @param      string  The string.
 * @param      length  The length to reach, at most `size - 1`.
 * @param      pad     The characters to repeat.
 * @param      edge    The edges to pad.
 * @param      size    Size of `string`.
 *
 * @return     - the new length
 */
forward String_Pad(string[], length, const pad[] = " ", STRING_EDGE:edge = STRING_EDGE_RIGHT, size = sizeof (string));

/**
 * @brief      Replace each occurrence of `search` in a string, from the left.
 *
 * Text pushed past `size` is cut off.
 *
 * @param      string       The string.
 * @param      search       The text to find.
 * @param      replacement  The text to put in its place.
 * @param      ignorecase   Whether case is ignored when finding.
 * @param      limit        The most occurrences to replace.
 * @param      size         Size of `string`.
 *
 * @return     - how many were replaced
 */
forward String_Replace(string[], const search[], const replacement[], bool:ignorecase = false, limit = cellmax, size = sizeof (string));

/**
 * @brief      How many times `search` occurs in a string, without overlaps.
 *
 * @param      string      The string.
 * @param      search      The text to find.
 * @param      ignorecase  Whether case is ignored.
 *
 * @return     - the count
 */
forward String_Count(const string[], const search[], bool:ignorecase = false);

/**
 * @brief      Whether a string starts with `prefix`.
 *
 * @param      string      The string.
 * @param      prefix      The start to look for. An empty one always matches.
 * @param      ignorecase  Whether case is ignored.
 */
forward bool:String_StartsWith(const string[], const prefix[], bool:ignorecase = false);

/**
 * @brief      Whether a string ends with `suffix`.
 *
 * @param      string      The string.
 * @param      suffix      The end to look for. An empty one always matches.
 * @param      ignorecase  Whether case is ignored.
 */
forward bool:String_EndsWith(const string[], const suffix[], bool:ignorecase = false);

/**
 * @brief      Split a string at each `delimiter` into the rows of `output`.
 *
 * Empty pieces are kept, and the last row takes the rest of the string when
 * there are more pieces than rows. An empty `delimiter` gives the whole string.
 *
 * @param      string      The string.
 * @param      delimiter   The text between pieces.
 * @param      output      Where the pieces go.
 * @param      ignorecase  Whether case is ignored when finding `delimiter`.
 * @param      count       Rows of `output`.
 * @param      size        Size of each row.
 *
 * @return     - how many rows were written, `0` only when `count` is `0`
 */
forward String_Split(const string[], const delimiter[], output[][], bool:ignorecase = false, count = sizeof (output), size = sizeof (output[]));

/**
 * @brief      Join the first `count` rows of `parts` into `output`, with `glue`
 *             between them.
 *
 * @param      output  Where the text goes.
 * @param      glue    The text between parts.
 * @param      parts   The parts.
 * @param      count   How many rows to join.
 * @param      size    Size of `output`.
 *
 * @return     - the length of `output`
 */
forward String_Join(output[], const glue[], const parts[][], count = sizeof (parts), size = sizeof (output));

/**
 * @brief      The edit distance between two strings: how many characters must
 *             be inserted, removed or changed to turn one into the other.
 *
 * Only the first `SSI_STRING_DISTANCE_MAX` characters of each are compared.
 *
 * @param      first       A string.
 * @param      second      Another string.
 * @param      ignorecase  Whether case is ignored.
 *
 * @return     - the distance, `0` for equal strings
 */
forward String_Distance(const first[], const second[], bool:ignorecase = false);

/**
 * @brief      Encode a string for a URL: every byte but letters, digits and
 *             `- _ . ~` becomes `%` and two hex digits.
 *
 * A byte that would not fit whole is left out with the rest.
 *
 * @param      output  Where the text goes.
 * @param      input   The string.
 * @param      size    Size of `output`.
 *
 * @return     - the length of `output`
 */
forward String_UrlEncode(output[], const input[], size = sizeof (output));

/**
 * @brief      Decode a string from a URL: `%` and two hex digits become their
 *             byte and `+` a space.
 *
 * @param      output  Where the text goes.
 * @param      input   The encoded string.
 * @param      size    Size of `output`.
 *
 * @return     - the length of `output`
 */
forward String_UrlDecode(output[], const input[], size = sizeof (output));

/**
 * # Internal
 */

static stock bool:SSI@String_IsTrimmed(character, const chars[]) {
    if (chars[0] == EOS) {
        return character != EOS && character <= ' ';
    }

    for (new i; chars[i] != EOS; ++i) {
        if (chars[i] == character) {
            return true;
        }
    }

    return false;
}

static stock SSI@String_HexDigit(character) {
    if ('0' <= character <= '9') {
        return character - '0';
    }

    if ('A' <= character <= 'F') {
        return character - 'A' + 10;
    }

    if ('a' <= character <= 'f') {
        return character - 'a' + 10;
    }

    return -1;
}

/**
 * # String
 */

stock String_Hash(const string[], bool:ignorecase = false) {
    new
        hash = 5381
    ;

    for (new i; string[i] != EOS; ++i) {
        new const
            character = string[i]
        ;

        hash = hash * 33 ^ ((ignorecase && 'A' <= character <= 'Z') ? character | 0x20 : character);
    }

    return hash;
}

stock String_ToUpper(string[]) {
    for (new i; string[i] != EOS; ++i) {
        string[i] = toupper(string[i]);
    }
}

stock String_ToLower(string[]) {
    for (new i; string[i] != EOS; ++i) {
        string[i] = tolower(string[i]);
    }
}

stock String_Trim(string[], const chars[] = "", STRING_EDGE:edge = STRING_EDGE_BOTH) {
    new
        length = strlen(string),
        start
    ;

    if (edge & STRING_EDGE_RIGHT) {
        while (length != 0 && SSI@String_IsTrimmed(string[length - 1], chars)) {
            --length;
        }

        string[length] = EOS;
    }

    if (edge & STRING_EDGE_LEFT) {
        while (start != length && SSI@String_IsTrimmed(string[start], chars)) {
            ++start;
        }

        if (start != 0) {
            strdel(string, 0, start);
        }
    }

    return length - start;
}

stock String_Pad(string[], length, const pad[] = " ", STRING_EDGE:edge = STRING_EDGE_RIGHT, size = sizeof (string)) {
    new const
        current = strlen(string),
        target = min(length, size - 1),
        padLength = strlen(pad)
    ;

    if (current >= target) {
        return current;
    }

    if (padLength == 0) {
        return current;
    }

    new const
        total = target - current,
        left = (edge == STRING_EDGE_BOTH) ? total / 2 : ((edge == STRING_EDGE_LEFT) ? total : 0)
    ;

    for (new i = current; i >= 0; --i) {
        string[i + left] = string[i];
    }

    for (new i; i != left; ++i) {
        string[i] = pad[i % padLength];
    }

    for (new i = left + current; i != target; ++i) {
        string[i] = pad[(i - left - current) % padLength];
    }

    string[target] = EOS;

    return target;
}

stock String_Replace(string[], const search[], const replacement[], bool:ignorecase = false, limit = cellmax, size = sizeof (string)) {
    new const
        searchLength = strlen(search),
        replacementLength = strlen(replacement)
    ;

    if (searchLength == 0) {
        return 0;
    }

    new
        count,
        position
    ;

    while (count != limit && (position = strfind(string, search, ignorecase, position)) != -1) {
        strdel(string, position, position + searchLength);
        strins(string, replacement, position, size);

        position += replacementLength;
        ++count;
    }

    return count;
}

stock String_Count(const string[], const search[], bool:ignorecase = false) {
    new const
        searchLength = strlen(search)
    ;

    if (searchLength == 0) {
        return 0;
    }

    new
        count,
        position
    ;

    while ((position = strfind(string, search, ignorecase, position)) != -1) {
        position += searchLength;
        ++count;
    }

    return count;
}

stock bool:String_StartsWith(const string[], const prefix[], bool:ignorecase = false) {
    new const
        length = strlen(prefix)
    ;

    if (length == 0) {
        return true;
    }

    if (strlen(string) < length) {
        return false;
    }

    return strcmp(string, prefix, ignorecase, length) == 0;
}

stock bool:String_EndsWith(const string[], const suffix[], bool:ignorecase = false) {
    new const
        length = strlen(suffix),
        offset = strlen(string) - length
    ;

    if (length == 0) {
        return true;
    }

    if (offset < 0) {
        return false;
    }

    return strcmp(string[offset], suffix, ignorecase) == 0;
}

stock String_Split(const string[], const delimiter[], output[][], bool:ignorecase = false, count = sizeof (output), size = sizeof (output[])) {
    if (count == 0) {
        return 0;
    }

    new const
        delimiterLength = strlen(delimiter)
    ;

    new
        pieces,
        start,
        position
    ;

    while (delimiterLength != 0 && pieces != count - 1 && (position = strfind(string, delimiter, ignorecase, start)) != -1) {
        strmid(output[pieces++], string, start, position, size);
        start = position + delimiterLength;
    }

    strmid(output[pieces++], string, start, strlen(string), size);

    return pieces;
}

stock String_Join(output[], const glue[], const parts[][], count = sizeof (parts), size = sizeof (output)) {
    if (count == 0) {
        output[0] = EOS;

        return 0;
    }

    strcopy(output, parts[0], size);

    for (new i = 1; i != count; ++i) {
        strcat(output, glue, size);
        strcat(output, parts[i], size);
    }

    return strlen(output);
}

stock String_Distance(const first[], const second[], bool:ignorecase = false) {
    static
        row[SSI_STRING_DISTANCE_MAX + 1]
    ;

    new const
        firstLength = min(strlen(first), SSI_STRING_DISTANCE_MAX),
        secondLength = min(strlen(second), SSI_STRING_DISTANCE_MAX)
    ;

    for (new j; j <= secondLength; ++j) {
        row[j] = j;
    }

    for (new i = 1; i <= firstLength; ++i) {
        new const
            firstCharacter = ignorecase ? tolower(first[i - 1]) : first[i - 1]
        ;

        new
            diagonal = row[0]
        ;

        row[0] = i;

        for (new j = 1; j <= secondLength; ++j) {
            new const
                secondCharacter = ignorecase ? tolower(second[j - 1]) : second[j - 1],
                above = row[j]
            ;

            row[j] = min(min(above, row[j - 1]) + 1, diagonal + _:(firstCharacter != secondCharacter));
            diagonal = above;
        }
    }

    return row[secondLength];
}

stock String_UrlEncode(output[], const input[], size = sizeof (output)) {
    static const
        hex[] = "0123456789ABCDEF"
    ;

    new
        length
    ;

    for (new i; input[i] != EOS; ++i) {
        new const
            character = input[i] & 0xFF
        ;

        if (('a' <= character <= 'z') || ('A' <= character <= 'Z') || ('0' <= character <= '9') || character == '-' || character == '_' || character == '.' || character == '~') {
            if (length + 1 >= size) {
                break;
            }

            output[length++] = character;

            continue;
        }

        if (length + 3 >= size) {
            break;
        }

        output[length++] = '%';
        output[length++] = hex[character >>> 4];
        output[length++] = hex[character & 0xF];
    }

    output[length] = EOS;

    return length;
}

stock String_UrlDecode(output[], const input[], size = sizeof (output)) {
    new
        length,
        i
    ;

    while (input[i] != EOS && length + 1 < size) {
        new
            character = input[i++]
        ;

        if (character == '+') {
            character = ' ';
        } else if (character == '%') {
            new const
                high = SSI@String_HexDigit(input[i]),
                low = (high == -1) ? -1 : SSI@String_HexDigit(input[i + 1])
            ;

            if (low != -1) {
                character = high << 4 | low;
                i += 2;
            }
        }

        output[length++] = character;
    }

    output[length] = EOS;

    return length;
}
