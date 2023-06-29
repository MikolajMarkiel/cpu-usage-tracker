add_library(reader STATIC cpu_reader.c)
target_include_directories(reader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)
