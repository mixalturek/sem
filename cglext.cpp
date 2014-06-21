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

#include "cglext.h"

namespace basecode
{

bool CGLExt::m_already_initialised = false;
bool CGLExt::m_gl_arb_multitexture = false;

PFNGLMULTITEXCOORD2FARBPROC CGLExt::glMultiTexCoord2fARB = NULL;
PFNGLMULTITEXCOORD2FVARBPROC CGLExt::glMultiTexCoord2fvARB = NULL;
PFNGLACTIVETEXTUREARBPROC CGLExt::glActiveTextureARB = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC CGLExt::glClientActiveTextureARB = NULL;



CGLExt::CGLExt()
{
	Init();
}

CGLExt::~CGLExt()
{

}

// Only if standard one is not defined
bool CGLExt::IsSupported(const char* extension_name)
{
#ifndef USE_OWN_CHECK_EXTENSION_FUNC
	return gluCheckExtension((const GLubyte*)extension_name,
			glGetString(GL_EXTENSIONS));
#else
	const unsigned char* extensions_string = NULL;
	const unsigned char* start_string;
	unsigned char* where_string;
	unsigned char* terminator_string;

	where_string = (unsigned char*)strchr(extension_name, ' ');

	if(where_string || *extension_name == '\0')
		return false;// Unsupported

	extensions_string = glGetString(GL_EXTENSIONS);

	if(extensions_string == 0)
		return false;// Unsupported

	start_string = extensions_string;

	while(true)
	{
		where_string = (unsigned char*)
			strstr((const char*)start_string, extension_name);

		if(!where_string)
			return false;// Unsupported

		terminator_string = where_string + strlen(extension_name);

		if(where_string == start_string || *(where_string - 1) == ' ')
			if(*terminator_string == ' '
			|| *terminator_string == '\0')
				return true;// Supported

		start_string = terminator_string;
	}

	return false;// Unsupported
#endif
}

void CGLExt::Init()
{
	if(m_already_initialised)
		return;

	m_already_initialised = true;

//////////////////////////////////////////////////////////////////////////////
//// GL_ARB_multitexture

	if(IsSupported("GL_ARB_multitexture"))
	{
		m_gl_arb_multitexture = true;

		glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)
			SDL_GL_GetProcAddress("glActiveTextureARB");
		glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)
			SDL_GL_GetProcAddress("glMultiTexCoord2fARB");
		glMultiTexCoord2fvARB = (PFNGLMULTITEXCOORD2FVARBPROC)
			SDL_GL_GetProcAddress("glMultiTexCoord2fvARB");
		glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)
			SDL_GL_GetProcAddress("glClientActiveTextureARB");

		if(glActiveTextureARB == NULL
				|| glMultiTexCoord2fARB == NULL
				|| glMultiTexCoord2fvARB == NULL
				|| glClientActiveTextureARB == NULL)
		{
			WARN << _("GL_ARB_multitexture is not supported by your video card") << endl;
			m_gl_arb_multitexture = false;
		}
	}
	else
	{
		WARN << _("GL_ARB_multitexture is not supported by your video card") << endl;
		m_gl_arb_multitexture = false;
	}

//////////////////////////////////////////////////////////////////////////////
////

}

}
