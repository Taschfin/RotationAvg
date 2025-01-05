#Add visualization sources

set(VISUALIZATION_SOURCES
    loading.cpp
	displaying.cpp
)

target_sources(${PROJECT_NAME} PRIVATE ${VISUALIZATION_SOURCES})
