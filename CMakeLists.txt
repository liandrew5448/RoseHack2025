# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(RoseHack VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable and include source files
add_executable(RoseHack
    main.cpp
    Interface.cpp
    Output.cpp
    User.cpp
    workout.cpp
)

# Include header files (optional if headers are in the same directory)
target_include_directories(RoseHack PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Add any necessary libraries (if applicable)
# target_link_libraries(RoseHack <library_name>)
