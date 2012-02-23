/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Language:  C++
Date:      $Date$
Version:   $Revision: 18127 $

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "my_awesomeproject_renderwindoweditor_Activator.h"

#include "QmitkAwesomeRenderWindowEditor.h"


void
my_awesomeproject_renderwindoweditor_Activator::start(ctkPluginContext* context)
{
  BERRY_REGISTER_EXTENSION_CLASS(QmitkAwesomeRenderWindowEditor, context)
}

void
my_awesomeproject_renderwindoweditor_Activator::stop(ctkPluginContext* context)
{
  Q_UNUSED(context)
}

Q_EXPORT_PLUGIN2(my_awesomeproject_renderwindoweditor, my_awesomeproject_renderwindoweditor_Activator)
