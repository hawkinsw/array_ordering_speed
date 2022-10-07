cmake_minimum_required(VERSION 3.10)

project(LoopSpeed VERSION 1.0 DESCRIPTION "LoopSpeed")

add_compile_options(-Wall -Wextra -pedantic -O3)
include_directories("include/")
add_executable(loop_speed loop_speed.cpp)

add_executable(row_major_measure loop_measure.cpp)
target_compile_options(row_major_measure PUBLIC -DROW_MAJOR)
add_executable(col_major_measure loop_measure.cpp)
target_compile_options(col_major_measure PUBLIC -DCOL_MAJOR)

foreach(ELEMENT_SIZE RANGE 8 128 8)
add_executable(loop_speed_${ELEMENT_SIZE} loop_speed_x.cpp)
target_compile_options(loop_speed_${ELEMENT_SIZE} PUBLIC -DX=${ELEMENT_SIZE})
endforeach()
