cmake_minimum_required(VERSION 3.22)
project(RotationAvg)

set(SOURCES src/main.cpp)

# Executable definieren
add_executable(${PROJECT_NAME} ${SOURCES})

# Externe Unterverzeichnisse hinzufügen
add_subdirectory(libs/eigen)
add_subdirectory(libs/polyscope)
add_subdirectory(libs/tinyobjloader)

# Add src
add_subdirectory(src)

# Projekt-spezifische Include-Pfade
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Bibliotheken verlinken
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        Eigen3::Eigen
        polyscope
        tinyobjloader
)


