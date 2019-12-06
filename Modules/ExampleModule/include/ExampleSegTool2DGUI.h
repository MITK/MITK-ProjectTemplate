/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

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
