# iterator.c contains include of bst.c for BST struct access
add_library(bst STATIC iterator.c)
target_include_directories(bst PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

get_target_property(OPTIONS_VAR bst COMPILE_OPTIONS)
message(STATUS "Building bst with flags: ${OPTIONS_VAR}")
