/**
 * Unique names: every `#include <SSI\unique>` moves on to a new suffix
 * of two characters, and `SSI_UNIQUE<prefix...suffix>` writes the current one
 * where the `...` is. The same declaration in two files, each including this
 * first, becomes two names:
 *
 *     #include <SSI\unique>
 *
 *     forward SSI_UNIQUE<@Reload_...>();
 *     public SSI_UNIQUE<@Reload_...>() {
 *     }
 *
 * The suffixes run `00`, `01`, ... `0z`, `10`, ... `zz`, 4096 of them, and sort
 * in the order the includes were made, so names that differ only in it sort
 * from the first include to the last. `SSI_UNIQUE_COUNT` is how many includes
 * there have been, starting from 1.
 */

#if !defined SSI_UNIQUE_LOW
    #define SSI_UNIQUE_LOW (-1)
    #define SSI_UNIQUE_HIGH (0)
    #define SSI_UNIQUE_COUNT (SSI_UNIQUE_HIGH * 64 + SSI_UNIQUE_LOW + 1)
    #define SSI_UNIQUE<%0...%1> SSI@UNIQUE_H<%0...%1>
    #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%00...%1>
    #define SSI@UNIQUE_L<%0...%1> %00%1
#endif

#if SSI_UNIQUE_LOW == -1
    #undef SSI_UNIQUE_LOW
    #define SSI_UNIQUE_LOW (0)
#else
    #if SSI_UNIQUE_LOW <= 31
        #if SSI_UNIQUE_LOW <= 15
            #if SSI_UNIQUE_LOW <= 7
                #if SSI_UNIQUE_LOW <= 3
                    #if SSI_UNIQUE_LOW <= 1
                        #if SSI_UNIQUE_LOW <= 0
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (1)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %01%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (2)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %02%1
                        #endif
                    #else
                        #if SSI_UNIQUE_LOW <= 2
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (3)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %03%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (4)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %04%1
                        #endif
                    #endif
                #else
                    #if SSI_UNIQUE_LOW <= 5
                        #if SSI_UNIQUE_LOW <= 4
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (5)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %05%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (6)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %06%1
                        #endif
                    #else
                        #if SSI_UNIQUE_LOW <= 6
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (7)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %07%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (8)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %08%1
                        #endif
                    #endif
                #endif
            #else
                #if SSI_UNIQUE_LOW <= 11
                    #if SSI_UNIQUE_LOW <= 9
                        #if SSI_UNIQUE_LOW <= 8
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (9)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %09%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (10)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0@%1
                        #endif
                    #else
                        #if SSI_UNIQUE_LOW <= 10
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (11)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0A%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (12)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0B%1
                        #endif
                    #endif
                #else
                    #if SSI_UNIQUE_LOW <= 13
                        #if SSI_UNIQUE_LOW <= 12
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (13)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0C%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (14)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0D%1
                        #endif
                    #else
                        #if SSI_UNIQUE_LOW <= 14
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (15)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0E%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (16)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0F%1
                        #endif
                    #endif
                #endif
            #endif
        #else
            #if SSI_UNIQUE_LOW <= 23
                #if SSI_UNIQUE_LOW <= 19
                    #if SSI_UNIQUE_LOW <= 17
                        #if SSI_UNIQUE_LOW <= 16
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (17)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0G%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (18)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0H%1
                        #endif
                    #else
                        #if SSI_UNIQUE_LOW <= 18
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (19)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0I%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (20)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0J%1
                        #endif
                    #endif
                #else
                    #if SSI_UNIQUE_LOW <= 21
                        #if SSI_UNIQUE_LOW <= 20
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (21)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0K%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (22)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0L%1
                        #endif
                    #else
                        #if SSI_UNIQUE_LOW <= 22
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (23)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0M%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (24)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0N%1
                        #endif
                    #endif
                #endif
            #else
                #if SSI_UNIQUE_LOW <= 27
                    #if SSI_UNIQUE_LOW <= 25
                        #if SSI_UNIQUE_LOW <= 24
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (25)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0O%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (26)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0P%1
                        #endif
                    #else
                        #if SSI_UNIQUE_LOW <= 26
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (27)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0Q%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (28)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0R%1
                        #endif
                    #endif
                #else
                    #if SSI_UNIQUE_LOW <= 29
                        #if SSI_UNIQUE_LOW <= 28
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (29)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0S%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (30)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0T%1
                        #endif
                    #else
                        #if SSI_UNIQUE_LOW <= 30
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (31)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0U%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (32)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0V%1
                        #endif
                    #endif
                #endif
            #endif
        #endif
    #else
        #if SSI_UNIQUE_LOW <= 47
            #if SSI_UNIQUE_LOW <= 39
                #if SSI_UNIQUE_LOW <= 35
                    #if SSI_UNIQUE_LOW <= 33
                        #if SSI_UNIQUE_LOW <= 32
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (33)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0W%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (34)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0X%1
                        #endif
                    #else
                        #if SSI_UNIQUE_LOW <= 34
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (35)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0Y%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (36)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0Z%1
                        #endif
                    #endif
                #else
                    #if SSI_UNIQUE_LOW <= 37
                        #if SSI_UNIQUE_LOW <= 36
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (37)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0_%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (38)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0a%1
                        #endif
                    #else
                        #if SSI_UNIQUE_LOW <= 38
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (39)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0b%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (40)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0c%1
                        #endif
                    #endif
                #endif
            #else
                #if SSI_UNIQUE_LOW <= 43
                    #if SSI_UNIQUE_LOW <= 41
                        #if SSI_UNIQUE_LOW <= 40
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (41)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0d%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (42)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0e%1
                        #endif
                    #else
                        #if SSI_UNIQUE_LOW <= 42
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (43)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0f%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (44)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0g%1
                        #endif
                    #endif
                #else
                    #if SSI_UNIQUE_LOW <= 45
                        #if SSI_UNIQUE_LOW <= 44
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (45)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0h%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (46)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0i%1
                        #endif
                    #else
                        #if SSI_UNIQUE_LOW <= 46
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (47)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0j%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (48)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0k%1
                        #endif
                    #endif
                #endif
            #endif
        #else
            #if SSI_UNIQUE_LOW <= 55
                #if SSI_UNIQUE_LOW <= 51
                    #if SSI_UNIQUE_LOW <= 49
                        #if SSI_UNIQUE_LOW <= 48
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (49)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0l%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (50)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0m%1
                        #endif
                    #else
                        #if SSI_UNIQUE_LOW <= 50
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (51)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0n%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (52)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0o%1
                        #endif
                    #endif
                #else
                    #if SSI_UNIQUE_LOW <= 53
                        #if SSI_UNIQUE_LOW <= 52
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (53)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0p%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (54)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0q%1
                        #endif
                    #else
                        #if SSI_UNIQUE_LOW <= 54
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (55)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0r%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (56)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0s%1
                        #endif
                    #endif
                #endif
            #else
                #if SSI_UNIQUE_LOW <= 59
                    #if SSI_UNIQUE_LOW <= 57
                        #if SSI_UNIQUE_LOW <= 56
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (57)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0t%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (58)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0u%1
                        #endif
                    #else
                        #if SSI_UNIQUE_LOW <= 58
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (59)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0v%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (60)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0w%1
                        #endif
                    #endif
                #else
                    #if SSI_UNIQUE_LOW <= 61
                        #if SSI_UNIQUE_LOW <= 60
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (61)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0x%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (62)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0y%1
                        #endif
                    #else
                        #if SSI_UNIQUE_LOW <= 62
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (63)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %0z%1
                        #else
                            #undef SSI_UNIQUE_LOW
                            #define SSI_UNIQUE_LOW (0)
                            #undef SSI@UNIQUE_L
                            #define SSI@UNIQUE_L<%0...%1> %00%1
                            #define SSI@UNIQUE_CARRY
                        #endif
                    #endif
                #endif
            #endif
        #endif
    #endif
