/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Language:  C++
Date:      $Date: 2010-01-16 19:57:43 +0100 (Sa, 16 Jan 2010) $
Version:   $Revision: 21070 $

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef KMAPSFILEOPENACTION_H_
#define KMAPSFILEOPENACTION_H_

#ifdef __MINGW32__
// We need to inlclude winbase.h here in order to declare
// atomic intrinsics like InterlockedIncrement correctly.
// Otherwhise, they would be declared wrong within qatomic_windows.h .
#include <windows.h>
#endif

#include <QAction>
#include <QIcon>

#include <it_unito_kmaps_app_Export.h>

#include <berryIWorkbenchWindow.h>
#include <berryIPreferences.h>

class KMAPS_APP_EXPORT KMapsFileOpenAction : public QAction
{
  Q_OBJECT

public:
  KMapsFileOpenAction(berry::IWorkbenchWindow::Pointer window);
  KMapsFileOpenAction(const QIcon & icon, berry::IWorkbenchWindow::Pointer window);

protected slots:

  void Run();

private:
  void init ( berry::IWorkbenchWindow::Pointer window );
  berry::IWorkbenchWindow::Pointer m_Window;
  berry::IPreferences::WeakPtr m_GeneralPreferencesNode;
};


#endif /*KMAPSFILEOPENACTION_H_*/
