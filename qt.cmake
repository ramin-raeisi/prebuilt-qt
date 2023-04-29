# Add qt bin folder to CMAKE_PREFIX_PATH to be found
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/bin)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Update qt.conf to redirect hard-coded paths to this qt folder
set(QT_CONF_ROOT ${CMAKE_CURRENT_LIST_DIR})
configure_file (
  "${CMAKE_CURRENT_LIST_DIR}/bin/qt.conf.in"
  "${CMAKE_CURRENT_LIST_DIR}/bin/qt.conf"
  )

# Resolve Qt4::qtmain error/warning by 
# defining qtmain imported library and its Qt4::qtmain alias
add_library(qtmain STATIC IMPORTED)
set_target_properties(qtmain PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/qtmain.lib
  )
add_library(Qt4::qtmain ALIAS qtmain)

include_directories(${CMAKE_CURRENT_LIST_DIR}/src)

# Keep backward compatibility with former build system 
macro(AziQt)
  find_package(Qt4 ${ARGN})
  include(${QT_USE_FILE})	
  include_directories(${CMAKE_CURRENT_BINARY_DIR})
  set(QtMajor 4)
endmacro(AziQt)
