#[[ Custom find script for Microsofts Guidelines Support Library (GSL) as
    CMake doesn't provide one yet.

    Creates an imported interface target called GuidelinesSupportLibrary that
    can be added to the package dependencies of an MITK module or plugin. ]]

find_path(GuidelinesSupportLibrary_INCLUDE_DIR
  NAMES gsl/gsl
  PATHS ${MITK_EXTERNAL_PROJECT_PREFIX}
  PATH_SUFFIXES include
)

if(NOT TARGET GuidelinesSupportLibrary)
  add_library(GuidelinesSupportLibrary INTERFACE IMPORTED GLOBAL)
  target_include_directories(GuidelinesSupportLibrary INTERFACE ${GuidelinesSupportLibrary_INCLUDE_DIR})
  if(CMAKE_CXX_COMPILER_ID MATCHES Clang OR CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    target_compile_options(GuidelinesSupportLibrary INTERFACE -fno-strict-aliasing)
  endif()
endif()

find_package_handle_standard_args(GuidelinesSupportLibrary
  FOUND_VAR GuidelinesSupportLibrary_FOUND
  REQUIRED_VARS GuidelinesSupportLibrary_INCLUDE_DIR
)
