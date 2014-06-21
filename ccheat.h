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

#ifndef __CCHEAT_H__
#define __CCHEAT_H__

#include <string>
#include <SDL.h>

#include "basecode.h"

using namespace std;

namespace basecode
{

/*
If user writes m_cheatstr on the keyboard, SDL_USEREVENT with m_event_code
code will be sent to application. The code should be exclusive in the program.
See KeyPress() function for details.
*/

class CCheat
{
public:
	CCheat(const string& cheat_str, int event_code);
	~CCheat();

	void SetCheatString(const string& cheat_str, int event_code);
	string GetCheatString() const { return m_cheat_str; }

	void KeyPress(char key);

private:
	string m_cheat_str;
	int m_event_code;
	unsigned int m_pos;
};

}

#endif
