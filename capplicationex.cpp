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

#include "capplicationex.h"

namespace basecode
{

CApplicationEx::CApplicationEx(int argc, char *argv[]) :
		CApplication(argc, argv),
		m_font(PATH_FONT),
		m_font_texture(0),
		m_fps_string("FPS"),
		m_fps_timer_id(NULL),
		m_bshow_fps(true)
{
	m_font.SetFontStyle(STYLE_BOLD);
}

CApplicationEx::~CApplicationEx()
{
	FPSTimerStop();

	if(glIsTexture(m_font_texture))
	{
		glDeleteTextures(1, &m_font_texture);
		m_font_texture = 0;
	}

	INFO << _("Time of running program: ") << (SDL_GetTicks()/1000.0f)
		<< " s" << endl;
}

void CApplicationEx::LoadSettings(CIni& ini)
{
	CApplication::LoadSettings(ini);

	m_bshow_fps = ini.Read("application_ex", "show_fps", m_bshow_fps);
}

void CApplicationEx::Init(const string& win_title)
{
	CApplication::Init(win_title);

	// No mouse motion events during initialization (enable - OnInit())
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
}

void CApplicationEx::InitGL()
//		throw(std::bad_alloc, CFileNotFound, CBadFileFormat)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_LINEAR);

	try
	{
		CImage splash(PATH_SPLASH_IMAGE);
		splash.ConvertToRGBA();
		splash.SwapRows();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, GetWinWidth(), 0, GetWinHeight());
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		int x = GetWinWidth() / 2 - splash.GetWidth() / 2;
		int y =  GetWinHeight() / 2 - splash.GetHeight() / 2;
		glRasterPos2i(x, y);

		glDrawPixels(
			splash.GetWidth(),
			splash.GetHeight(),
			GL_RGB,
			GL_UNSIGNED_BYTE,
			splash.GetDataPtr());

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
	catch(...)
	{
		WARN << "Unable to display splash image: "
				<< PATH_SPLASH_IMAGE << endl;
	}

	GetFont().Begin();
	GetFont().SetAlign(ALIGN_CENTER);
	GetFont().Draw(_("--loading--"), GetWinWidth()/2, GetWinHeight()-30);
	GetFont().SetAlign(ALIGN_LEFT);
	GetFont().End();

	SDL_GL_SwapBuffers();
}

void CApplicationEx::OnInit()
{
	INFO << _("Time of initialization: ") << (SDL_GetTicks()/1000.0f)
		<< " s" << endl;

	GetFont().Begin();
	GetFont().SetAlign(ALIGN_CENTER);
	GetFont().Draw(_("Press space to continue..."),
			GetWinWidth()/2, GetWinHeight()-10);
	GetFont().SetAlign(ALIGN_LEFT);
	GetFont().End();
	SDL_GL_SwapBuffers();

	while(SDL_GetTicks() < SPLASH_IMAGE_TIME)
	{
		SDL_PumpEvents();

		if(SDL_GetKeyState(NULL)[SDLK_SPACE] == SDL_PRESSED)
			break;

		SDL_Delay(50);
	}

	// Enable mouse motion events
	SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);

	FPSTimerStart();
}

void CApplicationEx::Draw()
{
	if(m_bshow_fps)
	{
		glColor3ub(255,255,255);
		m_font.Begin();
		m_font.Draw(m_fps_string, 10, GetWinHeight()-10);
		m_font.End();
	}
}

bool CApplicationEx::ProcessEvent(SDL_Event& event)
{
	switch(event.type)
	{
		case SDL_USEREVENT:
			switch(event.user.code)
			{
				case EVT_ACTUALIZE_FPS_STRING:
				{
					stringstream sbuf(m_fps_string);
					sbuf << GetFPS();
					m_fps_string = sbuf.str();
				}
				break;

				default:
					break;
			}
			break;

		case SDL_ACTIVEEVENT:// Minimalization of window
			if (event.active.state & SDL_APPACTIVE)
			{
				if (!event.active.gain)
				{
					// Timers must stop !!!
					// Warning: If there is still event
					// in the queue, program won't stop
					FPSTimerStop();
					SDL_WaitEvent(NULL);
					FPSTimerStart();
				}
			}
			break;

		default:// Other events
			return CApplication::ProcessEvent(event);
			break;
	}

	return true;
}

void CApplicationEx::FPSTimerStart()
{
	if(m_bshow_fps && SDL_InitSubSystem(SDL_INIT_TIMER) != -1)
	{
		if((m_fps_timer_id = SDL_AddTimer(FPS_INTERVAL,
				FPSTimerCallback, NULL)) == NULL)
		{
			WARN << _("Unable to start FPS timer.") << endl;
			m_bshow_fps = false;
		}
	}
}

void CApplicationEx::FPSTimerStop()
{
	if(m_bshow_fps && m_fps_timer_id != NULL)
	{
		if(!SDL_RemoveTimer(m_fps_timer_id))
		{
			WARN << _("Unable to stop FPS timer.") << endl;
		}

		m_fps_timer_id = NULL;
	}
}

Uint32 CApplicationEx::FPSTimerCallback(Uint32 interval, void* param)
{
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = EVT_ACTUALIZE_FPS_STRING;
	event.user.data1 = NULL;
	event.user.data2 = NULL;

	if(SDL_PushEvent(&event) == -1)
		WARN << _("Unable to push FPS actualize event.") << endl;

	return interval;
}

}
