"""Writes the benchmark scripts of this folder, one for each library and side."""

import os
from string import Template

HERE = os.path.dirname(os.path.abspath(__file__))

MAIN = '''
main() {
}

forward @Bench();
public @Bench() {
    if (gBenchRound == 0) {
        First();
        gBenchQuiet = true;
        Run();
        gBenchQuiet = false;
    } else {
        Bench_Calibrate();
        Run();
    }

    if (++gBenchRound > BENCH_ROUNDS) {
        Bench_Done();
    } else {
        SetTimer("@Bench", 500, false);
    }
}
'''

FIRST = '''
First() {
}
'''

START = '''
public OnGameModeInit() {
    Setup();
    SetTimer("@Bench", 1000, false);

    return 1;
}
'''


def write(name, text):
    with open(os.path.join(HERE, name + '.pwn'), 'w', newline='\n') as f:
        f.write(text.lstrip('\n'))


def head(side, includes):
    return '#define BENCH_SIDE "%s"\n\n#include <open.mp>\n%s\n#include "bench.inc"\n' % (side, includes)


def hooks():
    for side in ('SSI', 'YSI', 'PawnPlus'):
        for count in (0, 1, 10, 100):
            if side == 'SSI':
                text = head(side, '#include <SSI\\hooks>')
            elif side == 'YSI':
                text = head(side, '#define _FOREACH_NO_TEST\n#include <YSI_Coding\\y_hooks>')
            else:
                text = head(side, '#include <PawnPlus>')

            text += '''
#define HOOKS (%d)

new
    gHits
;

forward OnBench(a, b, c);
public OnBench(a, b, c) {
    gBenchSink += a;
    ++gHits;

    return 1;
}
''' % count

            for k in range(count):
                if side == 'SSI':
                    text += '\nhook OnBench@%d(a, b, c) {\n    gBenchSink += b;\n    ++gHits;\n\n    return 0;\n}\n' % k
                elif side == 'YSI':
                    text += '\n#include <YSI_Coding\\y_hooks>\n\nhook OnBench(a, b, c) {\n    gBenchSink += b;\n    ++gHits;\n\n    return 0;\n}\n'
                else:
                    text += '\nforward @Handler%d(a, b, c);\npublic @Handler%d(a, b, c) {\n    gBenchSink += b;\n    ++gHits;\n\n    return 0;\n}\n' % (k, k)

            setup = ''
            if side == 'PawnPlus':
                setup = ''.join('    pawn_register_callback("OnBench", "@Handler%d");\n' % k for k in range(count))

            text += '''
Setup() {
%s}

Run() {
    gHits = 0;
    CallLocalFunction("OnBench", "iii", 1, 2, 3);
    Bench_Check("hooks run", gHits, HOOKS + 1);

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            CallLocalFunction("OnBench", "iii", i, 2, 3);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("hooks", "callback with %d hooks");
}
''' % (setup, count) + FIRST + MAIN + START
            write('hooks_%s_%d' % (side.lower(), count), text)


COLLECTION_RUN = Template('''
Run() {
    new
        j,
        id
    ;

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            id = $alloc;
            $free;
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("collection", "take and give back an id, $filled of $size used");
    Bench_Check("ids used", $count, $filled);

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            if ($contains) {
                ++gBenchSink;
            }

            if (++j == $size) {
                j = 0;
            }
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("collection", "contains, $size ids");

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            $remove;
            $add;

            if ((j += 2) >= $size) {
                j = 0;
            }
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("collection", "remove and add a value, $size values");

    Bench_Begin();

    do {
        $walk
    } while (Bench_Next(1));

    Bench_End("collection", "walk, per id, $filled ids", $filled);
}
''')


