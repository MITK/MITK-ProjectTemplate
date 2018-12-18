/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#ifndef ExampleSegTool2D_h
#define ExampleSegTool2D_h

#include <mitkSegTool2D.h>
#include <MitkExampleModuleExports.h>

namespace us
{
  class ModuleResource;
}

class MITKEXAMPLEMODULE_EXPORT ExampleSegTool2D : public mitk::SegTool2D
{
public:
  mitkClassMacro(ExampleSegTool2D, SegTool2D)
  itkFactorylessNewMacro(Self)

  us::ModuleResource GetIconResource() const override;
  const char *GetName() const override;
  const char **GetXPM() const override;

  virtual void Paint(mitk::StateMachineAction* action, mitk::InteractionEvent* event);

protected:
  ExampleSegTool2D();
  ~ExampleSegTool2D() override;

  void ConnectActionsAndFunctions() override;
};

#endif
