project(maoUtil)

cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 23)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-D_DEBUG)
endif ()

set(CMAKE_DEBUG_POSTFIX "_d")

set(OUT_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(SOURCE_DIR ${CMAKE_SOURCE_DIR})

# 设置输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUT_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUT_DIR}/lib)
set(CMAKE_INSTALL_BINDIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_INSTALL_LIBDIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

message("++++ Set Runtime Out Dir: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message("++++ Set Library Out Dir: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message("++++ Set Archive Out Dir: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
message("++++ Set Bin Install Out Dir: ${CMAKE_INSTALL_BINDIR}")
message("++++ Set Lib Install Out Dir: ${CMAKE_INSTALL_LIBDIR}")

add_subdirectory(test)