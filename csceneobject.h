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

#ifndef __CSCENEOBJECT_H__
#define __CSCENEOBJECT_H__

#include <SDL_opengl.h>
#include "basecode.h"
#include "cvector.h"
#include "ctexturemanager.h"


namespace basecode
{

class CSceneObject
{
public:
	CSceneObject();
	CSceneObject(const CVector& pos);
	virtual ~CSceneObject();

	virtual void Draw() const = 0;
	virtual void Update(float fps) = 0;

	const CVector& GetPos() const { return m_pos; }
	float GetXPos() const { return m_pos.GetX(); }
	float GetYPos() const { return m_pos.GetY(); }
	float GetZPos() const { return m_pos.GetZ(); }

	void SetPos(const CVector& pos) { m_pos = pos; }
	void SetXPos(float x) { m_pos.SetX(x); }
	void SetYPos(float y) { m_pos.SetY(y); }
	void SetZPos(float z) { m_pos.SetZ(z); }

	float Distance(const CSceneObject& obj) const
			{ return m_pos.Distance(obj.GetPos()); }

	// When the area (terrain, playground etc.) has borders
	bool IsInQuad(int x_half, int z_half);
	void PosToQuad(int x_half, int z_half);

	// For sorting transparent objects (distance from camera)
	bool operator<(const CSceneObject& obj) const;
	static const CVector& GetCamPos() { return m_cam_pos; }
	static void SetCamPos(const CVector& cam_pos)
			{ m_cam_pos = cam_pos; }

	// Texture support
	GLuint CreateTexture(const string& path, bool mipmaps = false)
	{ return m_tex_man.CreateTexture(path, mipmaps); }
	void DeleteTexture(const string& path)
			{ m_tex_man.DeleteTexture(path); }
	void DeleteTexture(GLuint texture)
			{ m_tex_man.DeleteTexture(texture); }
	const CTextureManager& GetTexMan() const { return m_tex_man; }

protected:
	CVector m_pos;

private:
	static CVector m_cam_pos;
	static CTextureManager m_tex_man;
};

}

#endif
