add_library(cpu_printer STATIC cpu_printer.c)
target_link_libraries(cpu_printer PUBLIC cpu_analyser)
target_include_directories(cpu_printer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)
