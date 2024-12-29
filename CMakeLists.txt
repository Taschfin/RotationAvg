cmake_minimum_required(VERSION 3.22)
project(RotationAvg)

# Eigen
add_subdirectory(libs/eigen EXCLUDE_FROM_ALL)

# Assimp
add_subdirectory(libs/assimp)

#OpenGL
add_subdirectory(libs/glfw)
add_subdirectory(libs/glew)

# Executable
add_executable(${PROJECT_NAME} main.cpp)

# Link mit Open3D, Assimp und Eigen
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        assimp::assimp
		OpenGL::GL
        Eigen3::Eigen
		glfw
		glew
)
