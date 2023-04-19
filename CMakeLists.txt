cmake_minimum_required(VERSION 3.13)

project(Clustering)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)

set(ClusteringInclude
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/k-means.hpp
)

set (ClusteringSources 
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/k-means.cpp
)

add_executable(Clustering ${ClusteringSources} ${ClusteringInclude})

set_property(TARGET Clustering PROPERTY CXX_STANDARD 17)
set_property(TARGET Clustering PROPERTY CXX_STANDARD_REQUIRED ON)
