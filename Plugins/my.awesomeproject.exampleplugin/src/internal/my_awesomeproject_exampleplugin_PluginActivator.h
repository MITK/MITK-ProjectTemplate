/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#ifndef my_awesomeproject_exampleplugin_PluginActivator_h
#define my_awesomeproject_exampleplugin_PluginActivator_h

#include <ctkPluginActivator.h>

class my_awesomeproject_exampleplugin_PluginActivator
  : public QObject,
    public ctkPluginActivator
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "my_awesomeproject_exampleplugin")
  Q_INTERFACES(ctkPluginActivator)

public:
  void start(ctkPluginContext* context);
  void stop(ctkPluginContext* context);
};

#endif
