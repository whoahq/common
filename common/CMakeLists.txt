file(GLOB COMMON_SOURCES
    "*.cpp"
    "datastore/*.cpp"
    "objectalloc/*.cpp"
    "ref/*.cpp"
    "string/*.cpp"
    "thread/*.cpp"
    "xml/*.cpp"
)

add_library(common STATIC
    ${COMMON_SOURCES}
)

target_include_directories(common
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(common
    PUBLIC
        expat-2.0
        storm
)
