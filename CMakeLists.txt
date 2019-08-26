cmake_minimum_required(VERSION 3.0.0)
project(Chess C)

add_library(Util chess_util.c)
add_executable(Main chess_main.c)
target_link_libraries(Main Util)


install(TARGETS Main DESTINATION bin)