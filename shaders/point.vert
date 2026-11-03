#version 330 core
layout (location = 0) in vec3 pos;
uniform mat4 uMVP;
void main()
{
  gl_Position = uMVP * vec4(pos, 1.0); 
}
