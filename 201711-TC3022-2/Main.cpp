/*
********************************************
Pedro Ángel González González A01169094
Samantha López Xavier A01370070
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

ShaderProgram _shaderProgram;
std::vector<Billboard> _billboards;
ParticleSystem _particleSystem;
Camera _camera;
Camera _instrucCamera;
Texture2D _instrucTexture;
Transform _instrucTransform;
int _numberDrawn;
int _frameNumber;
int _type;

void Initialize()
{
	_particleSystem.Create();

	_shaderProgram.CreateProgram();
	_shaderProgram.Activate();
	_shaderProgram.AttachShader("Billboard.vert", GL_VERTEX_SHADER);
	_shaderProgram.AttachShader("Default.frag", GL_FRAGMENT_SHADER);
	_shaderProgram.SetAttribute(0, "VertexPosition");
	_shaderProgram.SetAttribute(1, "VertexTexCoord");
	_shaderProgram.LinkProgram();
	_shaderProgram.Deactivate();

	_camera.SetPerspective(1.0f, 1000.0f, 0.0f, 1.0f);
	_camera.SetPosition(0.0f, 0.0f, -12.0f);

	_instrucCamera.SetPerspective(1.0f, 1000.0f, 0.0f, 1.0f);
	_instrucCamera.SetPosition(0.0f, 100.0f, 0.0f);
	
	_instrucTexture.LoadTexture("instrucciones.png");
	
	_type = 1;
	_particleSystem.SetType(1);

	_instrucTransform.SetPosition(0.0f, 100.0f, 1.0f);

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


void GameLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shaderProgram.Activate();
	
	for (int i = 0; i < _numberDrawn; i++) {
		_particleSystem.ActivateTexture();
		_billboards[i].ChangeDrawValue(true);
		_billboards[i].ChangeDirection(_type);
		_billboards[i].Move();
		_shaderProgram.SetUniformMatrix("ModelViewMatrix", _camera.GetViewMatrix()*_billboards[i].GetModelMatrix());
		_shaderProgram.SetUniformMatrix("ProjectionMatrix", _camera.GetProjectionMatrix());
		_shaderProgram.SetUniformf("Transparency", _billboards[i].GetTransparency());
		_shaderProgram.SetUniformf("Scale", _billboards[i].GetTransform().GetScale().x);
		_billboards[i].UpdateLife();
		_billboards[i].Kill();
		_particleSystem.Draw(i);
		_particleSystem.DeactivateTexture();
		_billboards[i].Revive(_type);
	}

	_instrucTexture.Bind();
	_shaderProgram.SetUniformMatrix("ModelViewMatrix", _instrucCamera.GetViewMatrix()*_instrucTransform.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("ProjectionMatrix", _instrucCamera.GetProjectionMatrix());
	_shaderProgram.SetUniformf("Transparency", 1.0f);
	_shaderProgram.SetUniformf("Scale", 1.0f);
	_particleSystem.Draw(GL_TRIANGLES);
	_instrucTexture.Unbind();

	_shaderProgram.Deactivate();
	
	_frameNumber++;
	if (_frameNumber == 24) {
		if (_numberDrawn <= 96) {
			_numberDrawn += 3;
			_frameNumber = 0;
		}
	}
	
	glutSwapBuffers();
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
			_billboards[i].SetScale(1.0f, 1.0f, 1.0f);
		}
	}
	if (key == '2')
	{
		_type = 2;
		_particleSystem.SetType(2);
		for (int i = 0; i < _billboards.size(); i++) {
			_billboards[i].SetPosition(float(rand() % 21 + -10), float(rand() % 16 - 5), float(rand() % 21 + -10));
			_billboards[i].SetSpeed(1.0f);
			_billboards[i].SetScale(1.0f, 1.0f, 1.0f);
		}
	}
	if (key == '3')
	{
		_type = 3;
		_particleSystem.SetType(3);
		for (int i = 0; i < _billboards.size(); i++) {
			_billboards[i].SetPosition(float(rand() % 11 + -10), float(rand() % 21 + -10), float(rand() % 21 + -10));
			_billboards[i].SetSpeed(1.0f);
			_billboards[i].SetScale(5.0f,5.0f,5.0f);
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
	}

	if (key == GLUT_KEY_DOWN) {
		_camera.MoveForward(-0.1f, false);
	}

	if (key == GLUT_KEY_RIGHT) {
		_camera.Yaw(1.0f);
	}

	if (key == GLUT_KEY_LEFT) {
		_camera.Yaw(-1.0f);
	}
}

void ReshapeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
	_camera.SetPerspective(1.0f, 1000.0f, 60.0f, (float)width / (float)height);
	_instrucCamera.SetPerspective(1.0f, 1000.0f, 60.0f, (float)width / (float)height);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 4);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Particle System");
	glutDisplayFunc(GameLoop);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeys);
	int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutWarpPointer(centerX, centerY);
	glutReshapeFunc(ReshapeWindow);


	glewInit();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH);
	glEnable(GL_CULL_FACE);
	glDisable(GL_PROGRAM_POINT_SIZE);
	glPointSize(5);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	Initialize();

	glutMainLoop();

	return 0;
}