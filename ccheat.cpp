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

#include "ccheat.h"

namespace basecode
{

CCheat::CCheat(const string& cheat_str, int event_code) :
		m_cheat_str(cheat_str),
		m_event_code(event_code),
		m_pos(0)
{

}

CCheat::~CCheat()
{
	m_cheat_str.clear();
}

void CCheat::SetCheatString(const string& cheat_str, int event_code)
{
	m_cheat_str = cheat_str;
	m_event_code = event_code;
	m_pos = 0;
}

void CCheat::KeyPress(char key)
{
	if(m_cheat_str[m_pos] == key)// Right key
	{
		if(++m_pos == m_cheat_str.length())
		{
			// Right cheat, send message
			SDL_Event event;
			event.type = SDL_USEREVENT;
			event.user.code = m_event_code;
			event.user.data1 = NULL;
			event.user.data2 = NULL;

			SDL_PushEvent(&event);

			m_pos = 0;// For next checking
		}
	}
	else// Wrong cheat
		m_pos = 0;
}

};
