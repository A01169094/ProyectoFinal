#include "Billboard.h"



Billboard::Billboard()
{
	colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));

	positions.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	positions.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));

	//particlePosition.push_back(glm::vec3(0.0f, 0.0f, 0.0f));

	indices = { 0,1,2,0,2,3 };
}

Billboard::Billboard(int type)
{
	Texture2D _textura;
	//en cuanto a lluvia y nieve no creo que sea necesario mover la y, porque si queda que -0.5 o algo así entonces se detiene o como? si sigue derecho pues también da igual
	//hay que hacer aquí un shaderprogram??
	//lluvia
	if (type == 1) {
		direction.push_back(glm::vec3(float(rand() % 1), -1.0f, 0.0f));
		_textura.LoadTexture("lluvia.png");
		glActiveTexture(GL_TEXTURE0);
		_textura.Bind();
	}
	//nieve
	if (type == 2) {
		direction.push_back(glm::vec3(float(rand() % 1), -1.0f, 0.0f));
		_textura.LoadTexture("nieve.png");
		glActiveTexture(GL_TEXTURE0);
		_textura.Bind();
	}
	//polvo
	if (type == 3) {
		direction.push_back(glm::vec3(float(rand() % 1), float(rand() % 1), 0.0f));
		_textura.LoadTexture("polvo.png");
		glActiveTexture(GL_TEXTURE0);
		_textura.Bind();
	}
	glActiveTexture(GL_TEXTURE0);
	_textura.Unbind();
}

void Billboard::SetParticlePosition()
{

}

void Billboard::SetColors(float r, float g, float b)
{
	colors.push_back(glm::vec3(r, g, b));
	colors.push_back(glm::vec3(r, g, b));
	colors.push_back(glm::vec3(r, g, b));
	colors.push_back(glm::vec3(r, g, b));
}


std::vector<glm::vec3> Billboard::GetPositions()
{
	return positions;
}

std::vector<glm::vec3> Billboard::GetColors()
{
	return colors;
}

std::vector<glm::vec3> Billboard::GetParticlePosition()
{
	return particlePosition;
}

std::vector<unsigned int> Billboard::GetIndices()
{
	return indices;
}


Billboard::~Billboard()
{
}
