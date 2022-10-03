## Measuring The Difference Between Row and Column Major Ordering

### Building

Using cmake to build our tooling:

```
$ cmake -B build/
$ cmake --build build --target all
```

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