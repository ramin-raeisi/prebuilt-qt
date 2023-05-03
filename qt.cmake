if(${AZI_STATIC_LIBS})
  set(_linkstr lib)
else(${AZI_STATIC_LIBS})
  set(_linkstr dll)
endif(${AZI_STATIC_LIBS})

set(QT_ROOT ${CMAKE_CURRENT_LIST_DIR} CACHE PATH "Root to QT library")

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
