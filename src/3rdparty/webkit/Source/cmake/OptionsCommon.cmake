ADD_DEFINITIONS(-DBUILDING_WITH_CMAKE=1)
ADD_DEFINITIONS(-DHAVE_CONFIG_H=1)

SET(WTF_INCLUDE_DIRECTORIES
    "${JAVASCRIPTCORE_DIR}"
    "${JAVASCRIPTCORE_DIR}/wtf"
    "${JAVASCRIPTCORE_DIR}/wtf/unicode"
    "${DERIVED_SOURCES_JAVASCRIPTCORE_DIR}"
)

IF (WTF_OS_UNIX)
    ADD_DEFINITIONS(-DXP_UNIX)
ENDIF (WTF_OS_UNIX)

IF (MSVC)
    SET(CODE_GENERATOR_PREPROCESSOR "${CMAKE_CXX_COMPILER} /nologo /EP")
ELSE ()
    SET(CODE_GENERATOR_PREPROCESSOR "${CMAKE_CXX_COMPILER} -E -P -x c++")
ENDIF ()
