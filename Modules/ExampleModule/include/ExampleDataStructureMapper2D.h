/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef ExampleDataStructureMapper2D_h
#define ExampleDataStructureMapper2D_h

#include <mitkLocalStorageHandler.h>
#include <mitkPlaneGeometry.h>
#include <mitkVtkMapper.h>

#include <MitkExampleModuleExports.h>

#include <vtkSmartPointer.h>

class vtkPropAssembly;

// Renders an ExampleDataStructure in the 2D slice views.
//
// It uses the same per-renderer LocalStorage pattern as the 3D mapper. The one
// thing that makes a mapper "2D" is that it reacts to the current slice: here
// we only draw the points that are close enough to the slice plane to touch it.
// The LocalStorage therefore also caches the last slice so we can skip
// rebuilding when neither the data nor the slice changed.
class MITKEXAMPLEMODULE_EXPORT ExampleDataStructureMapper2D : public mitk::VtkMapper
{
public:
  mitkClassMacro(ExampleDataStructureMapper2D, mitk::VtkMapper)
  itkFactorylessNewMacro(Self)

  static void SetDefaultProperties(mitk::DataNode* node, mitk::BaseRenderer* renderer = nullptr, bool overwrite = false);

  vtkProp* GetVtkProp(mitk::BaseRenderer* renderer) override;

protected:
  ExampleDataStructureMapper2D();
  ~ExampleDataStructureMapper2D() override;

  void GenerateDataForRenderer(mitk::BaseRenderer* renderer) override;

private:
  class LocalStorage : public mitk::Mapper::BaseLocalStorage
  {
  public:
    LocalStorage();
    ~LocalStorage() override;

    vtkSmartPointer<vtkPropAssembly> m_PropAssembly;
    mitk::PlaneGeometry::ConstPointer m_LastPlaneGeometry;
  };

  mitk::LocalStorageHandler<LocalStorage> m_LocalStorageHandler;
};

#endif
