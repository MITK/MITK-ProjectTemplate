/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include "MainWindow.h"

#include <QmitkIOUtil.h>
#include <QmitkStdMultiWidget.h>

#include <QFileDialog>
#include <QMenuBar>

MainWindow::MainWindow()
  : m_DataStorage(mitk::StandaloneDataStorage::New()),
    m_MultiWidget(new QmitkStdMultiWidget(this))
{
  setWindowTitle("ExampleApp");
  resize(800, 600);

  auto openAction = new QAction(tr("&Open..."), this);
  openAction->setShortcut(QKeySequence::Open);
  connect(openAction, &QAction::triggered, this, &MainWindow::OnOpenFile);

  auto fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(openAction);

  m_MultiWidget->SetDataStorage(m_DataStorage);
  m_MultiWidget->InitializeMultiWidget();
  m_MultiWidget->AddPlanesToDataStorage();

  setCentralWidget(m_MultiWidget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::OnOpenFile()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"));

  if (fileName.isEmpty())
    return;

  try
  {
    QmitkIOUtil::Load(fileName, *m_DataStorage, this);
  }
  catch (const mitk::Exception& e)
  {
    MITK_ERROR << e.GetDescription();
    return;
  }

  m_MultiWidget->ResetCrosshair();
  m_MultiWidget->RequestUpdateAll();
}
