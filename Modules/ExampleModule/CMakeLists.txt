mitk_create_module(ExampleModule
  DEPENDS PUBLIC MitkSegmentationUI
  PACKAGE_DEPENDS
    PRIVATE GuidelinesSupportLibrary VTK|FiltersCore+FiltersSources
)

add_subdirectory(autoload/IO)
add_subdirectory(cmdapps)
add_subdirectory(test)
