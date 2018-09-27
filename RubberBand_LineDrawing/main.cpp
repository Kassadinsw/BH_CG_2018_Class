#include <stdio.h>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GraphicsObj.h"
#include "GLHelper.h"

CGraphicsObj g_obj;
GLuint g_simple_GLSL_prog;

vec2 g_cur_vertices[2]={vec2(0.0f), vec2(0.0f)};
bool g_rubber_band_mode=false;

int g_window_width, g_window_height;

void UpdateObjGLBuffer(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, g_obj.vertex_buffer_obj);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec2)*2,
		g_cur_vertices);
}

void MapMousePosToNormCoord(int mouse_x, int mouse_y, vec2& P)
{
	P.x=2.0f*(float)mouse_x/g_window_width-1.0f;
	P.y=2.0f*(float)(g_window_height-mouse_y)/g_window_height-1.0f;
}

void init_shaders(void)
{
	g_simple_GLSL_prog=InitShader(
		"..\\shaders\\simple-vs.txt",
		"..\\shaders\\simple-fs.txt");
	glUseProgram(g_simple_GLSL_prog);
}

void init_models(void)
{
	g_obj.Create2DLineSegment(g_cur_vertices);
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
	g_window_width=w;
	g_window_height=h;
	glViewport(0, 0, w, h);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	g_obj.Draw();
	glFlush();
}

void mouse(int button, int state, int x, int y)
{
	if (button==GLUT_LEFT_BUTTON)
	{
		if (state==GLUT_DOWN)
		{
			g_rubber_band_mode=true;
			vec2 P;
			MapMousePosToNormCoord(x, y, P);
			g_cur_vertices[0]=P;
			g_cur_vertices[1]=P;
			UpdateObjGLBuffer();
			glutPostRedisplay();
		}
		else
		{
			g_rubber_band_mode=false;
		}
	}
}

void mouse_motion(int x, int y)
{
	if (g_rubber_band_mode)
	{
		MapMousePosToNormCoord(x, y, g_cur_vertices[1]);
		UpdateObjGLBuffer();
		glutPostRedisplay();
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(640, 480);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Rubber-band line drawing");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(mouse_motion);

	glewExperimental=GL_TRUE;
	glewInit();

	init();

	glutMainLoop();

	return 1;
}
