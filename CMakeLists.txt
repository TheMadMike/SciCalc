cmake_minimum_required(VERSION 3.5)

project(SciCalc C)

set( SOURCES 
"src/shell.c"
"src/util.c"
"src/expr_stack.c"
)

set(TARGET_NAME "scicalc")

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(${TARGET_NAME} "src/main.c" ${SOURCES})
target_link_libraries(${TARGET_NAME} m)

if(MSVC)
  target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

set(TEST_TARGET_NAMES 
"expr_stack_test")

add_executable("expr_stack_test" ${SOURCES} "src/tests/expr_stack_test.c")
target_link_libraries("expr_stack_test" m)


enable_testing()

foreach(TEST_TARGET_NAME IN LISTS TEST_TARGET_NAMES)

  if(MSVC)
    # TODO: add sanitizers and static anlyzer option for MSVC
  else()
    target_compile_options(${TEST_TARGET_NAME} PRIVATE -fsanitize=leak -fanalyzer)
  endif()

  add_test(NAME ${TEST_TARGET_NAME} COMMAND ${TEST_TARGET_NAME})

endforeach()
