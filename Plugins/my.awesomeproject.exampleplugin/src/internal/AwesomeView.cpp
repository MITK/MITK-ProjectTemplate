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

#include <QMessageBox>

#include <AwesomeImageFilter.h>

const std::string AwesomeView::VIEW_ID = "my.awesomeproject.views.awesomeview";

void AwesomeView::CreateQtPartControl(QWidget* parent)
{
  m_Controls.setupUi(parent);
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
    if (dataNode.IsNotNull() && dynamic_cast<mitk::Image*>(dataNode->GetData()) != nullptr)
    {
      m_Controls.selectImageLabel->setVisible(false);
      return;
    }
  }

  m_Controls.selectImageLabel->setVisible(true);
}

void AwesomeView::ProcessSelectedImage()
{
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

  if (data != nullptr)
  {
    mitk::Image::Pointer image = dynamic_cast<mitk::Image*>(data);

    if (image.IsNotNull())
    {
      auto imageName = firstSelectedDataNode->GetName();
      auto offset = m_Controls.offsetSpinBox->value();

      MITK_INFO << "Process image \"" << imageName << "\" ...";

      auto filter = AwesomeImageFilter::New();
      filter->SetInput(image);
      filter->SetOffset(offset);

      filter->Update();

      MITK_INFO << "  done";

      auto processedImageDataNode = mitk::DataNode::New();
      processedImageDataNode->SetData(filter->GetOutput());
      processedImageDataNode->SetName(QString("%1 (Offset: %2)").arg(imageName.c_str()).arg(offset).toStdString());

      this->GetDataStorage()->Add(processedImageDataNode);
    }
  }
}
