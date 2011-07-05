#include "mitkPluginActivator.h"

#include <QtPlugin>

#include "QmitkAwesomeView.h"

namespace mitk {

void PluginActivator::start(ctkPluginContext* context)
{
  BERRY_REGISTER_EXTENSION_CLASS(QmitkAwesomeView, context)
}

void PluginActivator::stop(ctkPluginContext* context)
{
  Q_UNUSED(context)
}

}

Q_EXPORT_PLUGIN2(my_awesomeproject_exampleplugin, mitk::PluginActivator)
