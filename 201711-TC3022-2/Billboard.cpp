#include "Billboard.h"
Billboard::Billboard() {
	_speed = 1.0f;
	//kien zabe quanthoo
	_life = 200.0f;
	_transform.SetPosition(float(rand() % 21 + -10), 10.0f, float(rand() % 21 + -10));
	_direction = glm::vec3(0.0f, -0.1f, 0.0f);
	_isDrawn = false;
}

void Billboard::ChangeDirection(int type)
{
	if (type == 1) {
		_direction = glm::vec3(0.0f,-0.1f, 0.0f);
	}
	if (type == 2) {
			_direction= glm::vec3(((float(rand() % 2)) - 0.5f)*.1f, -0.03f, ((float(rand() % 2)) - 0.5f)*.1f);
		}
	if (type == 3) {
			_direction=glm::vec3(((float(rand()%2))-0.5f)*.1f, ((float(rand() % 2)) - 0.5f)*.1f, ((float(rand() % 2)) - 0.5f)*.1f);
		}
}

void Billboard::ChangeSpeed(float speed)
{
	_speed = speed;
}

void Billboard::Move() {
	_transform.Translate(_direction.x, _direction.y, _direction.z, true);
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

float Billboard::GetLife()
{
	return _life;
}

void Billboard::SetLife(float life)
{
	_life = life;
}

void Billboard::SetPosition(float x, float y, float z)
{
	_transform.SetPosition(x, y, z);
}

void Billboard::SetScale(float scale)
{
	_transform.SetScale(scale);
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

void Billboard::Kill()
{
		if (_life <= 10) {
			SetScale(-0.10f);
		}
		if (_life == 0) {
			ChangeDrawValue(false);
		}
	}

void Billboard::Revive(int type)
{
	if (_life == 0) {
		if (type == 1) {
			SetLife(200.f);
		}
		if (type == 2) {
			SetLife(600.f);
		}
		if (type == 3) {
			SetLife(1000.f);
		}
		SetScale(1.0f);
		if ((type == 1) || (type == 2))
		{
			SetPosition(float(rand() % 21 + -10), float(rand() % 5 + 7), float(rand() % 21 + -10));
		}
		if (type == 3){
			SetPosition(float(rand() % 21 + -10), float(rand() % 21 + -10), float(rand() % 21 + -10));
	}
		ChangeDrawValue(true);
	}
}