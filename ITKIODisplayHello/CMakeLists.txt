
if(NOT DEFINED NAME_SUFFIX)
  message(FATAL_ERROR "NAME_SUFFIX is expected to be set")
endif()

project(DisplayHelloImageIO_${NAME_SUFFIX})

message(STATUS "Configuring ${CMAKE_PROJECT_NAME}:${PROJECT_NAME}")

# --------------------------------------------------------------------------
# Dependencies
# --------------------------------------------------------------------------

#
# ITK
#

set(${PROJECT_NAME}_ITK_COMPONENTS
  ITKIOImageBase
  )
find_package(
  ITK ${ITK_MINIMUM_REQUIRED_VERSION}
  COMPONENTS ${${PROJECT_NAME}_ITK_COMPONENTS} REQUIRED
  )
include(${ITK_USE_FILE})

set(io_factory_name ${PROJECT_NAME})
add_library(${io_factory_name} MODULE
  itkDisplayHelloImageIO.cxx
  itkDisplayHelloImageIOFactory.cxx
  )
target_link_libraries(${io_factory_name} LINK_PUBLIC ${ITK_LIBRARIES})
set_target_properties(${io_factory_name}
  PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${ITKIODisplayHello_LIBRARY_OUTPUT_DIRECTORY}
    COMPILE_DEFINITIONS "DISPLAYHELLO_IMAGE_FACTORY_NAME=\"${PROJECT_NAME}\""
  )
