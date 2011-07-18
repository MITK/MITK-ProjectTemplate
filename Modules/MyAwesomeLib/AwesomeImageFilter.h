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

#ifndef AwesomeImageFilter_h
#define AwesomeImageFilter_h

#include <mitkImageToImageFilter.h>

#include <MyAwesomeLibExports.h>

class MyAwesomeLib_EXPORT AwesomeImageFilter : public mitk::ImageToImageFilter
{

public:

  /** Run-time type information (and related methods). */
  mitkClassMacro(AwesomeImageFilter, ImageToImageFilter);

  itkNewMacro(Self);
  
  itkSetMacro(Offset, int);
  itkGetMacro(Offset, int);

protected:

  AwesomeImageFilter();
  ~AwesomeImageFilter();
  
  void GenerateData();
  
private:

  int m_Offset;
};

#endif // AwesomeImageFilter_h

