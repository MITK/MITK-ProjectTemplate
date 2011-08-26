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

#ifndef KMAPSAPPLICATION_H_
#define KMAPSAPPLICATION_H_

#include <berryIApplication.h>

#include "it_unito_kmaps_app_Export.h"

class KMAPS_APP_EXPORT KMapsApplication : public QObject, public berry::IApplication
{
  Q_OBJECT
  Q_INTERFACES(berry::IApplication)

public:

  KMapsApplication();
  KMapsApplication(const KMapsApplication& other);
  
  int Start();
  void Stop();
};

#endif /*KMAPSAPPLICATION_H_*/
