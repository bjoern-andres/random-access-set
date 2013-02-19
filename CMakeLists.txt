cmake_minimum_required(VERSION 2.6)
project(random-access-set)
include_directories(include include/andres)
file(GLOB headers include/andres/*.hxx)

add_executable(test-random-access-set src/unittest/random-access-set.cxx ${headers})
add_test(test-random-access-set test-random-access-set)
