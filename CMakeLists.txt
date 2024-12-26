cmake_minimum_required(VERSION 3.22)
project(RotationAvg)

add_executable(${PROJECT_NAME} main.cpp)


# Eigen
add_subdirectory(libs/eigen EXCLUDE_FROM_ALL)

# Open3D
add_subdirectory(libs/Open3D)

target_link_libraries(${PROJECT_NAME} PRIVATE Open3D::Open3D)
target_link_libraries(${PROJECT_NAME} PRIVATE Eigen3::Eigen)
