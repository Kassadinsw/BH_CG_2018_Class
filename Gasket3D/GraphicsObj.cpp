#include <stdlib.h>
#include "GraphicsObj.h"

CGraphicsObj::CGraphicsObj(void)
{
	vertex_array_obj=0;
	vertex_buffer_obj=0;
	num_vertices=0;
	primitive_type=GL_TRIANGLES;
}

void CGraphicsObj::Draw(void)
{
	glBindVertexArray(vertex_array_obj);
	glDrawArrays(primitive_type, 0, num_vertices);
	glBindVertexArray(0);
}

void CGraphicsObj::CreateGasket2DPoints(
	const vec2 tri_vertices[3],
	const vec2& starting_point,
	int num_points)
{
	primitive_type=GL_POINTS;

	num_vertices=num_points;

	vec2 *p=new vec2 [num_points];

	p[0]=starting_point;

	for (int i=1; i<num_points; ++i)
	{
		int j=rand()%3;
		p[i]=0.5f*(p[i-1]+tri_vertices[j]);
	}

	glGenVertexArrays(1, &vertex_array_obj);
	glBindVertexArray(vertex_array_obj);

	glGenBuffers(1, &vertex_buffer_obj);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj);
	glBufferData(GL_ARRAY_BUFFER,
		num_points*sizeof(vec2), p,
		GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,
		2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);

	glBindVertexArray(0);

	delete [] p;
}

void CGraphicsObj::Divide2DTriangle(vec2 *v_out, int &ipos,
	const vec2& v0_in, const vec2& v1_in, const vec2& v2_in,
	int depth)
{
	if (depth>0)
	{
		vec2 m01=0.5f*(v0_in+v1_in);
		vec2 m12=0.5f*(v1_in+v2_in);
		vec2 m20=0.5f*(v2_in+v0_in);

		Divide2DTriangle(v_out, ipos,
			v0_in, m01, m20, depth-1);
		Divide2DTriangle(v_out, ipos,
			m01, v1_in, m12, depth-1);
		Divide2DTriangle(v_out, ipos,
			m20, m12, v2_in, depth-1);
	}
	else
	{
		v_out[ipos++]=v0_in;
		v_out[ipos++]=v1_in;
		v_out[ipos++]=v2_in;
	}
}

void CGraphicsObj::CreateGasket2DTriangles(
	const vec2 tri_vertices[3], int depth)
{
	primitive_type=GL_TRIANGLES;

	num_vertices=3;
	int i;
	for (i=0; i<depth; ++i)
		num_vertices*=3;

	vec2 *p=new vec2 [num_vertices];

	i=0;
	Divide2DTriangle(p, i, 
		tri_vertices[0], tri_vertices[1], tri_vertices[2],
		depth);

	glGenVertexArrays(1, &vertex_array_obj);
	glBindVertexArray(vertex_array_obj);

	glGenBuffers(1, &vertex_buffer_obj);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj);
	glBufferData(GL_ARRAY_BUFFER,
		num_vertices*sizeof(vec2), p,
		GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,
		2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);

	glBindVertexArray(0);

	delete [] p;
}

void CGraphicsObj::Divide3DTetra(vec3 *v_out, int &ipos,
	const vec3& v0_in, const vec3& v1_in,
	const vec3& v2_in, const vec3& v3_in,
	int depth)
{
	int i, j;
	vec3 mid[6];
	if (depth>0)
	{
		mid[0]=0.5f*(v0_in+v3_in);
		mid[1]=0.5f*(v1_in+v3_in);
		mid[2]=0.5f*(v2_in+v3_in);
		mid[3]=0.5f*(v1_in+v2_in);
		mid[4]=0.5f*(v2_in+v0_in);
		mid[5]=0.5f*(v0_in+v1_in);

		Divide3DTetra(v_out, ipos,
			v0_in, mid[5], mid[4], mid[0], depth-1);
		Divide3DTetra(v_out, ipos,
			v1_in, mid[3], mid[5], mid[1], depth-1);
		Divide3DTetra(v_out, ipos,
			v2_in, mid[4], mid[3], mid[2], depth-1);
		Divide3DTetra(v_out, ipos,
			mid[0], mid[1], mid[2], v3_in, depth-1);
	}
	else
	{
		const vec3 *pv[4]={&v0_in, &v1_in, &v2_in, &v3_in};
		const int iv_faces[4][3]={
			{3,0,1},{3,1,2},{3,2,0},{0,2,1}
		};
		for (i=0; i<4; ++i)
		{
			for (j=0; j<3; ++j)
				v_out[ipos++]=*pv[iv_faces[i][j]];
		}
	}
}

void CGraphicsObj::CreateGasket3D(
	const vec3 tetra_vertices[4], int depth)
{
	primitive_type=GL_TRIANGLES;

	num_vertices=12;
	int i;
	for (i=0; i<depth; ++i)
		num_vertices*=4;

	vec3 *p=new vec3 [num_vertices];

	i=0;
	Divide3DTetra(p, i, 
		tetra_vertices[0], tetra_vertices[1], 
		tetra_vertices[2], tetra_vertices[3],
		depth);

	glGenVertexArrays(1, &vertex_array_obj);
	glBindVertexArray(vertex_array_obj);

	glGenBuffers(1, &vertex_buffer_obj);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj);
	glBufferData(GL_ARRAY_BUFFER,
		num_vertices*sizeof(vec3), p,
		GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,
		3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);

	glBindVertexArray(0);

	delete [] p;
}
