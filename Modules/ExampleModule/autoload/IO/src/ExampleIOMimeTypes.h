/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef ExampleIOMimeTypes_h
#define ExampleIOMimeTypes_h

#include <mitkCustomMimeType.h>

#include <string>
#include <vector>

// A MIME type ties a file (by extension and, optionally, content) to the reader
// and writer that can handle it. Defining it in one place keeps the reader and
// writer from drifting apart.
class ExampleIOMimeTypes
{
public:
  static mitk::CustomMimeType EXAMPLEDATA_MIMETYPE();
  static std::string EXAMPLEDATA_MIMETYPE_NAME();

  // All MIME types provided by this module. The activator registers each one.
  static std::vector<mitk::CustomMimeType*> Get();

  ExampleIOMimeTypes() = delete;
  ExampleIOMimeTypes(const ExampleIOMimeTypes&) = delete;
};

#endif
