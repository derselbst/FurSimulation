cmake_minimum_required(VERSION 2.8)

### Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "")
  message(STATUS "Setting build type to 'Debug' as none was specified.")
  message(STATUS "")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# by default, force c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# in case we have any c code, use the best c standard ever
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)


include_directories(${CMAKE_SOURCE_DIR}/src/)
SET(FUR_SRC
      src/HairFactory.cpp
      src/main.cpp
)


find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR} ${GLM_INCLUDE_DIRS})



add_executable(fur ${FUR_SRC})
target_link_libraries(fur ${GLM_LIBRARIES} ${GLM_LIBRARY})


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

