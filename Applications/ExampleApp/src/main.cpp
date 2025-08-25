/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include "MainWindow.h"
#include <QApplication>

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  MainWindow window;
  window.show();

  return app.exec();
}
