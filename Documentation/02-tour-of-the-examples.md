# A tour of the examples

Every example here is small and thoroughly commented. This tour explains what
each one teaches and points you at the files to read. Open the code alongside
it: the comments are the detailed part, this page is the map.

MITK is extended through four kinds of building block, and the template has one
working example of each:

- **Modules** are C++ libraries (your data types, algorithms, interactions).
- **Plugins** contribute to the Workbench UI (views, editors, menus).
- **Applications** are the executables you ship.
- **External projects** are third-party libraries you build alongside MITK.

## The example module (`Modules/ExampleModule`)

A single module, `MitkExampleModule`, demonstrates most of what you can add to
MITK. Its build is defined by
[`CMakeLists.txt`](../Modules/ExampleModule/CMakeLists.txt) and
[`files.cmake`](../Modules/ExampleModule/files.cmake).

### Custom data type, IO, and mappers

This is the "add your own kind of data to MITK" story, in three parts.

- **The data type.**
  [`ExampleDataStructure`](../Modules/ExampleModule/include/ExampleDataStructure.h)
  derives from `mitk::BaseData` (like `mitk::Image` or `mitk::Surface` do) and
  holds a list of labeled 3D points. It implements the handful of methods every
  `BaseData` must provide, and computes its bounding box in
  `UpdateOutputInformation()` so the render windows can frame it.
- **Reading and writing.** The
  [`autoload/IO`](../Modules/ExampleModule/autoload/IO) subdirectory is a
  separate, small module holding a
  [reader](../Modules/ExampleModule/autoload/IO/src/ExampleDataStructureReader.cpp),
  a [writer](../Modules/ExampleModule/autoload/IO/src/ExampleDataStructureWriter.cpp),
  and a [MIME type](../Modules/ExampleModule/autoload/IO/src/ExampleIOMimeTypes.cpp)
  for a simple `.exampledata` text format. Because it is declared
  `AUTOLOAD_WITH MitkCore`, its reader and writer register themselves at
  application start, so `.exampledata` files load and save everywhere in MITK
  with no further setup.
- **Rendering.**
  [`ExampleDataStructureMapper2D`](../Modules/ExampleModule/include/ExampleDataStructureMapper2D.h)
  and
  [`ExampleDataStructureMapper3D`](../Modules/ExampleModule/include/ExampleDataStructureMapper3D.h)
  draw the points as spheres in the slice views and the 3D view. They follow the
  current MITK mapper pattern: all VTK objects live in a per-renderer
  `LocalStorage`, `GetVtkProp()` is a trivial lookup, and the VTK pipeline is
  rebuilt in `GenerateDataForRenderer()` only when the data or (for 2D) the
  slice changed.
  [`ExampleObjectFactory`](../Modules/ExampleModule/src/ExampleObjectFactory.cpp)
  is what tells MITK to use those mappers for this data type, including for data
  that was just loaded from a file.

The neat trick that ties it together: the IO submodule depends on the main
module, so auto-loading the IO also loads the main module, which registers the
rendering factory. That is why a dropped `.exampledata` file both loads *and*
renders without anyone writing glue code.

### Example image filter

[`ExampleImageFilter`](../Modules/ExampleModule/include/ExampleImageFilter.h)
adds an integer offset to every voxel. It shows the idiomatic way to run an ITK
filter on an `mitk::Image`: the `AccessByItk` family of macros lets you write a
templated function once and have MITK dispatch to the right pixel type and
dimension at runtime, without copying the image data. The comments in
[`ExampleImageFilter.cpp`](../Modules/ExampleModule/src/ExampleImageFilter.cpp)
explain why you constrain the pixel types you support.

### Example image interactor

[`ExampleImageInteractor`](../Modules/ExampleModule/include/ExampleImageInteractor.h)
lets you paint into an image with the mouse. It shows how MITK's interaction
framework works: a state machine described in
[`Paint.xml`](../Modules/ExampleModule/resource/Interactions/Paint.xml) maps
input events (configured in
[`PaintConfig.xml`](../Modules/ExampleModule/resource/Interactions/PaintConfig.xml))
to named actions, which you connect to C++ functions in
`ConnectActionsAndFunctions()`.

### Example segmentation tool

