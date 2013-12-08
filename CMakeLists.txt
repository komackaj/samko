cmake_minimum_required (VERSION 2.8)
project (SAMKO)

set (libSAMKO_VERSION_MAJOR 0)
set (libSAMKO_VERSION_MINOR 0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

link_directories (${SAMKO_BINARY_DIR}/libsamko)
add_subdirectory (libsamko)
