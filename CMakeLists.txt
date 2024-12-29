cmake_minimum_required(VERSION 3.22)
project(RotationAvg)

#VTK
add_subdirectory(libs/vtk)

# Executable
add_executable(${PROJECT_NAME} main.cpp)

# Link mit Open3D, Assimp und Eigen
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
		vtkCommonCore
		vtkRenderingCore
		vtkInteractionStyle
)
