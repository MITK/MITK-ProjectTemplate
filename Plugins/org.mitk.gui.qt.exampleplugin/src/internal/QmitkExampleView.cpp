/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include <berryISelectionService.h>
#include <berryIWorkbenchWindow.h>

#include <mitkNodePredicateAnd.h>
#include <mitkNodePredicateDataType.h>
#include <mitkNodePredicateNot.h>
#include <mitkNodePredicateOr.h>
#include <mitkNodePredicateProperty.h>

#include <usModuleRegistry.h>

#include <QMessageBox>

#include <ExampleImageFilter.h>
#include <ExampleImageInteractor.h>

#include "QmitkExampleView.h"

namespace
{
  // Helper function to create a fully set up instance of our
  // ExampleImageInteractor, based on the state machine specified in Paint.xml
  // as well as its configuration in PaintConfig.xml. Both files are compiled
  // into MitkExampleModule as resources.
  static ExampleImageInteractor::Pointer CreateExampleImageInteractor()
  {
    auto exampleModule = us::ModuleRegistry::GetModule("MitkExampleModule");

    if (nullptr != exampleModule)
    {
      auto interactor = ExampleImageInteractor::New();
      interactor->LoadStateMachine("Paint.xml", exampleModule);
      interactor->SetEventConfig("PaintConfig.xml", exampleModule);
      return interactor;
    }

    return nullptr;
  }
}

// Don't forget to initialize the VIEW_ID.
const std::string QmitkExampleView::VIEW_ID = "org.mitk.views.exampleview";

void QmitkExampleView::CreateQtPartControl(QWidget* parent)
{
  // Setting up the UI is a true pleasure when using .ui files, isn't it?
  m_Controls.setupUi(parent);

  m_Controls.selectionWidget->SetDataStorage(this->GetDataStorage());
  m_Controls.selectionWidget->SetSelectionIsOptional(true);
  m_Controls.selectionWidget->SetEmptyInfo(QStringLiteral("Select an image"));
  m_Controls.selectionWidget->SetNodePredicate(mitk::NodePredicateAnd::New(
    mitk::TNodePredicateDataType<mitk::Image>::New(),
    mitk::NodePredicateNot::New(mitk::NodePredicateOr::New(
      mitk::NodePredicateProperty::New("helper object"),
      mitk::NodePredicateProperty::New("hidden object")))));

  // Wire up the UI widgets with our functionality.
  connect(m_Controls.selectionWidget, &QmitkSingleNodeSelectionWidget::CurrentSelectionChanged, this, &QmitkExampleView::OnImageChanged);
  connect(m_Controls.processImageButton, SIGNAL(clicked()), this, SLOT(ProcessSelectedImage()));

  // Make sure to have a consistent UI state at the very beginning.
  this->OnImageChanged(m_Controls.selectionWidget->GetSelectedNodes());
}

void QmitkExampleView::SetFocus()
{
  m_Controls.processImageButton->setFocus();
}

void QmitkExampleView::OnImageChanged(const QmitkSingleNodeSelectionWidget::NodeList&)
{
  this->EnableWidgets(m_Controls.selectionWidget->GetSelectedNode().IsNotNull());
}

void QmitkExampleView::EnableWidgets(bool enable)
{
  m_Controls.processImageButton->setEnabled(enable);
}

void QmitkExampleView::ProcessSelectedImage()
{
  auto selectedDataNode = m_Controls.selectionWidget->GetSelectedNode();
  auto data = selectedDataNode->GetData();

  // We don't use the auto keyword here, which would evaluate to a native
  // image pointer. Instead, we want a smart pointer to ensure that
  // the image isn't deleted somewhere else while we're using it.
  mitk::Image::Pointer image = dynamic_cast<mitk::Image*>(data);

  auto imageName = selectedDataNode->GetName();
  auto offset = m_Controls.offsetSpinBox->value();

  MITK_INFO << "Process image \"" << imageName << "\" ...";

  // We're finally using the ExampleImageFilter from MitkExampleModule.
  auto filter = ExampleImageFilter::New();
  filter->SetInput(image);
  filter->SetOffset(offset);

  filter->Update();

  mitk::Image::Pointer processedImage = filter->GetOutput();

  if (processedImage.IsNull() || !processedImage->IsInitialized())
    return;

  MITK_INFO << "  done";

  // Stuff the resulting image into a data node, set some properties,
  // and add it to the data storage, which will eventually display the
  // image in the application.
  auto processedImageDataNode = mitk::DataNode::New();
  processedImageDataNode->SetData(processedImage);

  QString name = QString("%1 (Offset: %2)").arg(imageName.c_str()).arg(offset);
  processedImageDataNode->SetName(name.toStdString());

  // We don't really need to copy the level window, but if we wouldn't
  // do it, the new level window would be initialized to display the image
  // with optimal contrast in order to capture the whole range of pixel
  // values. This is also true for the input image as long as one didn't
  // modify its level window manually. Thus, the images would appear
  // identical unless you compare the level window widget for both images.
  mitk::LevelWindow levelWindow;

  if (selectedDataNode->GetLevelWindow(levelWindow))
    processedImageDataNode->SetLevelWindow(levelWindow);

  // We also attach our ExampleImageInteractor, which allows us to paint
  // on the resulting images by using the mouse as long as the CTRL key
  // is pressed.
  auto interactor = CreateExampleImageInteractor();

  if (interactor.IsNotNull())
    interactor->SetDataNode(processedImageDataNode);

  this->GetDataStorage()->Add(processedImageDataNode);
}
