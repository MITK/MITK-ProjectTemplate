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
