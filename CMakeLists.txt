cmake_minimum_required(VERSION 3.5)

project (GeoMath)

#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package (Threads)

#-------------------- Create a library -----------------------------------------
#Generate the shared library from the library sources
#-------------------------------------------------------------------------------
add_library(${PROJECT_NAME}_lib STATIC
            lib_src/GeoMath.cpp
            lib_src/GeoMath.h)

target_include_directories(${PROJECT_NAME}_lib
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/lib_src
)



# link the new library target with the binary target


install(FILES lib_src/GeoMath.h DESTINATION include)
install(FILES GeoMathConfig.cmake DESTINATION lib/cmake/GeoMath)

install(FILES build/lib${PROJECT_NAME}_lib.a DESTINATION lib)

#------------------- Create an executable --------------------------------------
file(GLOB 
          CPP_SOURCES "lib_src/*.cpp" "src/*.cpp")

add_executable(sample ${CPP_SOURCES} src/server.h)
target_link_libraries (sample ${CMAKE_THREAD_LIBS_INIT})



