add_library(analyser STATIC cpu_analyser.c)
target_link_libraries(analyser PUBLIC reader)
target_include_directories(analyser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)

