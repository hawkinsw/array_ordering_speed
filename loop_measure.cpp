#include <cstdint>
#include <iostream>
#include <chrono>

const unsigned int ITERATIONS{3};
const unsigned int ROWS{5000};
const unsigned int COLUMNS{5000};

int array[ROWS][COLUMNS];

int measure() {
  volatile int sum{0};
  auto before = std::chrono::high_resolution_clock::now();
  for (int i = 0; i<ITERATIONS; i++) {
    sum = 0;
#ifdef COL_MAJOR
    for (int c = 0; c < COLUMNS; c++) {
      for (int r = 0; r < ROWS; r++) {
#else
    for (int r = 0; r < ROWS; r++) {
      for (int c = 0; c < COLUMNS; c++) {
#endif
        //std::cout << "column_then_row addr: " << (std::uintptr_t)(&(array[r][c])) << "\n";
        sum += array[r][c]++;
      }
    }
  }
  //std::cout << "row varies fastest: " << (stop - start) << "\n";
  auto after = std::chrono::high_resolution_clock::now();
  std::chrono::nanoseconds difference = after - before;
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(difference).count() << ",";
  return 0;
}

int main() {
  std::cout << "measurement\n";
  unsigned int collections = 30;
  for (unsigned int i = 0; i<collections; i++) {
    measure();
    std::cout << "\n";
  }
}
