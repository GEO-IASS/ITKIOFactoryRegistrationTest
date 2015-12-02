project(App)

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

# By default factories are registered.
# set(ITK_NO_IO_FACTORY_REGISTER_MANAGER 0)

# --------------------------------------------------------------------------
# App Executable
# --------------------------------------------------------------------------

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})
