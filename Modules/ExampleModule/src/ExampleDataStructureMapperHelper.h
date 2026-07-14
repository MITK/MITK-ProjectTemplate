/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef ExampleDataStructureMapperHelper_h
#define ExampleDataStructureMapperHelper_h

#include <ExampleDataStructure.h>

#include <vtkSmartPointer.h>

#include <vector>

namespace mitk
{
  class DataNode;
  class BaseRenderer;
}

class vtkActor;

// Rendering code shared by the 2D and 3D example mappers. Factoring it out
// keeps the two mappers small and consistent, mirroring how MITK's own ROI
// module shares a helper between its mappers.
namespace ExampleDataStructureMapperHelper
{
  // Build an actor that draws each of the given points as a sphere of the
  // given radius (in millimeters). The points are expected in world
  // coordinates, so the actor can be rendered directly in both the 2D slice
  // views and the 3D view without any additional transform.
  vtkSmartPointer<vtkActor> CreateGlyphActor(const std::vector<ExampleDataStructure::LabeledPoint>& points, float radius);

  // Register the rendering-related default properties (color, opacity) shared
  // by both mappers.
  void SetDefaultProperties(mitk::DataNode* node, mitk::BaseRenderer* renderer, bool overwrite);
}

#endif
