
project(AppHelloPlugin)

include(GenerateExportHeader)

message(STATUS "Configuring ${CMAKE_PROJECT_NAME}:${PROJECT_NAME}")

# --------------------------------------------------------------------------
# Dependencies
# --------------------------------------------------------------------------

#
# ITK
#
set(ITK_IO_MODULES_USED
  ITKIOTIFF
  ITKIOMeta
  ITKIOTransformHDF5
  ITKIOTransformInsightLegacy
  )

set(${PROJECT_NAME}_ITK_COMPONENTS
  ITKIOImageBase
  ITKIOTransformBase
  ${ITK_IO_MODULES_USED}
  )
find_package(
  ITK ${ITK_MINIMUM_REQUIRED_VERSION}
  COMPONENTS ${${PROJECT_NAME}_ITK_COMPONENTS} REQUIRED
  )
include(${ITK_USE_FILE})

# --------------------------------------------------------------------------
# An application plugin
# --------------------------------------------------------------------------

set(PLUGIN_NAME ${PROJECT_NAME}Lib)

add_library(${PLUGIN_NAME} SHARED
  ${PROJECT_NAME}.h
  ${PROJECT_NAME}.cpp
  )
target_link_libraries(${PLUGIN_NAME} ${ITK_LIBRARIES})

generate_export_header(${PLUGIN_NAME})

# --------------------------------------------------------------------------
# An standalone CLI linked against the plugin
# --------------------------------------------------------------------------

# TBD
