cmake_minimum_required(VERSION 3.0.2)
project(cmake-extras)

include(GNUInstallDirs)

install(
  DIRECTORY "src/"
  DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/"
  USE_SOURCE_PERMISSIONS
)

