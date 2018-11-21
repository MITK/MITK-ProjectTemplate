The MITK Project Template
=========================

This project provides a complete CMake-based set-up to get started with [MITK](http://mitk.org).

Features
--------

- Example module
  - ITK-based image filter
  - Interactor to paint in images
- Example command-line app
  - Uses the image filter of the example module
- Example plugin
  - GUI for the image filter and interactor of the example module
- Example external project
  - Microsoft's Guidelines Support Library (GSL)

What's new in v2018.04
----------------------

The project template was completely restructured to fit the new extension
mechanism of MITK v2018.04. Here's how it basically works:

1. Clone MITK
2. Clone MITK-ProjectTemplate
3. Configure the MITK superbuild and set the advanced CMake cache variable `MITK_EXTENSION_DIRS` to your working copy of the project template
4. Generate and build the MITK superbuild

The project template is now integrated right into the MITK superbuild and MITK build. Thus you can extend MITK with your own modules, plugins, command-line apps, and external projects without touching the MITK source code. There is no need for a super-superbuild anymore.

Supported platforms and other requirements
------------------------------------------

See the [MITK documentation](http://docs.mitk.org/2018.04/).
