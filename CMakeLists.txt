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
add_subdirectory(HackForIOList)

message(STATUS "")
get_property(LIST_OF_ENABLED_ImageIO_MODULES GLOBAL PROPERTY LIST_OF_ENABLED_ImageIO_MODULES)
message(STATUS "LIST_OF_ENABLED_ImageIO_MODULES: ${LIST_OF_ENABLED_ImageIO_MODULES}")

get_property(LIST_OF_ENABLED_MeshIO_MODULES GLOBAL PROPERTY LIST_OF_ENABLED_MeshIO_MODULES)
message(STATUS "LIST_OF_ENABLED_MeshIO_MODULES: ${LIST_OF_ENABLED_MeshIO_MODULES}")

get_property(LIST_OF_ENABLED_TransformIO_MODULES GLOBAL PROPERTY LIST_OF_ENABLED_TransformIO_MODULES)
message(STATUS "LIST_OF_ENABLED_TransformIO_MODULES: ${LIST_OF_ENABLED_TransformIO_MODULES}")

# --------------------------------------------------------------------------
# Macro to build custom IO factories given a factory type

macro(build_custom_io_factories factory_type)

  message(STATUS "")

  set(INSTANTIATE_${factory_type}_TARGETS )
  set(INSTANTIATE_${factory_type}_INCLUDE_DIRS )

  string(TOLOWER ${factory_type} output_dir)

  set(ITK${factory_type}DisplayHello_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${output_dir})

  set(NAME_SUFFIX "0")
  add_subdirectory(ITK${factory_type}DisplayHello ITK${factory_type}DisplayHello${NAME_SUFFIX})

  list(APPEND INSTANTIATE_${factory_type}_TARGETS
    DisplayHello${factory_type}_${NAME_SUFFIX}
    )

  list(APPEND INSTANTIATE_${factory_type}_INCLUDE_DIRS
    ${DisplayHello${factory_type}_${NAME_SUFFIX}_SOURCE_DIR}
    )

  set(NAME_SUFFIX "1")
  add_subdirectory(ITK${factory_type}DisplayHello ITK${factory_type}DisplayHello${NAME_SUFFIX})

  list(APPEND INSTANTIATE_${factory_type}_TARGETS
    DisplayHello${factory_type}_${NAME_SUFFIX}
    )

  list(APPEND INSTANTIATE_${factory_type}_INCLUDE_DIRS
    ${DisplayHello${factory_type}_${NAME_SUFFIX}_SOURCE_DIR}
    )

  set(DYNAMIC_${factory_type}_COUNT 2)

  message(STATUS "Number of custom dynamic '${factory_type}' factories: ${DYNAMIC_${factory_type}_COUNT}")

  list(APPEND INSTANTIATE_${factory_type}_INCLUDE_DIRS
    ${${factory_type}_INCLUDE_DIRS}
    )
endmacro()

# --------------------------------------------------------------------------
# Build a custom IO factories

build_custom_io_factories("ImageIO")
build_custom_io_factories("MeshIO")
build_custom_io_factories("TransformIO")

# --------------------------------------------------------------------------
# Macro allowing to disable io factories instantiation
macro(disable_io_factories_instantiation)
  set(INSTANTIATE_ImageIO 0)
  set(INSTANTIATE_MeshIO 0)
  set(INSTANTIATE_TransformIO 0)
endmacro()

# --------------------------------------------------------------------------
# Macro to find and include ITK considering factory type
macro(define_itk_components)
  if("${APP_MAIN_${FACTORY_TYPE}_ITK_COMPONENT}" STREQUAL "")
    message(FATAL_ERROR "APP_MAIN_${FACTORY_TYPE}_ITK_COMPONENT is expected to be set !")
  endif()
  set(ITK_${FACTORY_TYPE}_MODULES_USED
    ${LIST_OF_ENABLED_${FACTORY_TYPE}_MODULES}
    )
  set(ITK_${FACTORY_TYPE}_COMPONENTS
    ${APP_MAIN_${FACTORY_TYPE}_ITK_COMPONENT}
    ${ITK_${FACTORY_TYPE}_MODULES_USED}
    )
endmacro()

set(LIST_OF_ENABLED_WithoutIO_MODULES )

set(APP_MAIN_WithoutIO_ITK_COMPONENT ITKCommon)
set(APP_MAIN_ImageIO_ITK_COMPONENT ITKIOImageBase)
set(APP_MAIN_MeshIO_ITK_COMPONENT ITKIOMeshBase)
set(APP_MAIN_TransformIO_ITK_COMPONENT ITKIOTransformBase)

# --------------------------------------------------------------------------
# Build App without IO factories

set(FACTORY_TYPE "WithoutIO")
define_itk_components()

# Build App without static initialization
set(APP_FACTORY_TYPE ${FACTORY_TYPE})
set(APP_NAME "App${APP_FACTORY_TYPE}")
disable_io_factories_instantiation()
set(INSTANTIATE_ImageIO 1)
set(INSTANTIATE_MeshIO 1)
set(INSTANTIATE_TransformIO 1)
add_subdirectory(App ${APP_NAME})

