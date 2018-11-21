set(CPP_FILES
  src/internal/PluginActivator.cpp
  src/internal/QmitkExampleView.cpp
)

set(UI_FILES
  src/internal/ExampleViewControls.ui
)

set(MOC_H_FILES
  src/internal/PluginActivator.h
  src/internal/QmitkExampleView.h
)

# List of resource files that can be used by the plugin system without loading
# the actual plugin. For example, the icon that is typically displayed in the
# plugin view menu at the top of the application window.
set(CACHED_RESOURCE_FILES
  resources/ExampleIcon.svg
  plugin.xml
)

set(QRC_FILES
)
