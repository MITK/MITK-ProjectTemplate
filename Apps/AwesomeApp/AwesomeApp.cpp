/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Module:    $RCSfile$
Language:  C++
Date:      $Date$
Version:   $Revision: 13820 $

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/ for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include <mitkBaseApplication.h>

#include <QVariant>

int main(int argc, char** argv)
{
  mitk::BaseApplication myApp(argc, argv);
  myApp.setApplicationName("AwesomeApp");
  myApp.setOrganizationName("AwesomeOrg");

  // -------------------------------------------------------------------
  // Here you can switch to your customizable application:
  // -------------------------------------------------------------------

  myApp.setProperty(mitk::BaseApplication::PROP_APPLICATION, "org.mitk.qt.extapplication");
  //myApp.setProperty(mitk::BaseApplication::PROP_APPLICATION, "my.awesomeproject.exampleapp");
  return myApp.run();
}
