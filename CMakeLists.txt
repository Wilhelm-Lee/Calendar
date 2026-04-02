cmake_minimum_required(VERSION 3.31.6)
project(Calendar C)

set(CMAKE_C_STANDARD 99)

#if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#    add_compile_options(-Wall -Wextra)
#elseif(MSVC)
#    add_compile_options(/W4;/WX)
#endif()

# 1. Process the Compound directory and build its targets
#add_subdirectory(Compound)

# 2. Define the main executable and its source files
add_executable(Calendar
        src/main.c
        src/write_event.c
        src/err_handle.c
        src/event.c
)

# 3. Tell Calendar where Compound's header files are located
#target_include_directories(Calendar PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Compound)

# 4. Link the Compound library to the Calendar executable
#target_link_libraries(Calendar PRIVATE compound)

# 5. Copy the compiled DLL to the executable's directory so it runs properly on Windows
#add_custom_command(TARGET Calendar POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy_if_different
#    $<TARGET_FILE:compound>
#    $<TARGET_FILE_DIR:Calendar>
#)
