#pragma once
#include <glm/glm.hpp>
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
	void SetScale(float x, float y, float z);
	glm::mat4 GetModelMatrix();
	Transform GetTransform();
	~Billboard();
	void Kill(int type);
	void Revive(int type);
	void SetSpeed(float speed);
	void SetTransparency(int type);
};

