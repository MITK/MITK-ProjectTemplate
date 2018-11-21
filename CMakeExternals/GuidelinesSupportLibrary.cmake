#[[ The Guidelines Support Library isn't really used in the project template.
    It serves as an example of how to add external projects, though.

    Also see the following files to get an overview of what is
    necessary to add an external project:

      - CMakeExternals/ExternalProjectList.cmake
      - CMake/FindGuidlinesSupportLibrary.cmake
      - CMake/PackageDepends/MITK_GuidelinesSupportLibrary_Config.cmake ]]

set(proj GuidelinesSupportLibrary)
set(${proj}_DEPENDS ${proj})

if(MITK_USE_${proj})
  if(DEFINED ${proj}_DIR AND NOT EXISTS ${${proj}_DIR})
    message(FATAL_ERROR "${proj}_DIR variable is defined but corresponds to non-existing directory!")
  endif()

  if(NOT DEFINED ${proj}_DIR)
    ExternalProject_Add(${proj}
      GIT_REPOSITORY https://github.com/Microsoft/GSL.git
      GIT_TAG v2.0.0
      CMAKE_ARGS ${ep_common_args}
      CMAKE_CACHE_ARGS ${ep_common_cache_args}
        -DGSL_CXX_STANDARD:STRING=${MITK_CXX_STANDARD}
        -DGSL_TEST:BOOL=OFF
      CMAKE_CACHE_DEFAULT_ARGS ${ep_common_cache_default_args}
    )

    set(${proj}_DIR ${ep_prefix})
  else()
    mitkMacroEmptyExternalProject(${proj} "${proj_DEPENDENCIES}")
  endif()
endif()
