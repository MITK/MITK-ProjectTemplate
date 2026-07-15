/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef ExampleDataStructure_h
#define ExampleDataStructure_h

#include <mitkBaseData.h>
#include <mitkPoint.h>

// As with the ExampleImageFilter, this CMake-generated header provides the
// export macro for everything that is part of this module's public interface.
#include <MitkExampleModuleExports.h>

#include <string>
#include <vector>

/** \brief A minimal custom data type: a list of labeled points in world space.
 *
 * This is the smallest data structure that is still interesting as an example.
 * It derives from mitk::BaseData just like mitk::Image or mitk::Surface do, so
 * it can be wrapped in a mitk::DataNode, stored in the DataStorage, saved and
 * loaded (see the reader and writer in the autoload/IO subdirectory), and
 * rendered (see ExampleDataStructureMapper2D and ExampleDataStructureMapper3D).
 *
 * All coordinates are in world (millimeter) space, which keeps this example
 * free of any reference image or index-to-world conversion.
 */
class MITKEXAMPLEMODULE_EXPORT ExampleDataStructure : public mitk::BaseData
{
public:
  // A single named point. A plain aggregate is enough here; there is no reason
  // to hide two public data members behind accessors.
  struct LabeledPoint
  {
    std::string label;
    mitk::Point3D position;
  };

  // Radius (in millimeters) each point is drawn with. It belongs to the data,
  // not to a render property, so UpdateOutputInformation() can pad the bounding
  // box to contain the drawn spheres and both mappers agree on the size.
  static constexpr double POINT_RADIUS = 5.0;

  // Every BaseData subclass needs these three macros: the class typedefs and
  // GetNameOfClass (mitkClassMacro), the static New() factory
  // (itkFactorylessNewMacro), and a type-safe Clone() (itkCloneMacro).
  mitkClassMacro(ExampleDataStructure, mitk::BaseData)
  itkFactorylessNewMacro(Self)
  itkCloneMacro(Self)

  // Append a labeled point in world coordinates.
  void AddPoint(const std::string& label, const mitk::Point3D& position);

  std::size_t GetNumberOfPoints() const;

  // Direct read access to the points, e.g. for the mappers and the writer.
  const std::vector<LabeledPoint>& GetPoints() const;

  void ClearPoints();

  // mitk::BaseData interface. The data lives entirely in main memory and is
  // not produced by a pipeline, so the region bookkeeping is trivial. The one
  // method that does real work is UpdateOutputInformation(), which refreshes
  // the geometry so the render windows can frame the points (e.g. on "Reinit").
  void UpdateOutputInformation() override;
  void SetRequestedRegionToLargestPossibleRegion() override;
  bool RequestedRegionIsOutsideOfTheBufferedRegion() override;
  bool VerifyRequestedRegion() override;
  void SetRequestedRegion(const itk::DataObject* referenceData) override;

protected:
  // itkCloneMacro delegates to InternalClone(), which mitkCloneMacro implements
  // by calling the copy constructor. Both stay protected to enforce creation
  // through New()/Clone().
  mitkCloneMacro(Self)

  ExampleDataStructure();
  ExampleDataStructure(const Self& other);
  ~ExampleDataStructure() override;

private:
  std::vector<LabeledPoint> m_Points;
};

/** \brief Return whether two ExampleDataStructures hold the same labeled points.
 *
 * Points are equal if their labels match and their coordinates differ by no
 * more than \p eps per component. Used by the IO round-trip test.
 */
MITKEXAMPLEMODULE_EXPORT bool Equal(const ExampleDataStructure* leftHandSide,
                                    const ExampleDataStructure* rightHandSide,
                                    mitk::ScalarType eps,
                                    bool verbose);

#endif
