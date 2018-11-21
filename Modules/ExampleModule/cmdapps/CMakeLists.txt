option(BUILD_ExtExampleCmdApps "Build command-line apps for the Example module" ON)

if(BUILD_ExtExampleCmdApps)
  mitkFunctionCreateCommandLineApp(
    NAME ExampleCmdApp
    DEPENDS MitkExampleModule
  )
endif()
