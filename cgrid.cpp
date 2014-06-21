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

#include "cgrid.h"

namespace basecode
{

CGrid::CGrid()
{

}

CGrid::~CGrid()
{

}

void CGrid::DrawCuboid(float width, float height, float depth)
{
	width /= 2;
	height /= 2;
	depth /= 2;

	glBegin(GL_LINE_STRIP);// Front
		glVertex3f(-width, height, depth);
		glVertex3f(-width,-height, depth);
		glVertex3f( width,-height, depth);
		glVertex3f( width, height, depth);
		glVertex3f(-width, height, depth);
	glEnd();

	glBegin(GL_LINE_STRIP);// Back
		glVertex3f(-width, height,-depth);
		glVertex3f(-width,-height,-depth);
		glVertex3f( width,-height,-depth);
		glVertex3f( width, height,-depth);
		glVertex3f(-width, height,-depth);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(-width, height, depth);
		glVertex3f(-width, height,-depth);

		glVertex3f( width, height, depth);
		glVertex3f( width, height,-depth);

		glVertex3f( width,-height, depth);
		glVertex3f( width,-height,-depth);

		glVertex3f(-width,-height, depth);
		glVertex3f(-width,-height,-depth);
	glEnd();
}

void CGrid::DrawSimulationCube(float size, float num_steps)
{
	float half_size = size / 2;

	CGrid::DrawPlaneXY(size, num_steps, half_size);
	CGrid::DrawPlaneXY(size, num_steps,-half_size);
	CGrid::DrawPlaneXZ(size, num_steps, half_size);
	CGrid::DrawPlaneXZ(size, num_steps,-half_size);
	CGrid::DrawPlaneYZ(size, num_steps, half_size);
	CGrid::DrawPlaneYZ(size, num_steps,-half_size);
}

void CGrid::DrawPlaneXY(float size, float num_steps, float zpos)
{
	float step = size / num_steps;
	size /= 2;

	glBegin(GL_LINES);
	for(register float i = -size; i <= size; i += step)
	{
		glVertex3f(-size, i, zpos);// X axis
		glVertex3f( size, i, zpos);

		glVertex3f( i,-size, zpos);// Y axis
		glVertex3f( i, size, zpos);
	}
	glEnd();
}

void CGrid::DrawPlaneXZ(float size, float num_steps, float ypos)
{
	float step = size / num_steps;
	size /= 2;

	glBegin(GL_LINES);
	for(register float i = -size; i <= size; i += step)
	{
		glVertex3f(-size, ypos, i);
		glVertex3f( size, ypos, i);

		glVertex3f( i, ypos,-size);
		glVertex3f( i, ypos, size);
	}
	glEnd();
}

void CGrid::DrawPlaneYZ(float size, float num_steps, float xpos)
{
	float step = size / num_steps;
	size /= 2;

	glBegin(GL_LINES);
	for(register float i = -size; i <= size; i += step)
	{
		glVertex3f(xpos,-size, i);
		glVertex3f(xpos, size, i);

		glVertex3f(xpos, i,-size);
		glVertex3f(xpos, i, size);
	}
	glEnd();
}

void CGrid::DrawAxis(float size, bool centered)
{
	glBegin(GL_LINES);
	if(centered)
	{
		size /= 2.0f;
		glVertex3f(-size, 0.0f, 0.0f);
		glVertex3f( size, 0.0f, 0.0f);

		glVertex3f(0.0f,-size, 0.0f);
		glVertex3f(0.0f, size, 0.0f);

		glVertex3f(0.0f, 0.0f,-size);
		glVertex3f(0.0f, 0.0f, size);
	}
	else
	{
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(size, 0.0f, 0.0f);

		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, size, 0.0f);

		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, size);
	}
	glEnd();
}

}
