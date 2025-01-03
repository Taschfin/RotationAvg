cmake_minimum_required(VERSION 3.22)
project(RotationAvg)

# Unterverzeichnisse hinzufügen
add_subdirectory(libs/eigen)
add_subdirectory(libs/polyscope)
add_subdirectory(libs/tinyobjloader)

# Quellen und Header definieren
set(SOURCES src/main.cpp src/helpers/math_operations.cpp)
#set(HEADERS include/r)

# Executable definieren
add_executable(${PROJECT_NAME} ${SOURCES})

# Projekt-spezifische Include-Pfade
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

message(STATUS "Include directories: ${CMAKE_CURRENT_SOURCE_DIR}/include")

# Bibliotheken verlinken
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        Eigen3::Eigen
        polyscope
        tinyobjloader
)
