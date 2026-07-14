/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include <ExampleDataStructureMapper2D.h>

#include "ExampleDataStructureMapperHelper.h"

#include <ExampleDataStructure.h>

#include <mitkBaseRenderer.h>
#include <mitkDataNode.h>

#include <vtkActor.h>
#include <vtkPropAssembly.h>

#include <cmath>

ExampleDataStructureMapper2D::LocalStorage::LocalStorage()
  : m_PropAssembly(vtkSmartPointer<vtkPropAssembly>::New())
{
}

ExampleDataStructureMapper2D::LocalStorage::~LocalStorage()
{
}

ExampleDataStructureMapper2D::ExampleDataStructureMapper2D()
{
}

ExampleDataStructureMapper2D::~ExampleDataStructureMapper2D()
{
}

void ExampleDataStructureMapper2D::SetDefaultProperties(mitk::DataNode* node, mitk::BaseRenderer* renderer, bool overwrite)
{
  ExampleDataStructureMapperHelper::SetDefaultProperties(node, renderer, overwrite);
  Superclass::SetDefaultProperties(node, renderer, overwrite);
}

vtkProp* ExampleDataStructureMapper2D::GetVtkProp(mitk::BaseRenderer* renderer)
{
  return m_LocalStorageHandler.GetLocalStorage(renderer)->m_PropAssembly.GetPointer();
}

void ExampleDataStructureMapper2D::GenerateDataForRenderer(mitk::BaseRenderer* renderer)
{
  auto* localStorage = m_LocalStorageHandler.GetLocalStorage(renderer);
  auto* node = this->GetDataNode();

  const auto* planeGeometry = renderer->GetCurrentWorldPlaneGeometry();

  if (planeGeometry == nullptr)
    return;

  // Rebuild when the data changed, a node property (color, opacity, ...)
  // changed, or the user scrolled to a different slice.
  const auto& lastGenerateTime = localStorage->GetLastGenerateDataTime();

  const bool sliceChanged = localStorage->m_LastPlaneGeometry.IsNull() ||
                            !localStorage->m_LastPlaneGeometry->IsOnPlane(planeGeometry);

  const bool needsUpdate =
    sliceChanged ||
    localStorage->IsGenerateDataRequired(renderer, this, node) ||
    lastGenerateTime < node->GetMTime() ||
    lastGenerateTime < node->GetPropertyList()->GetMTime() ||
    lastGenerateTime < node->GetPropertyList(renderer)->GetMTime();

  if (!needsUpdate)
    return;

  // Clone the plane so we can detect a slice change on the next call.
  localStorage->m_LastPlaneGeometry = planeGeometry->Clone();

  auto propAssembly = vtkSmartPointer<vtkPropAssembly>::New();

  if (node->IsVisible(renderer))
  {
    auto* data = dynamic_cast<ExampleDataStructure*>(node->GetData());

    if (data != nullptr && data->GetNumberOfPoints() != 0)
    {
      // Show a point only on the slices it actually touches, i.e. where its
      // distance to the slice plane is within the point radius.
      std::vector<ExampleDataStructure::LabeledPoint> pointsOnSlice;

      for (const auto& point : data->GetPoints())
      {
        if (std::abs(planeGeometry->SignedDistance(point.position)) <= ExampleDataStructure::POINT_RADIUS)
          pointsOnSlice.push_back(point);
      }

      if (!pointsOnSlice.empty())
      {
        auto actor = ExampleDataStructureMapperHelper::CreateGlyphActor(pointsOnSlice, ExampleDataStructure::POINT_RADIUS);
        this->ApplyColorAndOpacityProperties(renderer, actor);

        propAssembly->AddPart(actor);
      }
    }
  }

  localStorage->m_PropAssembly = propAssembly;
  localStorage->UpdateGenerateDataTime();
}
