/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include <ExampleDataStructure.h>

#include <mitkGeometry3D.h>
#include <mitkLog.h>

#include <algorithm>
#include <cmath>

ExampleDataStructure::ExampleDataStructure()
{
}

ExampleDataStructure::ExampleDataStructure(const Self& other)
  : mitk::BaseData(other),
    m_Points(other.m_Points)
{
}

ExampleDataStructure::~ExampleDataStructure()
{
}

void ExampleDataStructure::AddPoint(const std::string& label, const mitk::Point3D& position)
{
  m_Points.push_back({label, position});
  this->Modified();
}

std::size_t ExampleDataStructure::GetNumberOfPoints() const
{
  return m_Points.size();
}

const std::vector<ExampleDataStructure::LabeledPoint>& ExampleDataStructure::GetPoints() const
{
  return m_Points;
}

void ExampleDataStructure::Clear()
{
  m_Points.clear();
  this->Modified();
}

void ExampleDataStructure::UpdateOutputInformation()
{
  // Rebuild the geometry so its bounding box tightly contains all points.
  // A valid bounding box is what lets the render windows frame the data (for
  // example when the user hits "Reinit" in the Data Manager).
  auto geometry = mitk::Geometry3D::New();
  geometry->Initialize(); // identity index-to-world, so index == world below

  if (!m_Points.empty())
  {
    auto min = m_Points.front().position;
    auto max = min;

    for (const auto& point : m_Points)
    {
      for (unsigned int i = 0; i < 3; ++i)
      {
        min[i] = std::min(min[i], point.position[i]);
        max[i] = std::max(max[i], point.position[i]);
      }
    }

    // Pad by the point radius so the box contains the spheres the mappers draw,
    // not just the bare point centers.
    mitk::Geometry3D::BoundsArrayType bounds;
    bounds[0] = min[0] - ExampleDataStructure::POINT_RADIUS;
    bounds[1] = max[0] + ExampleDataStructure::POINT_RADIUS;
    bounds[2] = min[1] - ExampleDataStructure::POINT_RADIUS;
    bounds[3] = max[1] + ExampleDataStructure::POINT_RADIUS;
    bounds[4] = min[2] - ExampleDataStructure::POINT_RADIUS;
    bounds[5] = max[2] + ExampleDataStructure::POINT_RADIUS;

    geometry->SetBounds(bounds);
  }

  this->SetGeometry(geometry);
}

void ExampleDataStructure::SetRequestedRegionToLargestPossibleRegion()
{
}

bool ExampleDataStructure::RequestedRegionIsOutsideOfTheBufferedRegion()
{
  return false;
}

bool ExampleDataStructure::VerifyRequestedRegion()
{
  return true;
}

void ExampleDataStructure::SetRequestedRegion(const itk::DataObject*)
{
}

bool Equal(const ExampleDataStructure* leftHandSide,
           const ExampleDataStructure* rightHandSide,
           mitk::ScalarType eps,
           bool verbose)
{
  if (leftHandSide == nullptr || rightHandSide == nullptr)
  {
    if (verbose)
      MITK_INFO << "[Equal(ExampleDataStructure)] At least one argument is null.";

    return false;
  }

  if (leftHandSide->GetNumberOfPoints() != rightHandSide->GetNumberOfPoints())
  {
    if (verbose)
      MITK_INFO << "[Equal(ExampleDataStructure)] Different number of points.";

    return false;
  }

  const auto& leftPoints = leftHandSide->GetPoints();
  const auto& rightPoints = rightHandSide->GetPoints();

  for (std::size_t i = 0; i < leftPoints.size(); ++i)
  {
    if (leftPoints[i].label != rightPoints[i].label)
    {
      if (verbose)
        MITK_INFO << "[Equal(ExampleDataStructure)] Labels differ at index " << i << ".";

      return false;
    }

    for (unsigned int dim = 0; dim < 3; ++dim)
    {
      if (std::abs(leftPoints[i].position[dim] - rightPoints[i].position[dim]) > eps)
      {
        if (verbose)
          MITK_INFO << "[Equal(ExampleDataStructure)] Coordinates differ at index " << i << ".";

        return false;
      }
    }
  }

  return true;
}