def collection():
    for size, filled in ((4096, 2048), (100000, 99000)):
        values = dict(size=size, filled=filled)

        text = head('SSI', '#include <SSI\\collection>') + '''
new
    Collection:Pool<%d>,
    Collection:Set<%d>
;

#define Pool: _:
#define Set: _:

Setup() {
    for (new i; i != %d; ++i) {
        Collection_Alloc(Pool);
    }

    for (new i; i < %d; i += 2) {
        Collection_Add(Set, i);
    }
}
''' % (size, size, filled, size)
        text += COLLECTION_RUN.substitute(values,
            alloc='Collection_Alloc(Pool)',
            free='Collection_Remove(Pool, id)',
            count='Collection_Count(Pool)',
            contains='Collection_Contains(Pool, j)',
            remove='Collection_Remove(Set, j)',
            add='Collection_Add(Set, j)',
            walk='foreach (new k : Pool) {\n            gBenchSink += k;\n        }') + FIRST + MAIN + START
        write('collection_ssi_%d' % size, text)

        text = head('YSI', '#define _FOREACH_NO_TEST\n#include <YSI_Data\\y_iterate>') + '''
new
    Iterator:Pool<%d>,
    Iterator:Set<%d>
;

Setup() {
    for (new i; i != %d; ++i) {
        Iter_Alloc(Pool);
    }

    for (new i; i < %d; i += 2) {
        Iter_Add(Set, i);
    }
}
''' % (size, size, filled, size)
        text += COLLECTION_RUN.substitute(values,
            alloc='Iter_Alloc(Pool)',
            free='Iter_Remove(Pool, id)',
            count='Iter_Count(Pool)',
            contains='Iter_Contains(Pool, j)',
            remove='Iter_Remove(Set, j)',
            add='Iter_Add(Set, j)',
            walk='foreach (new k : Pool) {\n            gBenchSink += k;\n        }') + FIRST + MAIN + START
        write('collection_ysi_%d' % size, text)

        text = head('PawnPlus', '#include <PawnPlus>') + '''
new
    Pool:gPool,
    Pool:gSet
;

Setup() {
    gPool = pool_new(%d);
    gSet = pool_new(%d);

    for (new i; i != %d; ++i) {
        pool_add(gPool, 0);
    }

    for (new i; i < %d; ++i) {
        if (i & 1) {
            pool_add(gSet, 0);
        } else {
            pool_add(gSet, 1);
        }
    }

    for (new i = 1; i < %d; i += 2) {
        pool_remove(gSet, i);
    }
}
''' % (size, size, filled, size, size)
        text += COLLECTION_RUN.substitute(values,
            alloc='pool_add(gPool, 0)',
            free='pool_remove(gPool, id)',
            count='pool_size(gPool)',
            contains='pool_has(gPool, j)',
            remove='pool_remove(gSet, j)',
            add='pool_set(gSet, j, 1)',
            walk='for (new Iter:it = pool_iter(gPool); iter_inside(it); iter_move_next(it)) {\n            gBenchSink += iter_get_key(it);\n        }') + FIRST + MAIN + START
        write('collection_pawnplus_%d' % size, text)


DICTIONARY_RUN = Template('''
Run() {
    new
        value,
        fill,
        remove,
        rounds,
        start
    ;

    do {
        start = GetTickCount();

        for (new i; i != $size; ++i) {
            $set
        }

        fill += GetTickCount() - start;
        Bench_Check("keys", $count, $size);

        start = GetTickCount();

        for (new i; i != $size; ++i) {
            $remove
        }

        remove += GetTickCount() - start;
        ++rounds;
    } while (fill + remove < BENCH_TIME);

    Bench_Report("dictionary", "insert, $size $kind keys", fill, rounds * $size);
    Bench_Report("dictionary", "remove, $size $kind keys", remove, rounds * $size);

    for (new i; i != $size; ++i) {
        $set
    }

    Bench_Begin();

    do {
        for (new i; i != $size; ++i) {
            $get
        }
    } while (Bench_Next($size));

    Bench_End("dictionary", "get, $size $kind keys");

    Bench_Begin();

    do {
        for (new i; i != $size; ++i) {
            $miss
        }
    } while (Bench_Next($size));

    Bench_End("dictionary", "missing key, $size $kind keys");

    Bench_Begin();

    do {
        for (new i; i != $size; ++i) {
            $set
        }
    } while (Bench_Next($size));

    Bench_End("dictionary", "set a key that is there, $size $kind keys");

    for (new i; i != $size; ++i) {
        $remove
    }

    gBenchSink += value;
}
''')

