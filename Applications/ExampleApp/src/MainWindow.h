/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef MainWindow_h
#define MainWindow_h

#include <mitkStandaloneDataStorage.h>
#include <QMainWindow>

class QmitkStdMultiWidget;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow();
  ~MainWindow() override;

private:
  void OnOpenFile();

  mitk::StandaloneDataStorage::Pointer m_DataStorage;
  QmitkStdMultiWidget* m_MultiWidget;
};

#endif
