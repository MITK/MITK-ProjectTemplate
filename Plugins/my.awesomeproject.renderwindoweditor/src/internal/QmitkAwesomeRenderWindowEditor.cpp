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

#include <mitkPlaneGeometry.h>
#include <mitkInteractionConst.h>

#include "QmitkAwesomeRenderWindowEditor.h"
#include <QmitkRenderWindow.h>
#include <QVBoxLayout>


const std::string QmitkAwesomeRenderWindowEditor::EDITOR_ID = "org.mitk.editors.stdmultiwidget";


QmitkAwesomeRenderWindowEditor::QmitkAwesomeRenderWindowEditor()
  : m_RenderWindow(0)
{
}

QmitkRenderWindow *QmitkAwesomeRenderWindowEditor::GetActiveQmitkRenderWindow() const
{
  return m_RenderWindow;
}

QHash<QString, QmitkRenderWindow *> QmitkAwesomeRenderWindowEditor::GetQmitkRenderWindows() const
{
  QHash<QString, QmitkRenderWindow*> wnds;
  wnds.insert("transversal", m_RenderWindow);
  return wnds;
}

QmitkRenderWindow *QmitkAwesomeRenderWindowEditor::GetQmitkRenderWindow(const QString &id) const
{
  if (id == "transversal")
  {
    return m_RenderWindow;
  }
  return 0;
}

mitk::Point3D QmitkAwesomeRenderWindowEditor::GetSelectedPosition(const QString & /*id*/) const
{
  const mitk::PlaneGeometry* pg =
      m_RenderWindow->GetSliceNavigationController()->GetCurrentPlaneGeometry();
  if (pg)
  {
    return pg->GetCenter();
  }
  else
  {
    return mitk::Point3D();
  }
}

void QmitkAwesomeRenderWindowEditor::SetSelectedPosition(const mitk::Point3D &pos, const QString &/*id*/)
{
}

void QmitkAwesomeRenderWindowEditor::EnableDecorations(bool enable, const QStringList &decorations)
{
  if (decorations.isEmpty() || decorations.contains(DECORATION_MENU))
  {
    m_RenderWindow->ActivateMenuWidget(enable);
  }
}

bool QmitkAwesomeRenderWindowEditor::IsDecorationEnabled(const QString &decoration) const
{
  if (decoration == DECORATION_MENU)
  {
    return m_RenderWindow->GetActivateMenuWidgetFlag();
  }
  return false;
}

QStringList QmitkAwesomeRenderWindowEditor::GetDecorations() const
{
  QStringList decorations;
  decorations << DECORATION_MENU;
  return decorations;
}

void QmitkAwesomeRenderWindowEditor::SetFocus()
{
  m_RenderWindow->setFocus();
}

void QmitkAwesomeRenderWindowEditor::CreateQtPartControl(QWidget* parent)
{
  QVBoxLayout* layout = new QVBoxLayout(parent);
  layout->setContentsMargins(0,0,0,0);

  m_RenderWindow = new QmitkRenderWindow(parent);
  layout->addWidget(m_RenderWindow);

  mitk::DataStorage::Pointer ds = this->GetDataStorage();
  m_RenderWindow->GetRenderer()->SetDataStorage(ds);

  // Initialize the QmitkRenderWindow as transversal to all data objects in DataStorage
//  mitk::TimeSlicedGeometry::Pointer geo = ds->ComputeBoundingGeometry3D(ds->GetAll());
//  m_RenderWindow->
//  mitk::RenderingManager::GetInstance()->InitializeViews(geo);

  this->RequestUpdate();
}
