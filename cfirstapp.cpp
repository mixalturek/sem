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

#include "cfirstapp.h"

namespace basecode
{

CFirstApp::CFirstApp(int argc, char *argv[]) :
		CApplicationEx(argc, argv),
		m_terrain(NULL),
		m_cam(CVector(0.0f, 0.0f, 0.0f)),
#ifdef USE_CHEATS
		m_cheat("cheat", EVT_CHEAT_CODE),
#endif
		m_main_menu(5),
		m_terrain_menu(30),
		m_polyg_mode_menu(5),
		m_menu(NULL),
		m_obj_man(100),
		m_shoot_timer_id(NULL),
		m_which_camera(WHICH_CAMERA_PLAYER),
		m_sun_rot(0)
{
	int i;

	srand((unsigned int)time((time_t*)NULL));

#ifdef USE_TEXTURES
	for(i = 0; i < NUM_TEXTURES; i++)
		m_textures[i] = 0;
#endif

	// Main menu
	m_main_menu.AddItem(EVT_MAIN_MENU_TERRAIN, _("Select terrain >"));
	m_main_menu.AddItem(EVT_MAIN_MENU_POLYGON_MODE, _("Polygon mode >"));
	m_main_menu.AddItem(EVT_MAIN_MENU_TOGGLE_CAMERA, _("Toggle camera"));
	m_main_menu.AddItem(EVT_MAIN_MENU_TOGGLE_LIGHTS, _("Toggle lights"));
	m_main_menu.AddItem(EVT_MAIN_MENU_TOGGLE_FOG, _("Toggle fog"));
	m_main_menu.AddItem(EVT_MAIN_MENU_HIDE, _("Hide menu"));
	m_main_menu.AddItem(EVT_MAIN_MENU_EXIT, _("Exit"));

	// Polygon mode menu
	m_polyg_mode_menu.AddItem(EVT_POLYG_MENU_FILL, _("Fill"));
	m_polyg_mode_menu.AddItem(EVT_POLYG_MENU_LINES, _("Lines"));
	m_polyg_mode_menu.AddItem(EVT_POLYG_MENU_POINTS, _("Points"));
	m_polyg_mode_menu.AddItem(EVT_POLYG_MENU_GOTO_MAIN_MENU,
			_("< go back"));

	// terrain menu
	CIni ini("./cfg/terrains/general.ini");
	int num_terrains = ini.Read("general", "num", -1);

	string str;
	stringstream sstream(str);

	for(i = 0; i < num_terrains; i++)
	{
		sstream << "terrain" << i;
		m_terrain_menu.AddItem(EVT_TERRAIN_MENU_SEL,
			ini.ReadString(sstream.str(), "name",
			sstream.str()));

		sstream.str("");
	}

	m_terrain_menu.AddItem(EVT_TERRAIN_MENU_GOTO_MAIN_MENU,
			_("< go back"));

	m_bullets.reserve(100);
	m_explosions.reserve(50);
}

CFirstApp::~CFirstApp()
{
	unsigned int i;

	if(m_terrain != NULL)
		delete m_terrain;

#ifdef USE_TEXTURES
	for(i = 0; i < NUM_TEXTURES; i++)
	{
		if(glIsTexture(m_textures[i]))
		{
			glDeleteTextures(1, &m_textures[i]);
			m_textures[i] = 0;
		}
	}
#endif

	for(i = 0; i < m_bullets.size(); i++)
	{
		if(m_bullets[i] != NULL)
			delete m_bullets[i];
	}

	for(i = 0; i < m_explosions.size(); i++)
	{
		if(m_explosions[i] != NULL)
			delete m_explosions[i];
	}
}

void CFirstApp::Init(const string& win_title)
{
	CApplicationEx::Init(win_title);
	SDL_ShowCursor(SDL_DISABLE);
}

void CFirstApp::InitGL()
{
	CApplicationEx::InitGL();

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

/*	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_LINEAR);
*/

	GLfloat fogcolor[4]= {1.0f, 1.0f, 1.0f, 1.0f};
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogfv(GL_FOG_COLOR, fogcolor);
	glFogf(GL_FOG_DENSITY, 0.05f);
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogf(GL_FOG_START, 14.0f);
	glFogf(GL_FOG_END, 15.0f);
//	glEnable(GL_FOG);// Menu

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

/*	GLfloat materialAmbient[]={1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat materialDiffuse[]={1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat materialSpecular[]={1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat materialShininess[]={50.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);
*/
//	GLfloat global_ambient[]={ 0.0f, 0.0f, 0.0f, 1.0f };// Okolni
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);


