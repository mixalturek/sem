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

#ifndef __CGRID_H__
#define __CGRID_H__

#include "SDL_opengl.h"
#include "basecode.h"

namespace basecode
{

class CGrid
{
private:
	CGrid();
	~CGrid();

public:
	static void DrawCuboid(float width, float height, float depth);
	static void DrawCube(float size = 1.0f)
			{ DrawCuboid(size, size, size);}
	static void DrawSimulationCube(float size, float num_steps);

	static void DrawPlaneXY(float size, float num_steps,
			float zpos = 0.0f);
	static void DrawPlaneXZ(float size, float num_steps,
			float ypos = 0.0f);
	static void DrawPlaneYZ(float size, float num_steps,
			float xpos = 0.0f);

	static void DrawAxis(float size, bool centered = false);
};

}

#endif
