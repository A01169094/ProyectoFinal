#pragma once
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
class Billboard
{
private:
	std::vector<glm::vec3> _initialPositions;
	Transform _transform;
	glm::vec3 _direction;
	float _life;
	float _speed;
	bool _isDrawn;
	float _transparency;

public:
	Billboard();
	void ChangeDirection(int type);
	void ChangeSpeed(float speed);
	void Move();
	void UpdateLife();
	void ChangeDrawValue(bool value);
	bool isDrawn();
	float GetLife();
	float GetTransparency();
	void SetLife(float life);
	void SetPosition(float x, float y, float z);
	void SetScale(float scale);
	glm::mat4 GetModelMatrix();
	Transform GetTransform();
	~Billboard();
	void Kill();
	void Revive(int type);
	void SetSpeed(float speed);
};

