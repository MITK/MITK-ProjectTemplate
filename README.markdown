The MITK Project Template
=========================

This project provides a complete CMake-based set-up to get easily started
with using [MITK](http://www.mitk.org) and extending it via plug-ins and modules.

Provided Features
-----------------

- Superbuild: Let your project download, configure, and build its dependencies automatically.
- CTK Plug-ins: Easily integrate new CTK-based plug-ins.
- Deployment: Create deployable packages of your project

Getting Started
---------------

This is a *template*. You must modify it such that it fits the needs of your particular project.

Especially you should do a global search and replace for the string "awesome" to rename the template application and plug-in. You may want to rename some files too.

You can download a [tarball](https://github.com/MITK/MITK-ProjectTemplate/tarball/master) or [zipball](https://github.com/MITK/MITK-ProjectTemplate/zipball/master) which contains the current sources. You should only clone this repository (or fork it on github) if you want to work with the project template itself (i.e. by contributing improvements).

Please read [How to create a new MITK project](http://docs.mitk.org/nightly/HowToNewProject.html) for build instructions.

Supported Platforms
-------------------

- Linux
- Windows XP or newer with Visual Studio 2012
- MacOSX 10.9 or newer

Requirements
------------

- CMake 3.2 or newer
- Qt 5.0 to Qt 5.5
- It is also possible to create an MITK project without any Qt dependencies
