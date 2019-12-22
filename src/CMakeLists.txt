#v1.0 copyright Comine.com 20191221S1510
#
#
#   
#       $ mkdir build
#       $ cd build
#       $ cmake <directory>  -DCMAKE_INSTALL_PREFIX=<targetdir>
#       $ cmake --build . --config Release --target install
#

cmake_minimum_required(VERSION 3.1.6)

########################################
# Project
########################################
project(MDirFiles)
file(GLOB msource "*.h" "*.cpp")
add_executable(MDirFiles ${msource} )



