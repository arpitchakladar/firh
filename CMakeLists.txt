cmake_minimum_required(VERSION 3.25.2)

if (NOT "${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	set (CMAKE_BUILD_TYPE "Debug")
endif ()

project(Firh LANGUAGES CXX)

file(GLOB_RECURSE CXX_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_subdirectory(vendor/yaml-cpp)

add_executable(firh ${CXX_SOURCES})
target_include_directories(firh PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_include_directories(firh PRIVATE "${PROJECT_SOURCE_DIR}/vendor/libgit2/include")
target_link_libraries(firh PRIVATE libgit2.so)
target_link_libraries(firh PRIVATE yaml-cpp)
