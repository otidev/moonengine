# Edited by otidev, original FindSDL2_image.cmake

# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#  Copyright 2019 Amine Ben Hassouna <amine.benhassouna@gmail.com>
#  Copyright 2000-2019 Kitware, Inc. and Contributors
#  All rights reserved.

#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:

#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.

#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.

#  * Neither the name of Kitware, Inc. nor the names of Contributors
#    may be used to endorse or promote products derived from this
#    software without specific prior written permission.

#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
#  HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#[=======================================================================[.rst:
FindSDL2_gpu
--------------

Locate SDL2_gpu library

This module defines the following 'IMPORTED' target:

::

  SDL2::Image
    The SDL2_gpu library, if found.
    Have SDL2::Core as a link dependency.



This module will set the following variables in your project:

::

  SDL2_GPU_LIBRARIES, the name of the library to link against
  SDL2_GPU_INCLUDE_DIRS, where to find the headers
  SDL2_GPU_FOUND, if false, do not try to link against
  SDL2_GPU_VERSION_STRING - human-readable string containing the
                              version of SDL2_gpu



This module responds to the following cache variables:

::

  SDL2_GPU_PATH
    Set a custom SDL2_gpu Library path (default: empty)

  SDL2_GPU_NO_DEFAULT_PATH
    Disable search SDL2_gpu Library in default path.
      If SDL2_GPU_PATH (default: ON)
      Else (default: OFF)

  SDL2_GPU_INCLUDE_DIR
    SDL2_gpu headers path.

  SDL2_GPU_LIBRARY
    SDL2_gpu Library (.dll, .so, .a, etc) path.


Additional Note: If you see an empty SDL2_GPU_LIBRARY in your project
configuration, it means CMake did not find your SDL2_gpu library
(SDL2_gpu.dll, libsdl2_gpu.so, etc). Set SDL2_GPU_LIBRARY to point
to your SDL2_gpu library, and  configure again. This value is used to
generate the final SDL2_GPU_LIBRARIES variable and the SDL2::Image target,
but when this value is unset, SDL2_GPU_LIBRARIES and SDL2::Image does not
get created.


$SDL2GPUDIR is an environment variable that would correspond to the
./configure --prefix=$SDL2GPUDIR used in building SDL2_gpu.

$SDL2DIR is an environment variable that would correspond to the
./configure --prefix=$SDL2DIR used in building SDL2.



Created by Amine Ben Hassouna:
  Adapt FindSDL_gpu.cmake to SDL2_gpu (FindSDL2_gpu.cmake).
  Add cache variables for more flexibility:
    SDL2_GPU_PATH, SDL2_GPU_NO_DEFAULT_PATH (for details, see doc above).
  Add SDL2 as a required dependency.
  Modernize the FindSDL2_gpu.cmake module by creating a specific target:
    SDL2::Image (for details, see doc above).

Original FindSDL_gpu.cmake module:
  Created by Eric Wing.  This was influenced by the FindSDL.cmake
  module, but with modifications to recognize OS X frameworks and
  additional Unix paths (FreeBSD, etc).
#]=======================================================================]

# SDL2 Library required
find_package(SDL2 QUIET)
if(NOT SDL2_FOUND)
  set(SDL2_GPU_SDL2_NOT_FOUND "Could NOT find SDL2 (SDL2 is required by SDL2_gpu).")
  if(SDL2_gpu_FIND_REQUIRED)
    message(FATAL_ERROR ${SDL2_IMAGE_SDL2_NOT_FOUND})
  else()
      if(NOT SDL2_gpu_FIND_QUIETLY)
        message(STATUS ${SDL2_IMAGE_SDL2_NOT_FOUND})
      endif()
    return()
  endif()
  unset(SDL2_IMAGE_SDL2_NOT_FOUND)
endif()


# Define options for searching SDL2_gpu Library in a custom path

set(SDL2_GPU_PATH "" CACHE STRING "Custom SDL2_gpu Library path")

set(_SDL2_GPU_NO_DEFAULT_PATH OFF)
if(SDL2_GPU_PATH)
  set(_SDL2_GPU_NO_DEFAULT_PATH ON)
endif()

set(SDL2_GPU_NO_DEFAULT_PATH ${_SDL2_GPU_NO_DEFAULT_PATH}
    CACHE BOOL "Disable search SDL2_gpu Library in default path")
