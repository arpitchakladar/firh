cmake_minimum_required(VERSION 3.25.2)

if (NOT "${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	set (CMAKE_BUILD_TYPE "Debug")
endif ()

project(Firh LANGUAGES CXX)

file(GLOB_RECURSE CXX_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

option(YAML_CPP_BUILD_TOOLS OFF)
add_subdirectory(vendor/yaml-cpp)

option(BUILD_SHARED_LIBS OFF)
option(BUILD_CLAR OFF)
option(BUILD_CLI OFF)
option(BUILD_TESTS OFF)
add_subdirectory(vendor/libgit2)

add_executable(firh ${CXX_SOURCES})

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	target_compile_definitions(firh PRIVATE DEBUG CURRENT_DIRECTORY="${PROJECT_SOURCE_DIR}")
endif ()

target_include_directories(firh PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(firh PRIVATE yaml-cpp)
target_include_directories(firh PRIVATE "${PROJECT_SOURCE_DIR}/vendor/libgit2/include")
target_link_libraries(firh PRIVATE libgit2package)
