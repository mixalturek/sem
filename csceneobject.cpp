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

#include "csceneobject.h"

namespace basecode
{

CVector CSceneObject::m_cam_pos(0.0f, 0.0f, 0.0f);
CTextureManager CSceneObject::m_tex_man(20);


CSceneObject::CSceneObject() :
	m_pos(CVector(0.0f, 0.0f, 0.0f))
{

}

CSceneObject::CSceneObject(const CVector& pos) :
	m_pos(pos)
{

}

CSceneObject::~CSceneObject()
{

}

bool CSceneObject::IsInQuad(int x_half, int z_half)
{
	if(m_pos.GetX() < -x_half)
		return false;
	if(m_pos.GetX() > x_half)
		return false;

	if(m_pos.GetZ() < -z_half)
		return false;
	if(m_pos.GetZ() > z_half)
		return false;

	return true;
}

void CSceneObject::PosToQuad(int x_half, int z_half)
{
	if(m_pos.GetX() < -x_half)
		m_pos.SetX(-x_half);
	if(m_pos.GetX() > x_half)
		m_pos.SetX(x_half);

	if(m_pos.GetZ() < -z_half)
		m_pos.SetZ(-z_half);
	if(m_pos.GetZ() > z_half)
		m_pos.SetZ(z_half);
}

// Compare operator for sorting (distance from camera)
bool CSceneObject::operator<(const CSceneObject& obj) const
{
	CVector v1(m_pos, m_cam_pos);
	CVector v2(obj.GetPos(), m_cam_pos);

	if(v1.Magnitude() < v2.Magnitude())
		return false;// Swap
	else
		return true;
}

}
