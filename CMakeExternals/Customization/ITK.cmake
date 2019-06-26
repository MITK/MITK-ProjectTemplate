#[[ Customize MITK's external projects. This feature is supported only
    rudimentary and not all of MITK's external projects may take these
    customizations into account.

    The file's name must be equal to the external project's name. It may
    contain the following three variables:

      - CUSTOM_CMAKE_ARGS
      - CUSTOM_CMAKE_CACHE_ARGS
      - CUSTOM_CMAKE_DEFAULT_CACHE_ARGS

    You can lookup the meaning of these variables without the CUSTOM_ prefix
    in the official CMake documentation. The custom variables are simply added
    to the respective variables of the external project. ]]

set(CUSTOM_CMAKE_ARGS
  -DModule_TextureFeatures:BOOL=ON
  -DModule_RLEImage:BOOL=ON
  -DModule_IsotropicWavelets:BOOL=ON
  -DModule_PrincipalComponentsAnalysis:BOOL=ON
)
