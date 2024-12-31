cmake_minimum_required(VERSION 3.22)
project(RotationAvg)

include_directories(libs/polyscope/include)
include_directories(libs/tinyobjloader)

add_subdirectory(libs/eigen)
add_subdirectory(libs/polyscope)
add_subdirectory(libs/tinyobjloader)

# Executable
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
		Eigen3::Eigen
		polyscope
		tinyobjloader
)
