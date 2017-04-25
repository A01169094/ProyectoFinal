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
	int _life;
	float _speed;
	bool _isDrawn;
	
public:
	Billboard();
	void ChangeDirection(glm::vec3 direction);
	void ChangeSpeed(float speed);
	void UpdateLife();
	void ChangeDrawValue(bool value);
	bool isDrawn();
	int GetLife();
	void SetLife(int life);
	void SetPosition(float x, float y, float z);
	glm::mat4 GetModelMatrix();
	Transform GetTransform();
	~Billboard();
};

