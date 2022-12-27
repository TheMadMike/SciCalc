cmake_minimum_required(VERSION 3.5)

project(SciCalc C)

set( SOURCES 
"src/main.c"
"src/shell.c"
"src/util.c"
"src/expr_stack.c"
)

set(TARGET_NAME "scicalc")

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME} m)


add_executable("test" "src/expr_stack.c" "src/tests/tests.c")
target_link_libraries("test" m)