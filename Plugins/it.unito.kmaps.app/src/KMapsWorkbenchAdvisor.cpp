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

#include "KMapsWorkbenchAdvisor.h"
#include "internal/KMapsApplicationPlugin.h"

#include <berryQtAssistantUtil.h>
//#include <QmitkExtWorkbenchWindowAdvisor.h>
#include "KMapsWorkbenchWindowAdvisor.h"

const std::string KMapsWorkbenchAdvisor::DEFAULT_PERSPECTIVE_ID =
    "it.unito.kmaps.KMapsPerspective";

void
KMapsWorkbenchAdvisor::Initialize(berry::IWorkbenchConfigurer::Pointer configurer)
{
  berry::QtWorkbenchAdvisor::Initialize(configurer);

  configurer->SetSaveAndRestore(true);

  if (!berry::QtAssistantUtil::GetHelpCollectionFile().isEmpty())
  {
    typedef std::vector<berry::IBundle::Pointer> BundleContainer;
    BundleContainer bundles = berry::Platform::GetBundles();
    berry::QtAssistantUtil::RegisterQCHFiles(bundles);
  }
}

berry::WorkbenchWindowAdvisor*
KMapsWorkbenchAdvisor::CreateWorkbenchWindowAdvisor(
        berry::IWorkbenchWindowConfigurer::Pointer configurer)
{
  // -------------------------------------------------------------------
  // Here you can switch back to the original workbench window advisor:
  // (Include the header as well!)
  // -------------------------------------------------------------------
//  QmitkExtWorkbenchWindowAdvisor* advisor = new
//    QmitkExtWorkbenchWindowAdvisor(this, configurer);
  KMapsWorkbenchWindowAdvisor* advisor = new
    KMapsWorkbenchWindowAdvisor(this, configurer);
  advisor->SetWindowIcon(":/KMapslication/icon_research.xpm");
  return advisor;
}

std::string KMapsWorkbenchAdvisor::GetInitialWindowPerspectiveId()
{
  return DEFAULT_PERSPECTIVE_ID;
}
