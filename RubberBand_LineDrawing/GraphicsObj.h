#ifndef _GRAPHICS_OBJ_H_
#define _GRAPHICS_OBJ_H_

#include "GL/glew.h"
#include "vec.h"

class CGraphicsObj
{
public:
	GLuint vertex_array_obj;
	GLuint vertex_buffer_obj;

	GLenum primitive_type;
	int num_vertices;

	CGraphicsObj(void);
	
	void Draw(void);
	
	void CreateGasket2DPoints(
		const vec2 tri_vertices[3],
		const vec2& starting_point,
		int num_points);

protected:
	void Divide2DTriangle(vec2 *v_out, int &ipos,
		const vec2& v0_in, const vec2& v1_in, const vec2& v2_in,
		int depth);

public:
	void CreateGasket2DTriangles(
		const vec2 tri_vertices[3], int depth);

	void Create2DLineSegment(
		const vec2 end_points[2]);
};

#endif
