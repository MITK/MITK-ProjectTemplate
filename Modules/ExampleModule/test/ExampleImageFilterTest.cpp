/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include <mitkTestFixture.h>
#include <mitkTestingMacros.h>

#include <ExampleImageFilter.h>

#include <mitkImageCast.h>
#include <mitkImagePixelReadAccessor.h>

#include <itkImage.h>

// A CppUnit test suite for ExampleImageFilter. It builds a tiny synthetic image
// in memory so the test needs no external data and runs anywhere.
class ExampleImageFilterTestSuite : public mitk::TestFixture
{
  CPPUNIT_TEST_SUITE(ExampleImageFilterTestSuite);
  MITK_TEST(AddOffset_ShiftsEveryVoxel);
  MITK_TEST(ZeroOffset_LeavesImageUnchanged);
  CPPUNIT_TEST_SUITE_END();

private:
  mitk::Image::Pointer m_Image;

public:
  // setUp() runs before every test case, giving each a fresh 4x4x4 image whose
  // voxels are all 10.
  void setUp() override
  {
    using ImageType = itk::Image<short, 3>;

    auto itkImage = ImageType::New();

    ImageType::SizeType size;
    size.Fill(4);

    ImageType::RegionType region;
    region.SetSize(size);

    itkImage->SetRegions(region);
    itkImage->Allocate();
    itkImage->FillBuffer(10);

    mitk::CastToMitkImage(itkImage, m_Image);
  }

  void tearDown() override
  {
    m_Image = nullptr;
  }

  short GetFirstVoxel(const mitk::Image* image)
  {
    mitk::ImagePixelReadAccessor<short, 3> accessor(image);
    itk::Index<3> index;
    index.Fill(0);
    return accessor.GetPixelByIndex(index);
  }

  void AddOffset_ShiftsEveryVoxel()
  {
    auto filter = ExampleImageFilter::New();
    filter->SetInput(m_Image);
    filter->SetOffset(5);
    filter->Update();

    mitk::Image::Pointer output = filter->GetOutput();

    CPPUNIT_ASSERT_MESSAGE("Filter output must be initialized.",
                           output.IsNotNull() && output->IsInitialized());
    CPPUNIT_ASSERT_MESSAGE("Every voxel should be shifted by the offset (10 + 5).",
                           this->GetFirstVoxel(output) == 15);
  }

  void ZeroOffset_LeavesImageUnchanged()
  {
    auto filter = ExampleImageFilter::New();
    filter->SetInput(m_Image);
    filter->SetOffset(0);
    filter->Update();

    CPPUNIT_ASSERT_MESSAGE("A zero offset must not change any voxel.",
                           this->GetFirstVoxel(filter->GetOutput()) == 10);
  }
};

MITK_TEST_SUITE_REGISTRATION(ExampleImageFilter)
