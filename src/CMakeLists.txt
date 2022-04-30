add_library(sep main/simple_expression_parser.c main/token_linked_list.c)
target_include_directories(sep PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(sep_example main/sep_example.c)
target_link_libraries(sep_example sep)