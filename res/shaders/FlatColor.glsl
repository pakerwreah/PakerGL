// Flat Color Shader

#type vertex
#version 330 core

layout(location = 0) in vec2 position;

uniform mat4 projection;

void main()
{
	gl_Position = projection * vec4(position, 0.0, 1.0);
}

#type fragment
#version 330 core

uniform vec4 u_color;

void main()
{
	gl_FragColor = u_color;
}