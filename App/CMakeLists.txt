if(NOT DEFINED FACTORY_TYPE)
  message(FATAL_ERROR "FACTORY_TYPE is expected to be set to either ImageIO or TransformIO")
endif()

project(App${FACTORY_TYPE})

message(STATUS "Configuring ${CMAKE_PROJECT_NAME}:${PROJECT_NAME}")

# --------------------------------------------------------------------------
# Dependencies
# --------------------------------------------------------------------------

#
# ITK
#

find_package(
  ITK ${ITK_MINIMUM_REQUIRED_VERSION}
  COMPONENTS ${ITK_${FACTORY_TYPE}_COMPONENTS} REQUIRED
  )
include(${ITK_USE_FILE})

message(STATUS "ITK_MODULES_REQUESTED:${ITK_MODULES_REQUESTED}")

# --------------------------------------------------------------------------
# App Executable
# --------------------------------------------------------------------------

add_executable(${PROJECT_NAME} App.cpp)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})
set_target_properties(${PROJECT_NAME}
  PROPERTIES
    COMPILE_DEFINITIONS BUILD_${FACTORY_TYPE}_PLUGIN
  )