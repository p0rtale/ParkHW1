add_library(matrix_read STATIC src/matrix_read.c)
target_include_directories(matrix_read PUBLIC include)
target_link_libraries(matrix_read PUBLIC errors)

if(WITH_TESTS)
    add_subdirectory(tests)
endif()