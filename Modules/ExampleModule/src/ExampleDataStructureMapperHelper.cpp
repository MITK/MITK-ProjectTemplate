/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include "ExampleDataStructureMapperHelper.h"

#include <mitkColorProperty.h>
#include <mitkDataNode.h>
#include <mitkProperties.h>

#include <vtkActor.h>
#include <vtkGlyph3D.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkSphereSource.h>

vtkSmartPointer<vtkActor> ExampleDataStructureMapperHelper::CreateGlyphActor(
  const std::vector<ExampleDataStructure::LabeledPoint>& points, float radius)
{
  auto vtkPointData = vtkSmartPointer<vtkPoints>::New();

  for (const auto& point : points)
    vtkPointData->InsertNextPoint(point.position[0], point.position[1], point.position[2]);

  auto polyData = vtkSmartPointer<vtkPolyData>::New();
  polyData->SetPoints(vtkPointData);

  auto sphere = vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetRadius(radius);

  // vtkGlyph3D places a copy of the sphere at every point of the input.
  auto glyph = vtkSmartPointer<vtkGlyph3D>::New();
  glyph->SetInputData(polyData);
  glyph->SetSourceConnection(sphere->GetOutputPort());
  glyph->SetScaleModeToDataScalingOff(); // all spheres share the same radius

  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(glyph->GetOutputPort());
  // Color the glyphs from the actor's property (the node's "color"/"opacity"),
  // not from any scalars the pipeline might carry, so those properties work.
  mapper->ScalarVisibilityOff();

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  return actor;
}

void ExampleDataStructureMapperHelper::SetDefaultProperties(mitk::DataNode* node, mitk::BaseRenderer* renderer, bool overwrite)
{
  node->AddProperty("color", mitk::ColorProperty::New(1.0f, 1.0f, 0.0f), renderer, overwrite);
  node->AddProperty("opacity", mitk::FloatProperty::New(1.0f), renderer, overwrite);
}
