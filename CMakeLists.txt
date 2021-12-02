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

# For beta10 and later due to change in location for dpl library.
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fsycl -std=c++17 -I $ENV{ONEAPI_ROOT}/dpl/2021.1-beta10/linux/include -fsycl-unnamed-lambda")

# Beta 09
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++17")


#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ltbb -lsycl")
include_directories(${MPI_INCLUDE_PATH})

add_executable (pic_ppl src/pic_ppl.C)
target_link_libraries(pic_ppl ${MPI_LIBRARIES})

if(MPI_COMPILE_FLAGS)
  set_target_properties(pic_ppl PROPERTIES
    COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
  set_target_properties(pic_ppl PROPERTIES
    LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()
#add_custom_target (run
#        COMMAND CL_CONFIG_CPU_FORCE_PRIVATE_MEM_SIZE=16MB  ./pic_ppl
#        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
#)
