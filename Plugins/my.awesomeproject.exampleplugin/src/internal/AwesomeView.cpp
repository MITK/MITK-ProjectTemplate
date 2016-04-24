/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#include "AwesomeView.h"

#include <berryISelectionService.h>
#include <berryIWorkbenchWindow.h>

#include <usModuleRegistry.h>

#include <QMessageBox>

#include <AwesomeImageFilter.h>
#include <AwesomeImageInteractor.h>

// Helper function to create a fully set up instance of our
// AwesomeImageInteractor, based on the state machine specified in Paint.xml
// as well as its configuration in PaintConfig.xml. Both files are compiled
// into our MyAwesomeLib module as resources.
static AwesomeImageInteractor::Pointer CreateAwesomeImageInteractor()
{
  auto myAwesomeLib = us::ModuleRegistry::GetModule("MyAwesomeLib");

  auto interactor = AwesomeImageInteractor::New();
  interactor->LoadStateMachine("Paint.xml", myAwesomeLib);
  interactor->SetEventConfig("PaintConfig.xml", myAwesomeLib);

  return interactor;
}

// Don't forget to initialize the VIEW_ID.
const std::string AwesomeView::VIEW_ID = "my.awesomeproject.views.awesomeview";

void AwesomeView::CreateQtPartControl(QWidget* parent)
{
  // Setting up the UI is a true pleasure when using .ui files, isn't it?
  m_Controls.setupUi(parent);

  // Wire up the UI widgets with our functionality.
  connect(m_Controls.processImageButton, SIGNAL(clicked()), this, SLOT(ProcessSelectedImage()));
}

void AwesomeView::SetFocus()
{
  m_Controls.processImageButton->setFocus();
}

void AwesomeView::OnSelectionChanged(berry::IWorkbenchPart::Pointer, const QList<mitk::DataNode::Pointer>& dataNodes)
{
  for (const auto& dataNode : dataNodes)
  {
    // Write robust code. Always check pointers before using them. If the
    // data node pointer is null, the second half of our condition isn't
    // even evaluated and we're safe (C++ short-circuit evaluation).
    if (dataNode.IsNotNull() && dynamic_cast<mitk::Image*>(dataNode->GetData()) != nullptr)
    {
      m_Controls.selectImageLabel->setVisible(false);
      return;
    }
  }

  // Nothing is selected or the selection doesn't contain an image.
  m_Controls.selectImageLabel->setVisible(true);
}

void AwesomeView::ProcessSelectedImage()
{
  // Before we even think about processing something, we need to make sure
  // that we have valid input. Don't be sloppy, this is a main reason
  // for application crashes if neglected.

  auto selectedDataNodes = this->GetDataManagerSelection();

  if (selectedDataNodes.empty())
    return;

  auto firstSelectedDataNode = selectedDataNodes.front();

  if (firstSelectedDataNode.IsNull())
  {
    QMessageBox::information(nullptr, "Awesome View", "Please load and select an image before starting image processing.");
    return;
  }

  auto data = firstSelectedDataNode->GetData();

  // Something is selected, but does it contain data?
  if (data != nullptr)
  {
    // We don't use the auto keyword here, which would evaluate to a native
    // image pointer. Instead, we want a smart pointer in order to ensure that
    // the image isn't deleted somewhere else while we're using it.
    mitk::Image::Pointer image = dynamic_cast<mitk::Image*>(data);

    // Something is selected and it contains data, but is it an image?
    if (image.IsNotNull())
    {
      auto imageName = firstSelectedDataNode->GetName();
      auto offset = m_Controls.offsetSpinBox->value();

      MITK_INFO << "Process image \"" << imageName << "\" ...";

      // We're finally using the AwesomeImageFilter from our AwesomeLib module.
      auto filter = AwesomeImageFilter::New();
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

      if (firstSelectedDataNode->GetLevelWindow(levelWindow))
        processedImageDataNode->SetLevelWindow(levelWindow);

      // We also attach our AwesomeImageInteractor, which allows us to paint
      // on the resulting images by using the mouse as long as the CTRL key
      // is pressed.
      auto interactor = CreateAwesomeImageInteractor();

      if (interactor.IsNotNull())
        interactor->SetDataNode(processedImageDataNode);

      this->GetDataStorage()->Add(processedImageDataNode);
    }
  }

  // Now it's your turn. This class/method has lots of room for improvements,
  // for example:
  //
  // - What happens when multiple items are selected but the first one isn't
  //   an image? - There isn't any feedback for the user at all.
  // - What's the front item of a selection? Does it depend on the order
  //   of selection or the position in the Data Manager? - Isn't it
  //   better to process all selected images? Don't forget to adjust the
  //   titles of the UI widgets.
  // - In addition to the the displayed label, it's probably a good idea to
  //   enable or disable the button depending on the selection.
}
