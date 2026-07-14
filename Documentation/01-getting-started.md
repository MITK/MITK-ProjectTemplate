# Getting started

This walks you through building the template against MITK, running the
Workbench, and trying the examples.

## Prerequisites

The template has the same prerequisites as MITK itself (a C++20 compiler, a
recent CMake, and Qt). See the
[MITK build instructions](https://docs.mitk.org/nightly/BuildInstructionsPage.html)
for the exact versions and platform notes. You do **not** need to build MITK
separately: the MITK superbuild builds MITK and this template together.

## Get the sources

Put MITK and the template side by side, for example:

```
dev/
  MITK/                   # cloned from https://github.com/MITK/MITK
  MITK-ProjectTemplate/   # this project (your copy)
```

Check out matching release tags of both (the template tracks MITK's releases).
For your own project, start from "Use this template" on GitHub instead of
cloning; see [Make it your own](03-make-it-your-own.md).

## Configure and build

You point the MITK **superbuild** at the template with the `MITK_EXTENSION_DIRS`
cache variable. Everything in the template is then built as if it were part of
MITK.

**Windows (Visual Studio):**

```bash
cmake -S MITK -B MITK-superbuild -G "Visual Studio 17 2022" ^
  -D MITK_EXTENSION_DIRS=C:/dev/MITK-ProjectTemplate
cmake --build MITK-superbuild --config Release
```

**Linux / macOS (Ninja):**

```bash
cmake -S MITK -B MITK-superbuild -G Ninja -D CMAKE_BUILD_TYPE=Release \
  -D MITK_EXTENSION_DIRS=/path/to/MITK-ProjectTemplate
cmake --build MITK-superbuild
```

The first build takes a while because it downloads and builds MITK's
dependencies. After that, rebuild only the inner tree (MITK plus the template):

```bash
cmake --build MITK-superbuild/MITK-build --config Release
```

`MITK_EXTENSION_DIRS` accepts a semicolon-separated list, so you can point it at
several extension directories at once.

## Run the Workbench

The applications land in `MITK-superbuild/MITK-build/bin`.

- **Windows:** run `startMitkWorkbench_release.bat` from that folder (it sets up
  the required `PATH`).
- **Linux / macOS:** run the `MitkWorkbench` binary directly.

## Try the examples

In the Workbench:

1. Open **Window > Views > Example View** (category "Examples"). Load any image,
   select it in the Example View, set an offset, and press "Add Offset" to run
   the [example image filter](02-tour-of-the-examples.md#example-image-filter).
   The result carries an interactor: Ctrl-click in the image to paint.
2. Load the custom data type: open the bundled sample file
   [`points.exampledata`](points.exampledata) (File > Open, or drag it onto a
   render window). It is plain text with one `label x y z` per line:

   ```
   # label x y z
   origin 0 0 0
   right 50 0 0
   up 0 50 0
   ```

   The points render as spheres in the 2D and 3D windows, drawn by the
   [custom mappers](02-tour-of-the-examples.md#custom-data-type-io-and-mappers).

## Run the command-line app

`ExampleCmdApp` (in `MITK-build/bin`) adds an offset to every voxel of an image:

```bash
ExampleCmdApp -i input.nrrd -o output.nrrd -f 100
```

Run it without arguments to print the full help.

## Run the tests

Build the inner tree with testing enabled (`BUILD_TESTING=ON` in the
`MITK-build` CMake cache), then run the template's tests through `ctest`:

```bash
cd MITK-superbuild/MITK-build
ctest -C Release -R Example
```

This runs the [example unit tests](02-tour-of-the-examples.md#unit-tests) (the
image-filter test and the IO round-trip test). Always run tests through `ctest`,
never the test-driver executables directly.