TEXT_KEYS = '''
new
    gKey[%d][33],
    gMiss[%d][33]
;

MakeKeys() {
    for (new i; i != sizeof (gKey); ++i) {
        format(gKey[i], sizeof (gKey[]), "account_%%08i_character_name", i * 7919);
        format(gMiss[i], sizeof (gMiss[]), "account_%%08i_character_other", i * 7919);
    }
}
'''


def dictionary():
    for size in (4096, 100000):
        values = dict(size=size, kind='number')

        text = head('SSI', '#include <SSI\\dictionary>') + '''
new
    Dictionary:Numbers<%d>
;

Setup() {
}
''' % size
        text += DICTIONARY_RUN.substitute(values,
            set='Dictionary_Set(Numbers, i * 15838, i);',
            remove='Dictionary_Remove(Numbers, i * 15838);',
            count='Dictionary_Count(Numbers)',
            get='Dictionary_Get(Numbers, i * 15838, value);',
            miss='if (Dictionary_Contains(Numbers, i * 15838 + 1)) {\n                ++value;\n            }') + FIRST + MAIN + START
        write('dictionary_ssi_number_%d' % size, text)

        text = head('PawnPlus', '#include <PawnPlus>') + '''
new
    Map:gNumbers
;

Setup() {
    gNumbers = map_new();
}
'''
        text += DICTIONARY_RUN.substitute(values,
            set='map_set(gNumbers, i * 15838, i);',
            remove='map_remove(gNumbers, i * 15838);',
            count='map_size(gNumbers)',
            get='value += map_get(gNumbers, i * 15838);',
            miss='if (map_has_key(gNumbers, i * 15838 + 1)) {\n                ++value;\n            }') + FIRST + MAIN + START
        write('dictionary_pawnplus_number_%d' % size, text)

    for size in (4096, 20000):
        values = dict(size=size, kind='text')

        text = head('SSI', '#include <SSI\\dictionary>') + TEXT_KEYS % (size, size) + '''
new
    Dictionary:Names<%d, 32>
;

Setup() {
    MakeKeys();
}
''' % size
        text += DICTIONARY_RUN.substitute(values,
            set='Dictionary_Set(Names<>, gKey[i], i);',
            remove='Dictionary_Remove(Names<>, gKey[i]);',
            count='Dictionary_Count(Names<>)',
            get='Dictionary_Get(Names<>, gKey[i], value);',
            miss='if (Dictionary_Contains(Names<>, gMiss[i])) {\n                ++value;\n            }') + FIRST + MAIN + START
        write('dictionary_ssi_text_%d' % size, text)

        text = head('PawnPlus', '#include <PawnPlus>') + TEXT_KEYS % (size, size) + '''
new
    Map:gNames
;

Setup() {
    MakeKeys();
    gNames = map_new();
}
'''
        text += DICTIONARY_RUN.substitute(values,
            set='map_str_set(gNames, gKey[i], i);',
            remove='map_str_remove(gNames, gKey[i]);',
            count='map_size(gNames)',
            get='value += map_str_get(gNames, gKey[i]);',
            miss='if (map_has_str_key(gNames, gMiss[i])) {\n                ++value;\n            }') + FIRST + MAIN + START
        write('dictionary_pawnplus_text_%d' % size, text)


