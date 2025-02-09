#Add math sources

set(MATH_SOURCES
	rotationOptimizer.cpp
    rotations.cpp
    convexCombination.cpp
	distances.cpp
	distancesFlags.cpp
)

target_sources(${PROJECT_NAME} PRIVATE ${MATH_SOURCES})
