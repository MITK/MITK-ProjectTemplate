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


#include "AwesomeImageFilter.h"

#include <mitkImageAccessByItk.h>
#include <itkShiftScaleImageFilter.h>

template<typename TPixel, unsigned int VImageDimension>
void AddOffset(itk::Image<TPixel, VImageDimension>* image, int offset, mitk::Image::Pointer outputImage)
{
  typedef itk::Image<TPixel, VImageDimension> ImageType;
  typedef itk::ShiftScaleImageFilter<ImageType, ImageType> FilterType;

  typename FilterType::Pointer filter = FilterType::New();
  filter->SetShift(offset);

  filter->SetInput(image);
  filter->Update();
  mitk::CastToMitkImage(filter->GetOutput(), outputImage);
}

AwesomeImageFilter::AwesomeImageFilter()
  : m_Offset(0)
{
  this->SetNumberOfRequiredInputs(1);
  this->SetNumberOfRequiredOutputs(1);
}

AwesomeImageFilter::~AwesomeImageFilter()
{
}

void AwesomeImageFilter::GenerateData()
{
  mitk::Image::ConstPointer image = this->GetInput(0);
  try
  {
    mitk::Image::Pointer outputImage = this->GetOutput();
    AccessIntegralPixelTypeByItk_n(image, AddOffset, (m_Offset, outputImage))
  }
  catch (const mitk::AccessByItkException& e)
  {
    MITK_WARN << "Unsupported pixel type: " << e.what();
  }
}

