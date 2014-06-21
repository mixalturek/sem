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

#ifndef __CCOLOR_H__
#define __CCOLOR_H__

#include <SDL.h>
#include "basecode.h"

// Private use only
#define R m_data[0]
#define G m_data[1]
#define B m_data[2]
#define A m_data[3]

namespace basecode
{

class CColor
{
public:
	CColor(Uint8 r = 255, Uint8 g = 255, Uint8 b = 255, Uint8 a = 255);
	~CColor();

	Uint8 GetR() const { return R; }
	Uint8 GetG() const { return G; }
	Uint8 GetB() const { return B; }
	Uint8 GetA() const { return A; }

	void Set(Uint8 r = 255, Uint8 g = 255, Uint8 b = 255, Uint8 a = 255)
		{ R = r; G = g; B = b; A = a; }
	void SetR(Uint8 r) { R = r; }
	void SetG(Uint8 g) { G = g; }
	void SetB(Uint8 b) { B = b; }
	void SetA(Uint8 a) { A = a; }

	// Return pointer to data (for glColor4ubv())
	Uint8* GetDataPtr() const	{ return (Uint8*)m_data; }
	operator Uint8*() const		{ return (Uint8*)m_data; }
	operator const Uint8*() const	{ return m_data; }

	bool operator==(const CColor& color) const;
	bool operator!=(const CColor& color) const
		{ return !(*this == color); }

	SDL_Color GetSDLColor() const;

public:
	Uint8 m_data[4];
};

// I/O support
istream& operator>>(istream& is, CColor& color);
ostream& operator<<(ostream& os, CColor& color);

}

#endif
