add_executable(matrix_calc_consistent_test src/matrix_calc_test.cpp)
target_link_libraries(matrix_calc_consistent_test matrix_calc_consistent utils GTest::gtest)

add_test(NAME              matrix_calc_consistent_test 
         COMMAND           matrix_calc_consistent_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data_consistent)


add_executable(matrix_calc_parallel_test src/matrix_calc_test.cpp)
target_link_libraries(matrix_calc_parallel_test matrix_calc_parallel utils GTest::gtest)

add_test(NAME              matrix_calc_parallel_test 
         COMMAND           matrix_calc_parallel_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data_parallel)


add_executable(compare_reports src/compare_reports.cpp)
target_link_libraries(compare_reports GTest::gtest)

add_test(NAME              compare_reports
         COMMAND           compare_reports
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


if(VALGRIND)                                            
    target_compile_definitions(matrix_calc_consistent_test PRIVATE TIME_ITERS=1 STRESS_ITERS=1)
    target_compile_definitions(matrix_calc_parallel_test PRIVATE TIME_ITERS=1 STRESS_ITERS=1)
endif()