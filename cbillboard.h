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

#ifndef __CBILLBOARD_H__
#define __CBILLBOARD_H__

#include <SDL_opengl.h>
#include "basecode.h"
#include "cvector.h"
#include "csceneobject.h"
#include "ccolor.h"

namespace basecode
{

class CBillboard : public CSceneObject
{
public:
	CBillboard();
	CBillboard(const CVector& pos);
	virtual ~CBillboard();

	void SetWidth(float width) { m_halfwidth = width/2; }
	void SetHeight(float height) { m_halfheight = height/2; }

	float GetWidth() const { return m_halfwidth*2; }
	float GetHeight() const { return m_halfheight*2; }

	void SetTexture(GLuint texture) { m_texture = texture; }
	void SetColor(const CColor& color) { m_color = color; }
	const CColor& GetColor() const { return m_color; }

	static void PrepareDrawing();
	virtual void Draw() const;
	virtual void Update(float fps) {}

private:
	GLuint m_texture;
	float m_halfwidth;
	float m_halfheight;
	CColor m_color;

	static CVector m_cam_right;
	static CVector m_cam_up;
};

}

#endif
