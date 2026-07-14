/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include "ExampleDataStructureReader.h"

#include "ExampleIOMimeTypes.h"

#include <ExampleDataStructure.h>

#include <mitkCustomMimeType.h>
#include <mitkExceptionMacro.h>
#include <mitkLog.h>

#include <fstream>
#include <sstream>

ExampleDataStructureReader::ExampleDataStructureReader()
  : mitk::AbstractFileReader(mitk::CustomMimeType(ExampleIOMimeTypes::EXAMPLEDATA_MIMETYPE()),
                             "Reader for example labeled-point data")
{
  // Announce this reader to MITK. Without this call the reader exists but no
  // one would ever ask it to read anything.
  this->RegisterService();
}

ExampleDataStructureReader::ExampleDataStructureReader(const ExampleDataStructureReader& other)
  : mitk::AbstractFileReader(other)
{
}

std::vector<mitk::BaseData::Pointer> ExampleDataStructureReader::DoRead()
{
  std::ifstream file(this->GetInputLocation());

  if (!file.is_open())
    mitkThrow() << "Could not open file \"" << this->GetInputLocation() << "\" for reading.";

  auto data = ExampleDataStructure::New();

  std::string line;

  while (std::getline(file, line))
  {
    // Skip blank lines and comments (see the writer for the format).
    if (line.empty() || line.front() == '#')
      continue;

    std::istringstream stream(line);
    std::string label;
    mitk::Point3D position;

    if (stream >> label >> position[0] >> position[1] >> position[2])
      data->AddPoint(label, position);
    else
      MITK_WARN << "Ignoring malformed line in \"" << this->GetInputLocation() << "\": " << line;
  }

  return {data.GetPointer()};
}

ExampleDataStructureReader* ExampleDataStructureReader::Clone() const
{
  return new ExampleDataStructureReader(*this);
}
