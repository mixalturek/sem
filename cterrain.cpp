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

#include "cterrain.h"

namespace basecode
{

CTerrain::CTerrain(const string& filename) :
		m_width(0),
		m_depth(0),
		m_hfactor(1.0f),
		m_det_level(80.0f),
		m_pdata(NULL),
		m_texture(0),
		m_texture_detail(0),
		m_vertices(NULL),
		m_explosion_img(NULL)
{
	CGLExt::Init();

	CIni ini(filename);
	string str;

	m_hfactor = ini.Read("display", "height_factor", m_hfactor);

	// Data of terrain
	if((str = ini.ReadString("paths", "terrain", "")) == "")
		throw std::runtime_error(
			_("Unable to load image path for terrain data"));
	GenerateTerrain(str);

	// Terain texture
	if((str = ini.ReadString("paths", "texture", "")) == "")
		throw std::runtime_error(
			_("Unable to load path for terrain texture"));
	m_texture = CreateTexture(str);

	// Detail texture
	if(CGLExt::IsGL_ARB_multitexture())
	{
		if((str = ini.ReadString("paths", "detail_texture", ""))
				== "")
			throw std::runtime_error(
			_("Unable to load path for detailed texture."));

		m_texture_detail = CreateTexture(str, true);
		m_det_level = ini.Read("display", "detail_level",
				 m_det_level);
	}

	m_explosion_img = new CImage("data/bullets/explosion.png");
	m_explosion_img->ConvertToRGBA();
}

CTerrain::~CTerrain()
{
	if(m_pdata != NULL)
		delete [] m_pdata;

	if(m_vertices != NULL)
		delete [] m_vertices;

	if(m_explosion_img != NULL)
		delete m_explosion_img;

	DeleteTexture(m_texture);
	DeleteTexture(m_texture_detail);
}

void CTerrain::GenerateTerrain(const string& filename)
{
	CImage img(filename);
	img.ConvertToRGBA();
	img.SwapRows();

	m_width = img.GetWidth();
	m_depth = img.GetHeight();

	int num = m_width*m_depth;
	GLubyte* p_pix = img.GetDataPtr();

	// Only constructor can create object, so there can be no recreating

	// At Explode() would be access to invalid memory when there isn't +1
	// This is the fastest solution
	m_pdata = new GLubyte[num+1];
	m_vertices = new CVertex[num];

	for(int i = 0; i < num; i++)
		m_pdata[i] = (GLubyte)(p_pix[i*img.GetBPP()]);// Only red


	int x, z;
	const int width_half = m_width >> 1;
	const int depth_half = m_depth >> 1;
	CVertex* v1 = m_vertices;

	// Vertices and textures
	for(z = 0; z < m_depth; z++)
	{
		for(x = 0; x < m_width; x++)
		{
			v1->m_pos.Set(x-width_half,
					GetHeightGLFast(x,z), z-depth_half);
			v1->m_coords[0] = x / (float)m_width;
			v1->m_coords[1] = z / (float)m_depth;
			v1++;
		}
	}

	v1 = m_vertices;// This line
	CVertex* v2 = m_vertices + m_depth;// Next line
	CVector normal;

	// Normal vectors
	for(z = 0; z < m_depth-1; z++)// From top to bottom
	{
		for(x = 0; x < m_width-1; x++)// From left to right
		{
			// v1 * * * v2
			//      * *
			//        * v2 + 1
			normal = v1->m_pos.Cross((v2 + 1)->m_pos, v2->m_pos);
			v1->m_norm += normal;
			v2->m_norm += normal;
			(v2 + 1)->m_norm += normal;

			//     v1 *
			//        * *
			// v1 + 1 * * * v2 + 1
			normal = v1->m_pos.Cross((v1 + 1)->m_pos, (v2 + 1)->m_pos);
			v1->m_norm += normal;
			(v2 + 1)->m_norm += normal;
			(v1 + 1)->m_norm += normal;

			v1++;
			v2++;
		}

		// Because, the loop is to m_depth-1
		v1++;
		v2++;
	}


	v1 = m_vertices;

	// Unit legth of normals
	for(z = 0; z < m_depth; z++)
	{
		for(x = 0; x < m_width; x++)
		{
			(v1++)->m_norm.Normalize();
		}
	}
}

void CTerrain::Draw() const
{
	glPushAttrib(GL_ENABLE_BIT);

	if(CGLExt::IsGL_ARB_multitexture())// With multitexturing
	{
		// Second texture unit
		CGLExt::glActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
				GL_COMBINE_EXT);
		glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT, 2);
		glBindTexture(GL_TEXTURE_2D, m_texture_detail);

