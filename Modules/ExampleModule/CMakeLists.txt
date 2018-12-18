mitk_create_module(ExampleModule
  DEPENDS PUBLIC MitkSegmentation
  PACKAGE_DEPENDS PRIVATE GuidelinesSupportLibrary
)

add_subdirectory(cmdapps)
