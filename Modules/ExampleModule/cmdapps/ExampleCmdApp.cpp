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

#include <mitkCommandLineParser.h>
#include <mitkIOUtil.h>

#include <ExampleImageFilter.h>

#include <algorithm>
#include <string>

/** \brief Example command-line app that demonstrates the example image filter
 *
 * This command-line app will take the first given image and add the
 * provided offset to each voxel.
 */

int main(int argc, char* argv[])
{
  mitkCommandLineParser parser;

  // Set general information about your command-line app
  parser.setCategory("Example Cmd App Category");
  parser.setTitle("Example Cmd App");
  parser.setContributor("CAMIC");
  parser.setDescription(
    "This command-line app takes the given image and adds the provided offset to each voxel.");

  // How should arguments be prefixed
  parser.setArgumentPrefix("--", "-");

  // Add arguments. Unless specified otherwise, each argument is optional.
  // See mitkCommandLineParser::addArgument() for more information.
  parser.addArgument(
    "input",
    "i",
    mitkCommandLineParser::File,
    "Input Image",
    "Any image format known to MITK.",
    us::Any(),
    false);
  parser.addArgument(
    "output",
    "o",
    mitkCommandLineParser::File,
    "Output file",
    "Where to save the output.",
    us::Any(),
    false);
  parser.addArgument(
    "offset",
    "f",
    mitkCommandLineParser::Int,
    "Offset",
    "the offset integer to add to each voxel.",
    us::Any(),
    false);
  parser.addArgument( // optional
    "verbose",
    "v",
    mitkCommandLineParser::Bool,
    "Verbose Output",
    "Whether to produce verbose output");

  // Parse arguments. This method returns a mapping of long argument names to
  // their values.
  auto parsedArgs = parser.parseArguments(argc, argv);

  if (parsedArgs.empty())
    return EXIT_FAILURE; // Just exit, usage information was already printed.

  if (parsedArgs["input"].Empty() || parsedArgs["output"].Empty() || parsedArgs["offset"].Empty())
  {
    MITK_INFO << parser.helpText();
    return EXIT_FAILURE;
  }

  // Parse, cast and set required arguments
  auto inFilename = us::any_cast<std::string>(parsedArgs["input"]);
  auto outFilename = us::any_cast<std::string>(parsedArgs["output"]);
  auto offset = us::any_cast<int>(parsedArgs["offset"]);

  // Default values for optional arguments
  auto verbose = false;

  // Parse, cast and set optional arguments
  if (parsedArgs.end() != parsedArgs.find("verbose"))
    verbose = us::any_cast<bool>(parsedArgs["verbose"]);

  try
  {
    if (verbose)
      MITK_INFO << "Read input file";

    auto inImage = mitk::IOUtil::Load<mitk::Image>(inFilename);

    if (inImage.IsNull())
    {
      MITK_ERROR << "Could not read \"" << inFilename << "\"!";
      return EXIT_FAILURE;
    }

    if (verbose)
      MITK_INFO << "Add offset to image";

    auto exampleFilter = ExampleImageFilter::New();
    exampleFilter->SetInput(inImage);
    exampleFilter->SetOffset(offset);
    exampleFilter->Update();

    auto outImage = exampleFilter->GetOutput();

    if (nullptr == outImage)
    {
      MITK_ERROR << "Image processing failed!";
      return EXIT_FAILURE;
    }

    if (verbose)
      MITK_INFO << "Write output file";

    mitk::IOUtil::Save(outImage, outFilename);

    return EXIT_SUCCESS;
  }
  catch (const std::exception &e)
  {
    MITK_ERROR << e.what();
    return EXIT_FAILURE;
  }
  catch (...)
  {
    MITK_ERROR << "Unexpected error!";
    return EXIT_FAILURE;
  }
}
