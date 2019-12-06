/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include <ExampleSegTool2D.h>

#include <usGetModuleContext.h>
#include <usModuleResource.h>

MITK_TOOL_MACRO(MITKEXAMPLEMODULE_EXPORT, ExampleSegTool2D, "Example tool");

ExampleSegTool2D::ExampleSegTool2D()
  : SegTool2D("Paint", us::GetModuleContext()->GetModule())
{
}

ExampleSegTool2D::~ExampleSegTool2D()
{
}

void ExampleSegTool2D::ConnectActionsAndFunctions()
{
  CONNECT_FUNCTION("paint", Paint)
}

void ExampleSegTool2D::Paint(mitk::StateMachineAction*, mitk::InteractionEvent*)
{
  MITK_INFO << "Hello from the other side!";
}

us::ModuleResource ExampleSegTool2D::GetIconResource() const
{
  auto moduleContext = us::GetModuleContext();
  auto module = moduleContext->GetModule();
  auto resource = module->GetResource("ExampleIcon.svg");
  return resource;
}

const char *ExampleSegTool2D::GetName() const
{
  return "Example";
}

const char **ExampleSegTool2D::GetXPM() const
{
  return nullptr;
}