#endif

#if defined SSI@UNIQUE_CARRY
    #undef SSI@UNIQUE_CARRY

    #if SSI_UNIQUE_HIGH <= 31
        #if SSI_UNIQUE_HIGH <= 15
            #if SSI_UNIQUE_HIGH <= 7
                #if SSI_UNIQUE_HIGH <= 3
                    #if SSI_UNIQUE_HIGH <= 1
                        #if SSI_UNIQUE_HIGH <= 0
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (1)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%01...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (2)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%02...%1>
                        #endif
                    #else
                        #if SSI_UNIQUE_HIGH <= 2
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (3)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%03...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (4)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%04...%1>
                        #endif
                    #endif
                #else
                    #if SSI_UNIQUE_HIGH <= 5
                        #if SSI_UNIQUE_HIGH <= 4
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (5)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%05...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (6)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%06...%1>
                        #endif
                    #else
                        #if SSI_UNIQUE_HIGH <= 6
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (7)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%07...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (8)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%08...%1>
                        #endif
                    #endif
                #endif
            #else
                #if SSI_UNIQUE_HIGH <= 11
                    #if SSI_UNIQUE_HIGH <= 9
                        #if SSI_UNIQUE_HIGH <= 8
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (9)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%09...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (10)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0@...%1>
                        #endif
                    #else
                        #if SSI_UNIQUE_HIGH <= 10
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (11)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0A...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (12)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0B...%1>
                        #endif
                    #endif
                #else
                    #if SSI_UNIQUE_HIGH <= 13
                        #if SSI_UNIQUE_HIGH <= 12
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (13)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0C...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (14)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0D...%1>
                        #endif
                    #else
                        #if SSI_UNIQUE_HIGH <= 14
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (15)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0E...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (16)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0F...%1>
                        #endif
                    #endif
                #endif
            #endif
        #else
            #if SSI_UNIQUE_HIGH <= 23
                #if SSI_UNIQUE_HIGH <= 19
                    #if SSI_UNIQUE_HIGH <= 17
                        #if SSI_UNIQUE_HIGH <= 16
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (17)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0G...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (18)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0H...%1>
                        #endif
                    #else
                        #if SSI_UNIQUE_HIGH <= 18
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (19)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0I...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (20)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0J...%1>
                        #endif
                    #endif
                #else
                    #if SSI_UNIQUE_HIGH <= 21
                        #if SSI_UNIQUE_HIGH <= 20
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (21)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0K...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (22)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0L...%1>
                        #endif
                    #else
                        #if SSI_UNIQUE_HIGH <= 22
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (23)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0M...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (24)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0N...%1>
                        #endif
                    #endif
                #endif
            #else
                #if SSI_UNIQUE_HIGH <= 27
                    #if SSI_UNIQUE_HIGH <= 25
                        #if SSI_UNIQUE_HIGH <= 24
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (25)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0O...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (26)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0P...%1>
                        #endif
                    #else
                        #if SSI_UNIQUE_HIGH <= 26
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (27)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0Q...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (28)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0R...%1>
                        #endif
                    #endif
                #else
                    #if SSI_UNIQUE_HIGH <= 29
                        #if SSI_UNIQUE_HIGH <= 28
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (29)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0S...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (30)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0T...%1>
                        #endif
                    #else
                        #if SSI_UNIQUE_HIGH <= 30
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (31)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0U...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (32)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0V...%1>
                        #endif
                    #endif
                #endif
            #endif
        #endif
    #else
        #if SSI_UNIQUE_HIGH <= 47
            #if SSI_UNIQUE_HIGH <= 39
                #if SSI_UNIQUE_HIGH <= 35
                    #if SSI_UNIQUE_HIGH <= 33
                        #if SSI_UNIQUE_HIGH <= 32
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (33)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0W...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (34)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0X...%1>
                        #endif
                    #else
                        #if SSI_UNIQUE_HIGH <= 34
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (35)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0Y...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (36)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0Z...%1>
                        #endif
                    #endif
                #else
                    #if SSI_UNIQUE_HIGH <= 37
                        #if SSI_UNIQUE_HIGH <= 36
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (37)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0_...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (38)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0a...%1>
                        #endif
                    #else
                        #if SSI_UNIQUE_HIGH <= 38
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (39)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0b...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (40)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0c...%1>
                        #endif
                    #endif
                #endif
            #else
                #if SSI_UNIQUE_HIGH <= 43
                    #if SSI_UNIQUE_HIGH <= 41
                        #if SSI_UNIQUE_HIGH <= 40
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (41)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0d...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (42)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0e...%1>
                        #endif
                    #else
                        #if SSI_UNIQUE_HIGH <= 42
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (43)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0f...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (44)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0g...%1>
                        #endif
                    #endif
                #else
                    #if SSI_UNIQUE_HIGH <= 45
                        #if SSI_UNIQUE_HIGH <= 44
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (45)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0h...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (46)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0i...%1>
                        #endif
                    #else
                        #if SSI_UNIQUE_HIGH <= 46
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (47)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0j...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (48)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0k...%1>
                        #endif
                    #endif
                #endif
            #endif
        #else
            #if SSI_UNIQUE_HIGH <= 55
                #if SSI_UNIQUE_HIGH <= 51
                    #if SSI_UNIQUE_HIGH <= 49
                        #if SSI_UNIQUE_HIGH <= 48
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (49)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0l...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (50)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0m...%1>
                        #endif
                    #else
                        #if SSI_UNIQUE_HIGH <= 50
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (51)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0n...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (52)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0o...%1>
                        #endif
                    #endif
                #else
                    #if SSI_UNIQUE_HIGH <= 53
                        #if SSI_UNIQUE_HIGH <= 52
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (53)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0p...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (54)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0q...%1>
                        #endif
                    #else
                        #if SSI_UNIQUE_HIGH <= 54
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (55)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0r...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (56)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0s...%1>
                        #endif
                    #endif
                #endif
            #else
                #if SSI_UNIQUE_HIGH <= 59
                    #if SSI_UNIQUE_HIGH <= 57
                        #if SSI_UNIQUE_HIGH <= 56
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (57)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0t...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (58)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0u...%1>
                        #endif
                    #else
                        #if SSI_UNIQUE_HIGH <= 58
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (59)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0v...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (60)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0w...%1>
                        #endif
                    #endif
                #else
                    #if SSI_UNIQUE_HIGH <= 61
                        #if SSI_UNIQUE_HIGH <= 60
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (61)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0x...%1>
                        #else
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (62)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0y...%1>
                        #endif
                    #else
                        #if SSI_UNIQUE_HIGH <= 62
                            #undef SSI_UNIQUE_HIGH
                            #define SSI_UNIQUE_HIGH (63)
                            #undef SSI@UNIQUE_H
                            #define SSI@UNIQUE_H<%0...%1> SSI@UNIQUE_L<%0z...%1>
                        #else
                            #error SSI\unique ran out of names after 4096 includes
                        #endif
                    #endif
                #endif
            #endif
        #endif
    #endif
#endif
