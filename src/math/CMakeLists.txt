#Add math sources

set(MATH_SOURCES
    rotations.cpp
    convexCombination.cpp
)

target_sources(${PROJECT_NAME} PRIVATE ${MATH_SOURCES})
