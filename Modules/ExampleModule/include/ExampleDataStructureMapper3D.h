/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef ExampleDataStructureMapper3D_h
#define ExampleDataStructureMapper3D_h

#include <mitkLocalStorageHandler.h>
#include <mitkVtkMapper.h>

#include <MitkExampleModuleExports.h>

#include <vtkSmartPointer.h>

class vtkPropAssembly;

// Renders an ExampleDataStructure as sphere glyphs in the 3D render window.
//
// This mapper follows the modern MITK mapper pattern:
//   - every VTK object lives in a per-renderer LocalStorage, never as a member
//     of the mapper itself (so the same data can render independently in each
//     render window),
//   - GetVtkProp() is a trivial per-renderer lookup,
//   - the VTK pipeline is (re)built in GenerateDataForRenderer() and only when
//     the data has actually changed.
class MITKEXAMPLEMODULE_EXPORT ExampleDataStructureMapper3D : public mitk::VtkMapper
{
public:
  mitkClassMacro(ExampleDataStructureMapper3D, mitk::VtkMapper)
  itkFactorylessNewMacro(Self)

  // Register the default rendering properties on a node. Applied via the
  // mapper provider registered in ExampleModuleActivator, so that even a
  // freshly loaded node looks right.
  static void SetDefaultProperties(mitk::DataNode* node, mitk::BaseRenderer* renderer = nullptr, bool overwrite = false);

  vtkProp* GetVtkProp(mitk::BaseRenderer* renderer) override;

protected:
  ExampleDataStructureMapper3D();
  ~ExampleDataStructureMapper3D() override;

  void GenerateDataForRenderer(mitk::BaseRenderer* renderer) override;

private:
  class LocalStorage : public mitk::Mapper::BaseLocalStorage
  {
  public:
    LocalStorage();
    ~LocalStorage() override;

    vtkSmartPointer<vtkPropAssembly> m_PropAssembly;
  };

  mitk::LocalStorageHandler<LocalStorage> m_LocalStorageHandler;
};

#endif