unset(_SDL2_GPU_NO_DEFAULT_PATH)

set(SDL2_GPU_NO_DEFAULT_PATH_CMD)
if(SDL2_GPU_NO_DEFAULT_PATH)
  set(SDL2_GPU_NO_DEFAULT_PATH_CMD NO_DEFAULT_PATH)
endif()

# Search for the SDL2_gpu include directory
find_path(SDL2_GPU_INCLUDE_DIR SDL_gpu.h
  HINTS
    ENV SDL2GPUDIR
    ENV SDL2DIR
    ${SDL2_GPU_NO_DEFAULT_PATH_CMD}
  PATH_SUFFIXES SDL2
                # path suffixes to search inside ENV{SDL2DIR}
                # and ENV{SDL2GPUDIR}
                include/SDL2 include
  PATHS ${SDL2_GPU_PATH}
  DOC "Where the SDL2_gpu headers can be found"
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(VC_LIB_PATH_SUFFIX lib/x64)
else()
  set(VC_LIB_PATH_SUFFIX lib/x86)
endif()

# Search for the SDL2_gpu library
find_library(SDL2_GPU_LIBRARY
  NAMES SDL2_gpu
  HINTS
    ENV SDL2GPUDIR
    ENV SDL2DIR
    ${SDL2_GPU_NO_DEFAULT_PATH_CMD}
  PATH_SUFFIXES lib ${VC_LIB_PATH_SUFFIX}
  PATHS ${SDL2_GPU_PATH}
  DOC "Where the SDL2_gpu Library can be found"
)

# Read SDL2_gpu version
if(SDL2_GPU_INCLUDE_DIR AND EXISTS "${SDL2_GPU_INCLUDE_DIR}/SDL_gpu.h")
  file(STRINGS "${SDL2_GPU_INCLUDE_DIR}/SDL_gpu.h" SDL2_GPU_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_GPU_MAJOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_GPU_INCLUDE_DIR}/SDL_gpu.h" SDL2_GPU_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL_GPU_MINOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_GPU_INCLUDE_DIR}/SDL_gpu.h" SDL2_GPU_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL_GPU_PATCHLEVEL[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+SDL_GPU_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_GPU_VERSION_MAJOR "${SDL2_GPU_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_GPU_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_GPU_VERSION_MINOR "${SDL2_GPU_VERSION_MINOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_GPU_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" SDL2_GPU_VERSION_PATCH "${SDL2_GPU_VERSION_PATCH_LINE}")
  set(SDL2_GPU_VERSION_STRING ${SDL2_GPU_VERSION_MAJOR}.${SDL2_GPU_VERSION_MINOR}.${SDL2_GPU_VERSION_PATCH})
  unset(SDL2_GPU_VERSION_MAJOR_LINE)
  unset(SDL2_GPU_VERSION_MINOR_LINE)
  unset(SDL2_GPU_VERSION_PATCH_LINE)
  unset(SDL2_GPU_VERSION_MAJOR)
  unset(SDL2_GPU_VERSION_MINOR)
  unset(SDL2_GPU_VERSION_PATCH)
endif()

set(SDL2_GPU_LIBRARIES ${SDL2_GPU_LIBRARY})
set(SDL2_GPU_INCLUDE_DIRS ${SDL2_GPU_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_gpu
                                  REQUIRED_VARS SDL2_GPU_LIBRARIES SDL2_GPU_INCLUDE_DIRS
                                  VERSION_VAR SDL2_GPU_VERSION_STRING)


mark_as_advanced(SDL2_GPU_PATH
                 SDL2_GPU_NO_DEFAULT_PATH
                 SDL2_GPU_LIBRARY
                 SDL2_GPU_INCLUDE_DIR)


if(SDL2_GPU_FOUND)

  # SDL2::Image target
  if(SDL2_GPU_LIBRARY AND NOT TARGET SDL2::Image)
    add_library(SDL2::Image UNKNOWN IMPORTED)
    set_target_properties(SDL2::Image PROPERTIES
                          IMPORTED_LOCATION "${SDL2_GPU_LIBRARY}"
                          INTERFACE_INCLUDE_DIRECTORIES "${SDL2_GPU_INCLUDE_DIR}"
                          INTERFACE_LINK_LIBRARIES SDL2::Core)
  endif()
endif()
