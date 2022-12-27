cmake_minimum_required(VERSION 3.5)

project(SciCalc C)

set( SOURCES 
"src/main.c"
"src/shell.c"
"src/util.c"
)

set(TARGET_NAME "scicalc")

add_executable(${TARGET_NAME} ${SOURCES})