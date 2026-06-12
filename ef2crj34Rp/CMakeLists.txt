cmake_minimum_required(VERSION 3.31.6)
project(Calendar C)

set(CMAKE_C_STANDARD 99)

# 编译选项
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
elseif(MSVC)
    add_compile_options(/W4 /WX)
endif()

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 添加可执行文件
add_executable(Calendar
    src/main.c
    src/write_event.c
    src/err_handle.c
    src/event.c
)

# 设置包含目录
target_include_directories(Calendar PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 设置链接库
if(UNIX AND NOT APPLE)
    target_link_libraries(Calendar m)
endif()

# 安装目标
install(TARGETS Calendar DESTINATION bin)
install(FILES README.md LICENSE DESTINATION share/calendar)

# 版本信息
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

# 添加测试目标（如果启用测试）
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    # 这里可以添加测试配置
endif()

# 添加示例
if(BUILD_EXAMPLES)
    # 这里可以添加示例配置
endif()

message(STATUS "Calendar v${PROJECT_VERSION} configured successfully")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")