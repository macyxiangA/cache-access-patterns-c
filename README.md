# Cache Pin Microbenchmarks

This repo contains four small C programs that write to global 1D / 2D arrays using different access patterns. The goal is to make cache behavior observable (hits, misses, miss rate) by running the compiled executables under a cache-tracing tool (Pin + a D-cache simulator).

Nothing is printed. Each program only performs deterministic memory writes and exits.

## Files

Source files (do not rename):

    cache1D.c
    cache2Drows.c
    cache2Dcols.c
    cache2Dclash.c

Optional outputs you may generate locally:

    cache1D
    cache2Drows
    cache2Dcols
    cache2Dclash
    *.out   (tool outputs)

## What Each Program Does

cache1D.c
    Writes sequentially across a 1D global array of 100,000 ints:
    arr[i] = i

cache2Drows.c
    Uses a 3000 x 500 global int array and traverses row-major:
    outer loop over rows, inner loop over cols

cache2Dcols.c
    Uses the same 3000 x 500 global int array but traverses column-major:
    outer loop over cols, inner loop over rows

cache2Dclash.c
    Uses a 128 x 8 global int array and accesses rows with a stride (row += 64),
    repeated for 100 iterations. This pattern can amplify conflict behavior
    depending on cache mapping / associativity.

## Build

Build all executables:

    make

Or compile each source manually:

    gcc cache1D.c -Wall -Wextra -std=gnu99 -o cache1D
    gcc cache2Drows.c -Wall -Wextra -std=gnu99 -o cache2Drows
    gcc cache2Dcols.c -Wall -Wextra -std=gnu99 -o cache2Dcols
    gcc cache2Dclash.c -Wall -Wextra -std=gnu99 -o cache2Dclash

## Run (no output expected)

    ./cache1D
    ./cache2Drows
    ./cache2Dcols
    ./cache2Dclash

## Measure Cache Hit/Miss with Pin (D-cache)

Pin runs your executable, records data memory addresses, and feeds them into a D-cache simulator tool that reports cache statistics.

Command template:

    <PIN_BIN> -injection child -t <DCACHE_TOOL> -c <capacity_kib> -a <associativity> -b <block_bytes> -o <output_file> -- <executable>

Parameter meaning:
- -c capacity_kib: total D-cache capacity in KiB (example: 2 means 2 KiB)
- -a associativity: set associativity (example: 1 for direct-mapped)
- -b block_bytes: cache block size in bytes (example: 32 or 64)
- -o output_file: where the simulator writes results
- -- executable: the program you are measuring

Example runs (fill in <PIN_BIN> and <DCACHE_TOOL> to match your environment):

    <PIN_BIN> -injection child -t <DCACHE_TOOL> -c 2 -a 1 -b 32 -o out_cache1D_c2_a1_b32.txt -- ./cache1D
    <PIN_BIN> -injection child -t <DCACHE_TOOL> -c 2 -a 1 -b 64 -o out_cache1D_c2_a1_b64.txt -- ./cache1D

    <PIN_BIN> -injection child -t <DCACHE_TOOL> -c 2 -a 1 -b 64 -o out_rows_c2_a1_b64.txt -- ./cache2Drows
    <PIN_BIN> -injection child -t <DCACHE_TOOL> -c 2 -a 1 -b 64 -o out_cols_c2_a1_b64.txt -- ./cache2Dcols

    <PIN_BIN> -injection child -t <DCACHE_TOOL> -c 2 -a 1 -b 64 -o out_clash_c2_a1_b64.txt -- ./cache2Dclash
    <PIN_BIN> -injection child -t <DCACHE_TOOL> -c 2 -a 2 -b 64 -o out_clash_c2_a2_b64.txt -- ./cache2Dclash

Important safety note:
- Do not use a source filename as the -o output file. Always write tool output to a separate .txt/.out file name.

## Interpreting Results (quick guidance)

Typical expectations when comparing access patterns:
- cache2Drows tends to have higher locality than cache2Dcols in C (row-major layout).
- cache2Dclash is designed to make certain cache organizations show noticeably different miss behavior when you change associativity.
