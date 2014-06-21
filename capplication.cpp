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

#include "capplication.h"

namespace basecode
{

// Default values is changed when settings is loaded from file
CApplication::CApplication(int argc, char *argv[]) :
	m_window(NULL),
	m_win_width(640),
	m_win_height(480),
	m_win_bpp(0),// Use system color depth
	m_win_flags(SDL_OPENGL | SDL_RESIZABLE),
			//| SDL_FULLSCREEN | SDL_NOFRAME

	m_near_plane(1.0),
	m_far_plane(100.0),

	m_last_time(0),
	m_miliseconds(1),
	m_fps(1.0f)// It is dividing by this
{

}

void CApplication::LoadSettings(CIni& ini)
{
	m_win_width = ini.Read("application", "win_width", m_win_width);
	m_win_height = ini.Read("application", "win_height", m_win_height);
	m_win_bpp = ini.Read("application", "bpp", m_win_bpp);

	if(ini.Read("application", "win_resizable",
			(m_win_flags & SDL_RESIZABLE) ? true : false))
		m_win_flags |= SDL_RESIZABLE;
	else
		m_win_flags &= ~SDL_RESIZABLE;

	if(ini.Read("application", "win_noframe",
			(m_win_flags & SDL_NOFRAME) ? true : false))
		m_win_flags |= SDL_NOFRAME;
	else
		m_win_flags &= ~SDL_NOFRAME;

	if(ini.Read("application", "start_fullscreen",
			(m_win_flags & SDL_FULLSCREEN) ? true : false))
		m_win_flags |= SDL_FULLSCREEN;
	else
		m_win_flags &= ~SDL_FULLSCREEN;

	m_near_plane = ini.Read("application", "near_plane", m_near_plane);
	m_far_plane = ini.Read("application", "far_plane", m_far_plane);
}

CApplication::~CApplication()
{
	SDL_Quit();
}

void CApplication::Init(const string& win_title)
{
	try
	{
		CIni ini(PATH_CFG_FILE);
		LoadSettings(ini);
	}
	catch(CFileNotFound& ex)
	{
		WARN << _("Unable to load settings, using predefined values: ") << PATH_CFG_FILE << endl;
		return;
	}

	CreateWindow(win_title);
	InitGL();
	ResizeWindow();

	m_last_time = SDL_GetTicks();
}

void CApplication::CreateWindow(const string& win_title)
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		throw runtime_error(string(_("Unable to initialize SDL: "))
				+ string(SDL_GetError()));
	}

	SDL_WM_SetCaption(win_title.c_str(), NULL);

	SDL_Surface *icon = SDL_LoadBMP(PATH_ICON);
	if(icon != NULL)
	{
		SDL_WM_SetIcon(icon, NULL);
		SDL_FreeSurface(icon);
	}
	else
	{
		WARN << _("Unable to load window icon: ") << PATH_ICON << endl;
	}

	SetPixelFormat();

	m_window = SDL_SetVideoMode(m_win_width, m_win_height,
			m_win_bpp, m_win_flags);

	if(m_window == NULL)
	{
		throw runtime_error(string(_("Unable to create window: "))
				+ string(SDL_GetError()));
	}
}

void CApplication::SetPixelFormat()
{
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);

	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 0);

	// My card does not support GL_ARB_multitexture, not tested
//	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
//	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
}

void CApplication::ResizeWindow()
{
	if(m_win_height == 0)// Dividing by zero
		m_win_height = 1;

	glViewport(0, 0, m_win_width, m_win_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0, (GLdouble)m_win_width/(GLdouble)m_win_height,
		m_near_plane, m_far_plane);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CApplication::MainLoop()
{
	SDL_Event event;

	OnInit();

	while(true)
	{
		while(SDL_PollEvent(&event))
		{
			if(!ProcessEvent(event))
				return;// Exit program
		}

		m_miliseconds = SDL_GetTicks() - m_last_time;

//		if(m_miliseconds == 0)
//			m_miliseconds = 1;

		if(m_miliseconds < 10)// Max. ~100 fps
		{
			SDL_Delay(10-m_miliseconds);
			m_miliseconds = SDL_GetTicks() - m_last_time;
		}

//		m_fps = 1.0f / (m_miliseconds / 1000.0f);
		m_fps = 1000.0f / m_miliseconds;
		m_last_time = SDL_GetTicks();

		Update();
		Draw();
		glFlush();
		SDL_GL_SwapBuffers();
	}
}

bool CApplication::ProcessEvent(SDL_Event& event)
{
	switch(event.type)
	{
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					return false;// Exit program
					break;

				case SDLK_F1:
					if(!ToggleFullscreen())
						return false;// Exit program
					break;

				default:
					break;
			}
			break;

		case SDL_VIDEORESIZE:
			m_win_width = event.resize.w;
			m_win_height = event.resize.h;

#ifdef CAPPLICATION_CALL_SETVIDEOMODE
			m_window = SDL_SetVideoMode(m_win_width,
				m_win_height, m_win_bpp, m_win_flags);

			if(m_window == NULL)
			{
				ERROR << _("Unable to resize window: ")
						<< SDL_GetError() << endl;
				return false;// Exit program
			}
#endif
			ResizeWindow();
			break;

		case SDL_ACTIVEEVENT:// Minimalization of window
			if (event.active.state & SDL_APPACTIVE)
			{
				if (!event.active.gain)
				{
					// Warn: There can be some events yet
					SDL_WaitEvent(NULL);
				}
			}
			break;

		case SDL_QUIT:
			return false;// Exit program
			break;

		default:
			break;
	}

	return true;
}

void CApplication::PushQuitEvent()
{
	SDL_Event event;
	event.type = SDL_QUIT;

	if(SDL_PushEvent(&event) == -1)
	{
		// The event cannot be sent
		ERROR << _("Unable to push quit event, calling exit()!")
				<< endl;

		exit(1);// Hard kill :-(
	}
}

bool CApplication::ToggleFullscreen()
{
	if(m_win_flags & SDL_FULLSCREEN)// In fullscreen, to window
		m_win_flags &= ~SDL_FULLSCREEN;
	else// In window, to fullscreen
		m_win_flags |= SDL_FULLSCREEN;

	if(SDL_WM_ToggleFullScreen(m_window) == 0)
	{
		// Can't toogle (probably not x11), recreation of window

		WARN << _("Unable to toggle fullscreen, recreating window.")
				<< endl;

		SDL_FreeSurface(m_window);
		m_window = SDL_SetVideoMode(m_win_width, m_win_height,
				m_win_bpp, m_win_flags);

		if(m_window == NULL)
		{
			ERROR << _("Unable to recreate window: ")
					<< SDL_GetError() << endl;
			return false;// Exit program
		}

		// Reinicialization of OpenGL (parameters, textures...).
		// Old OpenGL context isn't avaible yet
		try
		{
			InitGL();
		}
		catch(exception& ex)
		{
			ERROR << _("Unable to reinitialize OpenGL: \n")
					<< ex.what() << endl;
			return false;// Exit program
		}

		ResizeWindow();// Set OpenGL perspective
	}

	return true;// OK
}

}
