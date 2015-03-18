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

#include "mitkExampleAppPluginActivator.h"
#include "QmitkAwesomeApplication.h"
#include "QmitkAwesomePerspective.h"

#include <berryLog.h>

#include <mitkVersion.h>

#include <QFileInfo>
#include <QDateTime>

namespace mitk {

ExampleAppPluginActivator* ExampleAppPluginActivator::inst = 0;

ExampleAppPluginActivator::ExampleAppPluginActivator()
{
  inst = this;
}

ExampleAppPluginActivator::~ExampleAppPluginActivator()
{
}

ExampleAppPluginActivator* ExampleAppPluginActivator::GetDefault()
{
  return inst;
}

void ExampleAppPluginActivator::start(ctkPluginContext* context)
{
  berry::AbstractUICTKPlugin::start(context);
  
  this->context = context;
  
  BERRY_REGISTER_EXTENSION_CLASS(QmitkAwesomeApplication, context);
  BERRY_REGISTER_EXTENSION_CLASS(QmitkAwesomePerspective, context);

  QString collectionFile = GetQtHelpCollectionFile();

  // berry::QtAssistantUtil::SetHelpCollectionFile(collectionFile);
  // berry::QtAssistantUtil::SetDefaultHelpUrl("qthelp://my.awesomeproject.exampleapp/bundle/index.html");
}

ctkPluginContext* ExampleAppPluginActivator::GetPluginContext() const
{
  return context;
}

QString ExampleAppPluginActivator::GetQtHelpCollectionFile() const
{
  if (!helpCollectionFile.isEmpty())
  {
    return helpCollectionFile;
  }

  QString collectionFilename = "ExampleAppQtHelpCollection.qhc";

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

}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
  #include <QtPlugin>
  Q_EXPORT_PLUGIN2(my_awesomeproject_exampleapp, mitk::ExampleAppPluginActivator)
#endif
