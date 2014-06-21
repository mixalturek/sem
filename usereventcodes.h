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

#ifndef __USEREVENTCODES_H__
#define __USEREVENTCODES_H__

enum user_event
{
	// FPS
	EVT_ACTUALIZE_FPS_STRING = 0,

	// Cheats
	EVT_CHEAT_CODE,

	// Main menu
	EVT_MAIN_MENU_TERRAIN,
	EVT_MAIN_MENU_POLYGON_MODE,
	EVT_MAIN_MENU_TOGGLE_CAMERA,
	EVT_MAIN_MENU_TOGGLE_LIGHTS,
	EVT_MAIN_MENU_TOGGLE_FOG,
	EVT_MAIN_MENU_HIDE,
	EVT_MAIN_MENU_EXIT,

	// Terrain menu
	// Which terrain was selected is m_menu.GetSel()
	EVT_TERRAIN_MENU_SEL,
	EVT_TERRAIN_MENU_GOTO_MAIN_MENU,

	// Polygon menu
	EVT_POLYG_MENU_FILL,
	EVT_POLYG_MENU_LINES,
	EVT_POLYG_MENU_POINTS,
	EVT_POLYG_MENU_GOTO_MAIN_MENU,

	// Shoot
	EVT_SHOOT
};

#endif
