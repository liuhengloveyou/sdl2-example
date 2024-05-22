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

########### 三方依赖库 ############
include(${CMAKE_SOURCE_DIR}/deps/sdl2.cmake)
########### 三方依赖库 ###########


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

message(STATUS "[${PROJECT_NAME}][cmake] Build type:             ${CMAKE_BUILD_TYPE}")
message(STATUS "[${PROJECT_NAME}][cmake] Build compiler:             ${CMAKE_CXX_COMPILER_ID}")
string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_TYPE)
message(STATUS "[${PROJECT_NAME}][cmake] Build with cxx flags:   ${CMAKE_CXX_FLAGS_${BUILD_TYPE}} ${CMAKE_CXX_FLAGS}")
message(STATUS "[${PROJECT_NAME}][cmake] Build with c flags:     ${CMAKE_C_FLAGS_${BUILD_TYPE}} ${CMAKE_C_FLAGS}")
