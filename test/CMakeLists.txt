
cmake_minimum_required(VERSION 3.0)
project(yzy)

set(EXECUTABLE_OUTPUT_PATH ${EXEBIN})
message("exebin :" ${EXEBIN})
message("log src:" ${LOG_SRC})
aux_source_directory(./ SRC_TEST)
add_executable(test testtimestamp.cpp ${LOG_SRC})
