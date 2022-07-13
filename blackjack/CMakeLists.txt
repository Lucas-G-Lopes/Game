cmake_minimum_required(VERSION 3.5)

project(blackjack)

add_executable(${PROJECT_NAME} main.c)

function(print)
    message("${var} = ${${var}}")
endfunction(print)

print(PROJECT_NAME)


