#version 330

in vec3 InterpolatedVertexColor;

out vec4 FragColor;

uniform vec2 iResolution;
uniform float iGlobalTime;

void main()
{
	vec2 uv = gl_FragCoord.xy / iResolution.xy;
	FragColor = vec4(uv,0.5f+0.5f*sin(iGlobalTime),1.0f);
}