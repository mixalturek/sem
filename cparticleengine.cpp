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

#include <algorithm>
#include "cparticleengine.h"

namespace basecode
{

CParticleEngine::CParticleEngine(const CVector& pos,
	int num_particles, const CColor& color, GLuint texture,
	float time) :

		CSceneObject(pos),
		m_color(color),
		m_num_particles(num_particles),
		m_particles(NULL),
		m_texture(texture),
		m_time(time)
{
	m_particles = new CParticle[num_particles];

	InitAllParticles();
}

CParticleEngine::~CParticleEngine()
{
	if(m_particles != NULL)
	{
		delete [] m_particles;
		m_particles = NULL;
	}
}

void CParticleEngine::InitAllParticles()
{
	for(int i = 0; i < m_num_particles; i++)
		InitParticle(m_particles[i]);
}

void CParticleEngine::InitParticle(CParticle& particle)
{
	particle.m_active = true;
	particle.m_pos = m_pos;
	particle.m_life = 1.0f;
	particle.m_fade = 0.0f; //(rand() % 1000) / 50.0f + 0.5f;
	particle.SetColor(m_color);
	particle.SetTexture(m_texture);
	particle.m_dir.X = (rand() / (float)RAND_MAX - 0.5f) * 50.0f;
	particle.m_dir.Y = (rand() / (float)RAND_MAX - 0.5f) * 50.0f;
	particle.m_dir.Z = (rand() / (float)RAND_MAX - 0.5f) * 50.0f;
}

void CParticleEngine::Draw() const
{
	if(!IsLive())
		return;

	CParticle::PrepareDrawing();

	sort(&m_particles[0], &m_particles[m_num_particles]);

	for(int i = 0; i < m_num_particles; i++)
		m_particles[i].Draw();
}

void CParticleEngine::Update(float fps)
{
	if(!IsLive())
		return;

	m_time -= 1000.0f / fps;

	for(int i = 0; i < m_num_particles; i++)
	{
		m_particles[i].Update(fps);

		if(!m_particles[i].IsLive())
			InitParticle(m_particles[i]);
	}
}

}
