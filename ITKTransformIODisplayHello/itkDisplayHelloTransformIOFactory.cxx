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
#include "itkDisplayHelloTransformIOFactory.h"
#include "itkCreateObjectFunction.h"
#include "itkDisplayHelloTransformIO.h"
#include "itkVersion.h"

namespace itk
{
void DisplayHelloTransformIOFactory::PrintSelf(std::ostream &, Indent) const
{}

DisplayHelloTransformIOFactory::DisplayHelloTransformIOFactory()
{
  std::cout << DISPLAYHELLO_TRANSFORM_FACTORY_NAME << std::endl;

  this->RegisterOverride( "itkTransformIOBaseTemplate",
                          "itkDisplayHelloTransformIO",
                          "DisplayHello Transform float IO",
                          1,
                          CreateObjectFunction< DisplayHelloTransformIOTemplate< float > >::New() );
  this->RegisterOverride( "itkTransformIOBaseTemplate",
                          "itkDisplayHelloTransformIO",
                          "DisplayHello Transform double IO",
                          1,
                          CreateObjectFunction< DisplayHelloTransformIOTemplate< double > >::New() );
}

DisplayHelloTransformIOFactory::~DisplayHelloTransformIOFactory()
{}

const char *
DisplayHelloTransformIOFactory::GetITKSourceVersion(void) const
{
  return ITK_SOURCE_VERSION;
}

const char *
DisplayHelloTransformIOFactory::GetDescription() const
{
  return "DisplayHello TransformIO Factory, displays its name when registered";
}

// Undocumented API used to register during static initialization.
// DO NOT CALL DIRECTLY.
static bool DisplayHelloTransformIOFactoryHasBeenRegistered;

void DisplayHelloTransformIOFactoryRegister__Private(void)
{
  if( ! DisplayHelloTransformIOFactoryHasBeenRegistered )
    {
    DisplayHelloTransformIOFactoryHasBeenRegistered = true;
    DisplayHelloTransformIOFactory::RegisterOneFactory();
    }
}
} // end namespace itk
