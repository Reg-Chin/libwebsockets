#
# libwebsockets - small server side websockets and web server implementation
#
# Copyright (C) 2010 - 2020 Andy Green <andy@warmcat.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
#
# The strategy is to only export to PARENT_SCOPE
#
#  - changes to LIB_LIST
#  - includes via include_directories
#
# and keep everything else private

include_directories(.)

set(LWS_LIBUV_LIBRARIES CACHE PATH "Path to the libuv library")
set(LWS_LIBUV_INCLUDE_DIRS CACHE PATH "Path to the libuv include directory")

if (NOT LIBUV_FOUND)
	find_path(LIBUV_INCLUDE_DIRS NAMES uv.h)
	find_library(LIBUV_LIBRARIES NAMES uv)
endif()
message("libuv include dir: ${LIBUV_INCLUDE_DIRS}")
message("libuv libraries: ${LIBUV_LIBRARIES}")
include_directories("${LIBUV_INCLUDE_DIRS}")
list(APPEND LIB_LIST ${LIBUV_LIBRARIES})

if ("${LWS_LIBUV_LIBRARIES}" STREQUAL "" OR "${LWS_LIBUV_INCLUDE_DIRS}" STREQUAL "")
else()
	set(LIBUV_LIBRARIES ${LWS_LIBUV_LIBRARIES})
	set(LIBUV_INCLUDE_DIRS ${LWS_LIBUV_INCLUDE_DIRS})
endif()

CHECK_INCLUDE_FILE(uv-version.h LWS_HAVE_UV_VERSION_H)
  # libuv changed the location in 1.21.0. Retain both
  # checks temporarily to ensure a smooth transition.
  if (NOT LWS_HAVE_UV_VERSION_H)
    CHECK_INCLUDE_FILE(uv/version.h LWS_HAVE_NEW_UV_VERSION_H)
  endif()

if (LWS_WITH_NETWORK)
	list(APPEND SOURCES
		event-libs/libuv/libuv.c)
endif()

#
# Keep explicit parent scope exports at end
#

exports_to_parent_scope()
set(LWS_HAVE_UV_VERSION_H ${LWS_HAVE_UV_VERSION_H} PARENT_SCOPE)
set(LWS_HAVE_NEW_UV_VERSION_H ${LWS_HAVE_NEW_UV_VERSION_H} PARENT_SCOPE)
