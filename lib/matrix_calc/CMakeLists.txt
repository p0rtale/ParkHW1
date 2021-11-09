add_library(matrix_calc_consistent STATIC src/matrix_calc_consistent.c)
target_include_directories(matrix_calc_consistent PUBLIC include)
target_link_libraries(matrix_calc_consistent PUBLIC errors)

add_library(matrix_calc_parallel SHARED src/matrix_calc_parallel.c)
target_include_directories(matrix_calc_parallel PUBLIC include)
find_package(Threads REQUIRED)
target_link_libraries(matrix_calc_parallel PUBLIC errors
                                           PRIVATE Threads::Threads)

if(WITH_TESTS)
    add_subdirectory(tests)
endif()