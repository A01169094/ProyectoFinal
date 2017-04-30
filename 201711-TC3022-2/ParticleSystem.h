#pragma once
#include "Mesh.h"
#include "Texture2D.h"
#include "Billboard.h"
#include <vector>

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	void Create();
	void SetType(int type);
	void ActivateTexture();
	void DeactivateTexture();
	void UpdateLife();
	void Revive();
	void ChangeSpeed(float speed);
	void Draw(int number);
	void Kill();
	std::vector<Billboard> GetBillboards();
private:
	int _limit;
	Mesh _mesh;
	Texture2D _texture;
	std::vector<glm::vec3> _vertices;
	std::vector<unsigned int> _indices;
	std::vector<Billboard> _billboards;
	int _type;
};

