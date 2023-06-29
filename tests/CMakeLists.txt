add_executable(t_logger test_logger.c)
target_link_libraries(t_logger PUBLIC logger)
add_test(test_logger t_logger)
