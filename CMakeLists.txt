cmake_minimum_required(VERSION 3.13)
project(lotyr)

set(CMAKE_CXX_STANDARD 14)

# Make sure everything is compiled to produce position-independent code
add_compile_options(-fPIC)

# Compile Protobuf
set(protobuf_INSTALL OFF CACHE BOOL "Disable Protobuf installing" FORCE)
set(protobuf_BUILD_TESTS OFF CACHE BOOL "Disable Protobuf tests" FORCE)
add_subdirectory(third_party/protobuf)

# Make sure Valhalla uses the correct version of Protobuf
set(Protobuf_LIBRARIES "${CMAKE_SOURCE_DIR}/build/protobuf/${CMAKE_STATIC_LIBRARY_PREFIX}protobuf${CMAKE_STATIC_LIBRARY_SUFFIX}" CACHE STRING "Use the built static library for Protobuf" FORCE)
set(Protobuf_USE_STATIC_LIBS ON CACHE BOOL "Use static libraries for Protobuf" FORCE)
# Disable all the Valhalla options we don't need
set(ENABLE_TOOLS OFF CACHE BOOL "Disable Valhalla tools" FORCE)
set(ENABLE_DATA_TOOLS OFF CACHE BOOL "Disable Valhalla data tools" FORCE)
set(ENABLE_SERVICES OFF CACHE BOOL "Disable Valhalla services" FORCE)
set(ENABLE_HTTP OFF CACHE BOOL "Disable Valhalla HTTP server" FORCE)
set(ENABLE_PYTHON_BINDINGS OFF CACHE BOOL "Disable Valhalla python bindings" FORCE)
set(ENABLE_TESTS OFF CACHE BOOL "Disable Valhalla tests" FORCE)
set(ENABLE_BENCHMARKS OFF CACHE BOOL "Disable Valhalla benchmarks" FORCE)
add_subdirectory(third_party/valhalla)
add_dependencies(valhalla libprotobuf)

add_library(lotyr SHARED lotyr.cpp)
target_include_directories(lotyr PRIVATE "valhalla")
target_link_libraries(lotyr valhalla)
