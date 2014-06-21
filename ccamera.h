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

#ifndef __CCAMERA_H__
#define __CCAMERA_H__

#include <cmath>
#include <SDL_opengl.h>
#include "basecode.h"
#include "cvector.h"
#include "csceneobject.h"

// Standard up vector
#define UP CVector(0.0f, 1.0f, 0.0f)


namespace basecode
{

class CCamera : public CSceneObject
{
public:
	CCamera(const CVector& pos);
	~CCamera();

//	const CVector& GetPos() const { return m_pos; }
	const CVector& GetDir() const { return m_dir; }
	const CVector GetLeft() const { return UP.Cross(m_dir); }
	const CVector GetRight() const { return m_dir.Cross(UP); }
	const CVector GetUp() const { return UP; }

/*	float GetXPos() const { return m_pos.GetX(); }
	float GetYPos() const { return m_pos.GetY(); }
	float GetZPos() const { return m_pos.GetZ(); }
*/
	float GetXDir() const { return m_dir.GetX(); }
	float GetYDir() const { return m_dir.GetY(); }
	float GetZDir() const { return m_dir.GetZ(); }

/*	void SetPos(const CVector& pos) { m_pos = pos; }
	void SetXPos(float x) { m_pos.SetX(x); }
	void SetYPos(float y) { m_pos.SetY(y); }
	void SetZPos(float z) { m_pos.SetZ(z); }
*/
	float GetHorizontalAngle() const { return m_horz_angle; }
	float GetVerticalAngle() const { return m_vert_angle; }

	void SetHorizontalAngle(float horz_angle);
	void SetVerticalAngle(float vert_angle);

	void GoFront(float fps) { m_pos += (m_dir*m_speed / fps); }
	void GoBack(float fps) { m_pos -= (m_dir*m_speed / fps); }
	void GoLeft(float fps) { m_pos += (UP.Cross(m_dir)*m_speed / fps); }
	void GoRight(float fps) { m_pos += (m_dir.Cross(UP)*m_speed / fps);}

	void Rotate(int xrel, int yrel, float fps);
	void LookAt() const;// gluLookAt()

	virtual void Draw() const {}
	virtual void Update(float fps) {}

protected:
//	CVector m_pos;
	CVector m_dir;// Relative to position
	float m_horz_angle;// All angles are in degrees
	float m_vert_angle;
	float m_speed_rot;
	float m_speed;
	float m_max_vert_angle;
};

}

#endif
