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

/*
 * Author of this class: Bernard Lidicky <2berny (at) seznam.cz>
 */

#ifndef __CINI_H__
#define __CINI_H__

#include <string>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>

#include "basecode.h"

using namespace std;

namespace basecode
{

/* Structure of the .ini file
 *	[section1]
 *	key1=value
 *	key2=value
 *
 *	[section2]
 *	key1=value
 *	key2=value
 *	...
 *
 * The class is case-sensitive ('a' and 'A' is two diferent characters)
 * Comments can be done with '#' or ';' (to end of line)
 * There can be empty lines, structure of the file will not be changed
 * Round '=' must NOT be spaces (when they aren't in key/value)
 * When there is present more than one 'key' (in the same section),
 * the last one will be used
 * The format of boolean values is true/false, yes/no, 1/0
 * When saving to the file, all comments are deleted
 * Theoretical complication with dos/unix EOL - not tested
 *
 * At end of file MUST be empty line, if no, last value won't be loaded
 */

class CIni
{
public:
	CIni(const string& filename);// throw(CFileNotFound);
	~CIni();

	// Grab the string from section using key
	string ReadString(const string& section, const string& key,
			const string& default_value);

	template<class T>
	T Read(const string& section, const string& key,
			const T& default_value);

	// Special for bool (true/false, yes/no, 1/0)
	bool Read(const string& section, const string& key,
			bool default_value);


	// Write settings using section and key
	void Write(const string& section, const string& key,
			const string& value);

	template<class T>
	void Write(const string& section, const string& key, const T& value);

	// Special for bool
	void Write(const string& section, const string& key, bool value);


	// Write all to the disk file (warning: all comments are deleted)
	void SaveToFile(const string& inifile) const;// throw(CFileNotFound);
	void SaveToFile() const// throw(CFileNotFound)
			{ SaveToFile(m_filename); }

private:
	// Inner methods to search string

	// Read name of section
	void ReadSection(ifstream &inifile, string& section) const;

	// Read 'key=value'
	bool ReadKeyValue(ifstream &inifile, string& key,
			string& value) const;

	// Skip the white characters
	void WhiteSkip(ifstream &inifile) const;

private:
	typedef map<string, string, less<string> > _map_key;
	typedef map<string, _map_key, less<string> > _map_section;

	_map_section m_data;// All data
	string m_filename;// Name of the file
};

// Save T converted to string to m_data[section][key]
template<class T>
void CIni::Write(const string& section, const string& key, const T& value)
{
	string tmp;
	stringstream sbuf(tmp);
	sbuf << value;
	m_data[section][key] = sbuf.str();
}

// From m_data[section][key] string read type T
// When T is empty, return default_value
template<class T>
T CIni::Read(const string& section, const string& key, const T& default_value)
{
	string tmp(m_data[section][key]);

	if(tmp.empty())
		return default_value;

	stringstream sbuf(tmp);
	T value;
	sbuf >> value;
	return value;
}

}

#endif
