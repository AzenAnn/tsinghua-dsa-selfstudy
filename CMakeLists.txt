cmake_minimum_required(VERSION 3.16)
project(tsinghua_dsa_selfstudy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # 给 VS Code 的代码提示用

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

option(DSA_SANITIZE "打开 AddressSanitizer 和 UBSan，抓越界、内存泄漏和未定义行为" ON)

# 自己实现的数据结构都是头文件，放在 include/dsa/ 下
add_library(dsa INTERFACE)
target_include_directories(dsa INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_compile_options(dsa INTERFACE -Wall -Wextra -Wno-unused-parameter)
if(DSA_SANITIZE)
  target_compile_options(dsa INTERFACE -fsanitize=address,undefined -fno-omit-frame-pointer)
  target_link_options(dsa INTERFACE -fsanitize=address,undefined)
endif()

enable_testing()

# tests/test_<章>_<名字>.cpp：每个文件编成一个测试程序，新加的文件会自动收进来
file(GLOB DSA_TESTS CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/tests/test_*.cpp)
foreach(src ${DSA_TESTS})
  get_filename_component(name ${src} NAME_WE)
  add_executable(${name} ${src})
  target_include_directories(${name} PRIVATE ${PROJECT_SOURCE_DIR}/tests)
  target_link_libraries(${name} PRIVATE dsa)
  add_test(NAME ${name} COMMAND ${name})
endforeach()

# bench/<名字>.cpp：每个文件编成一个计时程序 bench_<名字>，用 tools/bench.sh 运行
file(GLOB DSA_BENCHES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/bench/*.cpp)
foreach(src ${DSA_BENCHES})
  get_filename_component(name ${src} NAME_WE)
  add_executable(bench_${name} ${src})
  target_link_libraries(bench_${name} PRIVATE dsa)
  target_compile_definitions(bench_${name} PRIVATE DSA_BENCH_DIR="${PROJECT_SOURCE_DIR}/bench/results")
endforeach()

# projects/ 下每个带 CMakeLists.txt 的综合项目
file(GLOB DSA_PROJECTS LIST_DIRECTORIES true ${PROJECT_SOURCE_DIR}/projects/*)
foreach(dir ${DSA_PROJECTS})
  if(EXISTS ${dir}/CMakeLists.txt)
    add_subdirectory(${dir})
  endif()
endforeach()
