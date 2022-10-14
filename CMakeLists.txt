cmake_minimum_required(VERSION 3.20)

project(state_machine VERSION 0.1.0 DESCRIPTION "C FSM based on lookup tables")

add_executable(${PROJECT_NAME} "main.c")

add_subdirectory(tests)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
  )