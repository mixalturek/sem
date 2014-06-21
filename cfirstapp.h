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

#ifndef __CFIRSTAPP_H__
#define __CFIRSTAPP_H__

#include <ctime>

#include "basecode.h"
#include "capplicationex.h"
#include "cterrain.h"
#include "cgrid.h"
#include "ccheat.h"
#include "cimage.h"
#include "csimplemenu.h"
#include "ccamera.h"
#include "csceneobjectmanager.h"
#include "cbullet.h"
#include "cbillboard.h"
#include "ccolor.h"
#include "cparticleengine.h"
#include "cplayer.h"

//#define USE_CHEATS
#define USE_TEXTURES

#ifdef USE_TEXTURES
#define NUM_TEXTURES 24
#define PLAYER_TEXTURES_BEGIN 2
#define PLAYER_TEXTURES_NUM (NUM_TEXTURES-PLAYER_TEXTURES_BEGIN)
#define NUM_PLAYERS 300
#endif

// Time diference between two shots
#define SHOOT_INTERVAL 500

// Camera
#define WHICH_CAMERA_MAX	2

#define WHICH_CAMERA_PLAYER	0
#define WHICH_CAMERA_DIST_ROT	1
#define WHICH_CAMERA_TOP	2

#define SUN_LIGHT		GL_LIGHT0
#define SPOT_LIGHT		GL_LIGHT1

using namespace std;

namespace basecode
{

class CFirstApp : public CApplicationEx
{
private:
	CFirstApp(const CFirstApp& obj) : CApplicationEx(0, NULL),
			m_cam(CVector(0.0f, 0.0f, 0.0f)) {}
	const CFirstApp& operator=(const CFirstApp& obj)
	{ return *this; }

public:
	CFirstApp(int argc, char *argv[]);
	virtual ~CFirstApp();
	virtual void Init(const string& win_title);

protected:
	virtual void InitGL();
	virtual void Draw();
	virtual void Update();
	virtual bool ProcessEvent(SDL_Event& event);

	void Shoot();
	void Explosion(float time, const CVector pos,
			const CColor& color);
	void Selection(int mouse_x, int mouse_y);

private:
	static Uint32 ShootTimerCallback(Uint32 interval, void* param);
	void ShootTimerStart();
	void ShootTimerStop();

private:
	CTerrain* m_terrain;
	CCamera m_cam;

#ifdef USE_TEXTURES
	GLuint m_textures[NUM_TEXTURES];
#endif

#ifdef USE_CHEATS
	CCheat m_cheat;
#endif

	CSimpleMenu m_main_menu;
	CSimpleMenu m_terrain_menu;
	CSimpleMenu m_polyg_mode_menu;
	CSimpleMenu* m_menu;

	CSceneObjectManager m_obj_man;
	vector<CBullet*> m_bullets;
	vector<CParticleEngine*> m_explosions;

	SDL_TimerID m_shoot_timer_id;

	int m_which_camera;
	float m_sun_rot;

	CPlayer m_players[NUM_PLAYERS];
};

}

#endif
