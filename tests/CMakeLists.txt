add_executable(bst_test test.c)
        target_link_libraries(bst_test PRIVATE bst)
add_test(NAME bst_test COMMAND bst_test)
