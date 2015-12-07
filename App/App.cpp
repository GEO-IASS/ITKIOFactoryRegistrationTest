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

// ITK includes
#include <itkCreateObjectFunction.h>
#include <itkDynamicLoader.h>

#ifdef BUILD_ImageIO_PLUGIN
const char* what = "ImageIO";
# include <itkImageFileReader.h>
#endif
#ifdef BUILD_MeshIO_PLUGIN
const char* what = "MeshIO";
# include <itkMeshFileReader.h>
#endif
#ifdef BUILD_TransformIO_PLUGIN
const char* what = "TransformIO";
# include <itkTransformFileReader.h>
#endif
#ifdef BUILD_WithoutIO_PLUGIN
const char* what = "WithoutIO";
#endif

#ifdef INSTANTIATE_ImageIO
# include "itkImageIOBase.h"
# include "itkImageIOFactory.h"
#endif

#ifdef INSTANTIATE_MeshIO
# include "itkMeshIOFactory.h"
#endif

#ifdef INSTANTIATE_TransformIO
# include "itkTransformIOBase.h"
# include "itkTransformIOFactory.h"
#endif

#include "../itkInstantiateFactoryObjectTestHelper.hxx"

// STD includes
#include <cstdlib>
#include <cstring>

namespace
{
bool checkRegisteredFactories(int line, int expectedRegisteredFactoryCount)
{
  // List all registered factories
  std::list<itk::ObjectFactoryBase *> factories =
    itk::ObjectFactoryBase::GetRegisteredFactories();
  const unsigned int numFactories = factories.size();

  if (numFactories != expectedRegisteredFactoryCount)
    {
    std::cerr << "Line " << line << " - Problem with ITK " << what << " factory registration"
              << "\n\texpectedRegisteredFactoryCount: " << expectedRegisteredFactoryCount
              << "\n\tcurrentRegisteredFactoryCount: " << numFactories
              << std::endl;

    std::cerr << "Registered factories:" << std::endl;
    for ( std::list<itk::ObjectFactoryBase*>::iterator
            f = factories.begin();
          f != factories.end(); ++f )
      {
      std::cerr << "  " << (*f)->GetDescription() << std::endl;
      }

    return false;
    }
  return true;
}

}

/**
 * A file scope typedef to make the cast code to the load
 * function cleaner to read.
 */
typedef void ( *APP_HELLO_PLUGIN_SAY_HELLO_FUNCTION )();

int main(int argc, char* argv[])
{
  if (argc < 3)
    {
    std::cerr << "Failed to run " << argv[0]
              << "\nUsage: App"
              << " <expectedRegisteredFactoryCount>"
              << " /path/to/AppHelloPlugin|None"
              << " [--with-dynamic-io-factory]"
              << std::endl;
    return EXIT_FAILURE;
    }

  int expectedRegisteredFactoryCount = atoi(argv[1]);
  std::string appplugin_fullpath = argv[2];

  bool load_plugin = true;

  if ( appplugin_fullpath == "None" )
    {
    load_plugin = false;
    }

  bool with_dynamic_io_factory = false;

  if (argc > 3)
    {
    if ( strcmp(argv[3], "--with-dynamic-io-factory") == 0 )
      {
      with_dynamic_io_factory = true;
      }
    }

  int expectedRegisteredFactoryCountBeforePluginLoad = expectedRegisteredFactoryCount;

#if BUILD_WithoutIO_PLUGIN
   expectedRegisteredFactoryCountBeforePluginLoad = 0;

   if (!itk::instantiateFactoryObjects("APP",
                                       /* expectedImageIO= */ false,
                                       /* expectedMeshIO= */ false,
                                       /* expectedTransformIO= */ false))
     {
     return EXIT_FAILURE;
     }

#endif

  std::cout << "expectedRegisteredFactoryCountBeforePluginLoad: "
            << expectedRegisteredFactoryCountBeforePluginLoad << std::endl;

  std::cout << "expectedRegisteredFactoryCount: "
            << expectedRegisteredFactoryCount << std::endl;

  /**
   * Check that ITK factories are registered
   */
  if ( !checkRegisteredFactories(__LINE__, expectedRegisteredFactoryCountBeforePluginLoad) )
    {
    return EXIT_FAILURE;
    }

  if ( !load_plugin )
    {
    return EXIT_SUCCESS;
    }

  /**
   * Load application plugin
   */
  itk::LibHandle lib = itk::DynamicLoader::OpenLibrary( appplugin_fullpath.c_str() );
  if ( !lib )
    {
    std::cerr << "Line " << __LINE__ << " - Failed to load plugin"
              <<  "\n\tappplugin_fullpath:" << appplugin_fullpath
              << std::endl;
    return EXIT_FAILURE;
    }

  /**
   * Look for the entry point symbol in the library
   */
  const char* symbol = "AppHelloPlugin_DisplayHello";
  APP_HELLO_PLUGIN_SAY_HELLO_FUNCTION sayHellofunction =
    ( APP_HELLO_PLUGIN_SAY_HELLO_FUNCTION ) itk::DynamicLoader::GetSymbolAddress(lib, symbol);
  if ( !sayHellofunction )
    {
    std::cerr << "Line " << __LINE__ << " - Failed to load symbol from plugin"
              <<  "\n\tappplugin_fullpath:" << appplugin_fullpath
              <<  "\n\tsymbol:" << symbol
              << std::endl;
    return EXIT_FAILURE;
    }

  /**
   * Call plugin function
   */
  ( *sayHellofunction )( );
  
  /**
   * Check that no additional ITK factories have been registered
   */
  if ( !checkRegisteredFactories(__LINE__, expectedRegisteredFactoryCount) )
    {
    return EXIT_FAILURE;
    }

  if (with_dynamic_io_factory)
    {
    if (!itk::instantiateFactoryObjects("APP",
                                        /* expectedImageIO= */ true,
                                        /* expectedMeshIO= */ true,
                                        /* expectedTransformIO= */ true))
      {
      return EXIT_FAILURE;
      }
    }

  return EXIT_SUCCESS;
}
