#version 330
 
in vec3 VertexPosition;
in vec2 VertexTexCoord;

out vec2 InterpolatedTexCoord;

uniform mat4 mvpMatrix;
uniform float time;

void main(){
	gl_Position=mvpMatrix*
		vec4(VertexPosition.x,
		VertexPosition.y+sin(time+gl_VertexID),
		VertexPosition.z,
		1.0f);
	InterpolatedTexCoord=VertexTexCoord;
}