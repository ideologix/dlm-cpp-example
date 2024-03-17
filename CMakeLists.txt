cmake_minimum_required(VERSION 3.21)
project(dlm_examples)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)

set(LIB_DLM_CLIENT lib/dlm-cpp/src/client.cpp lib/dlm-cpp/include/client.hpp lib/dlm-cpp/src/response.cpp lib/dlm-cpp/include/response.hpp lib/dlm-cpp/src/request.cpp lib/dlm-cpp/include/request.hpp lib/dlm-cpp/src/connection.cpp lib/dlm-cpp/include/connection.hpp lib/dlm-cpp/include/parameter.hpp)

add_executable(dlm_examples main.cpp ${LIB_DLM_CLIENT})

target_link_libraries(dlm_examples CURL::libcurl)