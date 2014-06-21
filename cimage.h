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


#ifndef __CIMAGE_H__
#define __CIMAGE_H__

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>// -lSDL_image

#include "basecode.h"

namespace basecode
{

class CImage
{
private:
	CImage(const CImage& obj) {}
	const CImage& operator=(const CImage& obj) { return *this; }

public:
	CImage(const string& filename);//throw(CFileNotFound)
	CImage(SDL_Surface* surface);
	~CImage();

	Uint16 GetWidth() const { return (m_surface == NULL)
			? 0 : m_surface->w; }
	Uint16 GetHeight() const { return (m_surface == NULL)
			? 0 : m_surface->h; }
	Uint16 GetBPP() const { return (m_surface == NULL)
			? 0 : m_surface->format->BytesPerPixel; }
	Uint16 GetBiPP() const { return (m_surface == NULL)
			? 0 : m_surface->format->BitsPerPixel; }
	Uint8* GetDataPtr() const { return (m_surface == NULL)
			? 0 : (Uint8*)m_surface->pixels; }
	SDL_Surface* GetSurface() const { return m_surface; }

	bool IsValid() const { return (m_surface == NULL); }
	bool IsRGBA() const;

	void ConvertToRGBA();// throw(runtime_error)
	void SwapRows();

	// If surface is not RGB, it will be converted
	// You should set texture fillters after calling this method
	GLuint CreateTexture(bool mipmaps = false);
			// throw(runtime_error)

private:
	SDL_Surface* m_surface;
};

}

#endif
