cmake_minimum_required(VERSION 3.22)
project(RotationAvg)

# Eigen
add_subdirectory(libs/eigen EXCLUDE_FROM_ALL)

#VTK
add_subdirectory(libs/vtk)

# Executable
add_executable(${PROJECT_NAME} main.cpp)

# Link mit Open3D, Assimp und Eigen
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        Eigen3::Eigen
)
