add_executable(bst_test test.c)
        target_link_libraries(bst_test PRIVATE bst)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(bst_test PRIVATE -g)
endif()
get_target_property(OPTIONS_VAR bst_test COMPILE_OPTIONS)
message(STATUS "Building bst_test with flags: ${OPTIONS_VAR}")
add_test(NAME bst_test COMMAND bst_test)
