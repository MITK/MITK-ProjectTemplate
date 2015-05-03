project(my_awesomeproject_exampleplugin)

mitk_create_plugin(
  EXPORT_DIRECTIVE AWESOME_EXPORTS
  EXPORTED_INCLUDE_SUFFIXES src
  MODULE_DEPENDS MitkQtWidgetsExt MyAwesomeLib
)
