/*
********************************************
Pedro Ángel González González A01169094
Samantha López Xavier A01370070
********************************************
*/

#include <GL/glew.h>SineWaveShaderProgram
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

ShaderProgram _shaderProgram;
std::vector<Billboard> _billboards;
ParticleSystem _particleSystem;
int _numberDrawn;
int _frameNumber;
int _type;
Camera _camera;
//****************************************************FALLE********************************************
Camera _camera2;
Mesh _instrucciones;
Texture2D _texturaInstrucciones;
Transform _TransInstrucciones;
//****************************************************FALLE********************************************


void Initialize()
{
	_particleSystem.Create();

	//****************************************************FALLE********************************************
	_instrucciones.CreateMesh(24);

	std::vector<glm::vec3> _vertices;
	_vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.0f));
	_vertices.push_back(glm::vec3(0.5f, -0.5f, 0.0f));
	_vertices.push_back(glm::vec3(0.5f, 0.5f, 0.0f));
	_vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.0f));

	std::vector<glm::vec2> texCoords;
	texCoords.push_back(glm::vec2(0.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));

	std::vector<unsigned int> _indices;
	_indices = { 0,1,2,0,2,3 };

	_instrucciones.CreateMesh(4);
	_instrucciones.SetPositionAttribute(_vertices, GL_STATIC_DRAW, 0);
	_instrucciones.SetTexCoordAttribute(texCoords, GL_STATIC_DRAW, 1);
	_instrucciones.SetIndices(_indices, GL_STATIC_DRAW);
	
	_shaderProgram.CreateProgram();
	_shaderProgram.Activate();
	_shaderProgram.AttachShader("Billboard.vert", GL_VERTEX_SHADER);
	_shaderProgram.AttachShader("Default.frag", GL_FRAGMENT_SHADER);
	_shaderProgram.SetAttribute(0, "VertexPosition");
	_shaderProgram.SetAttribute(1, "VertexTexCoord");
	//****************************************************FALLE********************************************

	_shaderProgram.LinkProgram();
	_shaderProgram.Deactivate();

	_camera.SetPerspective(1.0f, 1000.0f, 0.0f, 1.0f);
	_camera.SetPosition(0.0f, 0.0f, -12.0f);

	//****************************************************FALLE********************************************
	_camera2.SetPerspective(1.0f, 1000.0f, 0.0f, 1.0f);
	_camera2.SetPosition(0.0f, 0.0f, -12.0f);

	_texturaInstrucciones.LoadTexture("instrucciones.jpg");
	//****************************************************FALLE********************************************

	_type = 1;
	_particleSystem.SetType(1);
	
	_billboards = _particleSystem.GetBillboards();

	_shaderProgram.Activate();
	_shaderProgram.SetUniformi("DiffuseTexture", 0);
	_shaderProgram.Deactivate();

	_numberDrawn = 3;
	_frameNumber = 0;

}

void Idle()
{
	glutPostRedisplay();
}

//woo

void GameLoop()
{
	// Siempre es recomendable borrar la información anterior del framebuffer.
	// En este caso estamos borrando la información de color,
	// y la información de profundidad.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shaderProgram.Activate();

	//****************************************************FALLE********************************************
	glActiveTexture(GL_TEXTURE1);
	_texturaInstrucciones.Bind();
	_shaderProgram.SetUniformMatrix("ModelViewMatrix", _camera2.GetViewMatrix()*_TransInstrucciones.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("ProjectionMatrix", _camera2.GetProjectionMatrix());
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _TransInstrucciones.GetModelMatrix());
	_instrucciones.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE1);
	_texturaInstrucciones.Unbind();
	//****************************************************FALLE********************************************



	for (int i = 0; i < _numberDrawn; i++) {
		_particleSystem.ActivateTexture();
		_billboards[i].ChangeDrawValue(true);
		_billboards[i].ChangeDirection(_type);
		_billboards[i].Move();
		_shaderProgram.SetUniformMatrix("ModelViewMatrix", _camera.GetViewMatrix()*_billboards[i].GetModelMatrix());
		_shaderProgram.SetUniformMatrix("ProjectionMatrix", _camera.GetProjectionMatrix());
		_shaderProgram.SetUniformf("Transparency", _billboards[i].GetTransparency());
		_billboards[i].UpdateLife();
		_billboards[i].Kill();
		_particleSystem.Draw(i);
		_particleSystem.DeactivateTexture();
		_billboards[i].Revive(_type);
	}

	_shaderProgram.Deactivate();
	
	// Cambiar el buffer actual
	glutSwapBuffers();
	_frameNumber++;
	if (_frameNumber == 24) {
		if (_numberDrawn <= 96) {
			_numberDrawn += 3;
			_frameNumber = 0;
		}
	}
}

void Keyboard(unsigned char key, int y, int z)
{
	if (key == '1')
	{
		_type = 1;
		_particleSystem.SetType(1);
		for (int i = 0; i < _billboards.size(); i++) {
			_billboards[i].SetPosition(float(rand() % 21 + -10), float(rand() % 16 -5), float(rand() % 21 + -10));
			_billboards[i].SetSpeed(1.0f);
		}
	}
	if (key == '2')
	{
		_type = 2;
		_particleSystem.SetType(2);
		for (int i = 0; i < _billboards.size(); i++) {
			_billboards[i].SetPosition(float(rand() % 21 + -10), float(rand() % 16 - 5), float(rand() % 21 + -10));
			_billboards[i].SetSpeed(1.0f);
		}
	}
	if (key == '3')
	{
		_type = 3;
		_particleSystem.SetType(3);
		for (int i = 0; i < _billboards.size(); i++) {
			_billboards[i].SetPosition(float(rand() % 21 + -10), float(rand() % 21 + -10), float(rand() % 21 + -10));
			_billboards[i].SetSpeed(1.0f);
		}
	}
	if (key == 'f') {
		for (int i = 0; i < _billboards.size(); i++)
		{
			_billboards[i].ChangeSpeed(0.5f);
		}
	}
	if (key == 's') {
		for (int i = 0; i < _billboards.size(); i++)
		{
			_billboards[i].ChangeSpeed(-0.5f);
		}
	}
}

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) {
		_camera.MoveForward(0.1f, false);

		//****************************************************FALLE********************************************
		_camera2.MoveForward(0.1f, false);
	}

	if (key == GLUT_KEY_DOWN) {
		_camera.MoveForward(-0.1f, false);

		//****************************************************FALLE********************************************
		_camera2.MoveForward(-0.1f, false);
	}

	if (key == GLUT_KEY_RIGHT) {
		_camera.Yaw(1.0f);

		//****************************************************FALLE********************************************
		_camera2.Yaw(1.0f);
	}

	if (key == GLUT_KEY_LEFT) {
		_camera.Yaw(-1.0f);

		//****************************************************FALLE********************************************
		_camera2.Yaw(-1.0f);
	}
	

}

void ReshapeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
	_camera.SetPerspective(1.0f, 1000.0f, 60.0f, (float)width / (float)height);
	_camera2.SetPerspective(1.0f, 1000.0f, 60.0f, (float)width / (float)height);

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
	glutCreateWindow("Particle System");
	// Asociamos una funcion de render. Esta función se
	// mandará a llamar para dibujar un frame.
	glutDisplayFunc(GameLoop);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeys);
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH);
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