cmake_minimum_required(VERSION 3.20)

project(cpp_projects)
if (NOT DEFINED ENV{CUDACXX})
    add_subdirectory(central_lib)
    message(STATUS "Added lib central")
    add_subdirectory(net_prog)
    message(STATUS "Added net prog")
    add_subdirectory(misc)
    message(STATUS "Added misc")
    add_subdirectory(leetcode)
    message(STATUS "Added leetcode")
    add_subdirectory(lisp)
    message(STATUS "lisp interpreter")
else ()
    add_subdirectory(cuda_demos)
    message(STATUS "Added cuda demo")
endif ()
add_subdirectory(ray_trace)
message(STATUS "Added ray trace project")


