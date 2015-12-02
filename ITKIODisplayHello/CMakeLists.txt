
project(DisplayHelloImageIO)

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

set(io_factory_name ${PROJECT_NAME}Lib)
add_library(${io_factory_name} MODULE
  itk${PROJECT_NAME}.cxx
  itk${PROJECT_NAME}Factory.cxx
  )
target_link_libraries(${io_factory_name} LINK_PUBLIC ${ITK_LIBRARIES})
set_property(
  TARGET ${io_factory_name}
  PROPERTY LIBRARY_OUTPUT_DIRECTORY ${ITKIODisplayHello_LIBRARY_OUTPUT_DIRECTORY}
  )