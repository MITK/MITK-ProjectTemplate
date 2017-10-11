option(BUILD_MyAwesomeCmdApps "Build commandline tools for the awesome module" OFF)

if(BUILD_MyAwesomeCmdApps)

  mitkFunctionCreateCommandLineApp(
    NAME OffsetImageCmdApp
    DEPENDS MyAwesomeLib
    PACKAGE_DEPENDS ITK
    )

endif()
