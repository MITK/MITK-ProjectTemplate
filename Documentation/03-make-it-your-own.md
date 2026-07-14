# Make it your own

The template is a starting point, not a library you depend on. Copy it, rename
its pieces to your project, delete the examples you do not need, and add your
own. This page explains how.

## Start from a copy

On GitHub, use **"Use this template"** to create your own repository. Otherwise
clone or fork it. Either way, check out the tag or branch that matches the MITK
version you build against; the template follows MITK's release cadence.

## Rename the examples to your project

The template's own names all contain `Example` (plus the vendor `CAMIC`). None
of those strings appear in MITK's API, so renaming is mostly a matter of
replacing them consistently. Do it per building block rather than with one blind
search-and-replace, so you also rename the folders and files.

### A module

For [`Modules/ExampleModule`](../Modules/ExampleModule):

1. Rename the folder, e.g. `Modules/MyModule`.
2. Update the module name in
   [`Modules/ModuleList.cmake`](../Modules/ModuleList.cmake) and in the module's
   `CMakeLists.txt` (`mitk_create_module(MyModule ...)`). The library target
   becomes `MitkMyModule`.
3. `mitk_create_module` generates the export header and macro from the module
   name, so `MitkExampleModuleExports.h` becomes `MitkMyModuleExports.h` and
   `MITKEXAMPLEMODULE_EXPORT` becomes `MITKMYMODULE_EXPORT`. Update the
   `#include` and the macro in your headers accordingly.
4. Rename the class files and classes (`ExampleImageFilter` and friends) and the
   entries in `files.cmake`.

### A plugin

For [`Plugins/org.mitk.gui.qt.exampleplugin`](../Plugins/org.mitk.gui.qt.exampleplugin):

1. Rename the folder to your reverse-domain id, e.g.
   `org.mycompany.gui.qt.myview`.
2. Update the id in [`Plugins/PluginList.cmake`](../Plugins/PluginList.cmake).
3. In `plugin.xml`, set your view's `id`, `name`, `class`, and `category`.
4. In `manifest_headers.cmake`, set the plugin `Name` and `Vendor` (replace
   `CAMIC`).
5. Rename the view class (`QmitkExampleView` -> `QmitkMyView`) and its files,
   and update `files.cmake`.
6. Rename the help page so its Doxygen page id matches the new view id (see
   [the view's help page](02-tour-of-the-examples.md#the-views-help-page)).

### An application

For [`Applications/ExampleApp`](../Applications/ExampleApp): rename the folder,
update [`Applications/AppList.cmake`](../Applications/AppList.cmake) (the option
and the `MITK_APPS` entry, whose executable is `MitkExampleApp`), and adjust the
target name in its `CMakeLists.txt`.

### Everywhere

Replace the vendor/contributor string `CAMIC` (in the plugin manifests and the
command-line app) with your own, and update the MIME type name in
[`ExampleIOMimeTypes.cpp`](../Modules/ExampleModule/autoload/IO/src/ExampleIOMimeTypes.cpp)
if you keep the custom data type.

## Remove what you do not need

Each building block is independent. To drop one, delete its folder and remove
its entry from the corresponding list file:

- a module: from [`Modules/ModuleList.cmake`](../Modules/ModuleList.cmake)
- a plugin: from [`Plugins/PluginList.cmake`](../Plugins/PluginList.cmake)
- an application: from [`Applications/AppList.cmake`](../Applications/AppList.cmake)
- an external project: from
  [`CMakeExternals/ExternalProjectList.cmake`](../CMakeExternals/ExternalProjectList.cmake)

Mind the dependencies between the examples before deleting: the eager-activation
plugin and the example view both use the example module, and the IO submodule
and the object factory belong to the custom data type. If you delete the example
module, remove those too.

## Add your own

The quickest way to add a new module, plugin, app, or external project is to
copy the matching example, rename it as above, and replace its contents. The
[tour of the examples](02-tour-of-the-examples.md) points at the right example
for each case. Then register the new building block in the corresponding list
file.

## Stay in sync with MITK

The MITK API evolves between releases. Keep your project building by moving to a
new MITK release tag and the matching template tag together, rather than mixing
versions. Watching MITK's release notes for API changes that touch the pieces
you use will save you surprises.
