With cmake, you can rely on SDL2 with source code. The implementation steps are as follows:
1. Create a deps directory and put the SDL source package under it.
2. In the SDL source package sibling directory, create sdl2.cmake.
    ```
    if (POLICY CMP0135)
        cmake_policy(SET CMP0135 NEW)
        set(DOWNLOAD_EXTRACT_TIMESTAMP ON)
    endif ()

    include(FetchContent)
    FetchContent_Declare(
            SDL2
            URL ${CMAKE_CURRENT_LIST_DIR}/SDL-release-2.30.3.zip
    )

    set(BUILD_SHARED_LIBS OFF)
    set(protobuf_BUILD_TESTS OFF)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        SET(protobuf_MSVC_STATIC_RUNTIME OFF)
    endif ()
    FetchContent_MakeAvailable(SDL2)
    ```
3. Project Cmakelist.txt is as follows:
    ```
    cmake_minimum_required(VERSION 3.21)
    project(sdl2-example VERSION 0.1.0 LANGUAGES C CXX)

    set(CMAKE_CXX_STANDARD 17)

    #set(CMAKE_BUILD_TYPE "Release")

    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        add_compile_definitions(WIN32_LEAN_AND_MEAN)
    endif ()

    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
        add_compile_definitions(_ITERATOR_DEBUG_LEVEL=0)
    endif ()

    set(CMAKE_VERBOSE_MAKEFILE ON)

    set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

    include(${CMAKE_SOURCE_DIR}/deps/sdl2.cmake)


    set(SOURCES
            ${SOURCE_DIR}/main.cc
    )

    add_executable(${PROJECT_NAME}
            ${SOURCES}
    )

    set(INCLUDES
            ${CMAKE_SOURCE_DIR}/include
            ${CMAKE_SOURCE_DIR}/src/
            ${SOURCE_DIR}
    )

    target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})
    target_link_libraries(${PROJECT_NAME} SDL2::SDL2main SDL2::SDL2-static)
    ```