		glMatrixMode(GL_TEXTURE);
			glLoadIdentity();
			glScalef(m_det_level, m_det_level, 1.0f);
		glMatrixMode(GL_MODELVIEW);

		// First texture unit
		CGLExt::glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}
	else// Without multitexturing
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}


	int x, z;
	CVertex* v1 = m_vertices;// This line
	CVertex* v2 = m_vertices + m_depth;// Next line

	for(z = 0; z < m_depth-1; z++)// From top to bottom
	{
/*		glBegin(GL_TRIANGLES);
		for(z = 0; z < m_depth-1; z++)// From top to bottom
		{
			v1->Draw();		// v1 * * * v2
			v2->Draw();		//      * *
			(v2 + 1)->Draw();	//        * v2 + 1

			v1->Draw();		//     v1 *
			(v2 + 1)->Draw();	//        * *
			(v1 + 1)->Draw();	// v1 + 1 * * * v2 + 1

			v1++;
			v2++;
		}
		glEnd();
*/
		glBegin(GL_TRIANGLE_STRIP);
		for(x = 0; x < m_width-1; x++)// From left to right
		{
			v1->Draw();// Left
			v2->Draw();// Right

			v1++;
			v2++;
		}
		glEnd();

		// The loop is to m_depth-1
		v1++;
		v2++;
	}

	glPopAttrib();
}

void CTerrain::Explode(int x, int z, int radius)
{
	if(m_pdata == NULL)
		return;

	x = x + m_width / 2;
	z = z + m_depth / 2;
	radius /= 2;

	// Modification terrain texture
	int w, h;
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);

	glTexSubImage2D(GL_TEXTURE_2D, 0,
		x*(w/m_width)-m_explosion_img->GetWidth()/2,
		z*(h/m_depth)-m_explosion_img->GetHeight()/2,
		m_explosion_img->GetWidth(), m_explosion_img->GetHeight(),
		(m_explosion_img->GetBPP() == 3) ? GL_RGB : GL_RGBA,
		GL_UNSIGNED_BYTE, m_explosion_img->GetDataPtr());


	// Modification pixel and vertex data
	int mem_pos = 0;
	int x_border_minus = (x-radius < 0) ? 0 : x-radius;
	int z_border_minus = (z-radius < 0) ? 0 : z-radius;
	int x_border_plus = (x+radius > m_width) ? m_width : x+radius;
	int z_border_plus = (z+radius > m_depth) ? m_depth : z+radius;

	CVertex* v;

	// Memory is allocated bigger than it is used, so <= is OK
	for(int tmpx = x_border_minus; tmpx <= x_border_plus; tmpx++)
	{
		for(int tmpz = z_border_minus; tmpz < z_border_plus; tmpz++)
		{
			mem_pos = tmpz*m_width + tmpx;
			v = m_vertices + tmpz*m_width + tmpx;

			if(m_pdata[mem_pos] >= radius)
			{
				m_pdata[mem_pos] -= radius;
				v->m_pos.Y -= radius*m_hfactor;
			}
			else
			{
				m_pdata[mem_pos] = 0;
			}
		}
	}

	TODO << "prepocitat normaly" << endl;
}

float CTerrain::GetHeight(int x, int z) const
{
	if(m_pdata == NULL)
		return 0.0f;

	if((x > 0 && x < m_width) && (z > 0 && z < m_depth))
		return GetHeightFast(x, z);
	else
		return 0.0f;
}

float CTerrain::GetHeightGL(int x, int z) const
{
	if(m_pdata == NULL)
		return 0.0f;

	x = x + m_width / 2;
	z = z + m_depth / 2;

	if((x > 0 && x < m_width) && (z > 0 && z < m_depth))
		return GetHeightGLFast(x, z);
	else
		return 0.0f;
}

}
