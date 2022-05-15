cmake_minimum_required(VERSION 3.21)
set(project_name Clause_Resolution)
set(CMAKE_VERBOSE_MAKEFILEON ON)
project(${project_name})

set(CMAKE_CXX_STANDARD 14)
include_directories(./headers/ )
aux_source_directory(./cpp SOURCE_DIR)

add_executable(${project_name} ${SOURCE_DIR})
