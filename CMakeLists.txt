cmake_minimum_required(VERSION 3.16)
project(DemoGrpcProject)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH /home/alfredd/.local) # Path to Protobuf and gRPC libraries.

find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)
#include (GoogleTest)



add_executable(hwserver hwserver.cpp demo.grpc.pb.cc demo.pb.cc)
add_executable(hwclient hwclient.cpp demo.grpc.pb.cc demo.pb.cc)
target_link_libraries(hwserver gRPC::grpc++)
target_link_libraries(hwclient gRPC::grpc++)

#protoc -I=./ --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./demo.proto
#protoc -I=./ --cpp_out=. ./demo.proto

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)


add_executable(Tests UnitTests.cpp)
target_link_libraries(Tests gtest_main)
add_test( Name example_test COMMAND Tests)