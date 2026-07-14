/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef ExampleObjectFactory_h
#define ExampleObjectFactory_h

#include <mitkCoreObjectFactoryBase.h>

// This factory teaches MITK how to render our custom data type. Registering it
// with the CoreObjectFactory (see the .cpp) is what makes MITK pick the right
// mapper for an ExampleDataStructure node in each render window - including a
// node that was just loaded from a file, which no view had a chance to touch.
class ExampleObjectFactory : public mitk::CoreObjectFactoryBase
{
public:
  mitkClassMacro(ExampleObjectFactory, mitk::CoreObjectFactoryBase)
  itkFactorylessNewMacro(Self)

  mitk::Mapper::Pointer CreateMapper(mitk::DataNode* node, MapperSlotId slotId) override;
  void SetDefaultProperties(mitk::DataNode* node) override;

protected:
  ExampleObjectFactory();
  ~ExampleObjectFactory() override;
};

#endif
