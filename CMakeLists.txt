cmake_minimum_required(VERSION 3.10)
project(JournalSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Для Windows
if(WIN32)
    add_definitions(-DWIN32)
endif()

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(journal_system ${SOURCES})

# Для Linux/Unix
if(UNIX AND NOT APPLE)
    target_link_libraries(journal_system pthread)
endif()
