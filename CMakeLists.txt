project(buffermanager)

add_executable(buffermanager bufferframe.cpp buffermanager.cpp main.cpp)

install(TARGETS buffermanager RUNTIME DESTINATION bin)
