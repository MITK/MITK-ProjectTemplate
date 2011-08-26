/*=========================================================================
 
 Program:   BlueBerry Platform
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


#ifndef KMAPSAPPLICATIONPLUGIN_H_
#define KMAPSAPPLICATIONPLUGIN_H_

#include <berryAbstractUICTKPlugin.h>

#include <QString>

#include <berryQCHPluginListener.h>

class KMapsApplicationPlugin : public QObject, public berry::AbstractUICTKPlugin
{
  Q_OBJECT
  Q_INTERFACES(ctkPluginActivator)
  
public:

  KMapsApplicationPlugin();
  ~KMapsApplicationPlugin();

  static KMapsApplicationPlugin* GetDefault();

  ctkPluginContext* GetPluginContext() const;

  void start(ctkPluginContext*);

  QString GetQtHelpCollectionFile() const;

private:

  static KMapsApplicationPlugin* inst;

  ctkPluginContext* context;
  berry::QCHPluginListener* pluginListener;

  mutable QString helpCollectionFile;
};

#endif /* KMAPSAPPLICATIONPLUGIN_H_ */
