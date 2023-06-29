add_library(printer STATIC cpu_printer.c)
target_include_directories(printer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)
