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

#include "ccolor.h"

namespace basecode
{

CColor::CColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

CColor::~CColor()
{

}

SDL_Color CColor::GetSDLColor() const
{
	SDL_Color ret = { R, G, B };
	return ret;
}

bool CColor::operator==(const CColor& color) const
{
	return (R == color.R && G == color.G && B == color.B && A == color.A);
}


///////////////////////////////////////////////////////////////////////////
//// I/O support

istream& operator>>(istream& is, CColor& color)
{
	Uint8 tmp;

	is >> tmp; color.SetR(tmp);
	is >> tmp; color.SetG(tmp);
	is >> tmp; color.SetB(tmp);
	is >> tmp; color.SetA(tmp);

	return is;
}

ostream& operator<<(ostream& os, CColor& color)
{
	os << (int)color.GetR() << " " << (int)color.GetG() << " "
			<< (int)color.GetB() << " " << (int)color.GetA();
	return os;
}

}
