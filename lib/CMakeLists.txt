# iterator.c contains include of bst.c for BST struct access
add_library(bst STATIC iterator.c)
target_include_directories(bst PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(bst PRIVATE -g)
endif()
get_target_property(OPTIONS_VAR bst COMPILE_OPTIONS)
message(STATUS "Building bst with flags: ${OPTIONS_VAR}")
