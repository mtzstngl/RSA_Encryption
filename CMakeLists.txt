cmake_minimum_required (VERSION 2.8.8)
project (rsa_encryption)
add_definitions(-std=c++11)

# make Makefile with verbose output
set(CMAKE_VERBOSE_MAKEFILE OFF)

# run cmake .. within ./build so there is no mess
# build rsa encryption with large number support

# START_FINDGMP
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
# END_FINDGMP

# START FIND_CRYPTOPP
if(CRYPTOPP_INCLUDE_DIR AND CRYPTOPP_LIBRARY)
  # already cached
  set(CRYPTOPP_FIND_QUIETLY TRUE)
endif(CRYPTOPP_INCLUDE_DIR AND CRYPTOPP_LIBRARY)

find_path(CRYPTOPP_INCLUDE_DIR NAMES cryptopp/cryptlib.h)
find_library(CRYPTOPP_LIBRARY NAMES cryptopp libcryptopp)

if(NOT PTHREAD_LIBRARY)
  find_library(PTHREAD_LIBRARY NAMES pthread libpthread)
  MESSAGE(STATUS "PTHREAD lib: " ${PTHREAD_LIBRARY})
endif(NOT PTHREAD_LIBRARY)

set(CRYPTOPP_INCLUDE_DIR ${CRYPTOPP_INCLUDE_DIR}/cryptopp) # temporary fix -> see if better way
MESSAGE(STATUS "CRYTPOPP lib: " ${CRYPTOPP_LIBRARY})

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CRYPTOPP DEFAULT_MSG CRYPTOPP_INCLUDE_DIR CRYPTOPP_LIBRARY PTHREAD_LIBRARY)

mark_as_advanced(CRYPTOPP_INCLUDE_DIR CRYPTOPP_LIBRARY PTHREAD_LIBRARY)
# END FIND_CRYPTOPP

# START FIND_MPFR
if(MPFR_INCLUDE_DIR AND MPFR_LIBRARY)
  # already cached
  set(MPFR_FIND_QUIETLY TRUE)
endif(MPFR_INCLUDE_DIR AND MPFR_LIBRARY)

find_path(MPFR_INCLUDE_DIR NAMES mpfr.h)
find_library(MPFR_LIBRARY NAMES mpfr libmpfr)

if(NOT GMP_LIBRARIES)
  find_library(GMP_LIBRARIES NAMES gmp libgmp)
  MESSAGE(STATUS "GMP libs: " ${GMP_LIBRARIES})
endif(NOT GMP_LIBRARIES)

MESSAGE(STATUS "MPFR lib: " ${MPFR_LIBRARY})

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MPFR DEFAULT_MSG MPFR_INCLUDE_DIR MPFR_LIBRARY)

mark_as_advanced(MPFR_INCLUDE_DIR MPFR_LIBRARY)
# END FIND_MPFR

# START_QTGUI
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
QT5_WRAP_UI(UI_HEADERS mainwindow.ui)
# END_QTGUI

add_executable (rsa main.cpp rsa.cpp rsa.h mainwindow.cpp mainwindow.h dataconv.cpp dataconv.h rsaes-oaep.cpp rsaes-oaep.h mgf.cpp mgf.h ${UI_HEADERS})
qt5_use_modules(rsa Widgets)

# In case I need more libraries
set (all_libs ${GMP_LIBRARIES} ${GMPXX_LIBRARIES} ${CRYPTOPP_LIBRARY} ${MPFR_LIBRARY})

include_directories (${GMP_INCLDUE_DIR} ${CRYPTOPP_INCLUDE_DIR} ${MPFR_INCLUDE_DIR})
target_link_libraries (rsa ${all_libs})
