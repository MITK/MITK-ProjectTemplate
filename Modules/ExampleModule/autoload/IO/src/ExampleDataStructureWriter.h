/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef ExampleDataStructureWriter_h
#define ExampleDataStructureWriter_h

#include <mitkAbstractFileWriter.h>

// The counterpart to ExampleDataStructureReader: writes an ExampleDataStructure
// back to a .exampledata text file. Also registered by ExampleModuleIOActivator.
class ExampleDataStructureWriter : public mitk::AbstractFileWriter
{
public:
  ExampleDataStructureWriter();

  using AbstractFileWriter::Write;
  void Write() override;

private:
  ExampleDataStructureWriter(const ExampleDataStructureWriter& other);
  ExampleDataStructureWriter* Clone() const override;
};

#endif
