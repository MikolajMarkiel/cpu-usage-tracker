add_library(cpu_reader STATIC cpu_reader.c)
target_link_libraries(cpu_reader PUBLIC logger)
target_include_directories(cpu_reader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)
