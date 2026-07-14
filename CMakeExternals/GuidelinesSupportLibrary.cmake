#[[ The Guidelines Support Library isn't really used in the project template.
    It serves as an example of how to add external projects, though.

    Also see the following files to get an overview of what is
    necessary to add an external project:

      - CMakeExternals/ExternalProjectList.cmake
      - CMake/PackageDepends/MITK_GuidelinesSupportLibrary_Config.cmake ]]

set(proj GuidelinesSupportLibrary)
set(proj_DEPENDENCIES "")

if(MITK_USE_${proj})
  set(${proj}_DEPENDS ${proj})

  if(DEFINED ${proj}_DIR AND NOT EXISTS ${${proj}_DIR})
    message(FATAL_ERROR "${proj}_DIR variable is defined but corresponds to non-existing directory!")
  endif()

  if(NOT DEFINED ${proj}_DIR)
    ExternalProject_Add(${proj}
      GIT_REPOSITORY https://github.com/microsoft/GSL.git
      GIT_TAG v4.2.2
      CMAKE_ARGS ${ep_common_args}
      CMAKE_CACHE_ARGS ${ep_common_cache_args}
        -DGSL_INSTALL:BOOL=ON
        -DGSL_TEST:BOOL=OFF
      CMAKE_CACHE_DEFAULT_ARGS ${ep_common_cache_default_args}
      DEPENDS ${proj_DEPENDENCIES}
    )

    set(${proj}_DIR ${ep_prefix})
    mitkFunctionInstallExternalCMakeProject(${proj})
  else()
    mitkMacroEmptyExternalProject(${proj} "${proj_DEPENDENCIES}")
  endif()
endif()
