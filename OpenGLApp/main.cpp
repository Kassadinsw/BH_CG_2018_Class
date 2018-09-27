#include <stdio.h>
#include "GL/glew.h"
#include "GL/freeglut.h"

void init(void)
{
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

	printf("Vender: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(640, 480);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("OpenGL application");
	glutDisplayFunc(display);

	glewExperimental=GL_TRUE;
	glewInit();

	init();

	glutMainLoop();

	return 1;
}
