#!/bin/bash

# Typical usage scenario:
#
#  <get sources>
#  $ mkdir linux_build_debug
#  $ cd linux_build_debug
#  $ <source dir>/bootstrap.sh

source_directory=$(dirname ${BASH_SOURCE[0]})
build_directory=$PWD

# Build type obtained from the directory
configuration=Release
case `basename $build_directory` in
         *[Dd]ebug*)
            configuration=Debug
            ;;

         *[Rr]elease*)
            configuration=Release
            ;;

         *[Mm]em[Cc]heck*)
            configuration=MemCheck
            ;;

         *[Cc]ode[Cc]overage*)
            configuration=CodeCoverage
            ;;

         *)
           configuration=Release
           ;;
esac
configuration_option="-DCMAKE_BUILD_TYPE=${configuration}"

for arg in "$@"
do
   case $arg in
      *CMAKE_BUILD_TYPE=*)           # build type is given as command line parameter
         configuration_option=""
         ;;
   esac
done

# Prepare environment
source "${source_directory}/setupEnv.sh"

export CXX=icpc;
export CC=icc
module load CMake/3.9.6
### Run CMake
rm -rf CMakeCache.txt CMakeFiles
cmake -DCMAKE_INSTALL_PREFIX=${build_directory}/install ${configuration_option} $@ $source_directory