	GLfloat sun_ambient[]={ 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat sun_diffuse[]={ 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(SUN_LIGHT, GL_AMBIENT, sun_ambient);
	glLightfv(SUN_LIGHT, GL_DIFFUSE, sun_diffuse);
	glEnable(SUN_LIGHT);

	GLfloat spot_color[]={1.0f, 1.0f, 0.6f};
	glLightf(SPOT_LIGHT, GL_SPOT_CUTOFF, 30);
	glLightf(SPOT_LIGHT, GL_SPOT_EXPONENT, 0.4f);
	glLightf(SPOT_LIGHT, GL_LINEAR_ATTENUATION, 0.07f);
//	glLightfv(SPOT_LIGHT, GL_DIFFUSE, spot_color);
	glLightfv(SPOT_LIGHT, GL_AMBIENT, spot_color);
	glEnable(SPOT_LIGHT);

//	glEnable(GL_LIGHTING);

	m_main_menu.SetFont(&GetFont());
	m_terrain_menu.SetFont(&GetFont());
	m_polyg_mode_menu.SetFont(&GetFont());

	m_textures[0] = CImage("./data/bullets/bullet.png").CreateTexture();
	m_textures[1] = CImage("./data/bullets/particle.png").CreateTexture();

	m_textures[2] = CImage("./data/players/ark.png").CreateTexture();
	m_textures[3] = CImage("./data/players/tux.png").CreateTexture();
	m_textures[4] = CImage("./data/players/arts.png").CreateTexture();
	m_textures[5] = CImage("./data/players/bell.png").CreateTexture();
	m_textures[6] = CImage("./data/players/bsd.png").CreateTexture();
	m_textures[7] = CImage("./data/players/cache.png").CreateTexture();
	m_textures[8] = CImage("./data/players/cat.png").CreateTexture();
	m_textures[9] = CImage("./data/players/clanbomber.png").CreateTexture();
	m_textures[10] = CImage("./data/players/clock.png").CreateTexture();
	m_textures[11] = CImage("./data/players/skull.png").CreateTexture();
	m_textures[12] = CImage("./data/players/gnu.png").CreateTexture();
	m_textures[13] = CImage("./data/players/juk.png").CreateTexture();
	m_textures[14] = CImage("./data/players/kaddressbook.png").CreateTexture();
	m_textures[15] = CImage("./data/players/kcmmemory.png").CreateTexture();
	m_textures[16] = CImage("./data/players/kfm_home.png").CreateTexture();
	m_textures[17] = CImage("./data/players/khelpcenter.png").CreateTexture();
	m_textures[18] = CImage("./data/players/ksmiletris.png").CreateTexture();
	m_textures[19] = CImage("./data/players/kwalletmanager.png").CreateTexture();
	m_textures[20] = CImage("./data/players/lukas.png").CreateTexture();
	m_textures[21] = CImage("./data/players/lukas1.png").CreateTexture();
	m_textures[22] = CImage("./data/players/package_favourite.png").CreateTexture();
	m_textures[23] = CImage("./data/players/package_toys.png").CreateTexture();


	if(m_terrain != NULL)
		delete m_terrain;

	m_terrain = new CTerrain("./cfg/terrains/default.ini");

	for(int i = 0; i < NUM_PLAYERS; i++)
	{
		m_players[i].SetTexture(PLAYER_TEXTURES_BEGIN +
				m_textures[rand() % PLAYER_TEXTURES_NUM]);
		m_players[i].SetWidth(4.0f);
		m_players[i].SetHeight(4.0f);
		m_players[i].SetPos(CVector(
			(rand() % m_terrain->GetWidth()) - m_terrain->GetWidth() / 2,
			0.0f,
			(rand() % m_terrain->GetDepth()) - m_terrain->GetDepth() / 2));
		m_obj_man.Add(&m_players[i], true);
	}
}

void CFirstApp::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	GLfloat spot[4];

	// Select camera
	switch(m_which_camera)
	{
	case WHICH_CAMERA_TOP:
		gluLookAt(0, m_terrain->GetDepth()<<1, 0,
			0, 0, 0 ,
			1, 0, 0);// Directly from top
		break;

	case WHICH_CAMERA_DIST_ROT:// From distance, rotating
		gluLookAt(m_terrain->GetWidth(),
			m_terrain->GetWidth() >> 1,
			m_terrain->GetDepth()*1.3f,
			0, 0, 0,
			0, 1, 0);
		glRotatef(m_sun_rot, 0.0f, 1.0f, 0.0f);
		break;

	case WHICH_CAMERA_PLAYER:// Player's camera
	default:
		m_cam.LookAt();

		spot[0] = m_cam.GetXPos();
		spot[1] = m_cam.GetYPos();
		spot[2] = m_cam.GetZPos();
		spot[3] = 1.0f;
		glLightfv(SPOT_LIGHT, GL_POSITION, spot);
		spot[0] = m_cam.GetXDir();
		spot[1] = m_cam.GetYDir()-0.5f;
		spot[2] = m_cam.GetZDir();
		spot[3] = 1.0f;
		glLightfv(SPOT_LIGHT, GL_SPOT_DIRECTION, spot);

		break;
	}

	// Sun light
	glPushMatrix();
	glRotatef(m_sun_rot, 1.0f, 0.0f, 0.0f);
	GLfloat sun_pos[]={ 0.0f, -1.0f, -4.0f, 0.0f };
	glLightfv(SUN_LIGHT, GL_POSITION, sun_pos);
	glPopMatrix();


	// Cube from lines around terrain
	glPushAttrib(GL_ENABLE_BIT | GL_LINE_BIT);
		glDisable(GL_LIGHTING);
		glColor3ub(255, 255, 255);
		glLineWidth(3.0f);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		CGrid::DrawCuboid(m_terrain->GetWidth(), 256.0f,
				m_terrain->GetDepth());
	glPopAttrib();

	glColor3ub(255, 255, 255);
	m_terrain->Draw();

/*	sort(m_players, m_players+NUM_PLAYERS);
	for(int i = 0; i < NUM_PLAYERS; i++)
		m_players[i].Draw();
*/

	// Transparent objects
	CSceneObject::SetCamPos(m_cam.GetPos());// For transparent objects
	CBillboard::PrepareDrawing();
	m_obj_man.Draw();


	// Menu
	glColor3ub(255, 255, 255);
	if(m_menu != NULL)
		m_menu->Draw(GetWinWidth() / 2, 100);


	// Copyright ;-)
	glColor3ub(255, 255, 255);
	GetFont().Begin();
	GetFont().SetAlign(ALIGN_RIGHT);
	GetFont().Draw("(c) woq", GetWinWidth()-10, GetWinHeight()-10, true);
	GetFont().SetAlign(ALIGN_LEFT);
	GetFont().End();


	// Gun laser
	if(m_which_camera == WHICH_CAMERA_PLAYER)
	{
		glPushAttrib(GL_ENABLE_BIT);
		glLoadIdentity();
		glColor3ub(255, 0, 0);
		glPointSize(4);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glBegin(GL_POINTS);
			glVertex3i(0,0,-1);
		glEnd();
		glEnable(GL_DEPTH_TEST);
		glPointSize(1);
		glPopAttrib();
	}


	CApplicationEx::Draw();
}

void CFirstApp::Update()
{
	// Rotating camera
//	if(m_which_camera == WHICH_CAMERA_DIST_ROT)
		m_sun_rot += 5.0f / GetFPS();

	if(m_menu != NULL)
		return;

	SDL_PumpEvents();

	Uint8* keys;
	keys = SDL_GetKeyState(NULL);

	if(keys[SDLK_UP] == SDL_PRESSED || keys[SDLK_w] == SDL_PRESSED)
		m_cam.GoFront(GetFPS());
	if(keys[SDLK_DOWN] == SDL_PRESSED || keys[SDLK_s] == SDL_PRESSED)
		m_cam.GoBack(GetFPS());
	if(keys[SDLK_LEFT] == SDL_PRESSED || keys[SDLK_a] == SDL_PRESSED)
		m_cam.GoLeft(GetFPS());
	if(keys[SDLK_RIGHT] == SDL_PRESSED || keys[SDLK_d] == SDL_PRESSED)
		m_cam.GoRight(GetFPS());

	int width = (m_terrain->GetWidth() >> 1)-1;
	int height = (m_terrain->GetDepth() >> 1)-1;

	m_cam.PosToQuad(width, height);
	m_cam.SetYPos(m_terrain->GetHeightGL((int)m_cam.GetXPos(),
			(int)m_cam.GetZPos())+2.0f);

	for(int i = 0; i < NUM_PLAYERS; i++)
	{
		m_players[i].Update(GetFPS());
		m_players[i].SetYPos(m_terrain->GetHeightGL((int)m_players[i].GetXPos(),
			(int)m_players[i].GetZPos()) + m_players[i].GetHeight()/2);
	}

//	m_particle_engine.Update(GetFPS());

	// Deleting bullets
	vector<CBullet*>::iterator it;

	for(it = m_bullets.begin(); it < m_bullets.end(); it++)
	{
		// Bullet is outside of the terrain
		if(!(*it)->IsInQuad(width, height))
		{
			m_obj_man.Remove(*it);
			delete *it;
			m_bullets.erase(it);
			// Break MUST be here (Fatal signal:
			// Segmentation Fault (SDL Parachute Deployed)
			// erasing with iterators)
			break;
		}

		// Collision bullet and terrain
		if(m_terrain->GetHeightGL((int)(*it)->GetXPos(),
				(int)(*it)->GetZPos()) > (*it)->GetYPos())
		{
			Explosion(2000, (*it)->GetPos(), (*it)->GetColor());

			m_terrain->Explode((int)(*it)->GetXPos(),
					(int)(*it)->GetZPos(), 5);
			m_obj_man.Remove(*it);
			delete *it;
			m_bullets.erase(it);
			// Break MUST be here (Fatal signal:
			// Segmentation Fault (SDL Parachute Deployed)
			// erasing with iterators)
			break;

			// Try remove_if() from STL
		}
	}


	// Deleting explosions
	vector<CParticleEngine*>::iterator ite;

	for(ite = m_explosions.begin(); ite < m_explosions.end(); ite++)
	{
		if(!(*ite)->IsLive())
		{
			m_obj_man.Remove(*ite);
			delete *ite;
			m_explosions.erase(ite);
			// Break MUST be here (Fatal signal:
			// Segmentation Fault (SDL Parachute Deployed)
			// erasing with iterators)
			break;
		}
	}

	m_obj_man.Update(GetFPS());
}

bool CFirstApp::ProcessEvent(SDL_Event& event)
{
	switch(event.type)
	{
	case SDL_MOUSEMOTION:
		if(m_menu != NULL)
			break;

		// SDL_WarpMouse() generates SDL_MOUSEMOTION event :-(
		if(event.motion.x != GetWinWidth() >> 1
		|| event.motion.y != GetWinHeight() >> 1)
		{
			m_cam.Rotate(event.motion.xrel,
					event.motion.yrel, GetFPS());

			// Center mouse in window
			SDL_WarpMouse(GetWinWidth()>>1, GetWinHeight()>>1);
		}
		break;

	case SDL_MOUSEBUTTONDOWN:
		switch(event.button.button)
		{
		case SDL_BUTTON_LEFT:
			Shoot();
			ShootTimerStart();
			break;

		case SDL_BUTTON_RIGHT:
			Selection(event.button.x, event.button.y);
			break;

		default:
			break;
		}
		break;


	case SDL_MOUSEBUTTONUP:
		switch(event.button.button)
		{
		case SDL_BUTTON_LEFT:
			ShootTimerStop();
			break;

		default:
			break;
		}
		break;

	case SDL_KEYDOWN:
#ifdef USE_CHEATS
		m_cheat.KeyPress(event.key.keysym.sym);// Cheats
#endif
		switch(event.key.keysym.sym)
		{
		case SDLK_F10:
			if(m_menu == NULL)
			{
				m_menu = &m_main_menu;
				m_menu->SelectFirst();
			}
			else
				m_menu = NULL;
			break;

		case SDLK_RETURN:
			if(m_menu != NULL)
				m_menu->Choose();
			break;

		case SDLK_UP:
			if(m_menu != NULL)
				m_menu->SelectPrevious();
			break;

		case SDLK_DOWN:
			if(m_menu != NULL)
				m_menu->SelectNext();
			break;

		case SDLK_KP_PLUS:
			m_terrain->SetDetailLevel(m_terrain->GetDetailLevel()
					+ 10.0f);
			break;

		case SDLK_KP_MINUS:
			m_terrain->SetDetailLevel(m_terrain->GetDetailLevel()
					- 10.0f);
			break;

		case SDLK_ESCAPE:
			if(m_menu == NULL)
				return false;
			else
				m_menu->SelectLast();

			break;

		default:// Other key
			return CApplicationEx::ProcessEvent(event);
			break;
		}
		break;

	case SDL_USEREVENT:
		switch(event.user.code)
		{
		// Main menu
		case EVT_MAIN_MENU_TERRAIN: m_menu = &m_terrain_menu; break;
		case EVT_MAIN_MENU_POLYGON_MODE:
				m_menu = &m_polyg_mode_menu; break;
		case EVT_MAIN_MENU_HIDE: m_menu = NULL; break;
		case EVT_MAIN_MENU_TOGGLE_CAMERA:
			m_which_camera++;
			if(m_which_camera > WHICH_CAMERA_MAX)
				m_which_camera = 0;
			break;
		case EVT_MAIN_MENU_TOGGLE_FOG:
			if(glIsEnabled(GL_FOG))
			{
				glDisable(GL_FOG);
				glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			}
			else
			{
				glEnable(GL_FOG);
				glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
			}
			break;
		case EVT_MAIN_MENU_TOGGLE_LIGHTS:
			if(glIsEnabled(GL_LIGHTING))
				glDisable(GL_LIGHTING);
			else
				glEnable(GL_LIGHTING);
			break;
		case EVT_MAIN_MENU_EXIT: return false; break;

		// Terrain menu
		case EVT_TERRAIN_MENU_SEL:
		{
			delete m_terrain;

			string str;
			stringstream sstream(str);
			sstream << "./cfg/terrains/"
					<< m_terrain_menu.GetSel() << ".ini";
			m_terrain = new CTerrain(sstream.str());
			m_menu = NULL;
		}
			break;

		case EVT_TERRAIN_MENU_GOTO_MAIN_MENU:
		case EVT_POLYG_MENU_GOTO_MAIN_MENU:
			m_menu = &m_main_menu;
			break;

		// Polygon mode menu
		case EVT_POLYG_MENU_FILL:
		case EVT_POLYG_MENU_LINES:
		case EVT_POLYG_MENU_POINTS:
			switch(m_polyg_mode_menu.GetSel())
			{
			case 0:
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				break;
			case 1:
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				break;
			default:
				glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
				break;
			}
			break;

		// Other
#ifdef USE_CHEATS
		case EVT_CHEAT_CODE:
			INFO << "cheat" << endl;// Only test
			break;
#endif
		case EVT_SHOOT:
			Shoot();
			break;

		default:
			return CApplicationEx::ProcessEvent(event);
			break;
		}
		break;

	default:// Other events
		return CApplicationEx::ProcessEvent(event);
		break;
	}

	return true;
}

void CFirstApp::Shoot()
{
	// delete at Update() or destructor
	CBullet* bullet = new CBullet(m_cam.GetPos(),
			m_cam.GetDir()*20.0f);
	bullet->SetTexture(m_textures[0]);
	bullet->SetColor(CColor(100+rand()%156, 100+rand()%156,
			100+rand()%156));
	m_bullets.push_back(bullet);
	m_obj_man.Add(bullet, true);
}

void CFirstApp::Explosion(float time, const CVector pos,
	       const CColor& color)
{
	CParticleEngine* engine = new CParticleEngine(pos, 100, color,
			 m_textures[1], time);

	m_explosions.push_back(engine);
	m_obj_man.Add(engine, true);
}

void CFirstApp::ShootTimerStart()
{
//	if(SDL_InitSubSystem(SDL_INIT_TIMER) != -1)
//	{
		if(m_shoot_timer_id != NULL)
			return;

		if((m_shoot_timer_id = SDL_AddTimer(SHOOT_INTERVAL,
				ShootTimerCallback, NULL)) == NULL)
		{
			WARN << _("Unable to start shoot timer.") << endl;
		}
//	}
}

void CFirstApp::ShootTimerStop()
{
	if(m_shoot_timer_id != NULL)
	{
		if(!SDL_RemoveTimer(m_shoot_timer_id))
		{
			WARN << _("Unable to stop shoot timer.") << endl;
		}

		m_shoot_timer_id = NULL;
	}
}

Uint32 CFirstApp::ShootTimerCallback(Uint32 interval, void* param)
{
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = EVT_SHOOT;
	event.user.data1 = NULL;
	event.user.data2 = NULL;

	if(SDL_PushEvent(&event) == -1)
		WARN << _("Unable to push shoot event.") << endl;

	return interval;
}

void CFirstApp::Selection(int mouse_x, int mouse_y)
{
	if(m_which_camera != WHICH_CAMERA_PLAYER)
		return;

	GLuint buffer[512];			// Set Up A Selection Buffer
	GLint hits;				// The Number Of Objects That We Selected

	// The Size Of The Viewport. [0] Is <x>, [1] Is <y>, [2] Is <length>, [3] Is <width>
	GLint viewport[4];

	// This Sets The Array <viewport> To The Size And Location Of The Screen Relative To The Window
	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(512, buffer);		// Tell OpenGL To Use Our Array For Selection

	// Puts OpenGL In Selection Mode. Nothing Will Be Drawn. Object ID's and Extents Are Stored In The Buffer.
	(void)glRenderMode(GL_SELECT);

	glInitNames();				// Initializes The Name Stack
	glPushName(0);				// Push 0 (At Least One Entry) Onto The Stack

	glMatrixMode(GL_PROJECTION);		// Selects The Projection Matrix
	glPushMatrix();				// Push The Projection Matrix
	glLoadIdentity();			// Resets The Matrix

	// This Creates A Matrix That Will Zoom Up To A Small Portion Of The Screen, Where The Mouse Is.
	gluPickMatrix((GLdouble)mouse_x, (GLdouble)(viewport[3]-mouse_y), 1.0f, 1.0f, viewport);

	// Apply The Perspective Matrix
	gluPerspective(45.0f, (GLfloat) (viewport[2]-viewport[0])/(GLfloat) (viewport[3]-viewport[1]), 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);		// Select The Modelview Matrix

	m_cam.LookAt();
	for(int i = 0; i < NUM_PLAYERS; i++)
	{
		if(!m_players[i].IsSelected())
		{
			glLoadName(i);
			m_players[i].Draw();
		}
	}

	glMatrixMode(GL_PROJECTION);		// Select The Projection Matrix
	glPopMatrix();				// Pop The Projection Matrix
	glMatrixMode(GL_MODELVIEW);		// Select The Modelview Matrix

	hits = glRenderMode(GL_RENDER);		// Switch To Render Mode, Find Out How Many
						// Objects Were Drawn Where The Mouse Was

	if(hits > 0)				// If There Were More Than 0 Hits
	{
		int choose = buffer[3];		// Make Our Selection The First Object
		int depth = buffer[1];		// Store How Far Away It Is

		for(int i = 1; i < hits; i++)// Loop Through All The Detected Hits
		{
			// If This Object Is Closer To Us Than The One We Have Selected
			if(buffer[i*4+1] < GLuint(depth))
			{
//				if(!m_players[i*4+3].IsSelected())
//				{
					choose = buffer[i*4+3];// Select The Closer Object
					depth = buffer[i*4+1];// Store How Far Away It Is
//				}
			}
		}

		m_players[choose].ToggleSelected();

//		INFO << choose << endl;
	}
}

}
