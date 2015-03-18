#include "mitkPluginActivator.h"
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

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
  #include <QtPlugin>
  Q_EXPORT_PLUGIN2(my_awesomeproject_exampleplugin, mitk::PluginActivator)
#endif
