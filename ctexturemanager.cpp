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

#include "ctexturemanager.h"

namespace basecode
{

CTextureManager::CTextureManager(int reserve)
{
	m_items.reserve(reserve);
}

CTextureManager::~CTextureManager()
{
	vector<ITEM>::iterator it;

	for(it = m_items.begin(); it != m_items.end(); it++)
	{
		if(glIsTexture(it->m_texture))
			glDeleteTextures(1, &it->m_texture);
	}
}

GLuint CTextureManager::CreateTexture(const string& path, bool mipmaps)
{

	vector<ITEM>::iterator it;

	for(it = m_items.begin(); it != m_items.end(); it++)
	{
		if(it->m_path == path)
		{
			it->m_num_refs++;
			return it->m_texture;
		}
	}

	ITEM item = { path, CImage(path).CreateTexture(mipmaps), 1 };
	m_items.push_back(item);

	return item.m_texture;
}

void CTextureManager::DeleteTexture(const string& path)
{
	vector<ITEM>::iterator it;

	for(it = m_items.begin(); it != m_items.end(); it++)
	{
		if(it->m_path == path)
		{
			it->m_num_refs--;
			if(it->m_num_refs == 0)
			{
				if(glIsTexture(it->m_texture))
					glDeleteTextures(1, &it->m_texture);

				m_items.erase(it);
				return;
			}
		}
	}
}

void CTextureManager::DeleteTexture(GLuint texture)
{
	vector<ITEM>::iterator it;

	for(it = m_items.begin(); it != m_items.end(); it++)
	{
		if(it->m_texture == texture)
		{
			it->m_num_refs--;
			if(it->m_num_refs == 0)
			{
				if(glIsTexture(it->m_texture))
					glDeleteTextures(1, &it->m_texture);

				m_items.erase(it);
				return;
			}
		}
	}
}

}
