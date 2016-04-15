#
# Variables:
#  ${PROJECT_NAME}_DOXYGEN_OUTPUT_DIR: doxygen output directory (optional)

# Needed early on for redirecting the BlueBerry documentation output dir
set(${PROJECT_NAME}_DOXYGEN_OUTPUT_DIR ${PROJECT_BINARY_DIR}/Documentation/Doxygen CACHE PATH
    "Output directory for doxygen generated documentation." )

# Different doxygen versions produce significantly different behaviour in the ${PROJECT_NAME} documentation
# especially in regards to the ${PROJECT_NAME} Qt assistant help files and markdown files.
# The HTML documentation is supposed to be build with Doxygen 1.8.7 or newer, the
# Qt assistant QCH files are supposed to be generated with Doxygen 1.8.7 or newer.
# So we check for 1.8.7 here and QCH generation support is checked in
# BlueBerry/CMakeLists.txt
set(supported_doxygen_version "1.8.7")

if(DOXYGEN_VERSION VERSION_LESS ${supported_doxygen_version})
  MESSAGE(WARNING "Unsupported doxygen version ${DOXYGEN_VERSION}. The ${PROJECT_NAME} HTML documentation has been tested to work with doxygen ${supported_doxygen_version} or newer.")
endif()

option(USE_DOT "Use dot program for generating graphical class diagrams with doxygen, if available" ON)
option(${PROJECT_NAME}_DOXYGEN_BUILD_ALWAYS "Always build the documentation when building the default target" OFF)
option(${PROJECT_NAME}_DOXYGEN_GENERATE_QCH_FILES "Use doxygen to generate Qt compressed help files for ${PROJECT_NAME} docs" OFF)
mark_as_advanced(USE_DOT ${PROJECT_NAME}_DOXYGEN_BUILD_ALWAYS ${PROJECT_NAME}_DOXYGEN_GENERATE_QCH_FILES)
if (${PROJECT_NAME}_DOXYGEN_GENERATE_QCH_FILES AND DOXYGEN_VERSION VERSION_LESS "1.8.7")
  message(WARNING "> Forcing ${PROJECT_NAME}_DOXYGEN_GENERATE_QCH_FILES to OFF because Doxygen version 1.8.7 or newer not found.")
  set(${PROJECT_NAME}_DOXYGEN_GENERATE_QCH_FILES OFF CACHE BOOL "Use doxygen to generate Qt compressed help files for ${PROJECT_NAME} docs" FORCE)
endif()

set(HAVE_DOT "NO")
if(DOXYGEN_DOT_EXECUTABLE AND USE_DOT)
  set(HAVE_DOT "YES")
endif()

set(${PROJECT_NAME}_DOXYGEN_TAGFILE_NAME ${${PROJECT_NAME}_DOXYGEN_OUTPUT_DIR}/${PROJECT_NAME}.tag CACHE INTERNAL "${PROJECT_NAME} Doxygen tag file")

# This is relative to the working directory of the doxygen command
set(${PROJECT_NAME}_DOXYGEN_STYLESHEET doxygen_extra.css)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${${PROJECT_NAME}_DOXYGEN_STYLESHEET}
               ${CMAKE_CURRENT_BINARY_DIR}/${${PROJECT_NAME}_DOXYGEN_STYLESHEET} COPYONLY)

# Create QCH files for ${PROJECT_NAME} and external projects
set(${PROJECT_NAME}_DOXYGEN_GENERATE_QHP "NO")
if(${PROJECT_NAME}_DOXYGEN_GENERATE_QCH_FILES)

  find_program(QT_HELPGENERATOR_EXECUTABLE
    NAMES qhelpgenerator qhelpgenerator-qt5 qhelpgenerator5
    PATHS ${QT_BINARY_DIR}
    DOC "The location of the the Qt help generator executable"
    NO_DEFAULT_PATH
  )
  mark_as_advanced(QT_HELPGENERATOR_EXECUTABLE)

  if(NOT QT_HELPGENERATOR_EXECUTABLE)
    message(SEND_ERROR "The Qt help generator could not be found. Disabling qch generation")
  else()
    set(${PROJECT_NAME}_DOXYGEN_GENERATE_QHP "YES")
  endif()

  # The name of the generated ${PROJECT_NAME} qch file, relative to the
  # Doxygen HTML output folder
  set(${PROJECT_NAME}_DOXYGEN_QCH_FILE "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}-${${PROJECT_NAME}_REVISION_ID}.qch")

endif()

# Compile a doxygen input filter for processing CMake scripts
include(mitkFunctionCMakeDoxygenFilterCompile)
mitkFunctionCMakeDoxygenFilterCompile(NAMESPACE "CMake")

# Configure some doxygen options
if(NOT PROJECT_DOXYGEN_INTERNAL_DOCS)
  set(PROJECT_DOXYGEN_INTERNAL_DOCS "NO")
  set(PROJECT_DOXYGEN_HIDE_FRIEND_COMPOUNDS "YES")
  set(PROJECT_DOXYGEN_EXCLUDE_PATTERNS "*_p.* *Private.h */internal/*")
else()
  set(PROJECT_DOXYGEN_HIDE_FRIEND_COMPOUNDS "NO")
  set(PROJECT_DOXYGEN_EXCLUDE_PATTERNS "")
endif()

if(NOT PROJECT_DOXYGEN_GENERATE_TODOLIST)
  set(PROJECT_DOXYGEN_GENERATE_TODOLIST "NO")
endif()

if(NOT PROJECT_DOXYGEN_GENERATE_BUGLIST)
  set(PROJECT_DOXYGEN_GENERATE_BUGLIST "NO")
endif()

if(NOT PROJECT_DOXYGEN_HTML_DYNAMIC_SECTIONS)
  set(PROJECT_DOXYGEN_HTML_DYNAMIC_SECTIONS "NO")
endif()

if(NOT PROJECT_DOXYGEN_UML_LOOK)
  set(PROJECT_DOXYGEN_UML_LOOK "NO")
endif()

if(NOT PROJECT_DOXYGEN_GENERATE_DEPRECATEDLIST)
  set(PROJECT_DOXYGEN_GENERATE_DEPRECATEDLIST "YES")
endif()

if(NOT DEFINED PROJECT_DOXYGEN_DOT_NUM_THREADS)
  set(PROJECT_DOXYGEN_DOT_NUM_THREADS 0)
endif()

# create output directories for the guides
configure_file(doxygen.conf.in
               ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf)

if(${PROJECT_NAME}_DOXYGEN_BUILD_ALWAYS)
  set(_doc_in_all "ALL")
else()
  set(_doc_in_all "")
endif()

add_custom_target(doc ${_doc_in_all}
                  ${DOXYGEN} ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                  )
