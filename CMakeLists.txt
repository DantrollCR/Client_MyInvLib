cmake_minimum_required(VERSION 3.14)
project(Client_MyInvLib)

set(CMAKE_CXX_STANDARD 14)

add_executable(Client_MyInvLib main.cpp Client.cpp Client.h base64.cpp base64.h)