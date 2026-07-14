#[[ Since version 3, the Guidelines Support Library ships its own CMake config
    package (Microsoft.GSL), so a custom find script is no longer necessary.

    The external project is registered with PACKAGE Microsoft.GSL (see
    CMakeExternals/ExternalProjectList.cmake), so MITK's top-level CMakeLists.txt
    already locates it via find_package. Here we only expose the resulting
    imported target to modules and plugins that depend on
    GuidelinesSupportLibrary. ]]

set(ALL_LIBRARIES Microsoft.GSL::GSL)
