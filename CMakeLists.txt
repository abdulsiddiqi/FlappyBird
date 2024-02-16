cmake_minimum_required(VERSION 3.5.0)
project(FlappyBird VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

include(/Users/abdulazizsiddiqi/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

add_executable(FlappyBird main.cpp gameloop.cpp player.cpp pipemanager.cpp)

target_link_libraries(FlappyBird PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-audio)



