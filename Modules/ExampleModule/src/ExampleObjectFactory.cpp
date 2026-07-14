/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include "ExampleObjectFactory.h"

#include <ExampleDataStructure.h>
#include <ExampleDataStructureMapper2D.h>
#include <ExampleDataStructureMapper3D.h>

#include <mitkBaseRenderer.h>
#include <mitkCoreObjectFactory.h>
#include <mitkDataNode.h>

ExampleObjectFactory::ExampleObjectFactory()
{
}

ExampleObjectFactory::~ExampleObjectFactory()
{
}

mitk::Mapper::Pointer ExampleObjectFactory::CreateMapper(mitk::DataNode* node, MapperSlotId slotId)
{
  mitk::Mapper::Pointer mapper;

  if (dynamic_cast<ExampleDataStructure*>(node->GetData()) != nullptr)
  {
    if (slotId == mitk::BaseRenderer::Standard2D)
      mapper = ExampleDataStructureMapper2D::New();
    else if (slotId == mitk::BaseRenderer::Standard3D)
      mapper = ExampleDataStructureMapper3D::New();

    if (mapper.IsNotNull())
      mapper->SetDataNode(node);
  }

  return mapper;
}

void ExampleObjectFactory::SetDefaultProperties(mitk::DataNode* node)
{
  if (dynamic_cast<ExampleDataStructure*>(node->GetData()) == nullptr)
    return;

  ExampleDataStructureMapper2D::SetDefaultProperties(node);
  ExampleDataStructureMapper3D::SetDefaultProperties(node);
}

namespace
{
  // Registering the factory in the constructor of a file-scope static object
  // means it happens automatically as soon as MitkExampleModule is loaded into
  // the process, with no explicit call from anywhere. The autoloaded IO
  // submodule (see autoload/IO) depends on this module, so the module - and
  // hence this registration - is guaranteed to be loaded at application start.
  class RegisterExampleObjectFactory
  {
  public:
    RegisterExampleObjectFactory()
      : m_Factory(ExampleObjectFactory::New())
    {
      mitk::CoreObjectFactory::GetInstance()->RegisterExtraFactory(m_Factory);
    }

    ~RegisterExampleObjectFactory()
    {
      mitk::CoreObjectFactory::GetInstance()->UnRegisterExtraFactory(m_Factory);
    }

  private:
    ExampleObjectFactory::Pointer m_Factory;
  };

  RegisterExampleObjectFactory registerExampleObjectFactory;
}
