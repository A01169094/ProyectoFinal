#version 330

in vec3 VertexPosition;
in vec2 VertexTexCoord;

out vec2 InterpolatedTexCoord;

uniform mat4 mvpMatrix;
uniform sampler2D HeightMap;

void main(){
	InterpolatedTexCoord=VertexTexCoord;
	float displacement = texture2D(HeightMap, InterpolatedTexCoord).r*5.0f;
	gl_Position = mvpMatrix*vec4(VertexPosition.x, VertexPosition.y+displacement, VertexPosition.z, 1.0f);
}