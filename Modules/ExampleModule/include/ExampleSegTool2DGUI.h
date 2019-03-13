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

#ifndef ExampleSegTool2DGUI_h
#define ExampleSegTool2DGUI_h

#include <QmitkToolGUI.h>
#include <QScopedPointer>
#include <MitkExampleModuleExports.h>

namespace Ui
{
  class ExampleSegTool2DGUI;
}

// Look into ExampleSegTool2D.h for more information.

class MITKEXAMPLEMODULE_EXPORT ExampleSegTool2DGUI : public QmitkToolGUI
{
  Q_OBJECT

public:
  mitkClassMacro(ExampleSegTool2DGUI, QmitkToolGUI)
  itkFactorylessNewMacro(Self)

protected:
  ExampleSegTool2DGUI();
  ~ExampleSegTool2DGUI() override;

private:
  QScopedPointer<Ui::ExampleSegTool2DGUI> m_Ui;
};

#endif
