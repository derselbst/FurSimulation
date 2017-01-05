cmake_minimum_required(VERSION 2.8)

SET(FUR_SRC
      HairFactory.cpp
)

add_executable(fur FUR_SRC)


set(CMAKE_CXX_FLAGS "-pedantic -std=c++11 -Wall -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -DNDEBUG -g")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # using Clang

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  # using Intel C++

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -qopenmp")

  add_executable(fur.mic FUR_SRC)

  # compile flags only for the host version
  set_target_properties(fur PROPERTIES COMPILE_FLAGS "-xhost")

  # compile and link(!) flags only for the Xeon Phi version
  set_target_properties(fur.mic PROPERTIES COMPILE_FLAGS "-mmic" LINK_FLAGS "-mmic")

endif()

# compile flags for everything


# compile using CC=mpiicc CXX=mpiicpc cmake ..
# run using the following line
# mpirun -machinefile <machine_file> <executable>
# of course you have to replace the placeholders with actual files ...

