find_package( Doxygen )
if(NOT DOXYGEN_FOUND)
    message(WARNING "Doxygen not found, skipping documentation generation.")
    return( )
endif ()

message(STATUS "Doxygen found, configuring documentation generation.")

# We want to use a bridging software between doxygen generated xml for sphinx style documentation
set(DOXYGEN_GENERATE_HTML NO)
set(DOXYGEN_GENERATE_XML YES)

# We need to force relative paths
set(DOXYGEN_STRIP_FROM_PATH ${PROJECT_SOURCE_DIR}/include)

# We will exclude machinery (detail) code from ending up in out docs UI
set(DOXYGEN_EXCLUDE_PATTERNS "*/detail/*")

# Note: Use doxygen_add_docs(doxygen-doc ALL ...) if you want your
# documentation to be created by default each time you build. Without the # keyword
# you need to explicitly invoke building of the 'doc' target.
doxygen_add_docs(cydl-doxygen-doc ${PROJECT_SOURCE_DIR}/include COMMENT
"Generating API documentation with Doxygen")

find_package(Sphinx REQUIRED)
message(STATUS "Located Sphinx package.")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/conf.py.in
        ${CMAKE_SOURCE_DIR}/cmake-build-debug/doc/conf.py @ONLY)

add_custom_target(
        cydl-sphinx-doc ALL
        COMMAND ${SPHINX_EXECUTABLE} -b html -c ${CMAKE_CURRENT_BINARY_DIR}
                ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/html
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Sphinx"
        VERBATIM
)

# must force cmake to call doxygen each time we generate sphinx docs:
add_dependencies(cydl-sphinx-doc cydl-doxygen-doc)