#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "armadillo" for configuration "Release"
set_property(TARGET armadillo APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(armadillo PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "-framework Accelerate;/usr/local/lib/libarpack.dylib;/usr/local/lib/libsuperlu.a"
  IMPORTED_LOCATION_RELEASE "/usr/local/Cellar/armadillo/6.100.0/lib/libarmadillo.6.10.0.dylib"
  IMPORTED_SONAME_RELEASE "libarmadillo.6.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS armadillo )
list(APPEND _IMPORT_CHECK_FILES_FOR_armadillo "/usr/local/Cellar/armadillo/6.100.0/lib/libarmadillo.6.10.0.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
