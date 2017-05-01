#version 330

in vec2 InterpolatedTexCoord;

out vec4 FragColor;

uniform sampler2D DiffuseTexture;
uniform float Transparency;

void main()
{
	vec4 value = texture2D(DiffuseTexture, InterpolatedTexCoord);
	value.w*=Transparency;
	FragColor = value;

}