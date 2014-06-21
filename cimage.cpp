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

#include "cimage.h"

namespace basecode
{

CImage::CImage(const string& filename) : //throw(CFileNotFound)
	m_surface(NULL)
{
	// -lSDL_image
	if((m_surface = IMG_Load(filename.c_str())) == NULL)
		throw CFileNotFound(filename);
}

CImage::CImage(SDL_Surface* surface) :
	m_surface(surface)
{

}

CImage::~CImage()
{
	if(m_surface != NULL)
	{
		SDL_FreeSurface(m_surface);
		m_surface = NULL;
	}
}

bool CImage::IsRGBA() const
{
	return (m_surface != NULL &&
			m_surface->format->BytesPerPixel >= 3
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
			&& m_surface->format->Rmask == 0x000000FF
			&& m_surface->format->Gmask == 0x0000FF00
			&& m_surface->format->Bmask == 0x00FF0000);
//			&& m_surface->format->Amask == 0xFF000000);
#else
			&& m_surface->format->Rmask == 0xFF000000
			&& m_surface->format->Gmask == 0x00FF0000
			&& m_surface->format->Bmask == 0x0000FF00);
//			&& m_surface->format->Amask == 0x000000FF);
#endif

}

void CImage::ConvertToRGBA() // throw(runtime_error)
{
	SDL_Surface *tmp_surface;
	Uint32 saved_flags;
	Uint8  saved_alpha;

	if(m_surface == NULL)
		throw runtime_error("CImage has not been initialized yet");

	if(IsRGBA())
		return;

	tmp_surface = SDL_CreateRGBSurface(
			SDL_SWSURFACE,
			m_surface->w, m_surface->h,
			32,
//			m_surface->format->BytesPerPixel,// Seg. Fault ???
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
			0x000000FF,
			0x0000FF00,
			0x00FF0000,
			0xFF000000
//			(m_surface->format->BytesPerPixel < 4)
//					? 0 : 0xFF000000
#else
			0xFF000000,
			0x00FF0000,
			0x0000FF00,
			0x000000FF
//			(m_surface->format->BytesPerPixel < 4)
//					? 0 : 0x000000FF
#endif
			);

	if(tmp_surface == NULL)
		throw runtime_error("Unable to create temporary RGB surface");

	saved_flags = m_surface->flags & (SDL_SRCALPHA|SDL_RLEACCELOK);
	saved_alpha = m_surface->format->alpha;

	if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
		SDL_SetAlpha(m_surface, 0, 0);

	SDL_Rect area;
	area.x = 0;
	area.y = 0;
	area.w = m_surface->w;
	area.h = m_surface->h;
	SDL_BlitSurface(m_surface, &area, tmp_surface, &area);

	if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
		SDL_SetAlpha(m_surface, saved_flags, saved_alpha);

	SDL_FreeSurface(m_surface);
	m_surface = tmp_surface;
}

void CImage::SwapRows()
{
	Uint8 *hi_row, *lo_row, *tmp_row;

	tmp_row = new Uint8[m_surface->pitch];

	hi_row = (Uint8 *)m_surface->pixels;
	lo_row = hi_row + (m_surface->h*m_surface->pitch) - m_surface->pitch;

	if(SDL_MUSTLOCK(m_surface) && SDL_LockSurface(m_surface) == -1)
		WARN << _("Unable to lock surface") << endl;

	for(int i = 0; i < m_surface->h / 2; i++)
	{
		memcpy(tmp_row, hi_row, m_surface->pitch);
		memcpy(hi_row,  lo_row, m_surface->pitch);
		memcpy(lo_row, tmp_row, m_surface->pitch);

		hi_row += m_surface->pitch;
		lo_row -= m_surface->pitch;
	}

	if(SDL_MUSTLOCK(m_surface))
		SDL_UnlockSurface(m_surface);

	delete [] tmp_row;
}

GLuint CImage::CreateTexture(bool mipmaps)
		// throw(runtime_error)
{
	GLuint texture;

	ConvertToRGBA();
	SwapRows();

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if(mipmaps)
	{
		gluBuild2DMipmaps(
			GL_TEXTURE_2D,
			m_surface->format->BytesPerPixel,
			m_surface->w,
			m_surface->h,
			(m_surface->format->BytesPerPixel == 3)
					? GL_RGB : GL_RGBA,
			GL_UNSIGNED_BYTE,
			m_surface->pixels);
	}
	else
	{
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			m_surface->format->BytesPerPixel,
			m_surface->w,
			m_surface->h,
			0,
			(m_surface->format->BytesPerPixel == 3)
					? GL_RGB : GL_RGBA,
			GL_UNSIGNED_BYTE,
			m_surface->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				GL_LINEAR);
	}



	return texture;
}

}
