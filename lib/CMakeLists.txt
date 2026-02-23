add_library(bst STATIC bst.c)
add_library(bst_iterator STATIC iterator.c)
target_include_directories(bst PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(bst_iterator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

get_target_property(OPTIONS_VAR bst COMPILE_OPTIONS)
message(STATUS "Building bst with flags: ${OPTIONS_VAR}")
