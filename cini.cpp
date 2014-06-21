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

#include "cini.h"

namespace basecode
{

CIni::CIni(const string& filename)// throw(QFileNotFound)
	: m_filename(filename)
{
	ifstream inifile(filename.c_str());

	if(!inifile)
	{
		inifile.close();
		throw CFileNotFound(filename);
	}

	string section("global");// Actual section

	while(!inifile.eof())
	{
		char c;

		WhiteSkip(inifile);
		inifile.get(c);

		switch(c)
		{
			// Comment
			case ';':
			case '#':
				// Skip characters to end of line
				while(c != '\n' && inifile && !inifile.eof())
					inifile.get(c);
				break;

			// [section]
			case '[':
				ReadSection(inifile, section);
				break;

			// key=value
			default:
				string key, value;

				inifile.putback(c);
				if(ReadKeyValue(inifile, key, value))
					m_data[section][key] = value;
		}
	}
}

CIni::~CIni()
{
	m_filename.clear();
	m_data.clear();
}

// Read section name "section]" - first '[' has been already read
void CIni::ReadSection(ifstream& inifile, string& section) const
{
	char c;
	string tmp;

	while(inifile && !inifile.eof() && inifile.get(c))
	{
		switch(c)
		{
			// End of section
			case ']':
				section = tmp;// "Return" value (reference)
				return;

			// Probably error in the file
			case '\n':
				return;

			// Character of the section name
			default:
				tmp += c;
		}
	}
}

// Read pair 'key=value'
bool CIni::ReadKeyValue(ifstream& inifile, string& key, string& value) const
{
	char c;
	string tmp;

	// Read key - all to '=' character
	key = "";

	while(inifile && !inifile.eof() && inifile.get(c)
			&& c != '=' && c != '\n')
	{
		key += c;
	}

	if(c != '=')
		return false;

	// Read value
	WhiteSkip(inifile);
	value = "";

	while(inifile && !inifile.eof() && inifile.get(c) && c != '\n')
	{
		value += c;
	}

	if(c != '\n')
		return false;

	return true;
}

// Jump "white" characters in the input file
void CIni::WhiteSkip(ifstream &inifile) const
{
	char c;

	while(inifile && !inifile.eof() && inifile.get(c))
		if(c != '\t' && c != ' ' && c != '\n' && c != '\r')
			break;

	inifile.putback(c);
}

// Read string
string CIni::ReadString(const string& section, const string& key,
		const string& default_value)
{
	string tmp(m_data[section][key]);

	if(tmp.empty())
		return default_value;

	return tmp;
}

// Special for bool
bool CIni::Read(const string& section, const string& key,
		bool default_value)
{
	string tmp(m_data[section][key]);

	if(tmp.empty())
		return default_value;

	if(tmp == "true"  || tmp == "1" || tmp == "yes")
		return true;
	if(tmp == "false" || tmp == "0" || tmp == "no" )
		return false;

	return default_value;
}

// Writing function
void CIni::Write(const string& section, const string& key,
		const string& value)
{
	m_data[section][key] = value;
}

// Special for bool
void CIni::Write(const string& section, const string& key, bool value)
{
	if(value)
		Write(section, key, string("true"));
	else
		Write(section, key, string("false"));
}

// Go through the whole container and save all to the output file
void CIni::SaveToFile(const string& filename) const
		//throw(CFileNotFound)
{
	ofstream inifile(filename.c_str());

	if(!inifile)
		throw CFileNotFound(filename);

	for(_map_section::const_iterator section = m_data.begin();
			section != m_data.end(); ++section)
	{
		// The first section
		inifile << "[" << section->first << "]" << endl;

		for(_map_key::const_iterator key = section->second.begin();
				key != section->second.end(); ++key)
		{
			if(key->second.empty())
				continue;

			inifile << "  " << key->first << "=" << key->second
					<< endl;
		}

		inifile << endl;
	}
}

}
