/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include "ExampleDataStructureWriter.h"

#include "ExampleIOMimeTypes.h"

#include <ExampleDataStructure.h>

#include <mitkCustomMimeType.h>
#include <mitkExceptionMacro.h>

#include <fstream>

ExampleDataStructureWriter::ExampleDataStructureWriter()
  : mitk::AbstractFileWriter(ExampleDataStructure::GetStaticNameOfClass(),
                             mitk::CustomMimeType(ExampleIOMimeTypes::EXAMPLEDATA_MIMETYPE()),
                             "Writer for example labeled-point data")
{
  this->RegisterService();
}

ExampleDataStructureWriter::ExampleDataStructureWriter(const ExampleDataStructureWriter& other)
  : mitk::AbstractFileWriter(other)
{
}

void ExampleDataStructureWriter::Write()
{
  auto* input = dynamic_cast<const ExampleDataStructure*>(this->GetInput());

  if (input == nullptr)
    mitkThrow() << "Input to ExampleDataStructureWriter is not an ExampleDataStructure.";

  std::ofstream file(this->GetOutputLocation());

  if (!file.is_open())
    mitkThrow() << "Could not open file \"" << this->GetOutputLocation() << "\" for writing.";

  // One "label x y z" per line, with a comment header so the file is
  // self-explanatory when opened in a text editor.
  file << "# ExampleDataStructure: one \"label x y z\" per line\n";

  for (const auto& point : input->GetPoints())
    file << point.label << ' ' << point.position[0] << ' ' << point.position[1] << ' ' << point.position[2] << '\n';
}

ExampleDataStructureWriter* ExampleDataStructureWriter::Clone() const
{
  return new ExampleDataStructureWriter(*this);
}
