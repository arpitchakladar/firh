cmake_minimum_required(VERSION 3.25.2)

find_library(LIBGIT2 libgit2.so)

add_library(libgit2 SHARED IMPORTED GLOBAL)
set_target_properties(libgit2 PROPERTIES IMPORTED_LOCATION ${LIBGIT2})

target_include_directories(libgit2 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(libgit2 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/libgit2)
