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

#include "DisplayHelloImageIOExport.h"

#include "itkDisplayHelloImageIOFactory.h"
#include "itkDisplayHelloImageIO.h"
#include "itkCreateObjectFunction.h"
#include "itkVersion.h"

// #define SPECIFIC_IMAGEIO_MODULE_TEST

/**
 * Routine that is called when the shared library is loaded by
 * itk::ObjectFactoryBase::LoadDynamicFactories().
 *
 * itkLoad() is C (not C++) function.
 */
extern "C" {
  DisplayHelloImageIO_EXPORT itk::ObjectFactoryBase* itkLoad();
}


itk::ObjectFactoryBase* itkLoad()
{
  static itk::DisplayHelloImageIOFactory::Pointer f
    = itk::DisplayHelloImageIOFactory::New();
  std::cout << DISPLAYHELLO_ImageIO_FACTORY_NAME << std::endl;
  return f;
}

namespace itk
{

DisplayHelloImageIOFactory::DisplayHelloImageIOFactory()
{
  this->RegisterOverride("itkImageIOBase",
                         "itkDisplayHelloImageIO",
                         "DisplayHello ImageIO",
                         1,
                         CreateObjectFunction<DisplayHelloImageIO>::New());
}

DisplayHelloImageIOFactory::~DisplayHelloImageIOFactory()
{
}

const char*
DisplayHelloImageIOFactory::GetITKSourceVersion(void) const
{
  return ITK_SOURCE_VERSION;
}

const char*
DisplayHelloImageIOFactory::GetDescription() const
{
  return "DisplayHello ImageIO Factory, displays its name when registered";
}

} // end namespace itk
