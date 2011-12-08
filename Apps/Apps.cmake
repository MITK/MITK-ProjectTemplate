
# This file is included in the top-level CMakeLists.txt file to
# allow early dependency checking

option(${PROJECT_NAME}_Apps/${MY_APP_NAME} "Build the ${MY_APP_NAME}" ON)


# This variable is fed to ctkFunctionSetupPlugins() macro in the
# top-level CMakeLists.txt file. This allows to automatically
# enable required plug-in runtime dependencies for applications using
# the CTK DGraph executable and the ctkMacroValidateBuildOptions macro.
# For this to work, directories containing executables must contain
# a CMakeLists.txt file containing a "project(...)" command and a
# target_libraries.cmake file setting a list named "target_libraries"
# with required plug-in target names.

set(PROJECT_APPS
  Apps/${MY_APP_NAME}^^${PROJECT_NAME}_Apps/${MY_APP_NAME}
)
