#include <stdio.h>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GraphicsObj.h"
#include "GLHelper.h"
#include "mat.h"

CGraphicsObj g_obj;
GLuint g_simple_GLSL_prog;

void init_shaders(void)
{
	g_simple_GLSL_prog=InitShader(
		"..\\shaders\\simple-3D-vs.txt",
		"..\\shaders\\simple-3D-fs.txt");
	glUseProgram(g_simple_GLSL_prog);

	mat4 M;
	int loc=glGetUniformLocation(g_simple_GLSL_prog, "view_matrix");
	glUniformMatrix4fv(loc, 1, GL_TRUE, M);

	M=Translate(0.0f, 0.0f, -2.0f);
	loc=glGetUniformLocation(g_simple_GLSL_prog, "model_matrix");
	glUniformMatrix4fv(loc, 1, GL_TRUE, M);
}

void init_models(void)
{
	vec3 tetra_v[]={
		vec3(-1.0f, -1.0f, -1.0f),
		vec3(1.0f, -1.0f, -1.0f),
		vec3(0.0f, 1.0f, -1.0f),
		vec3(0.0f, 0.0f, 1.0f)
	};
	g_obj.CreateGasket3D(tetra_v, 5);
}

void init(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	printf("Vender: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	init_shaders();

	init_models();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	mat4 M;
	M=Perspective(60.0f, (float)w/(float)h, 0.01f, 5.0f);
	glUseProgram(g_simple_GLSL_prog);
	int loc=glGetUniformLocation(g_simple_GLSL_prog, "projection_matrix");
	glUniformMatrix4fv(loc, 1, GL_TRUE, M);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	g_obj.Draw();
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(640, 480);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Gasket 3D Program");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glewExperimental=GL_TRUE;
	glewInit();

	init();

	glutMainLoop();

	return 1;
}
