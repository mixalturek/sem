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

#include <fstream>
#include "basecode.h"
#include "cfirstapp.h"

using namespace std;
using namespace basecode;

void my_terminate();
void my_unexpected();

void (*old_terminate)() = set_terminate(my_terminate);
void (*old_unexpected)() = set_unexpected(my_unexpected);

void my_terminate()
{
	ERROR << _("Uncatched exception or throwing exception in destructor!")
			<< endl;
	old_terminate();
}

void my_unexpected()
{
	ERROR << _("Unexpected exception was thrown!") << endl;
	old_unexpected();
}


#ifdef USE_WINMAIN
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char *argv[])
#endif
{
	try
	{
#ifdef USE_WINMAIN
		CFirstApp app(0, NULL);
#else
		CFirstApp app(argc, argv);
#endif
		app.Init(_("sem"));
		app.MainLoop();
	}
	catch(CFileNotFound& ex)
	{
		ERROR << _("File was not found: ") << ex.what() << endl;
		return EXIT_FAILURE;
	}
	catch(CBadFileFormat& ex)
	{
		ERROR << _("Bad file format: ") << ex.what() << endl;
		return EXIT_FAILURE;
	}
	catch(std::bad_alloc& ex)
	{
		ERROR << _("Unable to allocate memory: ")
				<< ex.what() << endl;
		return EXIT_FAILURE;
	}
	catch(std::runtime_error& ex)
	{
		ERROR << ex.what() << endl;
		return EXIT_FAILURE;
	}
	catch(...)
	{
		ERROR << _("Unhandled exception occurs!") << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
