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
#ifndef itkDisplayHelloTransformIO_h
#define itkDisplayHelloTransformIO_h
#include "itkTransformIOBase.h"

namespace itk
{
/** \class DisplayHelloTransformIOTemplate
   * \brief TransformIO object that only display its name when registered.
   */
template<typename TParametersValueType>
class DisplayHelloTransformIOTemplate:public TransformIOBaseTemplate<TParametersValueType>
{
public:
  typedef DisplayHelloTransformIOTemplate               Self;
  typedef SmartPointer<Self>                            Pointer;

  /** Run-time type information (and related methods). */
  itkTypeMacro(DisplayHelloTransformIOTemplate, Superclass);
  itkNewMacro(Self);

  /** Determine the file type. Returns true if this ImageIO can read the
   * file specified. */
  virtual bool CanReadFile(const char *) ITK_OVERRIDE;

  /** Determine the file type. Returns true if this ImageIO can read the
   * file specified. */
  virtual bool CanWriteFile(const char *) ITK_OVERRIDE;

  /** Reads the data from disk into the memory buffer provided. */
  virtual void Read() ITK_OVERRIDE;

  /** Writes the data to disk from the memory buffer provided. Make sure
   * that the IORegions has been set properly. The buffer is cast to a
   * pointer to the beginning of the image data. */
  virtual void Write() ITK_OVERRIDE;

  /* Helper function for Read method, used for CompositeTransform reading. */
  void ReadComponentFile( std::string Value );

protected:
  DisplayHelloTransformIOTemplate();
  virtual ~DisplayHelloTransformIOTemplate();
};

/** This helps to meet backward compatibility */
typedef DisplayHelloTransformIOTemplate<double> DisplayHelloTransformIO;

}

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkDisplayHelloTransformIO.hxx"
#endif

#endif // itkDisplayHelloTransformIO_h
