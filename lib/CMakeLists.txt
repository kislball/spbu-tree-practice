add_library(bst STATIC bst.c)
add_library(stackNode STATIC stackNode.c)
add_library(bstIterator STATIC iterator.c)
target_include_directories(bst PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(stackNode PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(bstIterator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(bstIterator PRIVATE stackNode)

get_target_property(OPTIONS_VAR bst COMPILE_OPTIONS)
message(STATUS "Building bst with flags: ${OPTIONS_VAR}")
