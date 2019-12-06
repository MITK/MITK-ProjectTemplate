/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef ExampleSegTool2D_h
#define ExampleSegTool2D_h

#include <mitkSegTool2D.h>
#include <MitkExampleModuleExports.h>

namespace us
{
  class ModuleResource;
}

// This is an example on how to add a segmentation tool to the standard
// MITK Segmentation Views. Here's the crucial points to make it work:
//
//   * The name of the class MUST end in either SegTool2D or SegTool3D
//
//   * Derive directly or indirectly from mitk::Tool, for example
//     mitk::SegTool2D is a typical choice for 2d tools and
//     mitk::AutoSegmentationTool is a typical choice for 3d tools.
//
//   * Don't forget the MITK_TOOL_MACRO in the implementation file
//
//   * You don't have to provide your own state machine if the state
//     machines of the MitkSegmentation module are sufficient, but if
//     you do, you MUST provide both, the state machine and an event
//     config file, for example Paint.xml and PaintConfig.xml. The
//     file name of the event config file MUST be "equal" to the file
//     name of the state machine, suffixed by Config.xml instead of
//     .xml. The file name is passed to the base class constructor
//     without any extension, for example simply "Paint".
//
//   * Look into ExampleSegTool2DGUI.h for an example of how to provide
//     a custom tool GUI. The naming is important and basically "equals"
//     the class name of the tool class, suffixed by GUI. Don't forget
//     the MITK_TOOL_GUI_MACRO in the implementation file of the tool GUI.
//
//   * Ensure that the module containing your tool is loaded at runtime
//     before the MITK Segmentation Views are opened. Otherwise it cannot
//     be found. One way is to call anything from that module in a plugin
//     with eager activation policy. Such plugins are loaded very early
//     in MITK. For an example of how this works, look into ExampleModule.h
//     and the org_mitk_exampleplugin_eageractivation plugin.

class MITKEXAMPLEMODULE_EXPORT ExampleSegTool2D : public mitk::SegTool2D
{
public:
  mitkClassMacro(ExampleSegTool2D, SegTool2D)
  itkFactorylessNewMacro(Self)

  us::ModuleResource GetIconResource() const override;
  const char *GetName() const override;
  const char **GetXPM() const override;

protected:
  ExampleSegTool2D();
  ~ExampleSegTool2D() override;

  virtual void Paint(mitk::StateMachineAction* action, mitk::InteractionEvent* event);

private:
  void ConnectActionsAndFunctions() override;
};

#endif
