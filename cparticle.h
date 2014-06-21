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

#ifndef __CPARTICLE_H__
#define __CPARTICLE_H__


#include "basecode.h"
#include "cvector.h"
#include "ccolor.h"
#include "cbillboard.h"

namespace basecode
{

class CParticle : public CBillboard
{
public:
	friend class CParticleEngine;

	CParticle();
	CParticle(const CVector& pos, const CVector& dir);
	~CParticle();

	virtual void Update(float fps);
	bool IsLive() const { return m_life > 0.0f; }

/*	virtual void SetBlend() const
	{ glBlendFunc(GL_SRC_ALPHA, GL_ONE); }
*/
private:
	CVector m_dir;
	bool m_active;
	float m_life;
	float m_fade;
};

}

#endif
