add_library(cpu_analyser STATIC cpu_analyser.c)
target_link_libraries(cpu_analyser PUBLIC cpu_reader)
target_link_libraries(cpu_analyser PUBLIC logger)
target_include_directories(cpu_analyser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)

