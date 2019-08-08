cmake_minimum_required(VERSION 2.8)
set ( CMAKE_CXX_STANDARD 11 )
project( Knight )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_library( knight_common image.cc params.cc next.cc board.cc )

add_executable( bfs bfsRunner.cc bfs.cc)
target_link_libraries( bfs ${OpenCV_LIBS} knight_common )

add_executable( rw rwRunner.cc rw.cc)
target_link_libraries( rw ${OpenCV_LIBS} knight_common )
