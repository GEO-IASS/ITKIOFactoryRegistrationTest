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

set(ITKImageIODisplayHello_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/imageio)

set(NAME_SUFFIX "0")
add_subdirectory(ITKImageIODisplayHello ITKImageIODisplayHello${NAME_SUFFIX})

set(NAME_SUFFIX "1")
add_subdirectory(ITKImageIODisplayHello ITKImageIODisplayHello${NAME_SUFFIX})

# --------------------------------------------------------------------------
# Build a custom ITK TransformIO plugins

set(ITKTransformIODisplayHello_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/transformio)

set(NAME_SUFFIX "0")
add_subdirectory(ITKTransformIODisplayHello ITKTransformIODisplayHello${NAME_SUFFIX})

set(NAME_SUFFIX "1")
add_subdirectory(ITKTransformIODisplayHello ITKTransformIODisplayHello${NAME_SUFFIX})

# --------------------------------------------------------------------------
# Build App without IO factories
set(FACTORY_TYPE "WithoutIO")

set(ITK_${FACTORY_TYPE}_MODULES_USED
  ITKCommon
  )

# Build App without static initialization
add_subdirectory(App App${FACTORY_TYPE})

# --------------------------------------------------------------------------
# ImageIO

set(FACTORY_TYPE ImageIO)
set(ITK_${FACTORY_TYPE}_MODULES_USED
  ITKIOImageBase
  ITKIOTIFF
  ITKIOMeta
  )

# Build App plugin
set(PLUGIN_NAME "AppHelloPluginLoading${FACTORY_TYPE}")
add_subdirectory(AppHelloPlugin ${PLUGIN_NAME})

# Build App
add_subdirectory(App App${FACTORY_TYPE})

# --------------------------------------------------------------------------
# TransformIO

set(FACTORY_TYPE TransformIO)
set(ITK_${FACTORY_TYPE}_MODULES_USED
  ITKIOTransformBase
  ITKIOTransformHDF5
  ITKIOTransformInsightLegacy
  )

# Build App plugin
set(PLUGIN_NAME "AppHelloPluginLoading${FACTORY_TYPE}")
add_subdirectory(AppHelloPlugin ${PLUGIN_NAME})

# Build App
add_subdirectory(App App${FACTORY_TYPE})


# --------------------------------------------------------------------------
# Testing
# --------------------------------------------------------------------------

include(CTest)

if(CMAKE_CONFIGURATION_TYPES)
  set(ITKImageIODisplayHello_LIBRARY_OUTPUT_DIRECTORY "${ITKImageIODisplayHello_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIG>")
  set(ITKTransformIODisplayHello_LIBRARY_OUTPUT_DIRECTORY "${ITKTransformIODisplayHello_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIG>")
endif()

