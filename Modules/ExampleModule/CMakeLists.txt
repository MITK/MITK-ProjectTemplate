mitk_create_module(ExampleModule
  DEPENDS PUBLIC MitkCore
  PACKAGE_DEPENDS PRIVATE GuidelinesSupportLibrary
)

add_subdirectory(cmdapps)
