## Measuring The Difference Between Row and Column Major Ordering

### Building

Use cmake to build our tooling:

```
$ cmake -B build/
$ cmake --build build --target all
```

To clean, use

```
$ cmake --build build --target clean
```

### Using

In order to get a combination (suitable for easy graphing), run

```
$ ./build/loop_speed
```

In order to measure both individually, run

```
$ ./build/row_major_measure
```

or 

```
$ ./build/col_major_measure
```

In order to see the impact of the size of the elements relative to the size of a cache line (we probe up to 64k), run

```
$ ./loop_speed_x.sh
```

which will generate CSV files named `loop_speed_X.csv` (where `X` is `8`, `16`, `24`, `32`). The `X` indicates the size of the element (in bytes) in the 2d array. Notice how the difference in the order of array traversal matters less and less as you can put fewer and fewer elements in a cache line.

To clean all the data files from `loop_speed_x.sh`, run

```
$ ./loop_speed_x.sh clean
```

### Measuring (using perf -- Linux)

First, obviously, make sure that you have `perf` installed. With that, 


```
$ perf record -o perf-col.data -e cycles -e instructions -e L1-dcache-loads -e L1-dcache-load-misses --call-graph=dwarf build/col_major_measure
```

```
$ perf record -o perf-row.data -e cycles -e instructions -e L1-dcache-loads -e L1-dcache-load-misses --call-graph=dwarf build/row_major_measure
```

You can look deeply at the data using `perf report` but it's even *better* just to summarize with

```
$ perf report --stats -i perf-row.data
```

and

```
$ perf report --stats -i perf-col.data
```

### Creating Extra Data (automatically)

Use `gather.sh`:

```
$ ./gather.sh
```

To clean the extra data, run

```
$ ./gather.sh clean
```

