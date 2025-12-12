set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(day1-puzzle1 day1/puzzle1.cpp)
add_executable(day1-puzzle2 day1/puzzle2.cpp)

add_executable(day2-puzzle1 day2/puzzle1.cpp)
add_executable(day2-puzzle2 day2/puzzle2.cpp)

add_executable(day3-puzzle1 day3/puzzle1.cpp util.cpp)
add_executable(day3-puzzle2 day3/puzzle2.cpp util.cpp)