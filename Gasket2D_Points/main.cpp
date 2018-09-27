#include <stdio.h>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GraphicsObj.h"
#include "GLHelper.h"

CGraphicsObj g_obj;
GLuint g_simple_GLSL_prog;

void init_shaders(void)
{
	g_simple_GLSL_prog=InitShader(
		"..\\shaders\\simple-vs.txt",
		"..\\shaders\\simple-fs.txt");
	glUseProgram(g_simple_GLSL_prog);
}

void init_models(void)
{
	vec2 tri_v[3]={
		vec2(-1.0f, -1.0f), vec2(1.0f, -1.0f), vec2(0.0f, 1.0f)
	};
	g_obj.CreateGasket2DPoints(
		tri_v, vec2(0.25f, 0.5f), 100000);
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

	glutCreateWindow("Gasket Program");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glewExperimental=GL_TRUE;
	glewInit();

	init();

	glutMainLoop();

	return 1;
}
