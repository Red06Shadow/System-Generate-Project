cmake_minimum_required(VERSION 3.30)

option(USINGWCARACTER "Usa los caracteres wchar_t para las rutas de archivos" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "C:/Proyectos(Red06Shadow)/bin")

include_directories(include)

project(SG-Projects)
add_executable(SG-Projects 
${CMAKE_SOURCE_DIR}/main.cpp
${CMAKE_SOURCE_DIR}/libs/script.cpp
${CMAKE_SOURCE_DIR}/libs/commands.cpp
)
link_directories(${CMAKE_SOURCE_DIR}/libs)
target_link_libraries(SG-Projects PRIVATE ${CMAKE_SOURCE_DIR}/libs/SLOM/libslfm.a ${CMAKE_SOURCE_DIR}/libs/SLFBP/libSLFBP-Lexer.a Pathcch)