cmake_minimum_required(VERSION 3.16)
project(shop)

# Set the C++ standard to C++14
set(CMAKE_CXX_STANDARD 20)

# Add the main.cpp file as an executable
add_executable(shop main.cpp)

# Set the directories for the source and header files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_custom_target(data_target DEPENDS "${DATA_DIR}/data.csv")


# Add the books.cpp and item.cpp files as sources for the executable
target_sources(shop PRIVATE "${SRC_DIR}/book.cpp" "${SRC_DIR}/item.cpp" "${SRC_DIR}/database.cpp")

# Add the books.h and item.h files as include directories for the executable
target_include_directories(shop PRIVATE ${INC_DIR})

# # Add all .csv files in the data directory as resources for the executable
# file(GLOB_RECURSE CSV_FILES "${CMAKE_CURRENT_SOURCE_DIR}/data/*.csv")
# add_custom_target(csv_files ALL SOURCES ${CSV_FILES})