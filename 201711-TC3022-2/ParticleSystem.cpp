#include "ParticleSystem.h"



ParticleSystem::ParticleSystem()
{
}


ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::Create() {
	_limit = 200;
	for (int i = 0; i < _limit; i++) {
		Billboard billboard;
		_billboards.push_back(billboard);
	}

	_vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.0f));
	_vertices.push_back(glm::vec3(0.5f, -0.5f, 0.0f));
	_vertices.push_back(glm::vec3(0.5f, 0.5f, 0.0f));
	_vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.0f));

	std::vector<glm::vec2> texCoords;
	texCoords.push_back(glm::vec2(0.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 0.0f));
	texCoords.push_back(glm::vec2(1.0f, 1.0f));
	texCoords.push_back(glm::vec2(0.0f, 1.0f));

	_indices = { 0,1,2,0,2,3 };

	_mesh.CreateMesh(4);
	_mesh.SetPositionAttribute(_vertices, GL_STATIC_DRAW, 0);
	_mesh.SetTexCoordAttribute(texCoords, GL_STATIC_DRAW, 1);
	_mesh.SetIndices(_indices, GL_STATIC_DRAW);

}

void ParticleSystem::SetType(int type)
{
	if (type == 1) {
		_type = type;
		_texture.LoadTexture("lluvia.png");
	}

	if (type == 2) {
		_type = type;
		_texture.LoadTexture("nieve.png");
	}

	if (type == 3) {
		_type = type;
		_texture.LoadTexture("polvo.png");
	
	}
}

void ParticleSystem::ActivateTexture() {
	_texture.Bind();
	glActiveTexture(GL_TEXTURE0);
}

void ParticleSystem::DeactivateTexture()
{
	_texture.Unbind();
}

void ParticleSystem::Draw(int number)
{
	_mesh.Draw(GL_TRIANGLES);
}

std::vector<Billboard> ParticleSystem::GetBillboards()
{
	return _billboards;
}
