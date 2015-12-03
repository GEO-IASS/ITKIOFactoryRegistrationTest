/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#include "itkDisplayHelloImageIO.h"
#include "itksys/RegularExpression.hxx"
#include <string.h>
#include <stdlib.h>

#define SPECIFIC_IMAGEIO_MODULE_TEST

namespace itk {

DisplayHelloImageIO
::DisplayHelloImageIO()
{
}

DisplayHelloImageIO
::~DisplayHelloImageIO()
{
}

bool
DisplayHelloImageIO
::CanReadFile(const char* filename)
{
  return false;
}

void
DisplayHelloImageIO
::ReadImageInformation()
{
}

// Read from the generated image
void
DisplayHelloImageIO
::Read(void *buffer)
{
}

bool
DisplayHelloImageIO
::CanWriteFile(const char* )
{
  return false;
}

void
DisplayHelloImageIO
::WriteImageInformation()
{
}

void
DisplayHelloImageIO
::Write(const void *)
{
}

void
DisplayHelloImageIO
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
}

} // end namespace itk
