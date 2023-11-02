cmake_minimum_required(VERSION 3.15)
project(cs2_client)


add_compile_options(-w)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories("C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Include")
file(GLOB_RECURSE SOURCES "kiero/*.cpp" "kiero/*.c" "imgui/*.cpp" "src/*.cpp")

find_library(D3D11_LIBRARY 
            NAMES d3d11.lib dxgi.lib d3dcompiler.lib
            PATHS "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x64")


add_library(${PROJECT_NAME} SHARED maindll.cpp ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${D3D11_LIBRARY})
