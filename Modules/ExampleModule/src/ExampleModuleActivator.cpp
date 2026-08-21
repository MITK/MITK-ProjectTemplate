/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include <ExampleDataStructure.h>
#include <ExampleDataStructureMapper2D.h>
#include <ExampleDataStructureMapper3D.h>

#include <mitkBaseRenderer.h>
#include <mitkMapperProviderBase.h>

#include <usModuleActivator.h>
#include <usModuleContext.h>

#include <memory>
#include <vector>

// The module activator runs when MitkExampleModule is loaded into the process.
// The autoloaded IO submodule (see autoload/IO) depends on this module, so the
// module - and hence this registration - is guaranteed to be loaded at
// application start.
//
// Registering a mitk::MapperProviderBase per mapper and render-window slot is
// what makes MITK pick the right mapper for an ExampleDataStructure node in
// each render window - including a node that was just loaded from a file,
// which no view had a chance to touch. It also applies the mappers' default
// properties whenever an ExampleDataStructure is assigned to a data node.
class ExampleModuleActivator : public us::ModuleActivator
{
public:
  void Load(us::ModuleContext*) override
  {
    m_MapperProviders.push_back(
      std::make_unique<mitk::MapperProviderBase<ExampleDataStructureMapper2D, ExampleDataStructure>>(
        mitk::BaseRenderer::Standard2D));
    m_MapperProviders.push_back(
      std::make_unique<mitk::MapperProviderBase<ExampleDataStructureMapper3D, ExampleDataStructure>>(
        mitk::BaseRenderer::Standard3D));
  }

  void Unload(us::ModuleContext*) override
  {
    // Destroying the providers unregisters them.
    m_MapperProviders.clear();
  }

private:
  std::vector<std::unique_ptr<mitk::IMapperProvider>> m_MapperProviders;
};

US_EXPORT_MODULE_ACTIVATOR(ExampleModuleActivator)