BITS_RUN = Template('''
Setup() {
    for (new i; i < $size; i += $size / 64) {
        $let(Sparse, i);
    }

    for (new i; i != 1024; i += 2) {
        $let(Dense, i);
    }
}

Run() {
    new
        j
    ;

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            if ($test(Dense, j)) {
                ++gBenchSink;
            }

            j = (j + 1) & 1023;
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("bits", "test a bit");

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            $let(Work, j);
            $vet(Work, j);
            j = (j + 1) & 1023;
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("bits", "turn a bit on and off");

    Bench_Begin();

    do {
        gBenchSink += $count(Sparse);
    } while (Bench_Next(1));

    Bench_End("bits", "count, $size bits");

    Bench_Begin();

    do {
        foreach (new bit : Bits(Sparse)) {
            gBenchSink += bit;
        }
    } while (Bench_Next(1));

    Bench_End("bits", "walk 64 bits on of $size");

    Bench_Begin();

    do {
        foreach (new bit : Bits(Dense)) {
            gBenchSink += bit;
        }
    } while (Bench_Next(1));

    Bench_End("bits", "walk, per bit, 512 of 1024 on", 512);
}
''')


def bits():
    for size in (1024, 1048576):
        text = head('SSI', '#include <SSI\\bits>') + '''
new
    Bits:Sparse<%d>,
    Bits:Dense<1024>,
    Bits:Work<1024>
;
''' % size
        text += BITS_RUN.substitute(size=size, let='Bits_Let', vet='Bits_Vet', test='Bits_Test', count='Bits_Count') + FIRST + MAIN + START
        write('bits_ssi_%d' % size, text)

        text = head('YSI', '#define _FOREACH_NO_TEST\n#include <YSI_Data\\y_bit>\n#include <YSI_Data\\y_iterate>') + '''
new
    BitArray:Sparse<%d>,
    BitArray:Dense<1024>,
    BitArray:Work<1024>
;
''' % size
        text += BITS_RUN.substitute(size=size, let='Bit_Let', vet='Bit_Vet', test='Bit_Get', count='Bit_Count') + FIRST + MAIN + START
        write('bits_ysi_%d' % size, text)


VA_RUN = '''
new
    gOutput[256]
;

stock Wrap(output[], size, const text[], OPEN_MP_TAGS:...) {
    return format(output, size, text, ___(3));
}

Setup() {
}

Run() {
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            format(gOutput, sizeof (gOutput), "%i %i %i", i, 2, 3);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("va", "format, 3 values, called directly");

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            Wrap(gOutput, sizeof (gOutput), "%i %i %i", i, 2, 3);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("va", "format, 3 values, through a wrapper");

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            format(gOutput, sizeof (gOutput), "%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i", i, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("va", "format, 16 values, called directly");

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            Wrap(gOutput, sizeof (gOutput), "%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i", i, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("va", "format, 16 values, through a wrapper");

    Bench_Check("wrapped text", strlen(gOutput) > 30, 1);
}
'''


def va():
    write('va_ssi', head('SSI', '#include <SSI\\va>') + VA_RUN + FIRST + MAIN + START)
    write('va_ysi', head('YSI', '#define _FOREACH_NO_TEST\n#include <YSI_Coding\\y_va>') + VA_RUN + FIRST + MAIN + START)


INLINE_RUN = Template('''
Setup() {
}

CaptureNow() {
    new
        value = 3
    ;

    inline Bump() {
        gBenchSink += value;
        ++gHits;
    }

    CallNow(using inline Bump);
}

CaptureKept() {
    new
        value = 3
    ;

    inline Bump() {
        gBenchSink += value;
        ++gHits;
    }

    Keep(using inline Bump);
}

CaptureWide() {
    new
        a0 = 1, a1, a2, a3, a4, a5, a6, a7, a8, a9,
        b0, b1, b2, b3, b4, b5, b6, b7, b8, b9,
        c0, c1, c2, c3, c4, c5, c6, c7, c8, c9,
        d0, d1
    ;

    inline AddAll() {
        gBenchSink += a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9;
        gBenchSink += b0 + b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8 + b9;
        gBenchSink += c0 + c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8 + c9;
        gBenchSink += d0 + d1;
        ++gHits;
    }

    CallNow(using inline AddAll);
}

Run() {
    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            CaptureNow();
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("inline", "capture and call at once");
    Bench_Check("inline calls", gHits, gBenchOps);

    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            CaptureKept();
            $once
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("inline", "capture, keep, call later and free");
    Bench_Check("kept inline calls", gHits, gBenchOps);

    CaptureKept();
    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            $again
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("inline", "call a kept inline again");
    Bench_Check("repeated inline calls", gHits, gBenchOps);
    $free

    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            CaptureWide();
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("inline", "capture 32 locals and call at once");
    Bench_Check("wide inline calls", gHits, gBenchOps);
}
''')


