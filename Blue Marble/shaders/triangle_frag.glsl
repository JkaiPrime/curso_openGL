#version 330 core
in vec3 Color;
in vec2 UV;
out vec4 OutColor;
//(0,0,1,1) azul

// a conta esta sendo feita por pixel

void main(){

	//OutColor = vec4(Color,1);
	OutColor = vec4(UV,0,1);
}