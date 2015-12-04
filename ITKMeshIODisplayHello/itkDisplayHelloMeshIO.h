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

#ifndef itkDisplayHelloMeshIO_h
#define itkDisplayHelloMeshIO_h

#include "itkMeshIOBase.h"

namespace itk
{
/** \class DisplayHelloMeshIO
 * \brief MeshIO object that only display its name when registered.
 * \ingroup IOFilters
 * \ingroup ITKIOMesh
 */

class DisplayHelloMeshIO:public MeshIOBase
{
public:
  /** Standard class typedefs. */
  typedef DisplayHelloMeshIO           Self;
  typedef MeshIOBase                   Superclass;
  typedef SmartPointer< const Self >   ConstPointer;
  typedef SmartPointer< Self >         Pointer;

  typedef Superclass::SizeValueType    SizeValueType;
  typedef Superclass::StreamOffsetType StreamOffsetType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(DisplayHelloMeshIO, MeshIOBase);

  /*-------- This part of the interfaces deals with reading data. ----- */

  /** Determine if the file can be read with this MeshIO implementation.
  * \param FileNameToRead The name of the file to test for reading.
  * \post Sets classes MeshIOBase::m_FileName variable to be FileNameToWrite
  * \return Returns true if this MeshIO can read the file specified.
  */
  virtual bool CanReadFile(const char *FileNameToRead) ITK_OVERRIDE;

  /** Set the spacing and dimension information for the set filename. */
  virtual void ReadMeshInformation() ITK_OVERRIDE;

  /** Reads the data from disk into the memory buffer provided. */
  virtual void ReadPoints(void *buffer) ITK_OVERRIDE;

  virtual void ReadCells(void *buffer) ITK_OVERRIDE;

  virtual void ReadPointData(void *buffer) ITK_OVERRIDE;

  virtual void ReadCellData(void *buffer) ITK_OVERRIDE;

  /*-------- This part of the interfaces deals with writing data. ----- */

  /** Determine if the file can be written with this MeshIO implementation.
   * \param FileNameToWrite The name of the file to test for writing.
   * \post Sets classes MeshIOBase::m_FileName variable to be FileNameToWrite
   * \return Returns true if this MeshIO can write the file specified.
   */
  virtual bool CanWriteFile(const char *FileNameToWrite) ITK_OVERRIDE;

  /** Set the spacing and dimension information for the set filename. */
  virtual void WriteMeshInformation() ITK_OVERRIDE;

  /** Writes the data to disk from the memory buffer provided. Make sure
   * that the IORegions has been set properly. */
  virtual void WritePoints(void *buffer) ITK_OVERRIDE;

  virtual void WriteCells(void *buffer) ITK_OVERRIDE;

  virtual void WritePointData(void *buffer) ITK_OVERRIDE;

  virtual void WriteCellData(void *buffer) ITK_OVERRIDE;

  virtual void Write() ITK_OVERRIDE;

protected:
  DisplayHelloMeshIO();
  virtual ~DisplayHelloMeshIO();

  virtual void PrintSelf(std::ostream & os, Indent indent) const ITK_OVERRIDE;

private:
  DisplayHelloMeshIO(const Self &) ITK_DELETE_FUNCTION;
  void operator=(const Self &) ITK_DELETE_FUNCTION;
};
} // end namespace itk

#endif
