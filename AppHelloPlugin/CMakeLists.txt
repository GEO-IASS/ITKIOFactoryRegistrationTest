
if(NOT DEFINED PLUGIN_FACTORY_TYPE)
  message(FATAL_ERROR "PLUGIN_FACTORY_TYPE is expected to be set to either ImageIO or TransformIO")
endif()

if(NOT DEFINED PLUGIN_NAME)
  message(FATAL_ERROR "PLUGIN_NAME is expected to be set")
endif()

project(${PLUGIN_NAME})

include(GenerateExportHeader)

message(STATUS "")
message(STATUS "Configuring ${CMAKE_PROJECT_NAME}:${PLUGIN_NAME}")

# --------------------------------------------------------------------------
# An application plugin loading ${PLUGIN_FACTORY_TYPE} factories
# --------------------------------------------------------------------------

find_package(
  ITK ${ITK_MINIMUM_REQUIRED_VERSION}
  COMPONENTS ${ITK_${PLUGIN_FACTORY_TYPE}_COMPONENTS} REQUIRED
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
    COMPILE_DEFINITIONS BUILD_${PLUGIN_FACTORY_TYPE}_PLUGIN
  )

generate_export_header(${PLUGIN_NAME} BASE_NAME apphelloplugin)

# Link against selected factories
foreach(factory_type "ImageIO" "TransformIO" "MeshIO")
  if(INSTANTIATE_${factory_type})
    target_link_libraries(${PLUGIN_NAME} ${INSTANTIATE_${factory_type}_TARGETS})
    include_directories(${INSTANTIATE_${factory_type}_INCLUDE_DIRS})
    set_property(TARGET ${PLUGIN_NAME}
      APPEND
      PROPERTY COMPILE_DEFINITIONS INSTANTIATE_${factory_type}
      )
  endif()
endforeach()



# --------------------------------------------------------------------------
# An standalone CLI linked against the plugin
# --------------------------------------------------------------------------

# TBD
