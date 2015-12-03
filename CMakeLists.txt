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

set(ITKIODisplayHello_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/io)

add_subdirectory(App)
add_subdirectory(AppHelloPlugin)
add_subdirectory(ITKIODisplayHello)


# --------------------------------------------------------------------------
# Testing
# --------------------------------------------------------------------------

include(CTest)

set(testname ${PROJECT_NAME}_StaticIOFactory)
add_test(
  NAME ${testname}
  COMMAND $<TARGET_FILE:App> $<TARGET_FILE:AppHelloPluginLib>
  )
set_tests_properties(${testname}
  PROPERTIES
  PASS_REGULAR_EXPRESSION "^expectedRegisteredFactoryCount: 4\nHello\n$"
)

set(testname ${PROJECT_NAME}_StaticIOFactory_and_DynamicIOFactory)
add_test(
  NAME ${testname}
  COMMAND $<TARGET_FILE:App> $<TARGET_FILE:AppHelloPluginLib> --with-dynamic-io-factory
  )

if(CMAKE_CONFIGURATION_TYPES)
  set(ITKIODisplayHello_LIBRARY_OUTPUT_DIRECTORY "${ITKIODisplayHello_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIG>")
endif()

set_tests_properties(${testname}
  PROPERTIES
  PASS_REGULAR_EXPRESSION "^expectedRegisteredFactoryCount: 5\nDisplayHelloImageIOFactory\nHello\n$"
  ENVIRONMENT "ITK_AUTOLOAD_PATH=${ITKIODisplayHello_LIBRARY_OUTPUT_DIRECTORY}"
)

