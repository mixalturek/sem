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

#ifndef __CVECTOR_H__
#define __CVECTOR_H__

#include <cmath>
#include <iostream>
#include "basecode.h"

#define X m_data[0]
#define Y m_data[1]
#define Z m_data[2]

using namespace std;

namespace basecode
{

class CVector
{
public:
	CVector();
	CVector(float x, float y, float z);
	CVector(const CVector& v);

	// Vector from two points
	CVector(const CVector& start_point, const CVector& end_point);

	~CVector();


	void Set(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	void SetX(float x) { X = x; }
	void SetY(float y) { Y = y; }
	void SetZ(float z) { Z = z; }

	float GetX() const { return X; }
	float GetY() const { return Y; }
	float GetZ() const { return Z; }


	// Return pointer to data (for glVertex3*v())
	float* GetDataPtr() const { return (float*)m_data; }
	operator float*() const { return (float*)m_data; }
	operator const float*() const { return m_data; }

	bool IsZero() const { return (X == 0.0f && Y == 0.0f && Z == 0.0f); }


	const CVector& operator=(const CVector& v);

	void operator+=(const CVector& v);
	void operator-=(const CVector& v);

	CVector operator+(const CVector& v) const;
	CVector operator-(const CVector& v) const;

	// Inverse vector
	CVector operator-() const { return CVector(-X, -Y, -Z); }


	// Vector scaling
	void operator*=(float n);
	void operator/=(float n);
	CVector operator*(float n) const;
	CVector operator/(float n) const;

	// Vectors can be MATHEMATICAL equal (use Normalize() before)
	bool operator==(const CVector& v) const;
	bool operator!=(const CVector& v) const;


	// Dot product
	float operator*(const CVector& v) const;
	float Dot(const CVector& v) const;


	// Cross product from two vectors
	CVector Cross(const CVector& v) const;

	// Cross product from three points
	CVector Cross(const CVector& p1, const CVector& p2) const;


	double Magnitude() const;
	void Normalize();

	double AngleRad(const CVector& v) const;
	double AngleDeg(const CVector& v) const;

	// Distance of two points
	double Distance(const CVector& v) const;

public:
	float m_data[3];
};

///////////////////////////////////////////////////////////////////////////
//// I/O support

istream& operator>>(istream& is, CVector& v);
ostream& operator<<(ostream& os, CVector& v);

}

#endif
