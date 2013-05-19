project(buffermanager)

add_executable(buffermanager IO/datafile.cpp IO/datasource.cpp Test/BufferManager/buffermanagertest.cpp BufferManager/bufferreplacementstrategy.cpp BufferManager/bufferframe.cpp BufferManager/buffermanager.cpp main.cpp)

install(TARGETS buffermanager RUNTIME DESTINATION bin)

find_package(Threads REQUIRED)

target_link_libraries(buffermanager ${CMAKE_THREAD_LIBS_INIT})
add_subdirectory(BufferManager)
add_subdirectory(Test)
add_subdirectory(IO)