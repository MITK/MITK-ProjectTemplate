mitk_create_module(ExampleModule
  DEPENDS PUBLIC MitkSegmentationUI
  PACKAGE_DEPENDS PRIVATE GuidelinesSupportLibrary
)

add_subdirectory(cmdapps)
