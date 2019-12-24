#v1.0 copyright Comine.com 20191221S1510

cmake_minimum_required(VERSION 3.2)

########################################
# Project
########################################
project(MDirFiles)
file(GLOB msource "*.h" "*.cpp")
add_executable(MDirFiles ${msource} )