macro(ITKIOFactoryRegistrationByAppPlugin_add_test)
  set(extra_args "None")
  set(testenv )
  set(expectedRegisteredFactoryCountBeforePluginLoad 0)
  set(qualifier "WithoutIO")
  if(NOT app_factory_type STREQUAL "WithoutIO")
    set(qualifier "WithStatic${app_factory_type}")
    set(expectedRegisteredFactoryCountBeforePluginLoad ${expectedRegisteredFactoryCount})
  endif()
  if(with_app_plugin)
    set(qualifier "${qualifier}_WithPlugin")
    set(extra_args $<TARGET_FILE:AppHelloPluginLoading${plugin_factory_type}>)
    if(NOT plugin_factory_type STREQUAL "WithoutIO")
      set(qualifier ${qualifier}_WithStatic${plugin_factory_type})
    else()
      set(qualifier ${qualifier}_WithoutStatic)
    endif()
    if(NOT plugin_dynamic_factory_type STREQUAL "WithoutIO")
      set(qualifier "${qualifier}_WithDynamic${plugin_dynamic_factory_type}")
      list(APPEND extra_args "--with-dynamic-io-factory")
      set(testenv ENVIRONMENT "ITK_AUTOLOAD_PATH=${ITK${plugin_dynamic_factory_type}DisplayHello_LIBRARY_OUTPUT_DIRECTORY}")
    endif()
  else()
    set(qualifier "${qualifier}_WithoutPlugin")
  endif()
  set(testname ${PROJECT_NAME}_${qualifier})
  add_test(
    NAME ${testname}
    COMMAND $<TARGET_FILE:App${app_factory_type}>
      ${expectedRegisteredFactoryCount}
      ${extra_args}
    )

  set(pass_regex "expectedRegisteredFactoryCountBeforePluginLoad: ${expectedRegisteredFactoryCountBeforePluginLoad}\n")
  set(pass_regex "${pass_regex}expectedRegisteredFactoryCount: ${expectedRegisteredFactoryCount}\n")
  if(NOT plugin_dynamic_factory_type STREQUAL "WithoutIO")
    set(pass_regex "${pass_regex}DisplayHello${plugin_dynamic_factory_type}_[01]\n")
    set(pass_regex "${pass_regex}DisplayHello${plugin_dynamic_factory_type}_[01]\n")
  endif()
  if(with_app_plugin)
    set(pass_regex "${pass_regex}Hello from plugin loading ${plugin_factory_type}\n")
  endif()
  set_tests_properties(${testname}
    PROPERTIES
      PASS_REGULAR_EXPRESSION "^${pass_regex}$"
      ${testenv}
  )
endmacro()

# --------------------------------------------------------------------------
set(with_app_plugin FALSE)
set(plugin_factory_type "WithoutIO")
set(plugin_dynamic_factory_type "WithoutIO")

# Check App without IOFactory has zero factory registered
set(expectedRegisteredFactoryCount 0)
set(app_factory_type "WithoutIO")
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check ImageIO statically initialized are loaded only once
set(expectedRegisteredFactoryCount 2)
set(app_factory_type "ImageIO")
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check TransformIO statically initialized are loaded only once
set(expectedRegisteredFactoryCount 2)
set(app_factory_type "TransformIO")
ITKIOFactoryRegistrationByAppPlugin_add_test()

# --------------------------------------------------------------------------
set(with_app_plugin TRUE)

# Check App without ImageIO and plugin has registered factories
set(expectedRegisteredFactoryCount 2)
set(app_factory_type "WithoutIO")
set(plugin_factory_type "ImageIO")
set(plugin_dynamic_factory_type "WithoutIO")
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check App without TransformIO and plugin has registered factories
set(expectedRegisteredFactoryCount 2)
set(app_factory_type "WithoutIO")
set(plugin_factory_type "TransformIO")
set(plugin_dynamic_factory_type "WithoutIO")
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check ImageIO statically initialized are loaded only once
set(expectedRegisteredFactoryCount 2)
set(app_factory_type "ImageIO")
set(plugin_factory_type "ImageIO")
set(plugin_dynamic_factory_type "WithoutIO")
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check TransformIO statically initialized are loaded only once
set(expectedRegisteredFactoryCount 2)
set(app_factory_type "TransformIO")
set(plugin_factory_type "TransformIO")
set(plugin_dynamic_factory_type "WithoutIO")
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check shared ImageIO along with statically initialized ones are loaded only once
set(expectedRegisteredFactoryCount 4)
set(app_factory_type "ImageIO")
set(plugin_factory_type "ImageIO")
set(plugin_dynamic_factory_type "ImageIO")
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check shared TransformIO along with statically initialized ones are loaded only once
set(expectedRegisteredFactoryCount 4)
set(app_factory_type "TransformIO")
set(plugin_factory_type "TransformIO")
set(plugin_dynamic_factory_type "TransformIO")
# XXX TransformIO plugin are not supported
#ITKIOFactoryRegistrationByAppPlugin_add_test()
