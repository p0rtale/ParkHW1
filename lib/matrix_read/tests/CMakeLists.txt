add_executable(matrix_read_test src/matrix_read_test.cpp)
target_link_libraries(matrix_read_test matrix_read GTest::gtest)

add_test(NAME    matrix_read_test 
         COMMAND matrix_read_test)