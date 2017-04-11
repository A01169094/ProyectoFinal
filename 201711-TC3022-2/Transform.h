#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:
	Transform();
	Transform(glm::vec3 position);
	Transform(glm::vec3 position, glm::quat rotation);
	Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);

	glm::mat4 GetModelMatrix();
	glm::vec3 GetPosition();
	glm::quat GetRotation();
	glm::vec3 GetScale();

	void SetPosition(float x, float y, float z);
	void SetPosition(glm::vec3 position);
	void SetRotation(float x, float y, float z);
	void SetRotation(glm::vec3 rotation);
	void SetRotation(glm::quat rotation);
	void SetScale(float x, float y, float z);
	void SetScale(glm::vec3 scale);

	void Translate(float x, float y, float z, bool world);
	void MoveForward(float delta, bool world);
	void MoveUp(float delta, bool world);
	void MoveRight(float delta, bool world);
	void Rotate(float x, float y, float z, bool world);

	static const glm::vec3 WORLD_FORWARD_VECTOR;
	static const glm::vec3 WORLD_UP_VECTOR;
	static const glm::vec3 WORLD_RIGHT_VECTOR;

private:
	void SetDefaults();
	void UpdateModelMatrixPosition();
	void UpdateModelMatrixScale();
	void UpdateModelMatrixRotation();
	void UpdateLocalVectors();

	// La matriz de modelo del objeto con
	// esta transformación
	glm::mat4 _modelMatrix;

	glm::vec3 _position;
	glm::quat _rotation;
	glm::vec3 _scale;

	glm::vec3 _forward;
	glm::vec3 _up;
	glm::vec3 _right;
};