/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include "ExampleIOMimeTypes.h"

#include <mitkIOMimeTypes.h>

mitk::CustomMimeType ExampleIOMimeTypes::EXAMPLEDATA_MIMETYPE()
{
  mitk::CustomMimeType mimeType(EXAMPLEDATA_MIMETYPE_NAME());
  mimeType.SetCategory("Example Data");
  mimeType.SetComment("Example labeled points");
  mimeType.AddExtension("exampledata");
  return mimeType;
}

std::string ExampleIOMimeTypes::EXAMPLEDATA_MIMETYPE_NAME()
{
  // Build a unique name from MITK's default base name so it cannot clash with
  // the MIME types of other modules.
  static std::string name = mitk::IOMimeTypes::DEFAULT_BASE_NAME() + ".example.labeled-points";
  return name;
}

std::vector<mitk::CustomMimeType*> ExampleIOMimeTypes::Get()
{
  std::vector<mitk::CustomMimeType*> mimeTypes;
  mimeTypes.push_back(EXAMPLEDATA_MIMETYPE().Clone());
  return mimeTypes;
}
