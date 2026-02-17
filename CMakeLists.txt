################################################################
cmake_minimum_required(VERSION 3.21)
project(app)
set(CMAKE_C_STANDARD_REQUIRED 17)

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(CMAKE_C_FLAGS         "-Wall -Wextra -fsanitize=address -fno-omit-frame-pointer")
SET(CMAKE_C_FLAGS_DEBUG   "-g -Werror")
SET(CMAKE_C_FLAGS_RELEASE "-O3")

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

file(GLOB SRCS ${PROJECT_SOURCE_DIR}/src/*/*.c)
add_library(common
SHARED
    ${SRCS}
)
target_include_directories(common
PUBLIC
    ${PROJECT_SOURCE_DIR}/include/
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/Main.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/)
target_link_libraries(${PROJECT_NAME}
PRIVATE
    common
)

add_executable(tests ${PROJECT_SOURCE_DIR}/tests/Main.c)
target_include_directories(tests
PUBLIC
    ${CMAKE_SOURCE_DIR}/include/
    ${CMAKE_SOURCE_DIR}/tests/
)
target_link_libraries(tests
PRIVATE
    common
)
# target_compile_features(${PROJECT_NAME} PRIVATE c_std_17)
# target_compile_options(${PROJECT_NAME} PRIVATE -g -Wall -Wextra -O0)