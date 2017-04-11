#version 330

in vec3 InterpolatedColor;
in vec3 InterpolatedNormal;
in vec3 PixelPosition;
in vec2 InterpolatedTexCoord;

out vec4 FragColor;

uniform vec3 LightPosition;
uniform vec3 LightColor;
uniform vec3 CameraPosition;
uniform sampler2D DiffuseTexture;

void main()
{
	// Ambient component
	vec3 ambient = 0.1f * LightColor;

	// Diffuse component
	vec3 L = normalize(LightPosition - PixelPosition);
	vec3 N = normalize(InterpolatedNormal);
	vec3 diffuse = max(dot(N, L), 0.0f) * LightColor;

	// Specular component
	vec3 R = reflect(-L, N);
	vec3 V = normalize(CameraPosition - PixelPosition);
	vec3 specular = pow(max(dot(V, R), 0.0f), 8) * LightColor;
	
	vec4 textura = texture2D(DiffuseTexture, InterpolatedTexCoord);

	vec4 phong = vec4((ambient + diffuse + specular), 1.0f)* textura;
	FragColor = phong;
}