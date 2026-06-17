cmake_minimum_required(VERSION 3.10)
project(GarageManager VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the output directory to build/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# Include directory for headers
include_directories(include)

# Define source files
set(SOURCES
    src/main.cpp
    src/Files.cpp
    src/Vehicle.cpp
    src/Mechanic.cpp
    src/Tree.cpp
    src/WorkStation.cpp
    src/Garage.cpp
    src/Manager.cpp
)

# Add main executable
add_executable(GarageManager ${SOURCES})

# Define sources for Test Runner (exclude main.cpp and Manager.cpp since we mock the interactions)
set(TEST_SOURCES
    tests/test_main.cpp
    tests/test_memory.cpp
    tests/test_stress.cpp
    src/Files.cpp
    src/Vehicle.cpp
    src/Mechanic.cpp
    src/Tree.cpp
    src/WorkStation.cpp
    src/Garage.cpp
)

# Add executable for Tests
add_executable(GarageManager_TestRunner ${TEST_SOURCES})
