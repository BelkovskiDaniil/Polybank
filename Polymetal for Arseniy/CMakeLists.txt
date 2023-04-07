cmake_minimum_required(VERSION 3.16.5)
project(databaseproject)

set(CMAKE_CXX_STANDARD 14)

add_executable(databaseproject main.cpp #[[sqlite-amalgamation-3410200/shell.c]] sqlite-amalgamation-3410200/sqlite3.c sqlite-amalgamation-3410200/sqlite3.h sqlite-amalgamation-3410200/sqlite3ext.h)
