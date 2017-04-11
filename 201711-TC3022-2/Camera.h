#pragma once

#include "Transform.h"
#include <glm/glm.hpp>
#include <string>

class Camera
{
public:
	Camera();

	glm::mat4 GetViewProjection();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::vec3 GetPosition();

	void SetPosition(float x, float y, float z);
	void SetPosition(glm::vec3 position);
	void SetRotation(float x, float y, float z);
	void SetRotation(glm::vec3 rotation);

	void MoveForward(float delta, bool world = false);
	void MoveUp(float delta, bool world = false);
	void MoveRight(float delta, bool world = false);

	// Yaw the camera (rotate over the Y axis).
	void Yaw(float degrees);
	// Pitch the camera (rotate over the X axis).
	void Pitch(float degrees);
	// Roll the camera (rotate over the Z axis).
	void Roll(float degrees);
	void Rotate(float x, float y, float z, bool world = false);

	// Set this camera to be a 3D camera.
	void SetPerspective(float nearPlane, float farPlane, float fieldOfView, float aspectRatio);
	// Set this camera to be a 2D camera.
	void SetOrthographic(float size, float aspectRatio);

private:
	// The position of the camera. This transform is private so users have to use the included methods
	// to transform the camera. The _viewMatrix is then computed when the camera is actually moving
	// and not (possibly) every frame in GetViewMatrix() calls.
	Transform _transform;

	// The projection matrix
	glm::mat4 _projectionMatrix;
	// The view matrix
	glm::mat4 _viewMatrix;
};