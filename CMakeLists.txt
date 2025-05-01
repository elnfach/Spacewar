cmake_minimum_required(VERSION 3.31)
project(spacewar)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_PARALLEL_LEVEL 12)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -static -lpthread")

file(GLOB_RECURSE PRIVATE_HEADERS engine/*.hpp)
file(GLOB_RECURSE SOURCES engine/*.cpp)

set(ALL_SOURCES ${PRIVATE_HEADERS} ${SOURCES})

add_executable(spacewar ${ALL_SOURCES} spacewar.cpp)

target_include_directories(spacewar PRIVATE engine)
target_include_directories(spacewar PRIVATE thirdparty/lua/src)
target_include_directories(spacewar PRIVATE thirdparty/glm/include)
target_include_directories(spacewar PRIVATE thirdparty/sfml/include)
target_include_directories(spacewar PRIVATE thirdparty/json/include)
target_include_directories(spacewar PRIVATE thirdparty/entt/include)
target_include_directories(spacewar PRIVATE thirdparty/fk_yaml/include)
target_include_directories(spacewar PRIVATE thirdparty/boost-ext/include)
target_include_directories(spacewar PRIVATE thirdparty/win_socket/include)


add_subdirectory(thirdparty/sfml ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/sfml)
target_link_libraries(spacewar PRIVATE sfml-graphics)

add_subdirectory(thirdparty/lua ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/lua)
target_link_libraries(spacewar PRIVATE lua)

target_link_libraries(spacewar PRIVATE Ws2_32)

target_compile_definitions(spacewar PUBLIC RESOURCES="${CMAKE_CURRENT_SOURCE_DIR}/resources/")