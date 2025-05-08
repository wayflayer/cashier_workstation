cmake_minimum_required(VERSION 3.10)
project(cashier_workstation)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(Boost 1.66 REQUIRED COMPONENTS filesystem system json)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost libraries not found")
endif()

message(STATUS "Boost version: ${Boost_VERSION}")
message(STATUS "Boost includes: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost libraries: ${Boost_LIBRARIES}")

file(GLOB SOURCES "src/*.cpp")

add_executable(cashier_workstation ${SOURCES})

target_include_directories(cashier_workstation 
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(cashier_workstation
    PRIVATE
    ${Boost_LIBRARIES}
)

configure_file(
    ${CMAKE_SOURCE_DIR}/data/products.json
    ${CMAKE_BINARY_DIR}/data/products.json
    COPYONLY
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)