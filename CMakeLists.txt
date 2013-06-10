cmake_minimum_required(VERSION 2.8)

project(buffermanager)

link_directories(${MyProject_SOURCE_DIR}/libs)
include_directories(${MyProject_SOURCE_DIR}/include)

add_executable(buffermanager BTree/btreenode.cpp BTree/btree.cpp BTree/btreesegment.cpp Segments/spsegment.cpp Segments/tid.cpp Segments/slottedpage.cpp Segments/segmentinformation.cpp Segments/sisegment.cpp Segments/segment.cpp Segments/segmentmanager.cpp Segments/pagesegments.cpp IO/datafile.cpp IO/datasource.cpp Test/BufferManager/buffermanagertest.cpp BufferManager/bufferreplacementstrategy.cpp BufferManager/bufferframe.cpp BufferManager/buffermanager.cpp main.cpp)

install(TARGETS buffermanager RUNTIME DESTINATION bin)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


target_link_libraries(buffermanager ${CMAKE_THREAD_LIBS_INIT})

add_subdirectory(BufferManager)
add_subdirectory(Test)
add_subdirectory(IO)
add_subdirectory(Segments)
add_subdirectory(BTree)