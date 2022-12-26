file(GLOB_RECURSE TEST_SOURCES "*.cpp")

if(WHOA_SYSTEM_MAC)
    set_source_files_properties(${TEST_SOURCES}
        PROPERTIES COMPILE_FLAGS "-x objective-c++"
    )

    add_executable(CommonTest ${TEST_SOURCES})

    target_link_libraries(CommonTest
        PRIVATE
            common
            "-framework AppKit"
    )
endif()

if(WHOA_SYSTEM_LINUX OR WHOA_SYSTEM_WIN)
    add_executable(CommonTest ${TEST_SOURCES})

    target_link_libraries(CommonTest
        PRIVATE
            common
    )
endif()

target_include_directories(CommonTest
    PRIVATE
        ${PROJECT_SOURCE_DIR}
)

install(TARGETS CommonTest DESTINATION "bin")
