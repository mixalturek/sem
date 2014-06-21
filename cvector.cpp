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

#include "cvector.h"

namespace basecode
{

CVector::CVector()
{
	X = 0.0f;
	Y = 0.0f;
	Z = 0.0f;
}

CVector::CVector(const CVector& v)
{
	X = v.X;
	Y = v.Y;
	Z = v.Z;
}

CVector::CVector(const CVector& start_point, const CVector& end_point)
{
	*this = end_point - start_point;
}

CVector::CVector(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

CVector::~CVector()
{

}

void CVector::Set(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

void CVector::operator+=(const CVector& v)
{
	X += v.X;
	Y += v.Y;
	Z += v.Z;
}

void CVector::operator-=(const CVector& v)
{
	X -= v.X;
	Y -= v.Y;
	Z -= v.Z;
}

void CVector::operator*=(float n)
{
	X *= n;
	Y *= n;
	Z *= n;
}

void CVector::operator/=(float n)
{
	if(n != 0)
	{
		X /= n;
		Y /= n;
		Z /= n;
	}
}

const CVector & CVector::operator=(const CVector& v)
{
	X = v.X;
	Y = v.Y;
	Z = v.Z;
	return *this;
}

CVector CVector::operator+(const CVector& v) const
{
	return CVector(X + v.X, Y + v.Y, Z + v.Z);
}

CVector CVector::operator-(const CVector& v) const
{
	return CVector(X - v.X, Y - v.Y, Z - v.Z);
}

CVector CVector::operator*(float n) const
{
	return CVector(X * n, Y * n, Z * n);
}

CVector CVector::operator/(float n) const
{
	if(n != 0)
		return CVector(X / n, Y / n, Z / n);

	return *this;
}

// Dot product
float CVector::operator*(const CVector& v) const
{
	return X*v.X + Y*v.Y + Z*v.Z;
}

bool CVector::operator==(const CVector& v) const
{
	// Vectors can be MATHEMATICAL equal!!! (use Normalize() before)
	 return (X == v.X && Y == v.Y && Z == v.Z);
}

bool CVector::operator!=(const CVector& v) const
{
	return !(*this == v);
}

double CVector::Magnitude() const
{
	return sqrt(X*X + Y*Y + Z*Z);
}

void CVector::Normalize()
{
	*this /= this->Magnitude();
}

float CVector::Dot(const CVector& v) const
{
	return X*v.X + Y*v.Y + Z*v.Z;
}

// Cross product from two vectors
CVector CVector::Cross(const CVector& v) const
{
	CVector ret;

	ret.X = Y * v.Z - Z * v.Y;
	ret.Y = Z * v.X - X * v.Z;
	ret.Z = X * v.Y - Y * v.X;

	return ret;
}

// Cross product from three points
CVector CVector::Cross(const CVector& p1, const CVector& p2) const
{
	CVector v1(*this, p1);
	CVector v2(*this, p2);

	return v1.Cross(v2);
}

double CVector::AngleRad(const CVector& v) const
{
	float magnitudes = Magnitude() * v.Magnitude();

	if(magnitudes == 0)
		return 0;

	return acos((*this * v) / magnitudes);
}

double CVector::AngleDeg(const CVector& v) const
{
	return RADTODEG(AngleRad(v));
}

// Distance between two points
double CVector::Distance(const CVector& v) const
{
	return sqrt((X-v.X)*(X-v.X) + (Y-v.Y)*(Y-v.Y) + (Z-v.Z)*(Z-v.Z));
}


///////////////////////////////////////////////////////////////////////////
//// I/O support

istream& operator>>(istream& is, CVector& v)
{
	float tmp;

	is >> tmp; v.SetX(tmp);
	is >> tmp; v.SetY(tmp);
	is >> tmp; v.SetZ(tmp);

	return is;
}

ostream& operator<<(ostream& os, CVector& v)
{
	os << v.GetX() << " " << v.GetY() << " " << v.GetZ();
	return os;
}

}
