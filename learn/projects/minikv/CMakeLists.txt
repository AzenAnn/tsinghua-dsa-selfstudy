add_executable(minikv main.cpp)
target_link_libraries(minikv PRIVATE dsa)

# 测试程序放到构建目录的顶层，tools/test.sh 会和其他测试一起运行
add_executable(test_proj_minikv test_minikv.cpp)
target_include_directories(test_proj_minikv PRIVATE ${PROJECT_SOURCE_DIR}/tests)
target_link_libraries(test_proj_minikv PRIVATE dsa)
set_target_properties(test_proj_minikv PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME test_proj_minikv COMMAND test_proj_minikv)
