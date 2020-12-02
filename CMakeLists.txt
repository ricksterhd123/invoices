cmake_minimum_required(VERSION 3.10)
project(Sandbox VERSION 0.1 LANGUAGES C)
add_subdirectory(libs/SQLite3)
add_executable(Sandbox sandbox.c)
target_link_libraries(Sandbox PUBLIC SQLite3)
target_include_directories(Sandbox PUBLIC 
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/libs/sqlite3"
                            )
