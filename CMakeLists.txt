cmake_minimum_required (VERSION 2.8)

project(cpp-practice)

set(OUTPUT_FOLDER ${CMAKE_SOURCE_DIR}/output)
set(OUTPUT_BIN_FOLDER ${OUTPUT_FOLDER}/bin)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BIN_FOLDER})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SOURCES src/TypeTraits.hpp
			src/Tuple.hpp
			src/main.cpp)
			
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
