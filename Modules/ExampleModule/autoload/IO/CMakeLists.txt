# This submodule is auto-loaded together with MitkCore, so its reader and
# writer are available as soon as the application starts. Because it also
# depends on MitkExampleModule, loading it pulls in that module too - which is
# what registers the rendering factory for ExampleDataStructure (see
# ExampleObjectFactory). In short: this one AUTOLOAD_WITH line is what makes a
# dropped .exampledata file both load and render without any user setup.
mitk_create_module(ExampleModuleIO
  DEPENDS PUBLIC MitkExampleModule
  AUTOLOAD_WITH MitkCore
)
