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

#include "cplayer.h"

namespace basecode
{

CPlayer::CPlayer() :
	CBillboard(),
	m_selected(false),
	m_ytrans(0.0f)
{

}

CPlayer::CPlayer(const CVector& pos) :
	CBillboard(pos),
	m_selected(false),
	m_ytrans(0.0f)
{

}

CPlayer::~CPlayer()
{

}

void CPlayer::Draw() const
{
	glPushMatrix();
	glTranslatef(0.0f, m_ytrans, 0.0f);
	CBillboard::Draw();
	glPopMatrix();

/*	if(m_selected)
	{
		glMatrixMode(GL_TEXTURE);
			glLoadIdentity();
			glScalef(1.0f, -1.0f, 1.0f);
		glMatrixMode(GL_MODELVIEW);

		CBillboard::Draw();

		glMatrixMode(GL_TEXTURE);
			glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
	}
	else
	{
		CBillboard::Draw();
	}
*/
}

void CPlayer::Update(float fps)
{
	if(m_selected)
	{
		m_ytrans -= 1.0f / fps;

		if(m_ytrans < -10.0f)
		{
			m_ytrans = 0.0f;
			m_selected = false;
		}
	}
}

}
