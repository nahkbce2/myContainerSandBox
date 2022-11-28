# required cmake version
cmake_minimum_required(VERSION 3.5)

project (myMPI_program)
#set(CMAKE_CXX_COMPILER "mpicxx")

# Set default build type to RelWithDebInfo if not specified
if (NOT CMAKE_BUILD_TYPE)
    message (STATUS "Default CMAKE_BUILD_TYPE not set using Release with Debug Info")
    set (CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE
        STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel"
        FORCE)
endif()
find_package(MPI REQUIRED)

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
#find_package(Boost 1.45.0 COMPONENTS filesystem regex) 
find_package(Boost COMPONENTS program_options log filesystem system thread atomic date_time chrono iostreams regex log_setup zlib)
message (STATUS "Boost_Root is ${Boost_ROOT}")

# Use boost in our project
   set(BOOST_ROOT "${Boost_ROOT}")
   set(Boost_FOUND TRUE)
   

##set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib64-msvc-14.2")

#include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
# For beta10 and later due to change in location for dpl library.
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fsycl -std=c++17 -I $ENV{ONEAPI_ROOT}/dpl/2021.1-beta10/linux/include -fsycl-unnamed-lambda")

# Beta 09
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++17")

set (all_headers,
   src/MemoryChecker.h
   src/NumericFunctions.h
   src/MpiFunctions.h
   src/ConstantsMathematics.h
   src/System.h
   ${Boost_INCLUDE_DIRS}
    )

set(all_srcs
   src/MemoryChecker.cpp
   src/System.cpp
   src/pic_ppl.C
    )

source_group(HEAD FILES ${all_headers})

source_group(SRC FILES ${all_srcs})

set( APP_NAME "myPi" )

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ltbb -lsycl")
include_directories(${MPI_INCLUDE_PATH} 
                    SYSTEM
                    )

include_directories(${Boost_INCLUDE_DIRS})		

add_executable(${APP_NAME}
   ${all_srcs}
   ${all_headers}
)
target_link_libraries(${APP_NAME} ${MPI_LIBRARIES} ${Boost_LIBRARIES})
#set_target_properties( ${APP_NAME} PROPERTIES SUFFIX ".exe" )
#set_target_properties( ${APP_NAME} PROPERTIES FOLDER "${BASE_FOLDER}/${APP_NAME}" )

if(MPI_COMPILE_FLAGS)
  set_target_properties(${APP_NAME} PROPERTIES
    COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
  set_target_properties(${APP_NAME} PROPERTIES
    LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()
#add_custom_target (run
#        COMMAND CL_CONFIG_CPU_FORCE_PRIVATE_MEM_SIZE=16MB  ./pic_ppl
#        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
#)
