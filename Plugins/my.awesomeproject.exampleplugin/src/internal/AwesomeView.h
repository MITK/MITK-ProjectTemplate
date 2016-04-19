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

#ifndef AwesomeView_h
#define AwesomeView_h

#include <berryISelectionListener.h>
#include <QmitkAbstractView.h>

#include <ui_AwesomeViewControls.h>

class AwesomeView : public QmitkAbstractView
{  
  Q_OBJECT
  
public:  
  static const std::string VIEW_ID;

  void CreateQtPartControl(QWidget* parent) override;

private slots:
  void ProcessSelectedImage();

private:
  void SetFocus() override;

  void OnSelectionChanged(
    berry::IWorkbenchPart::Pointer source,
    const QList<mitk::DataNode::Pointer>& dataNodes) override;

  Ui::AwesomeViewControls m_Controls;
};

#endif
