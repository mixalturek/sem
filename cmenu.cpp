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

#include "cmenu.h"

namespace basecode
{

CMenu::CMenu(int num_items) :
	m_selected(0)
{
	m_event_codes.reserve(num_items);
	m_event_strings.reserve(num_items);
}

CMenu::~CMenu()
{
	m_event_codes.clear();
	m_event_strings.clear();
}

void CMenu::AddItem(int usr_event_code, const string& title)
{
	m_event_codes.push_back(usr_event_code);
	m_event_strings.push_back(title);
}

void CMenu::SelectNext()
{
	if(++m_selected >= (int)m_event_codes.size())
		m_selected = 0;
}

void CMenu::SelectPrevious()
{
	if(--m_selected < 0)
		m_selected = m_event_codes.size()-1;
}

void CMenu::Choose() const
{
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = m_event_codes[m_selected];
	SDL_PushEvent(&event);
}

void CMenu::ChangeString(const string& str, unsigned int index)
{
	if(index < m_event_strings.size())
		m_event_strings[index] = str;
}

}
