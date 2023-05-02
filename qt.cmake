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

include_directories(${CMAKE_CURRENT_LIST_DIR}/src)

# Keep backward compatibility with former build system 
macro(AziQt)
  find_package(Qt4 ${ARGN})
  include(${QT_USE_FILE})	
  include_directories(${CMAKE_CURRENT_BINARY_DIR})
  set(QtMajor 4)
endmacro(AziQt)
