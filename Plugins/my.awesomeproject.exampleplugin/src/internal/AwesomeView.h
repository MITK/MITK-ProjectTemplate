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

// There's an item "AwesomeViewControls.ui" in the UI_FILES list in
// files.cmake. The Qt UI Compiler will parse this file and generate a
// header file prefixed with "ui_", which is located in the build directory.
// Use Qt Creator to view and edit .ui files. The generated header file
// provides a class that contains all of the UI widgets.
#include <ui_AwesomeViewControls.h>

// All views in MITK derive from QmitkAbstractView. You have to override
// at least the two methods CreateQtPartControl() and SetFocus().
class AwesomeView : public QmitkAbstractView
{
  // As QmitkAbstractView derives from QObject and we want to use the Qt
  // signal and slot mechanism, we must not forget the Q_OBJECT macro.
  // This header file also has to be listed in MOC_H_FILES in files.cmake,
  // in order that the Qt Meta-Object Compiler can find and process this
  // class declaration.
  Q_OBJECT
  
public:
  // This is a tricky one and will give you some headache later on in
  // your debug sessions if it has been forgotten. Also, don't forget
  // to initialize it in the implementation file.
  static const std::string VIEW_ID;

  // In this method we initialize the GUI components and connect the
  // associated signals and slots.
  void CreateQtPartControl(QWidget* parent) override;

private slots:
  void ProcessSelectedImage();

private:
  // Typically a one-liner. Set the focus to the default widget.
  void SetFocus() override;

  // This method is conveniently called whenever the selection of Data Manager
  // items changes.
  void OnSelectionChanged(
    berry::IWorkbenchPart::Pointer source,
    const QList<mitk::DataNode::Pointer>& dataNodes) override;

  // Generated from the associated UI file, it encapsulates all the widgets
  // of our view.
  Ui::AwesomeViewControls m_Controls;
};

#endif
