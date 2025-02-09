#Add visualization sources

set(VISUALIZATION_SOURCES
	helpers.cpp
    loading.cpp
	displaying.cpp
)

target_sources(${PROJECT_NAME} PRIVATE ${VISUALIZATION_SOURCES})
