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

# 自己实现的代码：模板类只有头文件（include/dsa/*.h），普通函数的实现在 src/*.cpp，一起编成库 dsa
file(GLOB DSA_SOURCES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(dsa STATIC ${DSA_SOURCES})
target_include_directories(dsa PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(dsa PUBLIC -Wall -Wextra -Wno-unused-parameter)
if(DSA_SANITIZE)
  target_compile_options(dsa PUBLIC -fsanitize=address,undefined -fno-omit-frame-pointer)
  target_link_options(dsa PUBLIC -fsanitize=address,undefined)
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

# projects/ 下每个带 CMakeLists.txt 的综合项目（它们的测试程序 test_proj_* 也由 tools/test.sh 运行）
file(GLOB DSA_PROJECTS LIST_DIRECTORIES true ${PROJECT_SOURCE_DIR}/projects/*)
foreach(dir ${DSA_PROJECTS})
  if(EXISTS ${dir}/CMakeLists.txt)
    add_subdirectory(${dir})
  endif()
endforeach()
