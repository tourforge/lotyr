cmake_minimum_required(VERSION 3.13)
project(lotyr)

set(CMAKE_CXX_STANDARD 14)

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(-fPIC)
endif()

add_subdirectory(third_party/zlib)
set(ZLIB_INCLUDE_DIR
    "${CMAKE_BINARY_DIR}/third_party/zlib"
    "${CMAKE_SOURCE_DIR}/third_party/zlib"
    CACHE STRING "Set vendored zlib include directories" FORCE)
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # The Visual Studio CMake generator can have multiple configs (and does by default) and
    # produces output in a different subpath depending on the chosen config. At the same time,
    # we must specify one single path to the built zlib static library, which, under MSVC, varies
    # depending on the build type. Workaround: assume users have set CMAKE_BUILD_TYPE to a single
    # desired build type and set CMAKE_CONFIGURATION_TYPES to only have this value.
    #
    # Also, the compiled library name is different for debug builds, so we have to handle that too.
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(ZLIB_LIBRARY
            "${CMAKE_BINARY_DIR}/third_party/zlib/${CMAKE_BUILD_TYPE}/zlibstaticd.lib"
            CACHE STRING "Use the built (${CMAKE_BUILD_TYPE}) static library for zlib" FORCE)
    else()
        set(ZLIB_LIBRARY
            "${CMAKE_BINARY_DIR}/third_party/zlib/${CMAKE_BUILD_TYPE}/zlibstatic.lib"
            CACHE STRING "Use the built (${CMAKE_BUILD_TYPE}) static library for zlib" FORCE)
    endif()
    set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE})
else()
    set(ZLIB_LIBRARY
        "${CMAKE_BINARY_DIR}/third_party/zlib/${CMAKE_STATIC_LIBRARY_PREFIX}z${CMAKE_STATIC_LIBRARY_SUFFIX}"
        CACHE STRING "Use the built static library for zlib" FORCE)
endif()
set(ZLIB_USE_STATIC_LIBS ON CACHE BOOL "Use static libraries for zlib" FORCE)

set(protobuf_INSTALL OFF CACHE BOOL "Disable Protobuf installing" FORCE)
set(protobuf_BUILD_TESTS OFF CACHE BOOL "Disable Protobuf tests" FORCE)
add_subdirectory(third_party/protobuf)
add_dependencies(libprotobuf zlibstatic)
set(Protobuf_INCLUDE_DIR
    "${CMAKE_SOURCE_DIR}/third_party/protobuf/src"
    CACHE STRING "Set the vendored Protobuf include directory" FORCE)
set(Protobuf_LIBRARY
    "${CMAKE_BINARY_DIR}/third_party/protobuf/${CMAKE_STATIC_LIBRARY_PREFIX}protobuf${CMAKE_STATIC_LIBRARY_SUFFIX}"
    CACHE STRING "Use the built static library for Protobuf" FORCE)
set(Protobuf_USE_STATIC_LIBS ON CACHE BOOL "Use static libraries for Protobuf" FORCE)

set(ENABLE_TOOLS OFF CACHE BOOL "Disable Valhalla tools" FORCE)
set(ENABLE_DATA_TOOLS OFF CACHE BOOL "Disable Valhalla data tools" FORCE)
set(ENABLE_SERVICES OFF CACHE BOOL "Disable Valhalla services" FORCE)
set(ENABLE_HTTP OFF CACHE BOOL "Disable Valhalla HTTP server" FORCE)
set(ENABLE_PYTHON_BINDINGS OFF CACHE BOOL "Disable Valhalla python bindings" FORCE)
set(ENABLE_TESTS OFF CACHE BOOL "Disable Valhalla tests" FORCE)
set(ENABLE_BENCHMARKS OFF CACHE BOOL "Disable Valhalla benchmarks" FORCE)
set(ENABLE_SINGLE_FILES_WERROR OFF CACHE BOOL "Disable Valhalla -Werror since it often breaks things" FORCE)
set(ENABLE_COMPILER_WARNINGS OFF CACHE BOOL "Disable warnings while compiling Valhalla" FORCE)
add_subdirectory(third_party/valhalla)
add_dependencies(valhalla zlibstatic libprotobuf)

add_library(lotyr SHARED lotyr.cpp)
target_include_directories(lotyr PRIVATE "valhalla")
target_link_libraries(lotyr valhalla)
