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

#ifndef __CTERRAIN_H__
#define __CTERRAIN_H__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

#include "basecode.h"
#include "cimage.h"
#include "cini.h"
#include "csceneobject.h"
#include "cglext.h"
#include "cvector.h"

#define MAX_HEIGHT_HALF 128

namespace basecode
{

class CVertex
{
public:
	CVertex() :
		m_pos(0.0f, 0.0f, 0.0f),
		m_norm(0.0f, 0.0f, 0.0f)
	{
		m_coords[0] = 0.0f;
		m_coords[1] = 0.0f;
	}

	// glBegin() and glEnd() is assumed to be outside
	void Draw() const
	{
//		glTexCoord2fv(m_coords);
		CGLExt::glMultiTexCoord2fvARB(GL_TEXTURE0_ARB, m_coords);
		CGLExt::glMultiTexCoord2fvARB(GL_TEXTURE1_ARB, m_coords);

		glNormal3fv(m_norm);
		glVertex3fv(m_pos);
	}

public:
	CVector m_pos;
	CVector m_norm;
	float m_coords[2];
};



class CTerrain : public CSceneObject
{
private:
	CTerrain(const CTerrain& obj) {}
	const CTerrain& operator=(const CTerrain& obj) { return *this; }

public:
	CTerrain(const string& filename);// OpenGL must be inicialized
	~CTerrain();

	int GetWidth() const { return m_width; }
	int GetDepth() const { return m_depth; }
	float GetHeightFactor() const { return m_hfactor; }
	float GetDetailLevel() const { return m_det_level; }

	float GetHeight(int x, int z) const;
	float GetHeightGL(int x, int z) const;

	void SetHeightFactor(float height_factor)
			{ m_hfactor = height_factor; }
	void SetDetailLevel(float det_level)
			{ m_det_level = det_level; }

	virtual void Update(float fps) { } ;
	virtual void Draw() const;// Vertex arrays with GL_TRIANGLE_STRIP
	void Explode(int x, int z, int radius);

private:
	void GenerateTerrain(const string& filename);

	// Same as GetHeight() but without testing bounds of allocated memory
	float GetHeightFast(int x, int z) const
			{ return (m_pdata[z*m_width + x] * m_hfactor); }
	float GetHeightGLFast(int x, int z) const
			{ return ((m_pdata[z*m_width + x] - MAX_HEIGHT_HALF)
			* m_hfactor); }

private:
	int m_width;
	int m_depth;
	float m_hfactor;// The height is timed by this (hills X mountains)
	float m_det_level;// Detail lever of terrain (second texture)

	GLubyte* m_pdata;
	GLuint m_texture;
	GLuint m_texture_detail;

	CVertex* m_vertices;
	CImage* m_explosion_img;
};

}

#endif
