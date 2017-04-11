#version 330

in vec3 VertexPosition;
in vec2 VertexTexCoord;

out vec2 InterpolatedTexCoord;

uniform mat4 mvpMatrix;

void main()
{
	InterpolatedTexCoord = VertexTexCoord;
	gl_Position = mvpMatrix * vec4(VertexPosition, 1.0f);
}