[`ExampleSegTool2D`](../Modules/ExampleModule/include/ExampleSegTool2D.h) plugs a
custom tool into MITK's Segmentation views. Its header documents the naming and
macro rules a tool must follow, and it explains an important runtime detail: the
module providing the tool has to be loaded *before* the Segmentation view opens.
That is exactly what the [eager-activation plugin](#eager-activation-plugin)
guarantees.

### Unit tests

The [`test`](../Modules/ExampleModule/test) directory shows the MITK testing
convention (CppUnit via `MITK_CREATE_MODULE_TESTS`). Both tests are
self-contained and need no external data:
[`ExampleImageFilterTest`](../Modules/ExampleModule/test/ExampleImageFilterTest.cpp)
builds a tiny synthetic image and checks the offset, and
[`ExampleDataStructureIOTest`](../Modules/ExampleModule/test/ExampleDataStructureIOTest.cpp)
saves and reloads the custom data type and checks the result is unchanged. See
[Getting started](01-getting-started.md#run-the-tests) for how to run them.

### Example command-line app

[`ExampleCmdApp`](../Modules/ExampleModule/cmdapps/ExampleCmdApp.cpp) wraps the
image filter as a command-line tool. It shows how to use
`mitkCommandLineParser` to declare required and optional arguments and how to
load and save data with `mitk::IOUtil`.

## The example plugins

Plugins are how you add to the Workbench UI. They are BlueBerry/CTK plugins,
each with a `manifest_headers.cmake` and (for UI contributions) a `plugin.xml`.

### Example view

[`org.mitk.gui.qt.exampleplugin`](../Plugins/org.mitk.gui.qt.exampleplugin)
contributes the **Example View**. The view class
[`QmitkExampleView`](../Plugins/org.mitk.gui.qt.exampleplugin/src/internal/QmitkExampleView.cpp)
derives from `QmitkAbstractView`, lets the user pick an image with a node
selection widget, runs `ExampleImageFilter` on it, and attaches
`ExampleImageInteractor` to the result. It is the best starting point for your
own view.

### Eager-activation plugin

[`org.mitk.exampleplugin.eageractivation`](../Plugins/org.mitk.exampleplugin.eageractivation)
does no UI at all. Its only job is to demonstrate the **eager activation
policy** (`Plugin-ActivationPolicy: eager` in its manifest), which loads the
plugin early. It uses that to force the example module to load before the
Segmentation views, so the [example segmentation tool](#example-segmentation-tool)
is available.

### The view's help page

[`documentation/UserManual/ExamplePlugin.dox`](../Plugins/org.mitk.gui.qt.exampleplugin/documentation/UserManual/ExamplePlugin.dox)
is the in-application help shown when the user presses F1 in the Example View.
Its Doxygen page id must match the view id in `plugin.xml`. It is a small
example of how to document your own view.

## The example application (`Applications/ExampleApp`)

Not every project needs the full plugin-based Workbench. `MitkExampleApp`
([`Applications/ExampleApp`](../Applications/ExampleApp)) is a minimal standalone
application: a plain `QMainWindow` with a `QmitkStdMultiWidget` and a
`mitk::StandaloneDataStorage`, and a File menu that loads data. It shows how to
use MITK's rendering without BlueBerry, which is the right choice for small,
focused tools.

## Build-system examples

### External project (GSL)

The template pulls in Microsoft's Guidelines Support Library as an example of
adding a third-party dependency. The recipe is in
[`CMakeExternals/GuidelinesSupportLibrary.cmake`](../CMakeExternals/GuidelinesSupportLibrary.cmake),
registered in
[`CMakeExternals/ExternalProjectList.cmake`](../CMakeExternals/ExternalProjectList.cmake).
Because modern GSL ships its own CMake config package, a module just declares
the `GuidelinesSupportLibrary` package dependency and MITK links the
`Microsoft.GSL::GSL` target through
[`CMake/PackageDepends/MITK_GuidelinesSupportLibrary_Config.cmake`](../CMake/PackageDepends/MITK_GuidelinesSupportLibrary_Config.cmake).
GSL is not actually used; it is there purely to show the mechanism.

### Customizing an MITK external project (ITK)

[`CMakeExternals/Customization/ITK.cmake`](../CMakeExternals/Customization/ITK.cmake)
shows how to change how MITK builds one of *its own* external projects, here
turning on extra ITK modules, without editing MITK.
