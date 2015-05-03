PROJECT(my_awesomeproject_exampleapp)

mitk_create_plugin(
  EXPORT_DIRECTIVE AWESOME_APP_EXPORT
  EXPORTED_INCLUDE_SUFFIXES src
  MODULE_DEPENDS MitkQtWidgetsExt
)
