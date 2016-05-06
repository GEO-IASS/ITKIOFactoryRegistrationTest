
# This sub directory allows to get the list of enabled Transform and
# Image IO factories without having to include the ITK use file
# from the top-level. 
#
# Keeping this call in separate directory ensures the global scope is
# not "polluted" by side effect of ITK use file inclusion.
#
# XXX Update of the infrastructure to avoid this hack will be
# done later.

find_package(ITK ${ITK_MINIMUM_REQUIRED_VERSION} REQUIRED)
include(${ITK_USE_FILE})

# --------------------------------------------------------------------------
# XXX Adapated from 'ADD_FACTORY_REGISTRATION' available in UseITK.cmake
macro(_update_enabled_io_list _type _module_name)
  list(FIND ITK_MODULES_REQUESTED ${_module_name} _module_was_requested)
  if(NOT ${_module_was_requested} EQUAL -1)

    if(NOT ${_module_name}_ENABLE_SHARED)
      message(FATAL_ERROR "${_module_name} is NOT shared library: Every Transform and Image IO factories are expected to be shared when ITK is build with BUILD_SHARED_LIBS ON")
    endif()

    list(APPEND LIST_OF_ENABLED_${_type}_MODULES ${_module_name})
  endif()
endmacro()

# --------------------------------------------------------------------------
function(_set_enabled_modules_global_property factory_type formats)
  string(TOUPPER ${factory_type} _qualifier_uc)
  string(TOLOWER ${factory_type} _factory_type_lc)

  set(LIST_OF_ENABLED_${_qualifier_uc}IO_MODULES )

  set(_qualifier "_${_factory_type_lc}")

  # For backward compatibility, ImageIO exceptions are set as
  # "<format>_(module|factory)_name" instead of "<format>_image_(module|factory)_name".
  if("${factory_type}" STREQUAL "Image")
    set(_qualifier "")
  endif()

  foreach(format ${formats})
    if(NOT DEFINED ${format}${_qualifier}_module_name)
      message(FATAL_ERROR "Variable '${format}${_qualifier}_module_name' is expected to be defined.")
    endif()
    _update_enabled_io_list("${_qualifier_uc}IO" "${${format}${_qualifier}_module_name}")
  endforeach()

  set_property(GLOBAL PROPERTY LIST_OF_ENABLED_${factory_type}IO_MODULES ${LIST_OF_ENABLED_${_qualifier_uc}IO_MODULES})
endfunction()

# --------------------------------------------------------------------------

_set_enabled_modules_global_property("Image" "${LIST_OF_IMAGEIO_FORMATS}")
_set_enabled_modules_global_property("Mesh" "${LIST_OF_MESHIO_FORMATS}")
_set_enabled_modules_global_property("Transform" "${LIST_OF_TRANSFORMIO_FORMATS}")

