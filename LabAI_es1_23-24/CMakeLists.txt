cmake_minimum_required(VERSION 3.16)

project(esercitazione1_23-24)

set(CMAKE_CXX_FLAGS "-fdiagnostics-color=always -std=c++2b -pthread -Og -g -march=native -fPIC")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/)


add_library(uwimg++ SHARED
     src/utils.cpp
     src/utils.h
     src/image.h
     src/load_image.cpp
     src/stb_image.h
     src/stb_image_write.h
     
     src/access_image.cpp    # file to submit
     src/process_image.cpp   # file to submit
     
     
     )


link_libraries(uwimg++ m stdc++)


add_executable(test0 src/test/test0.cpp)

