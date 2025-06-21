cmake_minimum_required(VERSION 3.10)
project(random_generator)

include_directories(include)

add_executable(randgen randgen.cpp src/test.cpp src/rand.cpp src/uuid.cpp)