# Copyright (C) 2015-2016 Klaralvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

#
# Try to find XCB library and include path.
# Once done this will define
#
# XCB_INCLUDE_PATH
# XCB_INCLUDE_PATH_FOUND
# XCB_LIBRARIES
# XCB_LIBRARIES_FOUND
# XCB_SCREENSAVER_LIBRARIES
# XCB_SCREENSAVER_LIBRARIES_FOUND

IF ( UNIX AND NOT APPLE )

FIND_PATH( XCB_INCLUDE_PATH xcb/xcb.h
/usr/include
DOC "The directory where xcb/xcb.h resides")

FIND_LIBRARY( XCB_LIBRARY
NAMES xcb
PATHS
/usr/lib
DOC "The xcb library")

FIND_LIBRARY( XCB_SCREENSAVER_LIBRARY
NAMES xcb-screensaver
PATHS
/usr/lib
DOC "The xcb-screensaver library")

SET( XCB_INCLUDE_PATH ${XCB_INCLUDE_PATH} )
SET( XCB_LIBRARIES ${XCB_LIBRARY} )
SET( XCB_SCREENSAVER_LIBRARIES ${XCB_SCREENSAVER_LIBRARY} )
ENDIF ( UNIX AND NOT APPLE )

IF ( XCB_INCLUDE_PATH )
SET( XCB_INCLUDE_PATH_FOUND 1 CACHE STRING "Set to 1 if XCB INCLUDE PATH IS FOUND is found, 0 otherwise" )
ELSE ( XCB_INCLUDE_PATH )
SET( XCB_INCLUDE_PATH_FOUND 0 CACHE STRING "Set to 1 if XCB is found, 0 otherwise" )
ENDIF ( XCB_INCLUDE_PATH  )

IF ( XCB_LIBRARIES )
SET( XCB_LIBRARIES_FOUND 1 CACHE STRING "Set to 1 if XCB LIBRARIES are found, 0 otherwise" )
ELSE ( XCB_LIBRARIES )
SET( XCB_LIBRARIES_FOUND 0 CACHE STRING "Set to 1 if XCB LIBRARIES are found, 0 otherwise" )
ENDIF ( XCB_LIBRARIES  )

IF ( XCB_SCREENSAVER_LIBRARIES )
SET( XCB_SCREENSAVER_LIBRARIES_FOUND 1 CACHE STRING "Set to 1 if XCB screensaver library is found, 0 otherwise" )
ELSE ( XCB_SCREENSAVER_LIBRARIES )
SET( XCB_SCREENSAVER_LIBRARIES_FOUND 0 CACHE STRING "Set to 1 if XCB screensaver library is found, 0 otherwise" )
ENDIF ( XCB_SCREENSAVER_LIBRARIES  )

MARK_AS_ADVANCED( XCB_INCLUDE_PATH_FOUND XCB_LIBRARIES_FOUND  XCB_SCREENSAVER_LIBRARIES_FOUND )
