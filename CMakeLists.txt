
cmake_minimum_required(VERSION 3.0)
project(yzy)

set(EXEBIN ${PROJECT_SOURCE_DIR}/bin)
include_directories(./logsys/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/logsys/src LOG_SRC)
add_subdirectory(test)
