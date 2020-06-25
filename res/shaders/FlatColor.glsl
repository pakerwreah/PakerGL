// Flat Color Shader

#type vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 v_color;

out vec4 f_color;

//uniform mat4 u_ViewProjection;
//uniform mat4 u_Transform;

void main()
{
	gl_Position = /*u_ViewProjection * u_Transform **/ vec4(position, 1.0);
	f_color = v_color;
}

#type fragment
#version 330 core

in vec4 f_color;

out vec4 color;

//uniform vec4 u_Color;

void main()
{
	color = f_color;//u_Color;
}