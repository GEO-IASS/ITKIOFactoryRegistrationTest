
if(NOT DEFINED FACTORY_TYPE)
  message(FATAL_ERROR "FACTORY_TYPE is expected to be set to either ImageIO or TransformIO")
endif()

if(NOT DEFINED PLUGIN_NAME)
  message(FATAL_ERROR "PLUGIN_NAME is expected to be set")
endif()

project(${PLUGIN_NAME})

include(GenerateExportHeader)

message(STATUS "Configuring ${CMAKE_PROJECT_NAME}:${PLUGIN_NAME}")

# --------------------------------------------------------------------------
# An application plugin loading ${FACTORY_TYPE} factories
# --------------------------------------------------------------------------

set(${PROJECT_NAME}_ITK_COMPONENTS ${ITK_${FACTORY_TYPE}_MODULES_USED})
find_package(
  ITK ${ITK_MINIMUM_REQUIRED_VERSION}
  COMPONENTS ${${PROJECT_NAME}_ITK_COMPONENTS} REQUIRED
  )
include(${ITK_USE_FILE})

message(STATUS "ITK_MODULES_REQUESTED:${ITK_MODULES_REQUESTED}")

add_library(${PLUGIN_NAME} SHARED
  AppHelloPlugin.h
  AppHelloPlugin.cpp
  )
target_link_libraries(${PLUGIN_NAME} ${ITK_LIBRARIES})
set_target_properties(${PLUGIN_NAME}
  PROPERTIES
    COMPILE_DEFINITIONS BUILD_${FACTORY_TYPE}_PLUGIN
  )

generate_export_header(${PLUGIN_NAME} BASE_NAME apphelloplugin)

# --------------------------------------------------------------------------
# An standalone CLI linked against the plugin
# --------------------------------------------------------------------------

# TBD
