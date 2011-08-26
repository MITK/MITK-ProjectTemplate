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

#include "QmitkAwesomeFileOpenAction.h"

#include <QFileDialog>
#include <QFileInfo>
#include <mitkDataNodeFactory.h>

#include "mitkCoreObjectFactory.h"
#include "mitkSceneIO.h"
#include "mitkProgressBar.h"

#include <mitkCoreExtObjectFactory.h>
#include <mitkDataStorageEditorInput.h>
#include <berryIEditorPart.h>
#include <berryIWorkbenchPage.h>
#include <berryIPreferencesService.h>
#include <berryIWorkbench.h>
#include <berryPlatform.h>

#include "mitkProperties.h"
#include "mitkNodePredicateData.h"
#include "mitkNodePredicateNot.h"
#include "mitkNodePredicateProperty.h"


#include "QmitkStdMultiWidgetEditor.h"

QmitkAwesomeFileOpenAction::QmitkAwesomeFileOpenAction(berry::IWorkbenchWindow::Pointer window)
: QAction(0)
{
  this->init(window);
}

QmitkAwesomeFileOpenAction::QmitkAwesomeFileOpenAction(const QIcon & icon, berry::IWorkbenchWindow::Pointer window)
: QAction(0)
{
  this->setIcon(icon);

  this->init(window);
}

void QmitkAwesomeFileOpenAction::init(berry::IWorkbenchWindow::Pointer window)
{
  m_Window = window;
  this->setParent(static_cast<QWidget*>(m_Window->GetShell()->GetControl()));
  this->setText("&Open...");
  this->setToolTip("Open data files (images, surfaces,...) and project files (.mitk)");

  berry::IPreferencesService::Pointer prefService
    = berry::Platform::GetServiceRegistry()
    .GetServiceById<berry::IPreferencesService>(berry::IPreferencesService::ID);
  
  m_GeneralPreferencesNode = prefService->GetSystemPreferences()->Node("/General");

  this->connect(this, SIGNAL(triggered(bool)), this, SLOT(Run()));
}

void QmitkAwesomeFileOpenAction::Run()
{
  /**
  * @brief stores the last path of last opened file
  */
  static QString m_LastPath;

  if(m_GeneralPreferencesNode.Lock().IsNotNull())
  {
    if(m_LastPath.isEmpty())
      m_LastPath = QString::fromStdString(m_GeneralPreferencesNode.Lock()->Get("LastFileOpenPath", ""));
  }


  //QFileDialog dialog(static_cast<QWidget*>(m_Window->GetShell()->GetControl()));
  //dialog.setFileMode(QFileDialog::ExistingFiles);
  //QStringList filters;
  //filters << "Images (*.pic *.pic.gz *.vti *.dcm *.nhdr *.nrrd *.mhd)" 
  //  << "Surfaces (*.stl *.vtk *.vtp)"
  //  << "MITK Pointset (*.mps)"
  //  << "All Files (*.*)";
  //dialog.setFilters(filters);

  std::stringstream ss;
  ss << mitk::CoreObjectFactory::GetInstance()->GetFileExtensions();

  std::string fileExtensions = ss.str();
  fileExtensions.append(";;MITK Scene Files (*.mitk)");
  fileExtensions.insert( fileExtensions.find("all (") + 5, "*.mitk " );

  QStringList fileNames = QFileDialog::getOpenFileNames(NULL, "Open", m_LastPath, fileExtensions.c_str() );

  //if (dialog.exec())
  //  fileNames = dialog.selectedFiles();

  if (fileNames.empty()) 
    return;

  // check if there is an open perspective, if not open the default perspective
  if (m_Window->GetActivePage().IsNull())
  {
    std::string defaultPerspId = m_Window->GetWorkbench()->GetPerspectiveRegistry()->GetDefaultPerspective();
    m_Window->GetWorkbench()->ShowPerspective(defaultPerspId, m_Window);
  }

  QFileInfo info(fileNames.at(0));
  m_LastPath = info.filePath();

  if(m_GeneralPreferencesNode.Lock().IsNotNull())
  {
    m_GeneralPreferencesNode.Lock()->Put("LastFileOpenPath", m_LastPath.toStdString());
    m_GeneralPreferencesNode.Lock()->Flush();
  }

  mitk::DataStorageEditorInput::Pointer editorInput;
  mitk::DataStorage::Pointer dataStorage;
  QmitkStdMultiWidgetEditor::Pointer multiWidgetEditor;
  berry::IEditorPart::Pointer editor = m_Window->GetActivePage()->GetActiveEditor();
  
  if (editor.Cast<QmitkStdMultiWidgetEditor>().IsNull())
  {
    editorInput = new mitk::DataStorageEditorInput();
    dataStorage = editorInput->GetDataStorageReference()->GetDataStorage();
  }
  else
  {
    multiWidgetEditor = editor.Cast<QmitkStdMultiWidgetEditor>();
    dataStorage = multiWidgetEditor->GetEditorInput().Cast<mitk::DataStorageEditorInput>()->GetDataStorageReference()->GetDataStorage();
  }

  if (multiWidgetEditor.IsNull())
  {
    berry::IEditorPart::Pointer editor = m_Window->GetActivePage()->OpenEditor(editorInput, QmitkStdMultiWidgetEditor::EDITOR_ID);
    multiWidgetEditor = editor.Cast<QmitkStdMultiWidgetEditor>();
  }
  else
  {
    multiWidgetEditor->GetStdMultiWidget()->RequestUpdate();
  }

  bool dsmodified = false;
  
  for (QStringList::Iterator fileName = fileNames.begin();
    fileName != fileNames.end(); ++fileName)
  {
    if ( fileName->right(5) == ".mitk" ) 
    {
      mitk::SceneIO::Pointer sceneIO = mitk::SceneIO::New();

      bool clearDataStorageFirst(false);
      mitk::ProgressBar::GetInstance()->AddStepsToDo(2);
      dataStorage = sceneIO->LoadScene( fileName->toLocal8Bit().constData(), dataStorage, clearDataStorageFirst );
      dsmodified = true;
      mitk::ProgressBar::GetInstance()->Progress(2);
    }
    else
    {
      mitk::DataNodeFactory::Pointer nodeReader = mitk::DataNodeFactory::New();
      try
      {
        nodeReader->SetFileName(fileName->toLocal8Bit().data());
        nodeReader->Update();
        for ( unsigned int i = 0 ; i < nodeReader->GetNumberOfOutputs( ); ++i )
        {
          mitk::DataNode::Pointer node;
          node = nodeReader->GetOutput(i);
          if ( node->GetData() != NULL )
          {  
            dataStorage->Add(node);
            dsmodified = true;
          }
        }
      }
      catch(...)
      {

      }
    }
  }


  if(dsmodified)
  {
    // get all nodes that have not set "includeInBoundingBox" to false
    mitk::NodePredicateNot::Pointer pred 
      = mitk::NodePredicateNot::New(mitk::NodePredicateProperty::New("includeInBoundingBox"
      , mitk::BoolProperty::New(false)));

    mitk::DataStorage::SetOfObjects::ConstPointer rs = dataStorage->GetSubset(pred);
    // calculate bounding geometry of these nodes
    mitk::TimeSlicedGeometry::Pointer bounds = dataStorage->ComputeBoundingGeometry3D(rs);
    // initialize the views to the bounding geometry
    mitk::RenderingManager::GetInstance()->InitializeViews(bounds);
  }
}
