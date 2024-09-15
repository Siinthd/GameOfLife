cmake_minimum_required(VERSION 3.10)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(GameOfLife src/main.cpp src/GameOfLife.cpp)

target_link_libraries(GameOfLife ${SDL2_LIBRARIES})

install(TARGETS GameOfLife RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_DEB_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_VERSION 0.1)
set(CPACK_PACKAGE_CONTACT turel1405@gmail.com)
include(CPack)
