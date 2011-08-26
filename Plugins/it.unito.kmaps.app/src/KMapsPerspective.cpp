/*=========================================================================
 
 Program:   BlueBerry Platform
 Language:  C++
 Date:      $Date: 2010-01-16 19:57:43 +0100 (szo, 16 jan 2010) $
 Version:   $Revision: 21070 $
 
 Copyright (c) German Cancer Research Center, Division of Medical and
 Biological Informatics. All rights reserved.
 See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.
 
 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notices for more information.
 
 =========================================================================*/

#include "KMapsPerspective.h"

#include <berryIViewLayout.h>
#include <QDebug>


void KMapsPerspective::CreateInitialLayout(berry::IPageLayout::Pointer layout) {
	using namespace berry;

	// Editors are placed for free.
	std::string editorArea = layout->GetEditorArea();

	layout->AddView("it.unito.kmaps.views.DCEProtocolView", IPageLayout::LEFT, 0.2f, editorArea);
	layout->AddView("org.mitk.views.datamanager", IPageLayout::RIGHT, 0.7f, editorArea);

	IViewLayout::Pointer lo = layout->GetViewLayout("org.mitk.views.datamanager");
	lo->SetCloseable(false);

	layout->AddView("org.mitk.views.imagenavigator", IPageLayout::BOTTOM, 0.5f, "it.unito.kmaps.views.DCEProtocolView");

	IFolderLayout::Pointer bottomRightFolder = layout->CreateFolder("bottomRight", IPageLayout::BOTTOM, 0.4f, "org.mitk.views.datamanager");
	bottomRightFolder->AddView("org.mitk.views.segmentation");
	bottomRightFolder->AddView("it.unito.kmaps.views.IntensityProfileView");

	IFolderLayout::Pointer bottomFolder = layout->CreateFolder("bottom", IPageLayout::BOTTOM, 0.7f, editorArea);
	bottomFolder->AddView("org.mitk.views.propertylistview");
	bottomFolder->AddView("org.blueberry.views.logview");
}
