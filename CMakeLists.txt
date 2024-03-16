cmake_minimum_required(VERSION 3.21)
project(dlm_examples)

set(CMAKE_CXX_STANDARD 17)

find_package(cpr REQUIRED)

set(LIB_DLM_CLIENT lib/dlmclient/src/client.cpp lib/dlmclient/include/client.hpp lib/dlmclient/src/response.cpp lib/dlmclient/include/response.hpp lib/dlmclient/src/request.cpp lib/dlmclient/include/request.hpp lib/dlmclient/src/connection.cpp lib/dlmclient/include/connection.hpp)

add_executable(dlm_examples main.cpp ${LIB_DLM_CLIENT})

target_link_libraries(dlm_examples PRIVATE cpr::cpr)