# --------------------------------------------------------------------------
# ImageIO

set(FACTORY_TYPE ImageIO)
define_itk_components()

# Build App plugin
set(PLUGIN_NAME "AppHelloPluginLoading${FACTORY_TYPE}")
set(PLUGIN_FACTORY_TYPE ${FACTORY_TYPE})
disable_io_factories_instantiation()
add_subdirectory(AppHelloPlugin ${PLUGIN_NAME})

# Build App
set(APP_FACTORY_TYPE ${FACTORY_TYPE})
set(APP_NAME "App${APP_FACTORY_TYPE}")
disable_io_factories_instantiation()
set(INSTANTIATE_ImageIO 1)
add_subdirectory(App ${APP_NAME})

# --------------------------------------------------------------------------
# MeshIO

set(FACTORY_TYPE MeshIO)
define_itk_components()

# Build App plugin
set(PLUGIN_NAME "AppHelloPluginLoading${FACTORY_TYPE}")
set(PLUGIN_FACTORY_TYPE ${FACTORY_TYPE})
disable_io_factories_instantiation()
add_subdirectory(AppHelloPlugin ${PLUGIN_NAME})

# Build App
set(APP_FACTORY_TYPE ${FACTORY_TYPE})
set(APP_NAME "App${APP_FACTORY_TYPE}")
disable_io_factories_instantiation()
set(INSTANTIATE_MeshIO 1)
add_subdirectory(App ${APP_NAME})

# --------------------------------------------------------------------------
# TransformIO

set(FACTORY_TYPE TransformIO)
define_itk_components()

# Build App plugin
set(PLUGIN_NAME "AppHelloPluginLoading${FACTORY_TYPE}")
set(PLUGIN_FACTORY_TYPE ${FACTORY_TYPE})
disable_io_factories_instantiation()
add_subdirectory(AppHelloPlugin ${PLUGIN_NAME})

# Build App
set(APP_FACTORY_TYPE ${FACTORY_TYPE})
set(APP_NAME "App${APP_FACTORY_TYPE}")
disable_io_factories_instantiation()
set(INSTANTIATE_TransformIO 1)
add_subdirectory(App ${APP_NAME})

# --------------------------------------------------------------------------
# Testing
# --------------------------------------------------------------------------

include(CTest)

if(CMAKE_CONFIGURATION_TYPES)
  set(ITKImageIODisplayHello_LIBRARY_OUTPUT_DIRECTORY "${ITKImageIODisplayHello_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIG>")
  set(ITKMeshIODisplayHello_LIBRARY_OUTPUT_DIRECTORY "${ITKMeshIODisplayHello_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIG>")
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

  set(pass_regex )
  if(app_factory_type STREQUAL "WithoutIO")
    set(pass_regex "${pass_regex}APP_INSTANTIATE_ImageIO null\n")
    set(pass_regex "${pass_regex}APP_INSTANTIATE_MeshIO null\n")
    set(pass_regex "${pass_regex}APP_INSTANTIATE_TransformIO_float null\n")
    set(pass_regex "${pass_regex}APP_INSTANTIATE_TransformIO_double null\n")
  endif()
  set(pass_regex "${pass_regex}expectedRegisteredFactoryCountBeforePluginLoad: ${expectedRegisteredFactoryCountBeforePluginLoad}\n")
  set(pass_regex "${pass_regex}expectedRegisteredFactoryCount: ${expectedRegisteredFactoryCount}\n")
  if(NOT plugin_dynamic_factory_type STREQUAL "WithoutIO")
    set(pass_regex "${pass_regex}DisplayHello${plugin_dynamic_factory_type}_[01]\n")
    set(pass_regex "${pass_regex}DisplayHello${plugin_dynamic_factory_type}_[01]\n")
  endif()
  if(with_app_plugin)
    set(pass_regex "${pass_regex}Hello from plugin loading ${plugin_factory_type}\n")
  endif()
  if(NOT plugin_dynamic_factory_type STREQUAL "WithoutIO")
    if(plugin_dynamic_factory_type STREQUAL "ImageIO")
      set(pass_regex "${pass_regex}APP_INSTANTIATE_ImageIO DisplayHelloImageIO\n")
    endif()
    if(plugin_dynamic_factory_type STREQUAL "MeshIO")
      set(pass_regex "${pass_regex}APP_INSTANTIATE_MeshIO DisplayHelloMeshIO\n")
    endif()
    if(plugin_dynamic_factory_type STREQUAL "TransformIO")
      set(pass_regex "${pass_regex}APP_INSTANTIATE_TransformIO_float DisplayHelloTransformIOTemplate\n")
      set(pass_regex "${pass_regex}APP_INSTANTIATE_TransformIO_double DisplayHelloTransformIOTemplate\n")
    endif()
  endif()
  set_tests_properties(${testname}
    PROPERTIES
      PASS_REGULAR_EXPRESSION "^${pass_regex}$"
      ${testenv}
  )
