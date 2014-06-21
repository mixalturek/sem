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

#include "cbillboard.h"

namespace basecode
{

CVector CBillboard::m_cam_right(1.0f, 0.0f, 0.0f);
CVector CBillboard::m_cam_up(0.0f, 1.0f, 0.0f);

CBillboard::CBillboard() :
	CSceneObject(),
	m_texture(0),
	m_halfwidth(0.5f),
	m_halfheight(0.5f),
	m_color()
{

}

CBillboard::CBillboard(const CVector& pos) :
	CSceneObject(pos),
	m_texture(0),
	m_halfwidth(0.5f),
	m_halfheight(0.5f),
	m_color()
{

}

CBillboard::~CBillboard()
{

}

void CBillboard::Draw() const
{
	CVector right(m_cam_right * m_halfwidth);
	CVector up(m_cam_up * m_halfheight);

	glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT
			| GL_COLOR_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT, GL_FILL);

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glColor3ubv(m_color);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);// Down left
		glVertex3fv(m_pos - right - up);

		glTexCoord2f(1.0f, 0.0f);// Down right
		glVertex3fv(m_pos + right - up);

		glTexCoord2f(1.0f, 1.0f);// Up right
		glVertex3fv(m_pos + right + up);

		glTexCoord2f(0.0f, 1.0f);// Up left
		glVertex3fv(m_pos - right + up);
	glEnd();

	glPopAttrib();
}

void CBillboard::PrepareDrawing()
{
	float mat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);

	m_cam_right.Set(mat[0], mat[4], mat[8]);
	m_cam_up.Set(mat[1], mat[5], mat[9]);

	m_cam_right.Normalize();
	m_cam_up.Normalize();
}

}
