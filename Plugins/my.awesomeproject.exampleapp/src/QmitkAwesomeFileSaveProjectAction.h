/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Language:  C++
Date:      $Date: 2009-10-09 16:36:23 +0200 (Fr, 09 Okt 2009) $
Version:   $Revision: 19414 $

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef QmitkAwesomeFileSaveProjectAction_H_
#define QmitkAwesomeFileSaveProjectAction_H_

#ifdef __MINGW32__
// We need to inlclude winbase.h here in order to declare
// atomic intrinsics like InterlockedIncrement correctly.
// Otherwhise, they would be declared wrong within qatomic_windows.h .
#include <windows.h>
#endif

#include <QAction>

#include <my_awesomeproject_exampleapp_Export.h>

#include <berryIWorkbenchWindow.h>
#include <berryIPreferences.h>

class AWESOME_APP_EXPORT QmitkAwesomeFileSaveProjectAction : public QAction
{
  Q_OBJECT

public:

  QmitkAwesomeFileSaveProjectAction(berry::IWorkbenchWindow::Pointer window);

protected slots:

  void Run();

private:

  berry::IWorkbenchWindow::Pointer m_Window;
  berry::IPreferences::WeakPtr m_GeneralPreferencesNode;
};


#endif /*QmitkAwesomeFileSaveProjectAction_H_*/
