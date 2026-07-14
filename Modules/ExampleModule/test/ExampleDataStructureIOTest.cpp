/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include <mitkTestFixture.h>
#include <mitkTestingMacros.h>

#include <ExampleDataStructure.h>

#include <mitkIOUtil.h>
#include <mitkNumericConstants.h>

#include <itksys/SystemTools.hxx>

// Exercises the reader and writer end to end through mitk::IOUtil, exactly the
// way the application does. This works because the IO submodule is autoloaded,
// so its reader and writer services are registered by the time the test runs.
class ExampleDataStructureIOTestSuite : public mitk::TestFixture
{
  CPPUNIT_TEST_SUITE(ExampleDataStructureIOTestSuite);
  MITK_TEST(SaveThenLoad_YieldsEqualData);
  CPPUNIT_TEST_SUITE_END();

private:
  ExampleDataStructure::Pointer m_Data;

public:
  void setUp() override
  {
    m_Data = ExampleDataStructure::New();

    mitk::Point3D first;
    first[0] = 1.0;
    first[1] = 2.0;
    first[2] = 3.0;
    m_Data->AddPoint("first", first);

    mitk::Point3D second;
    second[0] = -4.5;
    second[1] = 5.0;
    second[2] = 6.25;
    m_Data->AddPoint("second", second);
  }

  void tearDown() override
  {
    m_Data = nullptr;
  }

  void SaveThenLoad_YieldsEqualData()
  {
    const std::string path =
      mitk::IOUtil::GetTempPath() + mitk::IOUtil::GetDirectorySeparator() + "ExampleData.exampledata";

    mitk::IOUtil::Save(m_Data, path);
    auto loaded = mitk::IOUtil::Load<ExampleDataStructure>(path);
    itksys::SystemTools::RemoveFile(path.c_str());

    CPPUNIT_ASSERT_MESSAGE("Data loaded from file must equal the data that was saved.",
                           Equal(m_Data, loaded, mitk::eps, true));
  }
};

MITK_TEST_SUITE_REGISTRATION(ExampleDataStructureIO)
