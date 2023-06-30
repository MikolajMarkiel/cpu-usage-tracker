add_executable(t_cpu_reader test_cpu_reader.c)
target_link_libraries(t_cpu_reader PUBLIC cpu_reader)
target_include_directories(t_cpu_reader PUBLIC ${CMAKE_SOURCE_DIR}/lib/cpu_reader)
add_test(test_cpu_reader t_cpu_reader)
#
# add_executable(t_cpu_analyser test_cpu_analyser.c)
# target_link_libraries(t_cpu_analyser PUBLIC cpu_analyser)
# add_test(test_cpu_analyser t_cpu_analyser)
#
# add_executable(t_cpu_printer test_cpu_printer.c)
# target_link_libraries(t_cpu_printer PUBLIC cpu_printer)
# add_test(test_cpu_printer t_cpu_printer)

add_executable(t_logger test_logger.c)
target_link_libraries(t_logger PUBLIC logger)
target_include_directories(t_logger PUBLIC ${CMAKE_SOURCE_DIR}/lib/logger)
add_test(test_logger t_logger)

