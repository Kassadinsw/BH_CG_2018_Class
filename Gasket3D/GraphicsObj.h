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

protected:
	void Divide3DTetra(vec3 *v_out, int &ipos,
		const vec3& v0_in, const vec3& v1_in,
		const vec3& v2_in, const vec3& v3_in,
		int depth);

public:
	void CreateGasket3D(
		const vec3 tetra_vertices[4], int depth);
};

#endif
