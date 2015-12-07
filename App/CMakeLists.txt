if(NOT DEFINED APP_FACTORY_TYPE)
  message(FATAL_ERROR "APP_FACTORY_TYPE is expected to be set.")
endif()

if(NOT DEFINED APP_NAME)
  message(FATAL_ERROR "APP_NAME is expected to be set")
endif()

project(${APP_NAME})

message(STATUS "")
message(STATUS "Configuring ${CMAKE_PROJECT_NAME}:${PROJECT_NAME}")

# --------------------------------------------------------------------------
# Dependencies
# --------------------------------------------------------------------------

#
# ITK
#

find_package(
  ITK ${ITK_MINIMUM_REQUIRED_VERSION}
  COMPONENTS ${ITK_${APP_FACTORY_TYPE}_COMPONENTS} REQUIRED
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
    COMPILE_DEFINITIONS BUILD_${APP_FACTORY_TYPE}_PLUGIN
  )

# Link against selected factories
foreach(factory_type "ImageIO" "TransformIO" "MeshIO")
  if(INSTANTIATE_${factory_type})
    target_link_libraries(${PROJECT_NAME} ${INSTANTIATE_${factory_type}_TARGETS})
    include_directories(${INSTANTIATE_${factory_type}_INCLUDE_DIRS})
    set_property(TARGET ${PROJECT_NAME}
      APPEND
      PROPERTY COMPILE_DEFINITIONS INSTANTIATE_${factory_type}
      )
  endif()
endforeach()
