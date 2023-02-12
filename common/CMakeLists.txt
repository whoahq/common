file(GLOB COMMON_SOURCES
    "*.cpp"
    "datamgr/*.cpp"
    "datastore/*.cpp"
    "mempool/*.cpp"
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
        tempest
)

if(CODE_COVERAGE)
    target_compile_options(common PRIVATE --coverage)
    target_link_options(common PUBLIC --coverage)
endif()
