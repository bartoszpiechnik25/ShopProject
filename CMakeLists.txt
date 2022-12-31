cmake_minimum_required(VERSION 3.16)
project(shop)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Add the main.cpp file as an executable
add_executable(shop main.cpp)

# Set the directories for the source and header files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


# add_custom_target(data_target DEPENDS "${DATA_DIR}/data.csv")


# Add the books.cpp and item.cpp files as sources for the executable
target_sources(shop PRIVATE "${SRC_DIR}/book.cpp" "${SRC_DIR}/item.cpp" "${SRC_DIR}/database.cpp" "${SRC_DIR}/phone.cpp")

# Add the books.h and item.h files as include directories for the executable
target_include_directories(shop PRIVATE ${INC_DIR})
