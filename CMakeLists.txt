cmake_minimum_required(VERSION 3.25.1)

project(cpu_usage_tracker VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_subdirectory(lib)
add_subdirectory(tests)

add_executable(main main.c)
target_link_libraries(main PUBLIC printer)
target_link_libraries(main PUBLIC logger)
