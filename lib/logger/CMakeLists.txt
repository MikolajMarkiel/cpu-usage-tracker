add_library(logger STATIC logger.c)
target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)
