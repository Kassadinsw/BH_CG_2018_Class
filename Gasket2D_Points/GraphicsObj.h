#ifndef _GRAPHICS_OBJ_H_
#define _GRAPHICS_OBJ_H_

#include "GL/glew.h"
#include "vec.h"

class CGraphicsObj
{
public:
	GLuint vertex_array_obj;
	GLuint vertex_buffer_obj;

	int num_vertices;

	CGraphicsObj(void);
	void Draw(void);
	void CreateGasket2DPoints(
		const vec2 tri_vertices[3],
		const vec2& starting_point,
		int num_points);
};

#endif
