/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef ExampleImageInteractor_h
#define ExampleImageInteractor_h

#include <mitkDataInteractor.h>
#include <itkIndex.h>

#include <MitkExampleModuleExports.h>

// See ExampleImageFilter.h for details on typical class declarations
// in MITK. The actual functionality of this class is commented in its
// implementation file.

class MITKEXAMPLEMODULE_EXPORT ExampleImageInteractor final : public mitk::DataInteractor
{
public:
  mitkClassMacro(ExampleImageInteractor, DataInteractor)
  itkFactorylessNewMacro(Self)

private:
  ExampleImageInteractor();
  ~ExampleImageInteractor();

  void ConnectActionsAndFunctions() override;
  void DataNodeChanged() override;

  void Paint(mitk::StateMachineAction* action, mitk::InteractionEvent* event);

  itk::Index<3> m_LastPixelIndex;
};

#endif
