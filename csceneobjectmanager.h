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

#ifndef __CSCENEOBJECTMANAGER_H__
#define __CSCENEOBJECTMANAGER_H__

#include <vector>
#include <algorithm>
#include <functional>

#include "basecode.h"
#include "csceneobject.h"

namespace basecode
{

class CSceneObjectManager
{
private:
	CSceneObjectManager(const CSceneObjectManager& obj) {}
	const CSceneObjectManager& operator=(const CSceneObjectManager& obj)
	{ return *this; }

public:
	CSceneObjectManager(int reserve = 500);
	~CSceneObjectManager();

	void Draw();// If transparent objects - CSceneObject::SetCamPos()
	void Update(float fps);

	void Add(CSceneObject* obj, bool transparent = false);
	void Remove(CSceneObject* obj);

private:
	vector<CSceneObject*> m_objects;
	vector<CSceneObject*> m_transparent_objects;
};

}

#endif

