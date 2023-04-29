cmake_minimum_required(VERSION 3.13)

project(Clustering)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)

set(ClusteringInclude
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/k-means.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/IClusterer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/IData.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/Iris.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/EuclidMetric.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/IMetric.hpp
)

set (ClusteringSources 
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/k-means.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Iris.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/EuclidMetric.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Main.cpp

)

add_executable(Clustering ${ClusteringSources} ${ClusteringInclude})

set_property(TARGET Clustering PROPERTY CXX_STANDARD 20)
set_property(TARGET Clustering PROPERTY CXX_STANDARD_REQUIRED ON)
