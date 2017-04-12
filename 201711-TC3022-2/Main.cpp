/*
********************************************
Pedro �ngel Gonz�lez Gonz�lez A01169094
********************************************
*/

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <IL/il.h>
#include "Camera.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Transform.h"
#include <iostream>
#include <vector>
#include <sstream>

Mesh _sineWaveMesh;
ShaderProgram _SineWaveShaderProgram;

Transform _SineWaveTransform;
Texture2D _SineWaveTexture;
Texture2D _heightMap;

Camera _camera;
float time;

void Initialize()
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> colors;
	std::vector<unsigned int> indices{ 0,1,2,0,2,3 };

	positions.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	positions.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));

	colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));

	_sineWaveMesh.CreateMesh(4);
	_sineWaveMesh.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	_sineWaveMesh.SetColorAttribute(colors, GL_STATIC_DRAW, 1);
	_sineWaveMesh.SetIndices(indices, GL_STATIC_DRAW);

	_SineWaveShaderProgram.CreateProgram();
	_SineWaveShaderProgram.Activate();
	_SineWaveShaderProgram.AttachShader("Billboard.vert", GL_VERTEX_SHADER);
	_SineWaveShaderProgram.AttachShader("Default.frag", GL_FRAGMENT_SHADER);
	_SineWaveShaderProgram.SetAttribute(0, "VertexPosition");
	_SineWaveShaderProgram.SetAttribute(1, "VertexColor");
	_SineWaveShaderProgram.LinkProgram();
	_SineWaveShaderProgram.Deactivate();


	_camera.SetPosition(0.0f, 0.0f, -8.0f);
	_camera.SetRotation(-20.0f, 0.0f, 0.0f);

	glm::vec3 translations[1000];
	int index = 0;
	GLfloat offset = 1.0f;
	for (GLint z = -10; z < 10; z += 2) {
		for (GLint y = -10; y < 10; y += 2)
		{
			for (GLint x = -10; x < 10; x += 2)
			{
				glm::vec3 translation;
				translation.x = (GLfloat)x / 10.0f + offset;
				translation.y = (GLfloat)y / 10.0f + offset;
				translation.z = (GLfloat)z / 10.0f + offset;
				translations[index++] = translation;
			}
		}
	}
	_SineWaveShaderProgram.Activate();
	for (GLuint i = 0; i < 1000; i++)
	{
		std::stringstream _ss;
		std::string _index;
		_ss << i;
		_index = _ss.str();
		_SineWaveShaderProgram.SetUniformf("offsets[" + _index + "]", translations[i].x, translations[i].y, translations[i].z);
	}
	_SineWaveShaderProgram.Deactivate();
}

void Idle()
{
	glutPostRedisplay();
}

void GameLoop()
{
	// Siempre es recomendable borrar la informaci�n anterior del framebuffer.
	// En este caso estamos borrando la informaci�n de color,
	// y la informaci�n de profundidad.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	time += 0.0005f;
	if (time >= 360)
		time = 0;

	_SineWaveShaderProgram.Activate();

	_SineWaveShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_SineWaveTransform.GetModelMatrix());
	_SineWaveShaderProgram.SetUniformMatrix("ModelViewMatrix", _camera.GetViewMatrix()*_SineWaveTransform.GetModelMatrix());
	_SineWaveShaderProgram.SetUniformMatrix("ProjectionMatrix", _camera.GetProjectionMatrix());
	_SineWaveShaderProgram.SetUniformMatrix("ViewMatrix", _camera.GetViewMatrix());
	_SineWaveShaderProgram.SetUniformMatrix("ModelMatrix", _SineWaveTransform.GetModelMatrix());
	_sineWaveMesh.Draw(GL_TRIANGLES, 1000);

	_SineWaveShaderProgram.Deactivate();



	// Cambiar el buffer actual
	glutSwapBuffers();
}

void Keyboard(unsigned char key, int y, int z)
{
	if (key == 'w')
		_camera.MoveForward(0.1f, false);
	if (key == 's')
		_camera.MoveForward(-0.1f, false);
	if (key == 'd')
		_camera.MoveRight(0.1f, false);
	if (key == 'a')
		_camera.MoveRight(-0.1f, false);
}

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		_camera.MoveForward(0.1f, false);
	if (key == GLUT_KEY_DOWN)
		_camera.MoveForward(-0.1f, false);
	if (key == GLUT_KEY_RIGHT)
		_camera.MoveRight(0.1f, false);
	if (key == GLUT_KEY_LEFT)
		_camera.MoveRight(-0.1f, false);

}

int _previousX = -1;
bool _mousePressed = false;

void MouseButtons(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		_mousePressed = true;
	if (button == GLUT_RIGHT_BUTTON)
		_mousePressed = false;
	_previousX = x;
}

void MouseMotion(int x, int y)
{
	if (!_mousePressed) return;

	_camera.Yaw((x - _previousX)*0.1f);
	_previousX = x;
}

//cuando el usuario mueve el mouse sin presionar
void MousePassiveMotion(int x, int y)
{
	int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	int deltaX = x - centerX;

	_camera.Rotate(0.0f, -deltaX*0.01f, 0.0f, true);

	if (deltaX)
		glutWarpPointer(centerX, centerY);
}

void ReshapeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
	_camera.SetPerspective(1.0f, 1000.0f, 60.0f, (float)width / (float)height);
}

int main(int argc, char* argv[])
{
	// Inicializaci�n de Freeglut.
	// Freeglut se encarga de crear una ventana
	// En donde vamos a poder dibujar
	glutInit(&argc, argv);
	// Freeglut es el encargado de solicitar un contexto
	// de OpenGL. El contexto se refiere a las capacidades
	// que va a tener nuestra aplicaci�n gr�fica.
	glutInitContextVersion(4, 4);
	// Tenemos que informar que queremos trabajar �nicamente con
	// el pipeline programable
	glutInitContextProfile(GLUT_CORE_PROFILE);
	// Freeglut nos permite configurar eventos que ocurren en la venta.
	// Un evento que nos interesa es cuando alguien cierra la venta.
	// En este caso simplemente dejamos de renderear y terminamos el programa.
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	// Configuramos el framebuffer. En este caso estamos solicitando
	// un buffer true color RGBA, un buffer de profundidad y un segundo buffer
	// para renderear.
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(400, 400);
	// Le damos un nombre a la ventana y la creamos.
	glutCreateWindow("Hello World GL");
	// Asociamos una funcion de render. Esta funci�n se
	// mandar� a llamar para dibujar un frame.
	glutDisplayFunc(GameLoop);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeys);
	glutMouseFunc(MouseButtons);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutWarpPointer(centerX, centerY);
	glutReshapeFunc(ReshapeWindow);


	// Inicializar GLEW. Esta librer�a se encarga
	// de obtener el API de OpenGL de nuestra tarjeta
	// de video. SHAME ON YOU MICROSOFT.
	glewInit();

	// Configuramos OpenGL. Este es el color
	// por default del buffer de color en el framebuffer.
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_PROGRAM_POINT_SIZE);
	glPointSize(5);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Inicializar DevIL
	ilInit();
	// Le decimos que queremos cambiar el punto de origen
	ilEnable(IL_ORIGIN_SET);
	// Configuramos el origen de las texturas cargadas por
	// DevIL como abajo a la izquierda
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	Initialize();

	// Iniciar la aplicaci�n. El main se pausar� en esta
	// l�nea hasta que se cierre la ventana de OpenGL.
	glutMainLoop();

	// Terminar.
	return 0;
}