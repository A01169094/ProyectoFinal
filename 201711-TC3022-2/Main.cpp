/*
********************************************
Pedro Ángel González González A01169094
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
#include "Billboard.h"
#include "ParticleSystem.h"
#include <iostream>
#include <vector>
#include <sstream>

//Mesh _sineWaveMesh;
ShaderProgram _SineWaveShaderProgram;
Transform _SineWaveTransform;
std::vector<Billboard> _billboards;
ParticleSystem _system;

Camera _camera;
float time;

void Initialize()
{
	_system.Create();
	_billboards = _system.GetBillboards();

	_SineWaveShaderProgram.CreateProgram();
	_SineWaveShaderProgram.Activate();
	_SineWaveShaderProgram.AttachShader("Billboard.vert", GL_VERTEX_SHADER);
	_SineWaveShaderProgram.AttachShader("Default.frag", GL_FRAGMENT_SHADER);
	_SineWaveShaderProgram.SetAttribute(0, "VertexPosition");
	_SineWaveShaderProgram.SetAttribute(1, "VertexTexCoord");

	_SineWaveShaderProgram.LinkProgram();
	_SineWaveShaderProgram.Deactivate();

	_camera.SetPerspective(1.0f, 1000.0f, 0.0f, 1.0f);
	_camera.SetPosition(0.0f, 0.0f, -10.0f);

	_system.SetType(1);

	_SineWaveShaderProgram.Activate();
	_SineWaveShaderProgram.SetUniformi("DiffuseTexture", 0);
	_SineWaveShaderProgram.Deactivate();

	time = 0.0f;

}

void Idle()
{
	glutPostRedisplay();
}

void GameLoop()
{
	// Siempre es recomendable borrar la información anterior del framebuffer.
	// En este caso estamos borrando la información de color,
	// y la información de profundidad.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_SineWaveShaderProgram.Activate();

	time += 0.0005f;
	if (time >= 360) {
		time = 0;

	}

	//Así más o menos se harían como por tanta (habría que modificar el espaciado y caída en x,y)
	for (int i = 0; i <_billboards.size(); i++) {
		_system.ActivateTexture();

		//Tanda 1
		_SineWaveShaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_billboards[i].GetModelMatrix());
		_SineWaveShaderProgram.SetUniformMatrix("ModelViewMatrix", _camera.GetViewMatrix()*_billboards[i].GetModelMatrix());
		_SineWaveShaderProgram.SetUniformMatrix("ProjectionMatrix", _camera.GetProjectionMatrix());
		_SineWaveShaderProgram.SetUniformMatrix("ViewMatrix", _camera.GetViewMatrix());
		_SineWaveShaderProgram.SetUniformMatrix("ModelMatrix", _billboards[i].GetTransform().GetModelMatrix());
		_system.PruebaDraw(i);

		_system.DeactivateTexture();

	}	

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
	// Inicialización de Freeglut.
	// Freeglut se encarga de crear una ventana
	// En donde vamos a poder dibujar
	glutInit(&argc, argv);
	// Freeglut es el encargado de solicitar un contexto
	// de OpenGL. El contexto se refiere a las capacidades
	// que va a tener nuestra aplicación gráfica.
	glutInitContextVersion(4, 4);
	// Tenemos que informar que queremos trabajar únicamente con
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
	// Asociamos una funcion de render. Esta función se
	// mandará a llamar para dibujar un frame.
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


	// Inicializar GLEW. Esta librería se encarga
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

	// Iniciar la aplicación. El main se pausará en esta
	// línea hasta que se cierre la ventana de OpenGL.
	glutMainLoop();

	// Terminar.
	return 0;
}