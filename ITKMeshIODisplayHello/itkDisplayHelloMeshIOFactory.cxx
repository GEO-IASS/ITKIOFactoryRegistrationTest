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

#include "DisplayHelloMeshIOExport.h"

#include "itkDisplayHelloMeshIO.h"
#include "itkDisplayHelloMeshIOFactory.h"
#include "itkVersion.h"

/**
 * Routine that is called when the shared library is loaded by
 * itk::ObjectFactoryBase::LoadDynamicFactories().
 *
 * itkLoad() is C (not C++) function.
 */
extern "C" {
  DisplayHelloMeshIO_EXPORT itk::ObjectFactoryBase* itkLoad();
}


itk::ObjectFactoryBase* itkLoad()
{
  static itk::DisplayHelloMeshIOFactory::Pointer f
    = itk::DisplayHelloMeshIOFactory::New();
  std::cout << DISPLAYHELLO_MeshIO_FACTORY_NAME << std::endl;
  return f;
}

namespace itk
{
void
DisplayHelloMeshIOFactory
::PrintSelf(std::ostream &, Indent) const
{}

DisplayHelloMeshIOFactory
::DisplayHelloMeshIOFactory()
{
  this->RegisterOverride( "itkMeshIOBase",
                         "itkDisplayHelloMeshIO",
                         "DisplayHello Mesh IO",
                         1,
                         CreateObjectFunction< DisplayHelloMeshIO >::New() );
}

DisplayHelloMeshIOFactory
::~DisplayHelloMeshIOFactory()
{}

const char *
DisplayHelloMeshIOFactory
::GetITKSourceVersion(void) const
{
  return ITK_SOURCE_VERSION;
}

const char *
DisplayHelloMeshIOFactory
::GetDescription() const
{
  return "DisplayHello Mesh IO Factory, displays its name when registered";
}

} // end namespace itk
