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

#include "KMapsApplicationPlugin.h"
#include "../KMapsApplication.h"
#include "KMapsPerspective.h"

#include <mitkVersion.h>
#include <berryQtAssistantUtil.h>

#include <QFileInfo>
#include <QDateTime>
#include <QtPlugin>

KMapsApplicationPlugin* KMapsApplicationPlugin::inst = 0;

KMapsApplicationPlugin::KMapsApplicationPlugin()
  : pluginListener(0)
{
  inst = this;
}

KMapsApplicationPlugin::~KMapsApplicationPlugin()
{
  delete pluginListener;
}

KMapsApplicationPlugin* KMapsApplicationPlugin::GetDefault()
{
  return inst;
}

void KMapsApplicationPlugin::start(ctkPluginContext* context)
{
  berry::AbstractUICTKPlugin::start(context);
  
  this->context = context;
  
  BERRY_REGISTER_EXTENSION_CLASS(KMapsApplication, context);
  BERRY_REGISTER_EXTENSION_CLASS(KMapsPerspective, context);

  QString collectionFile = GetQtHelpCollectionFile();

  berry::QtAssistantUtil::SetHelpCollectionFile(collectionFile);
  berry::QtAssistantUtil::SetDefaultHelpUrl("qthelp://it.unito.kmaps.app/bundle/index.html");

  delete pluginListener;
  pluginListener = new berry::QCHPluginListener(context);
  context->connectPluginListener(pluginListener, SLOT(pluginChanged(ctkPluginEvent)), Qt::DirectConnection);

  // register all QCH files from all the currently installed plugins
  pluginListener->processPlugins();
}

ctkPluginContext* KMapsApplicationPlugin::GetPluginContext() const
{
  return context;
}

QString KMapsApplicationPlugin::GetQtHelpCollectionFile() const
{
  if (!helpCollectionFile.isEmpty())
  {
    return helpCollectionFile;
  }

  QString collectionFilename;
//  QString na("n/a");
//  if (na != KMaps_REVISION)
//    collectionFilename = "KMapsQtHelpCollection_" KMaps_REVISION ".qhc";
//  else
    collectionFilename = "KMapsQtHelpCollection.qhc";

  QFileInfo collectionFileInfo = context->getDataFile(collectionFilename);
  QFileInfo pluginFileInfo = QFileInfo(QUrl(context->getPlugin()->getLocation()).toLocalFile());
  if (!collectionFileInfo.exists() ||
      pluginFileInfo.lastModified() > collectionFileInfo.lastModified())
  {
    // extract the qhc file from the plug-in
    QByteArray content = context->getPlugin()->getResource(collectionFilename);
    if (content.isEmpty())
    {
      BERRY_WARN << "Could not get plug-in resource: " << collectionFilename.toStdString();
    }
    else
    {
      QFile file(collectionFileInfo.absoluteFilePath());
      file.open(QIODevice::WriteOnly);
      file.write(content);
      file.close();
    }
  }

  if (QFile::exists(collectionFileInfo.absoluteFilePath()))
  {
    helpCollectionFile = collectionFileInfo.absoluteFilePath();
  }

  return helpCollectionFile;
}

Q_EXPORT_PLUGIN2(it_unito_kmaps_app, KMapsApplicationPlugin)
