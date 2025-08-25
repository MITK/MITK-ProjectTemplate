project(ExampleApp)

add_executable(MitkExampleApp
  src/main.cpp
  src/MainWindow.h
  src/MainWindow.cpp
)

target_link_libraries(MitkExampleApp
  PRIVATE
    MitkQtWidgets
)

set_target_properties(MitkExampleApp PROPERTIES
  AUTOMOC ON
)

mitkFunctionConfigureVisualStudioUserProjectFile(NAME MitkExampleApp)
