/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef ExampleDataStructureReader_h
#define ExampleDataStructureReader_h

#include <mitkAbstractFileReader.h>
#include <mitkBaseData.h>

// A file reader is a micro-service. This one turns a .exampledata text file
// into an ExampleDataStructure. It is created and registered by
// ExampleModuleIOActivator when the module is loaded.
class ExampleDataStructureReader : public mitk::AbstractFileReader
{
public:
  ExampleDataStructureReader();

  using AbstractFileReader::Read;

protected:
  // Does the actual reading. The base class handles opening/closing streams,
  // error reporting to the user, and progress; we only produce the data.
  std::vector<mitk::BaseData::Pointer> DoRead() override;

private:
  ExampleDataStructureReader(const ExampleDataStructureReader& other);
  ExampleDataStructureReader* Clone() const override;
};

#endif
