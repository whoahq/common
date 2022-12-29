file(GLOB COMMON_SOURCES
    "*.cpp"
    "objectalloc/*.cpp"
    "ref/*.cpp"
    "string/*.cpp"
    "thread/*.cpp"
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
        storm
)