def inline():
    text = head('SSI', '#include <SSI\\inline>') + '''
new
    gHits,
    Inline:gKept
;

stock CallNow(Inline:callback) {
    return @once.callback();
}

stock Keep(Inline:callback) {
    gKept = callback;
}
'''
    text += INLINE_RUN.substitute(once='@once.gKept();', again='@.gKept();', free='Inline_Free(gKept);') + FIRST + MAIN + START
    write('inline_ssi', text)

    text = head('YSI', '#define _FOREACH_NO_TEST\n#include <YSI_Coding\\y_inline>') + '''
new
    gHits,
    Func:gKept<>
;

stock CallNow(Func:callback<>) {
    return @.callback();
}

stock Keep(Func:callback<>) {
    Indirect_Claim(callback);
    gKept = callback;
}
'''
    text += INLINE_RUN.substitute(once='@.gKept();\n            Indirect_Release(gKept);', again='@.gKept();', free='Indirect_Release(gKept);') + FIRST + MAIN + START
    write('inline_ysi', text)


COMMANDS = 1000
CHAIN = 16


def owner(i):
    if i < 10:
        return 'helper'
    if i < 20:
        return 'moderator'
    if i < 30:
        return 'admin'
    return None


COMMAND_RUN = Template('''
new
    gHits,
    gAdminBot = INVALID_PLAYER_ID,
    gPlainBot = INVALID_PLAYER_ID,
    gChainBot = INVALID_PLAYER_ID
;

First() {
    gAdminBot = NPC_Create("AdminBot");
    gPlainBot = NPC_Create("PlainBot");
    gChainBot = NPC_Create("ChainBot");
    $join(gAdmin, gAdminBot$on);
    $join(gChain[$last], gChainBot$on);
}

Run() {
    new
        inherited[] = "/c5 hello",
        last[] = "/c999 hello",
        denied[] = "/c15 hello",
        unknown[] = "/nothing hello",
        member
    ;

    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            $run(gAdminBot, inherited$runargs);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("command", "allowed through 2 parent groups, $commands commands");
    Bench_Check("allowed commands ran", gHits, gBenchOps);

    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            $run(gPlainBot, last$runargs);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("command", "free, the last of $commands commands");
    Bench_Check("free commands ran", gHits, gBenchOps);

    gHits = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            $run(gPlainBot, denied$runargs);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("command", "denied, $commands commands");
    Bench_Check("denied commands ran", gHits, 0);

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            $run(gPlainBot, unknown$runargs);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("command", "unknown, $commands commands");

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            $join(gHelper, gPlainBot$on);
            $leave(gHelper, gPlainBot$off);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("group", "join and leave a group");

    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            $join(gChain[$last], gPlainBot$on);
            $leave(gChain[$last], gPlainBot$off);
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("group", "join and leave the end of a chain of $chain groups");

    member = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            if ($has(gHelper, gAdminBot)) {
                ++member;
            }
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("group", "member through 2 parent groups");
    Bench_Check("members", member, gBenchOps);

    member = 0;
    Bench_Begin();

    do {
        for (new i; i != BENCH_BATCH; ++i) {
            if ($has(gChain[0], gChainBot)) {
                ++member;
            }
        }
    } while (Bench_Next(BENCH_BATCH));

    Bench_End("group", "member through $parents parent groups");
    Bench_Check("chain members", member, gBenchOps);
}
''')


