cmake_minimum_required(VERSION 3.8)

project(XboxUnattend)

include(CMake/Config.cmake)
include(CMake/Compiler.cmake)
include(CMake/Scripts/Deploy.cmake)

set(XBOXUNATTEND_SRC
    "Src/Main.cpp"
    "Src/UnattendedUtilities.h"
)
 
add_executable(xboxunattend ${XBOXUNATTEND_SRC})
target_link_libraries(xboxunattend ${DEFAULT_STANDARD_LIBRARIES})