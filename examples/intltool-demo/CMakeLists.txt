cmake_minimum_required(VERSION 3.0.2)
project(intltool-demo LANGUAGES C CXX)

include(GNUInstallDirs)
find_package(PkgConfig REQUIRED)

pkg_check_modules(
  GLIB REQUIRED
  glib-2.0
)
include_directories(${GLIB_INCLUDE_DIRS})

set(GETTEXT_PACKAGE "intltool-demo")
set(LOCALE_DIR "${CMAKE_INSTALL_FULL_DATADIR}/locale")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wpedantic")

add_subdirectory(po)
add_subdirectory(src)
