project(org_mitk_exampleplugin_eageractivation)

mitk_create_plugin(
  EXPORT_DIRECTIVE EXAMPLE_EXPORT
  EXPORTED_INCLUDE_SUFFIXES src
  MODULE_DEPENDS PRIVATE MitkExampleModule
  PACKAGE_DEPENDS PRIVATE CTK|CTKPluginFramework
)
