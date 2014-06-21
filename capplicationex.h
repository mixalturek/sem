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

#ifndef __CAPPLICATIONEX_H__
#define __CAPPLICATIONEX_H__

#include "basecode.h"
#include "capplication.h"
#include "cini.h"
#include "cfont.h"
#include "cimage.h"

namespace basecode
{

class CApplicationEx : public CApplication
{
// Text support
// Splash image
// Displaying FPS

private:
	CApplicationEx(const CApplicationEx& obj)
			: CApplication(0, NULL), m_font(PATH_FONT) {}
	const CApplicationEx& operator=(const CApplicationEx& obj)
	{ return *this; }

public:
	CApplicationEx(int argc, char *argv[]);
	virtual ~CApplicationEx();

protected:
	virtual void Init(const string& win_title);
	virtual void InitGL();
	virtual void OnInit();
	virtual void Draw();
	virtual void LoadSettings(CIni& ini);
	virtual bool ProcessEvent(SDL_Event& event);

	// Printing is available for child classes
	CFont& GetFont() { return m_font; }

private:
	static Uint32 FPSTimerCallback(Uint32 interval, void* param);
	void FPSTimerStart();
	void FPSTimerStop();

private:
	CFont m_font;
	GLuint m_font_texture;
	string m_fps_string;
	SDL_TimerID m_fps_timer_id;
	bool m_bshow_fps;
};

}

#endif
