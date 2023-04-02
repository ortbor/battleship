cmake_minimum_required(VERSION 3.23)
project(battlesh_t VERSION 1.2.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(SRC_PATH src/)
set(SOURCES ${SRC_PATH}/button.cpp 
            ${SRC_PATH}/cell.cpp 
            ${SRC_PATH}/command.cpp 
            ${SRC_PATH}/field.cpp 
            ${SRC_PATH}/game.cpp 
            ${SRC_PATH}/player.cpp 
            ${SRC_PATH}/ship.cpp
            ${SRC_PATH}/window.cpp
            main.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

#add_compile_options(-std=c++20 -Wall -Werror -fsanitize=address)
#add_link_options(-fsanitize=address)
add_compile_options(-std=c++20 -Wall -Werror)

find_package(SFML 2.5.1 COMPONENTS window graphics system REQUIRED)
add_executable(main ${SOURCES})
target_link_libraries(main PRIVATE sfml-window sfml-graphics sfml-system)
