add_library(huffzip_lib STATIC huffzip.cpp)
target_link_libraries(huffzip_lib PUBLIC dsa)

add_executable(huffzip main.cpp)
target_link_libraries(huffzip PRIVATE huffzip_lib)

# 测试程序放到构建目录的顶层，tools/test.sh 会和其他测试一起运行
add_executable(test_proj_huffzip test_huffzip.cpp)
target_include_directories(test_proj_huffzip PRIVATE ${PROJECT_SOURCE_DIR}/tests)
target_link_libraries(test_proj_huffzip PRIVATE huffzip_lib)
set_target_properties(test_proj_huffzip PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME test_proj_huffzip COMMAND test_proj_huffzip)
