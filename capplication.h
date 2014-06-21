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

#ifndef __CAPPLICATION_H__
#define __CAPPLICATION_H__

#include <SDL.h>
#include <SDL_opengl.h>

#include "basecode.h"
#include "cini.h"

// Because of MS Windows(R)
#ifdef CreateWindow
#undef CreateWindow
#endif

using namespace std;

namespace basecode
{

class CApplication
{
private:
	CApplication(const CApplication& obj) {}
	const CApplication& operator=(const CApplication& obj)
	{ return *this; }

public:
	CApplication(int argc, char *argv[]);
	virtual ~CApplication();

	virtual void Init(const string& win_title);
	void MainLoop();

protected:
	virtual void InitGL() = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void OnInit() = 0;

	virtual void ResizeWindow();
	virtual bool ProcessEvent(SDL_Event& event);
	virtual void LoadSettings(CIni& ini);

	int GetWinWidth() const { return m_win_width; }
	int GetWinHeight() const { return m_win_height; }
	int GetWinBpp() const { return m_win_bpp; }
	Uint32 GetWinFlags() const { return m_win_flags; }
	double GetNearPlane() const { return m_near_plane; }
	double GetFarPlane() const { return m_far_plane; }
	float GetFPS() const { return m_fps; }
	Uint32 GetMiliseconds() const { return m_miliseconds; }

private:
	void PushQuitEvent();
	void SetPixelFormat();
	bool ToggleFullscreen();
	void CreateWindow(const string& win_title);

private:
	SDL_Surface* m_window;
	int m_win_width;
	int m_win_height;
	int m_win_bpp;
	Uint32 m_win_flags;

	double m_near_plane;
	double m_far_plane;

	Uint32 m_last_time;
	Uint32 m_miliseconds;
	float m_fps;
};

}

#endif
