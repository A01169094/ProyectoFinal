#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void CreateMesh(GLint vertexCount);
	void Draw(GLenum primitive);
	void SetPositionAttribute(std::vector<glm::vec2> positions, GLenum usage, GLuint locationIndex);
	void SetPositionAttribute(std::vector<glm::vec3> positions, GLenum usage, GLuint locationIndex);
	void SetColorAttribute(std::vector<glm::vec3> colors, GLenum usage, GLuint locationIndex);
	void SetColorAttribute(std::vector<glm::vec4> colors, GLenum usage, GLuint locationIndex);
	void SetNormalAttribute(std::vector<glm::vec3> normals, GLenum usage, GLuint locationIndex);
	void SetTexCoordAttribute(std::vector<glm::vec2> texCoords,
								GLenum usage,
								GLuint locationIndex);
	void SetIndices(std::vector<unsigned int> indices, GLenum usage);

private:
	void SetAttributeData(GLuint& buffer, const GLsizeiptr size, const void* data, GLenum usage, GLuint locationIndex, const GLint components);

	GLuint _vertexArrayObject;
	GLuint _positionsVertexBufferObject;
	GLuint _colorsVertexBufferObject;
	GLuint _normalsVertexBufferObject;
	GLuint _texCoordsVertexBufferObject;
	GLuint _indicesBufferObject;

	GLint _vertexCount;
	GLint _indicesCount;
};