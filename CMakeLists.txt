#
#   Copyright (C) 2021 Reiko Asakura. All Rights Reserved.
#
#   Vita Development Suite Libraries
#

cmake_minimum_required(VERSION 3.19)

set(CMAKE_TOOLCHAIN_FILE $ENV{SCE_PSP2_SDK_DIR}/host_tools/build/cmake/psp2-snc-toolchain.cmake)

project(vdsuite-libraries LANGUAGES NONE)

include(ExternalProject)
include(VitaDevelopmentSuite)

# Install stub archives

add_custom_target(install-stubs
  COMMAND ${CMAKE_COMMAND}
    -D NIDS_DIR=${CMAKE_CURRENT_SOURCE_DIR}/nids
    -D VDSUITE_LIBGEN=${VDSUITE_LIBGEN}
    -D CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
    -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/InstallStubs.cmake
)

# Install headers

install(DIRECTORY
  include/
  DESTINATION include/vdsuite
)

# Build and install GLES headers

ExternalProject_Add(opengl-registry
  URL https://github.com/KhronosGroup/OpenGL-Registry/archive/2afca877b25ec2c7f19ddcba21a8627b9fa8e026.tar.gz
  URL_HASH SHA256=d7447748ac3a10c9c6324e2ee980b3b0d6f75f8665d0d4055b1afd1aa3f5b67d
  EXCLUDE_FROM_ALL TRUE
  INSTALL_DIR ${CMAKE_INSTALL_PREFIX}
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/api/GLES2 <INSTALL_DIR>/include/vdsuite/user/GLES2
)

ExternalProject_Add(egl-registry
  URL https://github.com/KhronosGroup/EGL-Registry/archive/d42c684f61828e3ce18533f1c6893b79980e6acc.tar.gz
  URL_HASH SHA256=02ce918b4c9c65b5af1924330a17f3c7fbccfd87869a5c87b25d7c7c593a3d8b
  EXCLUDE_FROM_ALL TRUE
  INSTALL_DIR ${CMAKE_INSTALL_PREFIX}
  PATCH_COMMAND patch --forward --strip=1 --input=${CMAKE_CURRENT_SOURCE_DIR}/patches/egl-registry.patch
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ${CMAKE_COMMAND} -E chdir <SOURCE_DIR>/api python3 genheaders.py -registry egl.xml EGL/egl.h
  COMMAND       ${CMAKE_COMMAND} -E chdir <SOURCE_DIR>/api python3 genheaders.py -registry egl.xml EGL/eglext.h
  INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/api/EGL <INSTALL_DIR>/include/vdsuite/user/EGL
  COMMAND         ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/api/KHR <INSTALL_DIR>/include/vdsuite/user/KHR
)
