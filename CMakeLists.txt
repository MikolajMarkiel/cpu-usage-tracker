cmake_minimum_required(VERSION 3.25.1)

project(
  cpu_usage_tracker
  VERSION 0.1.0
  LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if("${CMAKE_C_COMPILER_ID}" MATCHES "GNU")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Weverything")
endif()

message(STATUS "Current compiler:" ${CMAKE_C_COMPILER_ID}) 
message(STATUS "Current flags:" ${CMAKE_C_FLAGS})

include(CTest)
enable_testing()

add_subdirectory(lib) 
add_subdirectory(tests)

add_executable(${CMAKE_PROJECT_NAME} main.c)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC cpu_printer) 
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC logger)
