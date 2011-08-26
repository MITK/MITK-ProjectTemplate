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

#ifndef __KMapsPerspective_h
#define __KMapsPerspective_h

#include <berryIPerspectiveFactory.h>

#include <it_unito_kmaps_app_Export.h>

/**
 * This perspective provides a layout for DCE analysis.
 */
class KMAPS_APP_EXPORT KMapsPerspective: public QObject, public berry::IPerspectiveFactory
{

	Q_OBJECT
	Q_INTERFACES(berry::IPerspectiveFactory)

public:

  /**
   * Defines the initial layout for a perspective.
   *
   * Implementors of this method may add additional views to a
   * perspective.  The perspective already contains an editor folder
   * with <code>ID = ILayoutFactory::ID_EDITORS</code>.  Add additional views
   * to the perspective in reference to the editor folder.
   *
   * This method is only called when a new perspective is created.  If
   * an old perspective is restored from a persistence file then
   * this method is not called.
   *
   * @param factory the factory used to add views to the perspective
   */
  virtual void CreateInitialLayout(berry::IPageLayout::Pointer layout);
};

#endif /* __KMapsPerspective_h */
