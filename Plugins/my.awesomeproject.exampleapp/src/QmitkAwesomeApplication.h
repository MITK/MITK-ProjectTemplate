/*=========================================================================
 
Program:   Medical Imaging & Interaction Toolkit
Language:  C++
Date:      $Date$
Version:   $Revision$
 
Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.
 
This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.
 
=========================================================================*/

#ifndef QMITKAWESOMEAPPLICATION_H_
#define QMITKAWESOMEAPPLICATION_H_

#include <berryIApplication.h>

#include "my_awesomeproject_exampleapp_Export.h"

class AWESOME_APP_EXPORT QmitkAwesomeApplication : public QObject, public berry::IApplication
{
  Q_OBJECT
  Q_INTERFACES(berry::IApplication)

public:

  QmitkAwesomeApplication();
  QmitkAwesomeApplication(const QmitkAwesomeApplication& other);
  
  int Start();
  void Stop();
};

#endif /*QMITKAWESOMEAPPLICATION_H_*/
