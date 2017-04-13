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
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec3> particlePosition;
	std::vector<glm::vec3> direction;
	std::vector<unsigned int> indices;
public:
	Billboard();
	Billboard(int type);
	void SetColors(float r, float g, float b);
	void SetParticlePosition();
	std::vector<glm::vec3> GetPositions();
	std::vector<glm::vec3> GetColors();
	std::vector<glm::vec3> GetParticlePosition();
	std::vector<unsigned int> GetIndices();
	~Billboard();
};

