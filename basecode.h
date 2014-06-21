/***************************************************************************
 *   basecode - archive of useful C++ classes                              *
 *   Copyright (C) 2004 by Michal Turek - Woq                              *
 *   WOQ (at) seznam.cz, http://woq.nipax.cz/                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef __BASECODE_H__
#define __BASECODE_H__


////////////////////////////////////////////////////////////////////////////
//// Dev-C++ libraries
/*
-lmingw32
-lSDLmain
-lSDL
-lSDL_image
-lSDL_ttf
-lopengl32
-lglu32
-mwindows
*/


////////////////////////////////////////////////////////////////////////////
//// Basic porting option

// #define MS_WINDOWS
#define GNU_LINUX


////////////////////////////////////////////////////////////////////////////
//// Main includes

// Must be the first of all!
#ifdef MS_WINDOWS
#include <windows.h>
#endif

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <stdexcept>
#include "usereventcodes.h"

using namespace std;

namespace basecode
{

////////////////////////////////////////////////////////////////////////////
//// System dependent settings

/*
Defined - function SDL_SetVideoMode() is caled after resizing window
Define in Linux - actualization of "window viewport"
Don't define in MS Windows - loss of OpenGL context (textures disapear etc.)
*/
#ifdef GNU_LINUX
#define CAPPLICATION_CALL_SETVIDEOMODE
#endif

/*
Define this if gluCheckExtension() is not defined (mostly MS Windows),
it will use own implementation
*/
#ifdef MS_WINDOWS
#define USE_OWN_CHECK_EXTENSION_FUNC
#endif

/*
Define at MS Windows(R) if needed
*/
#ifdef MS_WINDOWS
#define USE_WINMAIN
#endif

////////////////////////////////////////////////////////////////////////////
//// Paths

// .INI file with configuration
#define PATH_CFG_FILE "./cfg/basecode.ini"

// Icon of the window (it will be shown in title bar when supported)
#define PATH_ICON "./data/icon.bmp"

// Bitmap font
#define PATH_FONT "./data/DejaVuSansCondensed.ttf"

// Splash image
#define PATH_SPLASH_IMAGE "./data/splash.jpg"


////////////////////////////////////////////////////////////////////////////
//// Defines

// Prepare for gettext
#define _(string) (string)

// Some math
#define PI 3.1415926535897932384626433832795
#define DEGTORAD(deg) ((PI*(deg))/180.0)
#define RADTODEG(rad) ((180.0*(rad))/PI)

// Time of displaying splash image
#define SPLASH_IMAGE_TIME 2000

// Time of actualization displayed FPS
#define FPS_INTERVAL 500


////////////////////////////////////////////////////////////////////////////
//// Better messages

// Because of MS Windows(R)
#ifdef ERROR
#undef ERROR
#endif

#define POS   cout << "[p] " << __FILE__ << ":" << __LINE__ << " - " << __FUNCTION__ << "()" << endl
#define INFO  cout << "[i] "
#define TODO  cout << "[d] " << __FILE__ << ":" << __LINE__ << " - " << __FUNCTION__ << "() - "
#define WARN  cerr << "[w] " << __FILE__ << ":" << __LINE__ << " - " << __FUNCTION__ << "() - "
#define ERROR cerr << "[e] " << __FILE__ << ":" << __LINE__ << " - " << __FUNCTION__ << "() - "


////////////////////////////////////////////////////////////////////////////
//// Exception classes

// Standard exceptions from stdexcept are used too
// std::runtime_error
// std::bad_alloc

// Thrown to indicate that the 'filename' file was not found
// or program is unable to open it
class CFileNotFound : public runtime_error
{
public:
	CFileNotFound(const string& filename) : runtime_error(filename)
	{
	}
};

// Thrown to indicate bad file format (loaded image etc.)
class CBadFileFormat : public runtime_error
{
public:
	CBadFileFormat(const string& filename) : runtime_error(filename)
	{
	}
};

}

#endif
