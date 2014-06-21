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

#ifndef __CGLEXT_H__
#define __CGLEXT_H__

#include <SDL.h>
#include <SDL_opengl.h>
#include "basecode.h"


namespace basecode
{

// Warning!!!
// This class has not been (and probably never will be) completed yet
// see glext.h ;-)

class CGLExt
{
private:
	CGLExt();
	~CGLExt();

public:
	static void Init();

	static bool IsSupported(const char* extension_name);
	static bool IsGL_ARB_multitexture()
		{ return m_gl_arb_multitexture; }

	// Function pointers
	static PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
	static PFNGLMULTITEXCOORD2FVARBPROC glMultiTexCoord2fvARB;
	static PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
	static PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;

private:
	static bool m_already_initialised;
	static bool m_gl_arb_multitexture;
};

}

#endif
