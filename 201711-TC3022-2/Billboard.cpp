#include "Billboard.h"
Billboard::Billboard() {
	_speed = 1.0f;
	//kien zabe quanthoo
	_life = 100;
	_transform.SetPosition(float(rand() % 20 + -10), 10.0f, float(rand() % 20 + -10));
	_direction = glm::vec3(0.0f, -1.0f, 0.0f);
	_isDrawn = false;
}

void Billboard::ChangeDirection(glm::vec3 direction)
{
	_direction = direction;
}

void Billboard::ChangeSpeed(float speed)
{
	_speed = speed;
}

void Billboard::UpdateLife()
{
	_life--;
}

void Billboard::ChangeDrawValue(bool value)
{
	_isDrawn = value;
}

bool Billboard::isDrawn()
{
	return _isDrawn;
}

int Billboard::GetLife()
{
	return _life;
}

void Billboard::SetLife(int life)
{
	_life = life;
}

void Billboard::SetPosition(float x, float y, float z)
{
	_transform.SetPosition(x, y, z);
}

glm::mat4 Billboard::GetModelMatrix()
{
	return _transform.GetModelMatrix();
}

Transform Billboard::GetTransform()
{
	return _transform;
}

Billboard::~Billboard()
{
}