GROUPS = '''
new
    Group:gHelper,
    Group:gModerator,
    Group:gAdmin,
    Group:gChain[%d]
;
''' % 16


def owner(i):
    if i < 10:
        return 'Helper'
    if i < 20:
        return 'Moderator'
    if i < 30:
        return 'Admin'
    return None


def commands():
    count = 1000
    chain = 16
    values = dict(commands=count, chain=chain, last=chain - 1, parents=chain - 1)

    text = head('SSI', '#define MAX_COMMANDS (Command:1024)\n#define MAX_COMMAND_NAMES (2048)\n\n#include <SSI\\iterator>\n#include <SSI\\command>\n#include <SSI\\group>\n#include <SSI\\hooks>')
    text += GROUPS
    text += COMMAND_RUN.substitute(values, run='Command_Run', runargs='', join='Group_AddPlayer', on='', leave='Group_RemovePlayer', off='', has='Group_HasPlayer')
    text += ''.join('\nCMD:c%d(playerid, params[]) {\n    ++gHits;\n\n    return 1;\n}\n' % i for i in range(count))
    text += '''
Setup() {
    gHelper = Group_Create("Helper");
    gModerator = Group_Create("Moderator");
    gAdmin = Group_Create("Administrator");
    Group_SetParent(gModerator, gHelper);
    Group_SetParent(gAdmin, gModerator);

    for (new i; i != sizeof (gChain); ++i) {
        new
            name[16]
        ;

        format(name, sizeof (name), "Chain%%i", i);
        gChain[i] = Group_Create(name);

        if (i != 0) {
            Group_SetParent(gChain[i], gChain[i - 1]);
        }
    }

%s
}
''' % '\n'.join('    Group_AllowCommand(g%s, "c%d");' % (owner(i), i) for i in range(count) if owner(i))
    write('command_ssi', text + MAIN + START)

    text = head('YSI', '#define _FOREACH_NO_TEST\n#define MAX_COMMANDS (1024)\n\n#include <YSI_Visual\\y_commands>\n#include <YSI_Players\\y_groups>\n#include <YSI_Coding\\y_hooks>')
    text += GROUPS
    text += COMMAND_RUN.substitute(values, run='Command_ReProcess', runargs=', false, false', join='Group_SetPlayer', on=', true', leave='Group_SetPlayer', off=', false', has='Group_GetPlayer')
    text += ''.join('\nYCMD:c%d(playerid, params[], help) {\n    ++gHits;\n\n    return 1;\n}\n' % i for i in range(count))
    allow = []
    for i in range(count):
        if owner(i):
            allow.append('    Group_SetGlobalCommand(YCMD:c%d, UNDEF);' % i)
            allow.append('    Group_SetCommand(g%s, YCMD:c%d, ALLOW);' % (owner(i), i))
        else:
            allow.append('    Group_SetGlobalCommand(YCMD:c%d, ALLOW);' % i)
    text += '''
Setup() {
    gHelper = Group_Create("Helper");
    gModerator = Group_Create("Moderator");
    gAdmin = Group_Create("Administrator");
    Group_AddChild(gAdmin, gModerator);
    Group_AddChild(gModerator, gHelper);

    for (new i; i != sizeof (gChain); ++i) {
        new
            name[16]
        ;

        format(name, sizeof (name), "Chain%%i", i);
        gChain[i] = Group_Create(name);

        if (i != 0) {
            Group_AddChild(gChain[i], gChain[i - 1]);
        }
    }

%s
}
''' % '\n'.join(allow)
    write('command_ysi', text + MAIN + START)

hooks()
collection()
dictionary()
bits()
va()
inline()
commands()
print('ok')
