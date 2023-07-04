#version 330 core

layout (location = 0) in vec3 InPosition;
layout (location = 1) in vec3 InColor;
out vec3 Color;
// quando o shader terminar tem que ser atribuido o resultado a o gl_Position, faz a conta das cores por vertices
void main(){
	Color = InColor;
	gl_Position = vec4(InPosition,1.0);
}