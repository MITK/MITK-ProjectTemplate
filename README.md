# The MITK Project Template

A ready-to-build project that shows how to extend the
[MITK](https://github.com/MITK/MITK) Workbench with your own C++ code: custom
data types, image processing, interactions, tools, views, and applications.

## Why this template?

MITK is a toolkit. When you want to add your own functionality to the MITK
Workbench, you do not fork MITK. Instead you write **modules** (C++ libraries),
**plugins** (Workbench UI), **command-line apps**, and, if needed, pull in your
own **external projects**. This template is a working project made of exactly
those pieces, wired into the MITK build so you can start from something that
already compiles and runs.

Every example is small and heavily commented. Read the code alongside the
[Documentation](Documentation), which explains what each example teaches and
why.

> If you only want to call MITK's algorithms from Python rather than extend the
> Workbench, look at the `mitk-python` package instead. This template is for
> building C++ modules and plugins.

## What's inside

- **Example module** (`Modules/ExampleModule`)
  - A **custom data type** (`ExampleDataStructure`) with its own **file reader
    and writer** (auto-loaded IO) and **2D/3D rendering** (custom mappers)
  - An **ITK-based image filter** (`ExampleImageFilter`)
  - A **data interactor** that paints into images (`ExampleImageInteractor`)
  - A **segmentation tool** (`ExampleSegTool2D`) for the Segmentation views
  - **Unit tests** (`test/`)
- **Example command-line app** (`Modules/ExampleModule/cmdapps`, `ExampleCmdApp`)
- **Example plugins**
  - A Workbench **view** (`Plugins/org.mitk.gui.qt.exampleplugin`)
  - An **eager-activation** plugin (`Plugins/org.mitk.exampleplugin.eageractivation`)
- **Example standalone application** (`Applications/ExampleApp`, `MitkExampleApp`)
- **Example external project** (Microsoft's GSL) and **external-project
  customization** (extra ITK modules)

## Quick start

You do not build this template on its own. You point the MITK **superbuild** at
it with the `MITK_EXTENSION_DIRS` cache variable, and it is built as if it were
part of MITK.

1. Get MITK and this template (for example via "Use this template" on GitHub, or
   by cloning), checking out matching release tags of both.
2. Configure the MITK superbuild with `MITK_EXTENSION_DIRS` set to this working
   copy, then build. On Windows:

   ```bash
   cmake -S MITK -B MITK-superbuild -G "Visual Studio 17 2022" ^
     -D MITK_EXTENSION_DIRS=C:/path/to/MITK-ProjectTemplate
   cmake --build MITK-superbuild --config Release
   ```

3. Launch the MITK Workbench from the inner build tree and open the **Example
   View** (category "Examples").

See [Documentation/01-getting-started.md](Documentation/01-getting-started.md)
for prerequisites, Linux/macOS commands, running the tests, and launching the
applications.

## Documentation

- [Getting started](Documentation/01-getting-started.md): build, run, and test.
- [A tour of the examples](Documentation/02-tour-of-the-examples.md): what each
  example teaches and where to look.
- [Make it your own](Documentation/03-make-it-your-own.md): turn the template
  into your own project.

Requirements and supported platforms match MITK itself; see the
[MITK documentation](https://docs.mitk.org/nightly/).

## License

Copyright (c) [German Cancer Research Center (DKFZ)](https://www.dkfz.de)<br>
All rights reserved.

The MITK-ProjectTemplate is part of [MITK](https://github.com/MITK/MITK) and is
available as free open-source software under a
[3-clause BSD license](LICENSE).
