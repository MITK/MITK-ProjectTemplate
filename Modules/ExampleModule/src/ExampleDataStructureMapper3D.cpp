/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include <ExampleDataStructureMapper3D.h>

#include "ExampleDataStructureMapperHelper.h"

#include <ExampleDataStructure.h>

#include <mitkBaseRenderer.h>
#include <mitkDataNode.h>

#include <vtkActor.h>
#include <vtkPropAssembly.h>

ExampleDataStructureMapper3D::LocalStorage::LocalStorage()
  : m_PropAssembly(vtkSmartPointer<vtkPropAssembly>::New())
{
}

ExampleDataStructureMapper3D::LocalStorage::~LocalStorage()
{
}

ExampleDataStructureMapper3D::ExampleDataStructureMapper3D()
{
}

ExampleDataStructureMapper3D::~ExampleDataStructureMapper3D()
{
}

void ExampleDataStructureMapper3D::SetDefaultProperties(mitk::DataNode* node, mitk::BaseRenderer* renderer, bool overwrite)
{
  ExampleDataStructureMapperHelper::SetDefaultProperties(node, renderer, overwrite);
  Superclass::SetDefaultProperties(node, renderer, overwrite);
}

vtkProp* ExampleDataStructureMapper3D::GetVtkProp(mitk::BaseRenderer* renderer)
{
  return m_LocalStorageHandler.GetLocalStorage(renderer)->m_PropAssembly.GetPointer();
}

void ExampleDataStructureMapper3D::GenerateDataForRenderer(mitk::BaseRenderer* renderer)
{
  auto* localStorage = m_LocalStorageHandler.GetLocalStorage(renderer);
  auto* node = this->GetDataNode();

  // Rebuild when the data OR a node property (color, opacity, visibility, ...)
  // changed. IsGenerateDataRequired() only tracks the data, so we also compare
  // against the node and its property lists - otherwise a color change would
  // never reach the renderer.
  const auto& lastGenerateTime = localStorage->GetLastGenerateDataTime();

  const bool needsUpdate =
    localStorage->IsGenerateDataRequired(renderer, this, node) ||
    lastGenerateTime < node->GetMTime() ||
    lastGenerateTime < node->GetPropertyList()->GetMTime() ||
    lastGenerateTime < node->GetPropertyList(renderer)->GetMTime();

  if (!needsUpdate)
    return;

  auto propAssembly = vtkSmartPointer<vtkPropAssembly>::New();

  if (node->IsVisible(renderer))
  {
    auto* data = dynamic_cast<ExampleDataStructure*>(node->GetData());

    if (data != nullptr && data->GetNumberOfPoints() != 0)
    {
      auto actor = ExampleDataStructureMapperHelper::CreateGlyphActor(data->GetPoints(), ExampleDataStructure::POINT_RADIUS);
      this->ApplyColorAndOpacityProperties(renderer, actor);

      propAssembly->AddPart(actor);
    }
  }

  localStorage->m_PropAssembly = propAssembly;
  localStorage->UpdateGenerateDataTime();
}
