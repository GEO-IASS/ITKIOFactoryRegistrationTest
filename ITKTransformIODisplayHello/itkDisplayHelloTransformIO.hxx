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
#ifndef itkDisplayHelloTransformIO_hxx
#define itkDisplayHelloTransformIO_hxx

#include "itkDisplayHelloTransformIO.h"

#include "../itkStringifyType.hxx"

namespace itk
{
template<typename TParametersValueType>
DisplayHelloTransformIOTemplate<TParametersValueType>
::DisplayHelloTransformIOTemplate()
{}

template<typename TParametersValueType>
DisplayHelloTransformIOTemplate<TParametersValueType>
::~DisplayHelloTransformIOTemplate()
{}

template<typename TParametersValueType>
bool
DisplayHelloTransformIOTemplate<TParametersValueType>
::CanReadFile(const char *fileName)
{
  typedef itk::StringifyType<TParametersValueType> TypeName;

  if ( !fileName )
    {
    return false;
    }

  std::string recognizedFileName =
      std::string("TransformIO.") + TypeName::name + std::string(".hello");

  return std::string(fileName) == recognizedFileName;
}

template<typename TParametersValueType>
bool
DisplayHelloTransformIOTemplate<TParametersValueType>
::CanWriteFile(const char *fileName)
{
  typedef itk::StringifyType<TParametersValueType> TypeName;

  if ( !fileName )
    {
    return false;
    }

  std::string recognizedFileName =
      std::string("TransformIO.") + TypeName::name + std::string(".hello");

  return std::string(fileName) == recognizedFileName;
}

template<typename TParametersValueType>
void
DisplayHelloTransformIOTemplate<TParametersValueType>
::ReadComponentFile( std::string Value )
{
}

template<typename TParametersValueType>
void
DisplayHelloTransformIOTemplate<TParametersValueType>
::Read()
{
}

template<typename TParametersValueType>
void
DisplayHelloTransformIOTemplate<TParametersValueType>
::Write()
{
}
}

#endif
