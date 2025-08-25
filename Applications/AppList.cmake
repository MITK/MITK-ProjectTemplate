option(MITK_BUILD_APP_ExampleApp "Build the MITK ExampleApp executable" ON)

set(MITK_APPS
  ExampleApp^^MITK_BUILD_APP_ExampleApp^^MitkExampleApp
)
