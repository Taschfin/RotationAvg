#Add helpers sources

set(HELPERS_SOURCES
    transformations.cpp
    rotations.cpp
)

target_sources(${PROJECT_NAME} PRIVATE ${HELPERS_SOURCES})
