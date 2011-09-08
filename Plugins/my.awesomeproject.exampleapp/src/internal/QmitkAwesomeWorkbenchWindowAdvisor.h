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

#ifndef QMITKAWESOMEWORKBENCHWINDOWADVISOR_H_
#define QMITKAWESOMEWORKBENCHWINDOWADVISOR_H_

#include <berryWorkbenchWindowAdvisor.h>

#include <berryIPartListener.h>
#include <berryIEditorPart.h>
#include <berryIWorkbenchPage.h>
#include <berryWorkbenchAdvisor.h>
#include <QmitkCommonWorkbenchWindowAdvisor.h>

#include <QList>
class QAction;
class QMenu;

class QmitkAwesomeWorkbenchWindowAdvisor : public QmitkCommonWorkbenchWindowAdvisor
{
public:

    QmitkAwesomeWorkbenchWindowAdvisor(berry::WorkbenchAdvisor* wbAdvisor,
        berry::IWorkbenchWindowConfigurer::Pointer configurer);

    berry::ActionBarAdvisor::Pointer CreateActionBarAdvisor(
        berry::IActionBarConfigurer::Pointer configurer);

    void* CreateEmptyWindowContents(void* parent);

    void PostWindowCreate();

    void PreWindowOpen();

    void PostWindowClose();

    void ShowViewToolbar(bool show);

    void ShowVersionInfo(bool show);

    //TODO should be removed when product support is here
    void SetProductName(const std::string& product);
    void SetWindowIcon(const std::string& wndIcon);

    void SetPerspectiveExcludeList(std::vector<std::string> v);
    std::vector<std::string> GetPerspectiveExcludeList();

    void SetViewExcludeList(std::vector<std::string> v);
    std::vector<std::string> GetViewExcludeList();

private:

  /**
   * Hooks the listeners needed on the window
   *
   * @param configurer
   */
  void HookTitleUpdateListeners(berry::IWorkbenchWindowConfigurer::Pointer configurer);

  std::string ComputeTitle();

  void RecomputeTitle();

  QString GetQSettingsFile() const;

  /**
   * Updates the window title. Format will be: [pageInput -]
   * [currentPerspective -] [editorInput -] [workspaceLocation -] productName
   * @param editorHidden TODO
   */
  void UpdateTitle(bool editorHidden);

  void PropertyChange(berry::Object::Pointer /*source*/, int propId);

  static QString QT_SETTINGS_FILENAME;

  berry::IPartListener::Pointer titlePartListener;
  berry::IPerspectiveListener::Pointer titlePerspectiveListener;
  berry::IPerspectiveListener::Pointer menuPerspectiveListener;
  berry::IPartListener::Pointer imageNavigatorPartListener;
  berry::IPropertyChangeListener::Pointer editorPropertyListener;
  friend struct berry::PropertyChangeIntAdapter<QmitkAwesomeWorkbenchWindowAdvisor>;
  friend class PartListenerForTitle;
  friend class PerspectiveListenerForTitle;
  friend class PerspectiveListenerForMenu;
  friend class PartListenerForImageNavigator;

  berry::IEditorPart::WeakPtr lastActiveEditor;
  berry::IPerspectiveDescriptor::WeakPtr lastPerspective;
  berry::IWorkbenchPage::WeakPtr lastActivePage;
  std::string lastEditorTitle;
  berry::IAdaptable* lastInput;

  berry::WorkbenchAdvisor* wbAdvisor;
  bool showViewToolbar;
  bool showVersionInfo;
  std::string productName;
  std::string windowIcon;

  // stringlist for excluding perspectives from the perspective menu entry (e.g. Welcome Perspective)
  std::vector<std::string> perspectiveExcludeList;

  // stringlist for excluding views from the menu entry
  std::vector<std::string> viewExcludeList;

  // maps perspective ids to QAction objects
  std::map<std::string, QAction*> mapPerspIdToAction;

  // actions which will be enabled/disabled depending on the application state
  QList<QAction*> viewActions;
  QAction* fileSaveProjectAction;
  QAction* closeProjectAction;
  QAction* undoAction;
  QAction* redoAction;
  QAction* imageNavigatorAction;
  QAction* resetPerspAction;
  QAction* closePerspAction;
};

#endif /*QMITKAWESOMEWORKBENCHWINDOWADVISOR_H_*/
