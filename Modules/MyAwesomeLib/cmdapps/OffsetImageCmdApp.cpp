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

// std includes
#include <algorithm>
#include <string>

// MITK includes
#include <mitkIOUtil.h>
#include <mitkCommandLineParser.h>
#include <AwesomeImageFilter.h>

/** \brief Example command line app that demonstrates the awesome filter
 *
 * This command line application will take the first given image and add the
 * provided offset to each voxel.
 */

int main(int argc, char *argv[])
{

  mitkCommandLineParser parser;

  // set general information about your command line app
  parser.setCategory("Awesome Cmd App");
  parser.setTitle("Offset Image");
  parser.setDescription("This command line application will take the given "
                        "image and add the provided offset to each voxel.");
  parser.setContributor("MBI");

  // how should arguments be prefixed
  parser.setArgumentPrefix("--", "-");
  // add each argument, unless specified otherwise each argument is optional
  // see mitkCommandLineParser::addArgument for more information
  parser.beginGroup("Required I/O parameters");
  parser.addArgument(
      "input", "i", mitkCommandLineParser::InputFile, "Input Image",
      "Any image format that a reader is registered for.", us::Any(), false);
  parser.addArgument("output", "o", mitkCommandLineParser::OutputFile,
                     "Output file",
                     "where to save the output, can be a different image "
                     "format from the input.",
                     us::Any(), false);
  parser.addArgument("offset", "f", mitkCommandLineParser::Int, "Offset",
                     "the offset integer to add to each voxel.", us::Any(),
                     false);
  parser.endGroup();

  parser.beginGroup("Optional parameters");
  parser.addArgument(
    "verbose", "v", mitkCommandLineParser::Bool, "Verbose Output", "Whether to produce verbose output");
  parser.endGroup();

  // parse arguments, this method returns a mapping of long argument names and their values
  std::map<std::string, us::Any> parsedArgs = parser.parseArguments(argc, argv);

  if (parsedArgs.size() == 0)
    return EXIT_FAILURE;

  // parse, cast and set required arguments
  std::string inFilename = us::any_cast<std::string>(parsedArgs["input"]);
  std::string outFileName = us::any_cast<std::string>(parsedArgs["output"]);
  int offset = us::any_cast<int>(parsedArgs["offset"]);

  // default values for optional arguments
  bool verbose(false);

  // parse, cast and set optional arguments if given
  if (parsedArgs.count("verbose"))
  {
    verbose = us::any_cast<bool>(parsedArgs["verbose"]);
  }

  try
  {
    // verbosity in this example is slightly over the top
    if (verbose)
    {
      MITK_INFO << "Trying to read file.";
    }

    std::vector<mitk::BaseData::Pointer> inVector = mitk::IOUtil::Load(inFilename);
    if (inVector.empty())
    {
      std::string errorMessage = "File at " + inFilename + " could not be read. Aborting.";
      MITK_ERROR << errorMessage;
      return EXIT_FAILURE;
    }
    mitk::BaseData *inBaseData = inVector.at(0);
    mitk::Image *inImage = dynamic_cast<mitk::Image *>(inBaseData);

    if (inImage == nullptr)
    {
      std::string errorMessage = "File at " + inFilename + " is not an image. Aborting.";
      MITK_ERROR << errorMessage;
      return EXIT_FAILURE;
    }
    if (verbose)
    {
      MITK_INFO << "Adding offset.";
    }

    AwesomeImageFilter::Pointer awesomeFilter = AwesomeImageFilter::New();
    awesomeFilter->SetInput(inImage);
    awesomeFilter->SetOffset(offset);
    awesomeFilter->Update();
    mitk::Image::Pointer outImage = dynamic_cast<mitk::Image*>( awesomeFilter->GetOutput());

    if (outImage.IsNull())
    {
      std::string errorMessage = "Image processing failed.";
      MITK_ERROR << errorMessage;
      return EXIT_FAILURE;
    }

    if (verbose)
    {
      MITK_INFO << "Trying to write to file.";
    }

    mitk::IOUtil::Save(outImage.GetPointer(), outFileName);

    return EXIT_SUCCESS;
  }

  catch (itk::ExceptionObject e)
  {
    MITK_ERROR << e;
    return EXIT_FAILURE;
  }
  catch (std::exception e)
  {
    MITK_ERROR << e.what();
    return EXIT_FAILURE;
  }
  catch (...)
  {
    MITK_ERROR << "Unexpected error encountered.";
    return EXIT_FAILURE;
  }
}
