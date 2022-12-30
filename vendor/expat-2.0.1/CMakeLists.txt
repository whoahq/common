include("${CMAKE_CURRENT_LIST_DIR}/CMakeConfigure.cmake")

if(WHOA_SYSTEM_MAC OR WHOA_SYSTEM_LINUX)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-enum-conversion -Wno-switch")
endif()

set(EXPAT_SRC_DIR "./lib")

add_library(expat-2.0 STATIC
    ${EXPAT_SRC_DIR}/xmlparse.c
    ${EXPAT_SRC_DIR}/xmlrole.c
    ${EXPAT_SRC_DIR}/xmltok.c
)

if(WHOA_SYSTEM_WIN)
    target_compile_definitions(expat-2.0 PUBLIC -DXML_STATIC)
endif()

target_include_directories(expat-2.0
    PUBLIC
        ${EXPAT_SRC_DIR}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)
