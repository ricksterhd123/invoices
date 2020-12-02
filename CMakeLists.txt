cmake_minimum_required(VERSION 3.10)
project(Invoices VERSION 0.1 LANGUAGES C)
add_subdirectory(libs/SQLite3)
add_executable(Invoices src/main.c)
target_link_libraries(Invoices PUBLIC SQLite3)
target_include_directories(Invoices PUBLIC 
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/libs/sqlite3"
                            )
