
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
#message("LIST_OF_IMAGEIO_FORMATS: ${LIST_OF_IMAGEIO_FORMATS}")

set(LIST_OF_ENABLED_IMAGEIO_MODULES )

foreach(ImageFormat ${LIST_OF_IMAGEIO_FORMATS})
  _update_enabled_io_list("IMAGEIO" "${${ImageFormat}_module_name}")
endforeach()

set_property(GLOBAL PROPERTY LIST_OF_ENABLED_ImageIO_MODULES ${LIST_OF_ENABLED_IMAGEIO_MODULES})

# --------------------------------------------------------------------------
# XXX This variable is missing from UseITK.cmake
set(LIST_OF_TRANSFORMIO_FORMATS Matlab Txt HDF5 MINC)

#message("LIST_OF_TRANSFORMIO_FORMATS: ${LIST_OF_TRANSFORMIO_FORMATS}")

set(LIST_OF_ENABLED_TRANSFORMIO_MODULES )

foreach(TransformFormat ${LIST_OF_TRANSFORMIO_FORMATS})
  _update_enabled_io_list("TRANSFORMIO" "ITKIOTransform${TransformFormat}")
endforeach()

set_property(GLOBAL PROPERTY LIST_OF_ENABLED_TransformIO_MODULES ${LIST_OF_ENABLED_TRANSFORMIO_MODULES})
