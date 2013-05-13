project(buffermanager)

add_executable(buffermanager bufferreplacementstrategy.cpp bufferframe.cpp buffermanager.cpp main.cpp)

install(TARGETS buffermanager RUNTIME DESTINATION bin)

find_package(Threads REQUIRED)

target_link_libraries(buffermanager ${CMAKE_THREAD_LIBS_INIT})