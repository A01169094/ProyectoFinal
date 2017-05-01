#include "Billboard.h"
Billboard::Billboard() {
	_speed = 1.0f;
	//kien zabe quanthoo
	_life = 200.0f;
	_transform.SetPosition(float(rand() % 21 + -10), 10.0f, float(rand() % 21 + -10));
	_direction = glm::vec3(0.0f, -0.17f, 0.0f);
	_isDrawn = false;
	_transparency = 1.0f;
}

void Billboard::ChangeDirection(int type)
{
	if (type == 1) {
		_direction = glm::vec3(0.0f,-0.17f, 0.0f)*_speed;
	}
	if (type == 2) {
		_direction = glm::vec3(((float(rand() % 2)) - 0.5f)*.1f, -0.04f, ((float(rand() % 2)) - 0.5f)*.1f)*_speed;
		}
	if (type == 3) {
			_direction=glm::vec3(((float(rand()%2))-0.5f)*.1f, ((float(rand() % 2)) - 0.5f)*.1f, ((float(rand() % 2)) - 0.5f)*.1f)*_speed;
		}
}

void Billboard::ChangeSpeed(float speed)
{
	if ((_speed <= 4.0f) && (_speed >= -4.0f)) {
		_speed += speed;
	}
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

float Billboard::GetTransparency()
{
	return _transparency;
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
		if (_life < 40) {
			_transparency-=0.025f;
		}
		if (_life == 0) {
			_transparency = 0.0f;
			ChangeDrawValue(false);
		}
	}

void Billboard::Revive(int type)
{
	if (_life == 0) {
		if (type == 1) {
			SetLife(float(rand()%101 + 200));
		}
		if (type == 2) {
			SetLife(float(rand() % 101 + 300));
		}
		if (type == 3) {
			SetLife(float(rand() % 101 + 1000));
		}
		SetScale(1.0f);
		if (type == 1)
		{
			SetPosition(float(rand() % 21 + -10), float(rand() % 5 + 7), float(rand() % 21 + -10));
		}
		if (type == 2) {
			SetPosition(float(rand() % 21 + -10), float(rand() % 6 + 6), float(rand() % 21 + -10));
		}
		if (type == 3){
			SetPosition(float(rand() % 21 + -10), float(rand() % 21 + -10), float(rand() % 21 + -10));
	}
		ChangeDrawValue(true);
		_transparency = 1.0f;
	}
}