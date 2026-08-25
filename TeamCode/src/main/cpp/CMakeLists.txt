cmake_minimum_required(VERSION 4.1.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -O3")

project("sdk_loader")

file(GLOB_RECURSE LOADER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sdk/*.cpp")
file(GLOB_RECURSE OPMODE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main/*.cpp")

add_library(sdk_loader SHARED
        ${LOADER_SOURCES}
        ${OPMODE_SOURCES}
)

target_include_directories(sdk_loader PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Header
        sdk/lib_loader
)

find_library(log-lib log)

target_link_libraries(sdk_loader ${log-lib})

target_link_options(sdk_loader PRIVATE -Wl,--undefined=_ZN13OpmodeRegistry10getOpModesEv)

