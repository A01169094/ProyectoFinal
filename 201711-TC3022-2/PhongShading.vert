#version 330

in vec3 VertexPosition;
in vec3 VertexColor;
in vec3 VertexNormal;
in vec2 VertexTexCoord;

out vec3 InterpolatedColor;
out vec3 InterpolatedNormal;
out vec3 PixelPosition;
out vec2 InterpolatedTexCoord;

uniform mat4 mvpMatrix;
uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;

void main()
{
	InterpolatedColor = VertexColor;
	InterpolatedNormal = NormalMatrix * VertexNormal;
	InterpolatedTexCoord = VertexTexCoord;
	PixelPosition = vec3(ModelMatrix * vec4(VertexPosition, 1.0f));
	gl_Position = mvpMatrix * vec4(VertexPosition, 1.0f);
}