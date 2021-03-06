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


include_directories(${CMAKE_SOURCE_DIR}/src/ ${CMAKE_SOURCE_DIR}/src/sim)
SET(FUR_SRC
      src/sim/FTL.cpp
      src/sim/PBD.cpp
      src/ISimulation.cpp
      src/HairFactory.cpp
      src/Visualizer.cpp
      src/Vertex.cpp
      src/main.cpp
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(Boost 1.56.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIR} ${GLM_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} /usr/include)

add_executable(fur ${FUR_SRC})
target_link_libraries(fur ${GLM_LIBRARIES} ${GLM_LIBRARY} ${Boost_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

find_package ( OpenMP QUIET )
if ( OpenMP_FOUND OR OpenMP_C_FOUND )
    message(STATUS "Found OpenMP ${OpenMP_CXX_SPEC_DATE}")
    # require at least OMP 4.0
    if ( ( NOT OpenMP_CXX_SPEC_DATE LESS "201307" ) OR NOT ( OpenMP_CXX_VERSION VERSION_LESS "4.0" ) )
        set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}" )
         set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}" )
         target_link_libraries (fur ${OpenMP_CXX_LIBRARIES} )
    endif()
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O3 -DNDEBUG -g")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # using Clang
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Rpass=loop-vectorize -Rpass-analysis=loop-vectorize")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  # using Intel C++

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -qopt-report=5 -qopt-report-phase=vec -restrict")

#  add_executable(fur.mic ${FUR_SRC})

  # compile flags only for the host version
  set_target_properties(fur PROPERTIES COMPILE_FLAGS "-xhost")

  # compile and link(!) flags only for the Xeon Phi version
#  set_target_properties(fur.mic PROPERTIES COMPILE_FLAGS "-mmic" LINK_FLAGS "-mmic")

endif()

# compile flags for everything


# compile using CC=mpiicc CXX=mpiicpc cmake ..
# run using the following line
# mpirun -machinefile <machine_file> <executable>
# of course you have to replace the placeholders with actual files ...

