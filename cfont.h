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

#ifndef __CFONT_H__
#define __CFONT_H__

#include <vector>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#include "basecode.h"
#include "cimage.h"


// SetFontStyle()
#define STYLE_NORMAL	TTF_STYLE_NORMAL
#define STYLE_BOLD	TTF_STYLE_BOLD
#define STYLE_ITALIC	TTF_STYLE_ITALIC
#define STYLE_UNDERLINE	TTF_STYLE_UNDERLINE

// Align
#define ALIGN_LEFT	0
#define ALIGN_CENTER	1
#define ALIGN_RIGHT	2


using namespace std;

namespace basecode
{

class CFont
{

/*
Strings use utf8 encoding
Draw() must be caled between Begin() and End() section
[0,0] is top left corner of window and bottom left corder of rendered text
Don't forget to link -lSDL_ttf
*/

private:
	CFont(const CFont& obj) {}
	const CFont& operator=(const CFont& obj)
	{ return *this; }

public:
	CFont(const string& filename, int size = 14);// .TTF, .FON
	~CFont();

	static void Begin();
	void Draw(const string& str, int x, int y, bool cache = false);
	static void End();

	void SetColor(Uint8 r, Uint8 g, Uint8 b)
			{ m_color.r = r; m_color.g = g; m_color.b = b; }
	void GetColor(Uint8& r, Uint8& g, Uint8& b) const
			{ r = m_color.r; g = m_color.g; b = m_color.b; }

	void SetAlign(int align) { m_align = align; }
	int  GetAlign() const { return m_align; }

	void SetFontStyle(int style = STYLE_NORMAL)
			{ TTF_SetFontStyle(m_font, style); }
	int  GetFontStyle() const
			{ return TTF_GetFontStyle(m_font); }

	TTF_Font* GetFont() const { return m_font; }

	int GetFontHeight() const { return TTF_FontHeight(m_font); }
	int GetLineSkip() const { return TTF_FontLineSkip(m_font); }

	int GetStrWidth(const string& str) const
			{ int w, h; TTF_SizeUTF8(m_font,
			str.c_str(), &w, &h); return w; }
	int GetStrHeight(const string& str) const
			{ int w, h; TTF_SizeUTF8(m_font,
			str.c_str(), &w, &h); return h; }

private:
	CImage* GetCached(const string& str) const;
	void AddToCache(const string& str, CImage* img);

private:
	TTF_Font* m_font;
	SDL_Color m_color;
	int m_align;

	vector<string> m_str_cache;
	vector<CImage*> m_img_cache;

	static int m_num_instances;
};

}

#endif
