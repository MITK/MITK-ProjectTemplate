/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include "ExampleDataStructureReader.h"
#include "ExampleDataStructureWriter.h"
#include "ExampleIOMimeTypes.h"

#include <mitkCustomMimeType.h>

#include <usModuleActivator.h>
#include <usModuleContext.h>

#include <memory>
#include <vector>

// Loading this (autoloaded) module registers the reader, the writer, and the
// MIME type as micro-services. From then on, .exampledata files can be loaded
// and saved everywhere in MITK - the Data Manager, drag and drop, the
// command-line IO utilities - without any further setup by the user.
class ExampleModuleIOActivator : public us::ModuleActivator
{
public:
  void Load(us::ModuleContext* context) override
  {
    m_MimeTypes = ExampleIOMimeTypes::Get();

    us::ServiceProperties properties;
    properties[us::ServiceConstants::SERVICE_RANKING()] = 10;

    for (auto* mimeType : m_MimeTypes)
      context->RegisterService(mimeType, properties);

    // The reader and writer register themselves with MITK in their
    // constructors; the activator only has to keep them alive.
    m_Reader = std::make_unique<ExampleDataStructureReader>();
    m_Writer = std::make_unique<ExampleDataStructureWriter>();
  }

  void Unload(us::ModuleContext*) override
  {
    for (auto* mimeType : m_MimeTypes)
      delete mimeType;

    m_MimeTypes.clear();

    m_Reader.reset();
    m_Writer.reset();
  }

private:
  std::unique_ptr<ExampleDataStructureReader> m_Reader;
  std::unique_ptr<ExampleDataStructureWriter> m_Writer;
  std::vector<mitk::CustomMimeType*> m_MimeTypes;
};

US_EXPORT_MODULE_ACTIVATOR(ExampleModuleIOActivator)