endmacro()


# --------------------------------------------------------------------------
# This variables will be used to compute the number of expected registered
# factories.
list(LENGTH ITK_ImageIO_MODULES_USED STATIC_ImageIO_COUNT)
list(LENGTH ITK_MeshIO_MODULES_USED STATIC_MeshIO_COUNT)
list(LENGTH ITK_TransformIO_MODULES_USED STATIC_TransformIO_COUNT)

message(STATUS "")
foreach(factory_type "ImageIO" "MeshIO" "TransformIO")
  message(STATUS "Number of expected statically initialized '${factory_type}' factories: ${STATIC_${factory_type}_COUNT}")
endforeach()

# --------------------------------------------------------------------------
set(with_app_plugin FALSE)
set(plugin_factory_type "WithoutIO")
set(plugin_dynamic_factory_type "WithoutIO")

# Check App without IOFactory has zero factory registered
set(app_factory_type "WithoutIO")
set(expectedRegisteredFactoryCount 0)
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check ImageIO statically initialized are loaded only once
set(app_factory_type "ImageIO")
set(expectedRegisteredFactoryCount ${STATIC_${app_factory_type}_COUNT})
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check MeshIO statically initialized are loaded only once
set(app_factory_type "MeshIO")
set(expectedRegisteredFactoryCount ${STATIC_${app_factory_type}_COUNT})
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check TransformIO statically initialized are loaded only once
set(app_factory_type "TransformIO")
set(expectedRegisteredFactoryCount ${STATIC_${app_factory_type}_COUNT})
ITKIOFactoryRegistrationByAppPlugin_add_test()

# --------------------------------------------------------------------------
set(with_app_plugin TRUE)

# Check App without ImageIO and plugin has registered factories
set(app_factory_type "WithoutIO")
set(plugin_factory_type "ImageIO")
set(expectedRegisteredFactoryCount ${STATIC_${plugin_factory_type}_COUNT})
set(plugin_dynamic_factory_type "WithoutIO")
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check App without MeshIO and plugin has registered factories
set(app_factory_type "WithoutIO")
set(plugin_factory_type "MeshIO")
set(expectedRegisteredFactoryCount ${STATIC_${plugin_factory_type}_COUNT})
set(plugin_dynamic_factory_type "WithoutIO")
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check App without TransformIO and plugin has registered factories
set(app_factory_type "WithoutIO")
set(plugin_factory_type "TransformIO")
set(expectedRegisteredFactoryCount ${STATIC_${plugin_factory_type}_COUNT})
set(plugin_dynamic_factory_type "WithoutIO")
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check ImageIO statically initialized are loaded only once
set(app_factory_type "ImageIO")
set(plugin_factory_type "ImageIO")
set(expectedRegisteredFactoryCount ${STATIC_${plugin_factory_type}_COUNT})
set(plugin_dynamic_factory_type "WithoutIO")
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check MeshIO statically initialized are loaded only once
set(app_factory_type "MeshIO")
set(plugin_factory_type "MeshIO")
set(expectedRegisteredFactoryCount ${STATIC_${plugin_factory_type}_COUNT})
set(plugin_dynamic_factory_type "WithoutIO")
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check TransformIO statically initialized are loaded only once
set(app_factory_type "TransformIO")
set(plugin_factory_type "TransformIO")
set(expectedRegisteredFactoryCount ${STATIC_${plugin_factory_type}_COUNT})
set(plugin_dynamic_factory_type "WithoutIO")
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check shared ImageIO along with statically initialized ones are loaded only once
set(app_factory_type "ImageIO")
set(plugin_factory_type "ImageIO")
set(plugin_dynamic_factory_type "ImageIO")
math(EXPR expectedRegisteredFactoryCount "${STATIC_${plugin_factory_type}_COUNT} + ${DYNAMIC_${plugin_dynamic_factory_type}_COUNT}")
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check shared MeshIO along with statically initialized ones are loaded only once
set(app_factory_type "MeshIO")
set(plugin_factory_type "MeshIO")
set(plugin_dynamic_factory_type "MeshIO")
math(EXPR expectedRegisteredFactoryCount "${STATIC_${plugin_factory_type}_COUNT} + ${DYNAMIC_${plugin_dynamic_factory_type}_COUNT}")
ITKIOFactoryRegistrationByAppPlugin_add_test()

# Check shared TransformIO along with statically initialized ones are loaded only once
set(app_factory_type "TransformIO")
set(plugin_factory_type "TransformIO")
set(plugin_dynamic_factory_type "TransformIO")
math(EXPR expectedRegisteredFactoryCount "${STATIC_${plugin_factory_type}_COUNT} + ${DYNAMIC_${plugin_dynamic_factory_type}_COUNT}")
ITKIOFactoryRegistrationByAppPlugin_add_test()
