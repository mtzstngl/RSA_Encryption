cmake_minimum_required (VERSION 2.8.8)
project (rsa_encryption)
add_definitions(-std=c++11)

# make Makefile with verbose output
set(CMAKE_VERBOSE_MAKEFILE OFF)

# run cmake .. within ./build so there is no mess
# build rsa encryption with large number support

# START_FINDGMP copied from DGtal
if (GMP_INCLUDE_DIR AND GMP_LIBRARIES)
  # Already in cache, be silent
  set(GMP_FIND_QUIETLY TRUE)
endif (GMP_INCLUDE_DIR AND GMP_LIBRARIES)

find_path(GMP_INCLUDE_DIR NAMES gmp.h )
find_library(GMP_LIBRARIES NAMES gmp libgmp )
find_library(GMPXX_LIBRARIES NAMES gmpxx libgmpxx )
MESSAGE(STATUS "GMP libs: " ${GMP_LIBRARIES} " " ${GMPXX_LIBRARIES} )

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GMP DEFAULT_MSG GMP_INCLUDE_DIR GMP_LIBRARIES)

mark_as_advanced(GMP_INCLUDE_DIR GMP_LIBRARIES)
# END_FINDGMP copied from DGtal

# START_QTGUI
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
QT5_WRAP_UI(UI_HEADERS mainwindow.ui)
# END_QTGUI

add_executable (rsa main.cpp rsa.cpp rsa.h mainwindow.cpp mainwindow.h ${UI_HEADERS})
qt5_use_modules(rsa Widgets)

# In case I need more libraries
set (all_libs ${GMP_LIBRARIES} ${GMPXX_LIBRARIES})

include_directories (${GMP_INCLDUE_DIR})
target_link_libraries (rsa ${all_libs})
