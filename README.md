The MITK Project Template
=========================

This project provides a complete CMake-based set-up to get started with [MITK](https://github.com/MITK/MITK).

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

How it works
------------

1. Clone [MITK](https://github.com/MITK/MITK) and checkout the latest release tag or at least the stable master branch
2. Click on "Use this template", or clone/fork the MITK-ProjectTemplate, checking out the matching tag or branch
3. Configure the MITK superbuild and set the CMake cache variable `MITK_EXTENSION_DIRS` to your working copy of the project template
4. Generate and build the MITK superbuild

The project template is virtually integrated right into the MITK superbuild and MITK build as if it would be part of MITK. You can extend MITK with your own modules, plugins, command-line apps, and external projects without touching the MITK source code resp. repository.

Supported platforms and other requirements
------------------------------------------

See the [MITK documentation](http://docs.mitk.org/2022.10/).

License
-------

Copyright (c) [German Cancer Research Center (DKFZ)](https://www.dkfz.de)<br>
All rights reserved.

The MITK-ProjectTemplate is part of [MITK](https://github.com/MITK/MITK) and as such available as free open-source software under a [3-clause BSD license](https://github.com/MITK/MITK-ProjectTemplate/blob/master/LICENSE).
