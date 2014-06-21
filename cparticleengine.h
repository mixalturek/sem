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

#ifndef __CPARTICLEENGINE_H__
#define __CPARTICLEENGINE_H__

#include <SDL_opengl.h>

#include "basecode.h"
#include "cvector.h"
#include "ccolor.h"
#include "csceneobject.h"
#include "cparticle.h"

namespace basecode
{

class CParticleEngine : public CSceneObject
{
private:
	CParticleEngine(const CParticleEngine& obj) {}
	const CParticleEngine& operator=(const CParticleEngine& obj)
	{ return *this; }

public:
	CParticleEngine(const CVector& pos, int num_particles,
			const CColor& color, GLuint texture, float time);
	~CParticleEngine();

	virtual void Draw() const;
	virtual void Update(float fps);

	void InitParticle(CParticle& particle);
	void InitAllParticles();
	void SetTexture(GLuint texture) { m_texture = texture; }

	bool IsLive() const { return m_time > 0.0f; }

private:
	CColor m_color;
	int m_num_particles;
	CParticle* m_particles;
	GLuint m_texture;
	float m_time;// Live in miliseconds
};

}

#endif
