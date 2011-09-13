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

#include <berryStarter.h>
#include <Poco/Util/MapConfiguration.h>

#include <QApplication>

int main(int argc, char** argv)
{
  // Create a QApplication instance first
  QApplication myApp(argc, argv);
  myApp.setApplicationName("AwesomeApp");
  myApp.setOrganizationName("AwesomeOrg");

  // These paths replace the .ini file and are tailored for installation
  // packages created with CPack. If a .ini file is presented, it will
  // overwrite the settings in MapConfiguration
  Poco::Path basePath(argv[0]);
  basePath.setFileName("");
  
  Poco::Path provFile(basePath);
  provFile.setFileName("AwesomeApp.provisioning");

  Poco::Util::MapConfiguration* sbConfig(new Poco::Util::MapConfiguration());
  sbConfig->setString(berry::Platform::ARG_PROVISIONING, provFile.toString());
  // -------------------------------------------------------------------
  // Here you can switch to your customizable application:
  // -------------------------------------------------------------------
  sbConfig->setString(berry::Platform::ARG_APPLICATION, "org.mitk.qt.extapplication");
//  sbConfig->setString(berry::Platform::ARG_APPLICATION, "my.awesomeproject.exampleapp");
  return berry::Starter::Run(argc, argv, sbConfig);
}
