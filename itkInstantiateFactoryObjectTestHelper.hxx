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

#ifndef itkInstantiateFactoryObjectTestHelper_hxx
#define itkInstantiateFactoryObjectTestHelper_hxx

#include "itkStringifyType.hxx"

namespace itk
{

#ifdef INSTANTIATE_TransformIO

template<typename TParametersValueType>
bool instantiateTransformFactoryObject(const char* who, const char* fileName, bool expected)
{
  typedef itk::TransformIOBaseTemplate<TParametersValueType>  TransformIOType;
  typedef itk::TransformIOFactoryTemplate<TParametersValueType> TransformFactoryIOType;
  typedef itk::StringifyType<TParametersValueType> TypeName;

  bool result = expected;

  typename TransformIOType::Pointer transformIO;
  transformIO = TransformFactoryIOType::CreateTransformIO( fileName, itk::ReadMode );

  if ( transformIO.IsNull() )
    {
    result = false == expected;
    if ( !result )
      {
      std::cerr << "Failed to instantiate factory object reading " << fileName << std::endl;
      return false;
      }
    std::cout << who << "_INSTANTIATE_TransformIO_" << TypeName::name << " null" << std::endl;
    }
  else
    {
    result = true == expected;
    if ( !result )
      {
      std::cerr << "Instantiating factory object reading " << fileName << " is expected to FAIL" << std::endl;
      return false;
      }
    std::cout << who << "_INSTANTIATE_TransformIO_" << TypeName::name << " " << transformIO->GetNameOfClass() << std::endl;
    }

  return result;
}

#endif

bool instantiateFactoryObjects(const char* who,
                               bool expectedImageIO,
                               bool expectedMeshIO,
                               bool expectedTransformIO)
{
  bool result = true;
#ifdef INSTANTIATE_ImageIO
  {
  bool expected = expectedImageIO;
  itk::ImageIOBase::Pointer io;
  const char* factory_type = "ImageIO";
  const char* fileName = "ImageIO.hello";
  io = itk::ImageIOFactory::CreateImageIO( fileName, itk::ImageIOFactory::ReadMode );
  if ( io.IsNull() )
    {
    result = false == expected;
    if ( !result )
      {
      std::cerr << "Failed to instantiate factory object reading " << fileName << std::endl;
      return false;
      }
    std::cout << who << "_INSTANTIATE_" << factory_type << " null" << std::endl;
    }
  else
    {
    result = true == expected;
    if ( !result )
      {
      std::cerr << "Instantiating factory object reading " << fileName << " is expected to FAIL" << std::endl;
      return false;
      }
    std::cout << who << "_INSTANTIATE_" << factory_type << " " << io->GetNameOfClass() << std::endl;
    }
  }
#endif

#ifdef INSTANTIATE_MeshIO
  {
  bool expected = expectedMeshIO;
  itk::MeshIOBase::Pointer io;
  const char* factory_type = "MeshIO";
  const char* fileName = "MeshIO.hello";
  io = itk::MeshIOFactory::CreateMeshIO( fileName, itk::MeshIOFactory::ReadMode );
  if ( io.IsNull() )
    {
    result = false == expected;
    if ( !result )
      {
      std::cerr << "Failed to instantiate factory object reading " << fileName << std::endl;
      return false;
      }
    std::cout << who << "_INSTANTIATE_" << factory_type << " null" << std::endl;
    }
  else
    {
    result = true == expected;
    if ( !result )
      {
      std::cerr << "Instantiating factory object reading " << fileName << " is expected to FAIL" << std::endl;
      return false;
      }
    std::cout << who << "_INSTANTIATE_" << factory_type << " " << io->GetNameOfClass() << std::endl;
    }
  }
#endif

#ifdef INSTANTIATE_TransformIO
  if (!instantiateTransformFactoryObject<float>( who, "TransformIO.float.hello", expectedTransformIO )
      || !instantiateTransformFactoryObject<double>( who, "TransformIO.double.hello", expectedTransformIO ))
    {
    return false;
    }
#endif

  return result;
}

} // end namespace itk

#endif
