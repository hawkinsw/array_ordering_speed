#include <cstdint>
#include <iostream>
#include <chrono>
#include <memory.h>

const unsigned int ITERATIONS{3};
const unsigned int ROWS{5000};
const unsigned int COLUMNS{5000};

#ifndef X 
#pragma error You must define X.
#endif

struct element {
  char contained[X];
};

element array[ROWS][COLUMNS];

int row_major() {
  volatile char sum{0};

  auto before = std::chrono::high_resolution_clock::now();
  for (int i = 0; i<ITERATIONS; i++) {
    sum = 0;
    for (int r = 0; r < ROWS; r++) {
      for (int c = 0; c < COLUMNS; c++) {
        sum += array[r][c].contained[0]++;
      }
    }
  }
  auto after = std::chrono::high_resolution_clock::now();
  //std::cout << "column varies fastest: " << (stop - start) << "\n";
  std::chrono::nanoseconds difference = after - before;
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(difference).count() << ",";
  return 0;
}


int column_major() {
  volatile char sum{0};
  auto before = std::chrono::high_resolution_clock::now();
  for (int i = 0; i<ITERATIONS; i++) {
    sum = 0;
    for (int c = 0; c < COLUMNS; c++) {
      for (int r = 0; r < ROWS; r++) {
        //std::cout << "column_then_row addr: " << (std::uintptr_t)(&(array[r][c])) << "\n";
        sum += array[r][c].contained[0]++;
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
  std::cout << "row major, column major\n";
  unsigned int collections = 1;
  for (unsigned int i = 0; i<collections; i++) {
    row_major();
    column_major();
    std::cout << "\n";
  }
}
