cmake_minimum_required(VERSION 3.4)
project(snakegame)

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} src/game.cpp src/Snake.cpp src/Hamiltonian.cpp)

add_subdirectory(dependencies/SFML)

target_include_directories(${PROJECT_NAME} PUBLIC include PUBLIC dependencies/SFML/include)
target_link_directories(${PROJECT_NAME} PUBLIC dependencies/SFML/lib)
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)