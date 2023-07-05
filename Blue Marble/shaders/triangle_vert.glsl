#version 330 core

layout (location = 0) in vec3 InPosition;
layout (location = 1) in vec3 InColor;
layout (location = 2) in vec2 InUV;

uniform mat4 ModelViewProjection;

out vec3 Color;
out vec2 UV;

// quando o shader terminar tem que ser atribuido o resultado a o gl_Position, faz a conta das cores por vertices
void main(){
	Color = InColor;
	UV = InUV;
	gl_Position = ModelViewProjection * vec4(InPosition,1.0);
}