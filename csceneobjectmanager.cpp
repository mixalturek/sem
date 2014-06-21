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

#include "csceneobjectmanager.h"

namespace basecode
{

bool Compare(const CSceneObject* s1, const CSceneObject* s2)
{
    return *s1 < *s2;
}

CSceneObjectManager::CSceneObjectManager(int reserve)
{
	m_objects.reserve(reserve);
	m_transparent_objects.reserve(reserve);
}

CSceneObjectManager::~CSceneObjectManager()
{

}

void CSceneObjectManager::Draw()
{
	vector<CSceneObject*>::iterator it;

	for(it = m_objects.begin(); it != m_objects.end(); it++)
		(*it)->Draw();

	// Sort transparent objects
//	CSceneObject::SetCamPos(camera_pos);// Must be called before
//	sort(m_transparent_objects.begin(), m_transparent_objects.end());
//	sort(m_transparent_objects.begin(), m_transparent_objects.end(), less<CSceneObject*>());
//	sort(m_transparent_objects.begin(), m_transparent_objects.end(), greater<CSceneObject*>());
	sort(m_transparent_objects.begin(), m_transparent_objects.end(), Compare);

	for(it = m_transparent_objects.begin();
			it != m_transparent_objects.end(); it++)
		(*it)->Draw();
}

void CSceneObjectManager::Update(float fps)
{
	vector<CSceneObject*>::iterator it;

	for(it = m_objects.begin(); it != m_objects.end(); it++)
		(*it)->Update(fps);

	for(it = m_transparent_objects.begin();
			it != m_transparent_objects.end(); it++)
		(*it)->Update(fps);
}

void CSceneObjectManager::Add(CSceneObject* obj, bool transparent)
{
	if(transparent)
		m_transparent_objects.push_back(obj);
	else
		m_objects.push_back(obj);
}

void CSceneObjectManager::Remove(CSceneObject* obj)
{
	vector<CSceneObject*>::iterator it;

	for(it = m_objects.begin(); it != m_objects.end(); it++)
	{
		if(*it == obj)
		{
			m_objects.erase(it);
			return;
		}
	}

	for(it = m_transparent_objects.begin();
			it != m_transparent_objects.end(); it++)
	{
		if(*it == obj)
		{
			m_transparent_objects.erase(it);
			return;
		}
	}
}

}
