#version 330
in vec3 VertexPosition;
in vec2 VertexTexCoord;

out vec2 InterpolatedTexCoord;

uniform mat4 mvpMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

void main()
{
  mat4 modelView = ModelViewMatrix;
  
  // First colunm.
  modelView[0][0] = 1.0f; 
  modelView[0][1] = 0.0f; 
  modelView[0][2] = 0.0f; 
  // Second colunm.
  modelView[1][0] = 0.0f; 
  modelView[1][1] = 1.0f; 
  modelView[1][2] = 0.0f; 
  // Thrid colunm.
  modelView[2][0] = 0.0f; 
  modelView[2][1] = 0.0f; 
  modelView[2][2] = 1.0f; 
  
  vec4 P = modelView * vec4(VertexPosition,1.0f);
  
  InterpolatedTexCoord = VertexTexCoord;
  gl_Position = mvpMatrix * vec4(VertexPosition, 1.0f);
}