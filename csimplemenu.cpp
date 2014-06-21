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

#include "csimplemenu.h"

namespace basecode
{

CSimpleMenu::CSimpleMenu(int num_items) :
	CMenu(num_items),
	m_font(NULL)
{

}

CSimpleMenu::CSimpleMenu(CFont* font, int num_items) :
	CMenu(num_items),
	m_font(font)
{

}

CSimpleMenu::~CSimpleMenu()
{

}

void CSimpleMenu::Draw(int x, int y, int num_items)
{
	if(m_font == NULL)
	{
		WARN << _("Font hasn't been initialized yet") << endl;
		return;
	}

	if(m_event_codes.size() == 0)
	{
		WARN << _("Menu is empty") << endl;
		return;
	}

	int i;
	int min, max;

	min = m_selected - num_items/2;
	if(min < 0)
		min = 0;

	max = min + num_items;
	if(max > (int)m_event_codes.size())
		max = m_event_codes.size();

	if(max-min < num_items)
	{
		min = max - num_items;
		if(min < 0)
			min = 0;
	}

	if(m_font != NULL)
	{
		m_font->Begin();
		m_font->SetAlign(ALIGN_CENTER);

		for(i = min; i < m_selected; i++, y += m_font->GetLineSkip())
			m_font->Draw(m_event_strings[i], x, y, true);

		m_font->SetColor(255, 0, 0);
		m_font->Draw(m_event_strings[i], x, y);
		m_font->SetColor(255, 255, 255);

		y += m_font->GetLineSkip();

		for(i++; i < max; i++, y += m_font->GetLineSkip())
			m_font->Draw(m_event_strings[i], x, y, true);

		m_font->SetAlign(ALIGN_LEFT);
		m_font->End();
	}
}

}
