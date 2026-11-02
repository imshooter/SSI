# Benchmarks

The scripts behind the [Performance](https://github.com/imshooter/SSI/wiki/Performance) page of the wiki. Each one measures one library on one side, SSI, YSI or PawnPlus, and is named after them: `collection_ysi_100000.pwn` measures y_iterate with 100000 ids.

## Running

Compile a script with the open.mp includes, SSI, YSI and PawnPlus in the include path, and the same options as the results:

```bash
pawncc collection_ssi_4096.pwn -i<includes> -d0 -;+ -(+
```

Run it as the game mode of a server that loads the PawnPlus plugin, and allows three bots for `command_ssi` and `command_ysi`. It prints one line for each operation and round, then closes the server:

```
[bench] SSI|collection|contains, 4096 ids|4.70
```

The fields are the side, the library, the operation and the time of one operation in nanoseconds. The Performance page gives the median of 15 rounds from three runs, with and without a JIT. A line with `CHECK` means the library did not do the work it was given, and its times do not count.

## Files

* `bench.inc` times the loops, takes away the cost of an empty loop and checks the work.
* `generate.py` writes every script. Run it after changing a benchmark, since the hooks and commands are written out a hundred or a thousand times.
