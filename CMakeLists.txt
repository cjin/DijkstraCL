cmake_minimum_required(VERSION 3.3)
project(DijkstraCL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIR})
find_package(GSL REQUIRED)
include_directories(${GSL_INCLUDE_DIR})
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})


set(SOURCE_FILES main.cpp Matrix.cpp Matrix.h UndirectedWeightedGraph.h AdjacencyList.cpp AdjacencyList.h DijkstraCL.cpp DijkstraCL.h typedefs.h BoostAdjacencyList.cpp BoostAdjacencyList.h BoostDijkstra.cpp BoostDijkstra.h Dijkstra.cpp Dijkstra.h)
add_executable(DijkstraCL ${SOURCE_FILES})
target_link_libraries(DijkstraCL ${OpenCL_LIBRARY} ${GSL_LIBRARY})
target_compile_definitions(DijkstraCL PRIVATE TYPEDEFS_CL_INDEX=int TYPEDEFS_CL_SCALAR=float)


