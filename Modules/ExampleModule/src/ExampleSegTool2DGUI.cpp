/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include <ExampleSegTool2DGUI.h>
#include <ui_ExampleSegTool2DGUI.h>

MITK_TOOL_GUI_MACRO(MITKEXAMPLEMODULE_EXPORT, ExampleSegTool2DGUI, "")

ExampleSegTool2DGUI::ExampleSegTool2DGUI()
  : m_Ui(new Ui::ExampleSegTool2DGUI)
{
  m_Ui->setupUi(this);
}

ExampleSegTool2DGUI::~ExampleSegTool2DGUI()
{
}
