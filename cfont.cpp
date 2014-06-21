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

#include "cfont.h"

namespace basecode
{

int CFont::m_num_instances = 0;

CFont::CFont(const string& filename, int size) :
	m_font(NULL),
	m_align(ALIGN_LEFT)
{
	if(++m_num_instances == 1 && TTF_Init() == -1)
	{
		throw runtime_error(
			string(_("Unable to initialize SDL_ttf: "))
			+ string(TTF_GetError()));
	}

	m_font = TTF_OpenFont(filename.c_str(), size);
	if(m_font == NULL)
	{
		throw runtime_error(
			string(_("Unable to open font: "))
			+ string(TTF_GetError()));
	}

	m_color.r = 255;
	m_color.g = 255;
	m_color.b = 255;

	m_str_cache.reserve(50);
	m_img_cache.reserve(50);
}

CFont::~CFont()
{
	for(unsigned int i = 0; i < m_img_cache.size(); i++)
		delete m_img_cache[i];

	m_str_cache.clear();
	m_img_cache.clear();

	if(m_font != NULL)
	{
		TTF_CloseFont(m_font);
		m_font = NULL;
	}

	if(--m_num_instances == 0 && TTF_WasInit())
		TTF_Quit();
}

void CFont::Draw(const string& str, int x, int y, bool cache)
{
	CImage* img = NULL;
	bool using_cached = false;

	if(str.empty())
	{
		WARN << _("Rendered string is empty") << endl;
		return;
	}

	if(cache)
	{
		img = GetCached(str);
		if(img != NULL)
			using_cached = true;
	}

	if(img == NULL)
	{
		SDL_Surface* surface = TTF_RenderUTF8_Blended(m_font,
				str.c_str(), m_color);
		if(surface == NULL)
		{
			ERROR << _("Unable to render text surface: ")
					<< str << endl;
			return;
		}

		try
		{
			// Surface is freed in CImage
			img = new CImage(surface);
			img->ConvertToRGBA();
			img->SwapRows();
		}
		catch(exception& ex)
		{
			ERROR << ex.what() << endl;
			if(img != NULL)
				delete img;
			return;
		}
	}

	switch(m_align)
	{
		case ALIGN_RIGHT:
			glRasterPos2i(x - GetStrWidth(str), y);
			break;

		case ALIGN_CENTER:
			glRasterPos2i(x - GetStrWidth(str)/2, y);
			break;

//		case ALIGN_LEFT:
		default:
			glRasterPos2i(x, y);
			break;
	}

	glDrawPixels(
		img->GetWidth(),
		img->GetHeight(),
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		img->GetDataPtr());

	if(using_cached)
		return;
	else if(cache)
		AddToCache(str, img);
	else
		delete img;
}

void CFont::Begin()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void CFont::End()
{
	glPopAttrib();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

CImage* CFont::GetCached(const string& str) const
{
	for(unsigned int i = 0; i < m_str_cache.size(); i++)
	{
		if(m_str_cache[i] == str)
		{
//			INFO << i << " " << m_str_cache.size() << endl;
			return m_img_cache[i];
		}
	}

	return NULL;
}

void CFont::AddToCache(const string& str, CImage* img)
{
	if(GetCached(str) == NULL)
	{
		m_str_cache.push_back(str);
		m_img_cache.push_back(img);
	}
}

}
