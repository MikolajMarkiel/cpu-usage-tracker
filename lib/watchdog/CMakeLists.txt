add_library(watchdog STATIC watchdog.c)
target_link_libraries(watchdog PUBLIC logger)
target_include_directories(watchdog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)
