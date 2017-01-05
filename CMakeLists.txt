cmake_minimum_required(VERSION 2.8)

# compile flags for everything
set(CMAKE_CXX_FLAGS "-pedantic -ansi -std=c++11 -Wall -Werror -qopenmp")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -DNDEBUG -g")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")

add_executable(hello hello.cpp)
add_executable(pi pi.cpp)
# compile flags only for the host version
set_target_properties(hello PROPERTIES COMPILE_FLAGS "-xhost")
set_target_properties(pi PROPERTIES COMPILE_FLAGS "-xhost")

add_executable(hello.mic hello.cpp)
add_executable(pi.mic pi.cpp)
# compile and link(!) flags only for the Xeon Phi version
set_target_properties(hello.mic PROPERTIES COMPILE_FLAGS "-mmic" LINK_FLAGS "-mmic")
set_target_properties(pi.mic PROPERTIES COMPILE_FLAGS "-mmic" LINK_FLAGS "-mmic")

# compile using CC=mpiicc CXX=mpiicpc cmake ..
# run using the following line
# mpirun -machinefile <machine_file> <executable>
# of course you have to replace the placeholders with actual files ...
