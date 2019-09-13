cmake_minimum_required(VERSION 3.0.0)
project(Chess C)

add_library(Util chess_util.c)
add_library(CPU chess_cpu.c)
add_library(Comm chess_com.c)
add_executable(Chess chess_main.c)
target_link_libraries(Chess Util CPU Comm)


install(TARGETS Chess DESTINATION bin)