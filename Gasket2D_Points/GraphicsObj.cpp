#include <stdlib.h>
#include "GraphicsObj.h"

CGraphicsObj::CGraphicsObj(void)
{
	vertex_array_obj=0;
	vertex_buffer_obj=0;
	num_vertices=0;
}

void CGraphicsObj::Draw(void)
{
	glBindVertexArray(vertex_array_obj);
	glDrawArrays(GL_POINTS, 0, num_vertices);
	glBindVertexArray(0);
}

void CGraphicsObj::CreateGasket2DPoints(
	const vec2 tri_vertices[3],
	const vec2& starting_point,
	int num_points)
{
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

