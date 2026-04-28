cmake_minimum_required(VERSION 3.21)
project(gd-ai-builder VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(gd-ai-builder SHARED src/AIBuilder.cpp)

target_include_directories(gd-ai-builder PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(APPLE)
  set_target_properties(gd-ai-builder PROPERTIES
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
    XCODE_ATTRIBUTE_DEVELOPMENT_TEAM ""
  )
endif()
