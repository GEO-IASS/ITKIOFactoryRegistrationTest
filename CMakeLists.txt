cmake_minimum_required(VERSION 2.8.9 FATAL_ERROR)

foreach(p
    CMP0025 # CMake 3.0
    CMP0042 # CMake 3.0
    CMP0048 # CMake 3.0
    CMP0054 # CMake 3.1
    CMP0056 # CMake 3.2
    CMP0058 # CMake 3.3
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

project(ITKIOFactoryRegistrationByAppPlugin)

set(ITK_MINIMUM_REQUIRED_VERSION 4.8)

find_package(ITK ${ITK_MINIMUM_REQUIRED_VERSION} REQUIRED)

if(NOT ITK_BUILD_SHARED)
  message(WARNING "Skipping ${PROJECT_NAME}: Rebuild ITK with ITK_BUILD_SHARED_LIBS ON")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# --------------------------------------------------------------------------
# Build a custom ITK ImageIO plugin

set(ITKIODisplayHello_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/io)

set(NAME_SUFFIX "0")
add_subdirectory(ITKIODisplayHello ITKIODisplayHello${NAME_SUFFIX})

set(NAME_SUFFIX "1")
add_subdirectory(ITKIODisplayHello ITKIODisplayHello${NAME_SUFFIX})

# --------------------------------------------------------------------------
# Build App without IO factories
set(FACTORY_TYPE "WithoutIO")

set(ITK_${FACTORY_TYPE}_MODULES_USED
  ITKCommon
  )

add_subdirectory(App App${FACTORY_TYPE})

# --------------------------------------------------------------------------
# ImageIO

set(FACTORY_TYPE ImageIO)
set(ITK_${FACTORY_TYPE}_MODULES_USED
  ITKIOImageBase
  ITKIOTIFF
  ITKIOMeta
  )

# Build App plugin loading factories
set(PLUGIN_NAME "AppHelloPluginLoading${FACTORY_TYPE}")
add_subdirectory(AppHelloPlugin ${PLUGIN_NAME})

# Build App loading factories
add_subdirectory(App App${FACTORY_TYPE})

# --------------------------------------------------------------------------
# TransformIO

set(FACTORY_TYPE TransformIO)
set(ITK_${FACTORY_TYPE}_MODULES_USED
  ITKIOTransformBase
  ITKIOTransformHDF5
  ITKIOTransformInsightLegacy
  )

# Build App plugin loading factories
set(PLUGIN_NAME "AppHelloPluginLoading${FACTORY_TYPE}")
add_subdirectory(AppHelloPlugin ${PLUGIN_NAME})

# Build App loading factories
add_subdirectory(App App${FACTORY_TYPE})


# --------------------------------------------------------------------------
# Testing
# --------------------------------------------------------------------------

include(CTest)

if(CMAKE_CONFIGURATION_TYPES)
  set(ITKIODisplayHello_LIBRARY_OUTPUT_DIRECTORY "${ITKIODisplayHello_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIG>")
endif()

macro(ITKIOFactoryRegistrationByAppPlugin_add_test)
  set(extra_args $<TARGET_FILE:AppHelloPluginLoading${factory_type}>)
  set(qualifier "Static")
  if(factory_type STREQUAL "WithoutIO")
    set(extra_args "None")
    set(qualifier )
  endif()
  set(testname ${PROJECT_NAME}_${qualifier}${factory_type})
  set(testenv )
  if(with_dynamic_io_factory)
    set(testname "${testname}WithDynamicIOFactory")
    list(APPEND extra_args "--with-dynamic-io-factory")
    set(testenv ENVIRONMENT "ITK_AUTOLOAD_PATH=${ITKIODisplayHello_LIBRARY_OUTPUT_DIRECTORY}")
  endif()
  add_test(
    NAME ${testname}
    COMMAND $<TARGET_FILE:App${factory_type}>
      ${expectedRegisteredFactoryCount}
      ${extra_args}
    )
  set(pass_regex "expectedRegisteredFactoryCount: ${expectedRegisteredFactoryCount}\n")
  if(with_dynamic_io_factory)
    set(pass_regex "${pass_regex}DisplayHello${factory_type}_[01]\n")
    set(pass_regex "${pass_regex}DisplayHello${factory_type}_[01]\n")
  endif()
  if(NOT factory_type STREQUAL "WithoutIO")
    set(pass_regex "${pass_regex}Hello from plugin loading ${factory_type}\n")
  endif()
  set_tests_properties(${testname}
    PROPERTIES
      PASS_REGULAR_EXPRESSION "^${pass_regex}$"
      ${testenv}
  )
endmacro()

# Check App without IOFactory has zero factory registered
set(expectedRegisteredFactoryCount 0)
set(factory_type "WithoutIO")
set(with_dynamic_io_factory FALSE)
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check ImageIO statically initialized are loaded only once
set(expectedRegisteredFactoryCount 2)
set(factory_type "ImageIO")
set(with_dynamic_io_factory FALSE)
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check TransformIO statically initialized are loaded only once
set(expectedRegisteredFactoryCount 2)
set(factory_type "TransformIO")
set(with_dynamic_io_factory FALSE)
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check shared ImageIO along with statically initialized ones are loaded only once
set(expectedRegisteredFactoryCount 4)
set(factory_type "ImageIO")
set(with_dynamic_io_factory TRUE)
ITKIOFactoryRegistrationByAppPlugin_add_test()
