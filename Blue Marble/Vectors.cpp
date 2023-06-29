#include <iostream>
#define GLM_SWIZZLE // esta depreciado ,GLM_FORCE_SWIZZLE substitituir, pesquisar depois
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

void Construtor() {
	std::cout << "\nVetores de ponto flutuante" << std::endl;
	//vetoresde ponto flutuante de 2 por 2 ,3 por 3 e 4 por 4
	glm::vec2 ponto1 {10.0f, 10.0f};
	glm::vec3 ponto2 {10.0f, 0.0f, 0.0f};
	glm::vec4 ponto3 {10.0f, 0.0f, 0.0f, 0.0f};
	std::cout << "Ponto 1: " << glm::to_string(ponto1) << std::endl;
	std::cout << "Ponto 2: " << glm::to_string(ponto2) << std::endl;
	std::cout << "Ponto 3: " << glm::to_string(ponto3) << std::endl;
	std::cout << "\nVetores inteiros" << std::endl;
	glm::ivec2 _ponto1 {2,3};
	glm::ivec3 _ponto2 {2,3,4};
	glm::ivec4 _ponto3 {2,3,4,5};
	std::cout << "Ponto 1: " << glm::to_string(_ponto1) << std::endl;
	std::cout << "Ponto 2: " << glm::to_string(_ponto2) << std::endl;
	std::cout << "Ponto 3: " << glm::to_string(_ponto3) << std::endl;
	std::cout << "\nVetores de boleanos" << std::endl;
	glm::bvec2 __ponto1 {true,false};
	glm::bvec3 __ponto2 {true,false,true};
	glm::bvec4 __ponto3 {true,false,true,false};
	std::cout << "Ponto 1: " << glm::to_string(__ponto1) << std::endl;
	std::cout << "Ponto 2: " << glm::to_string(__ponto2) << std::endl;
	std::cout << "Ponto 3: " << glm::to_string(__ponto3) << std::endl;
	std::cout << "\nVetores de ponto flutuante com precisao dupla" << std::endl;
	//utiliza o dobro de bytes por tanto a precisão dele e dupla
	glm::dvec2 ___ponto1 {10.0, 10.0};
	glm::dvec3 ___ponto2 {10.0f, 0.0f, 0.0f};
	glm::dvec4 ___ponto3 {10.0f, 0.0f, 0.0f, 0.0f};
	std::cout << "Ponto 1: " << glm::to_string(___ponto1) << std::endl;
	std::cout << "Ponto 2: " << glm::to_string(___ponto2) << std::endl;
	std::cout << "Ponto 3: " << glm::to_string(___ponto3) << std::endl;
	
	//é possivel contruir um vetor a ppartir do outro
	glm::vec4 p{ponto2, 10.0f};
	std::cout << "\n\nteste criando variavel a partir de outa variavel: " << glm::to_string(p) << std::endl;
	glm::vec2 p1 {ponto3};
	std::cout << "teste2 criando variavel a partir de outa variavel: " << glm::to_string(p1) << std::endl;
}
void Componentes() {
	std::cout << std::endl;
	glm::vec3 p {10, 11, 12};
	//diferentes formas de pegar as cordenadas dependendo da sua prefenrencia ou necessidade
	//XYZ para cor, STP para texture
	std::cout << "X:" << p.x << " Y:" << p.y << " Z:" << p.z << std::endl;
	std::cout << "R:" << p.r << " G:" << p.g <<  " B:" << p.b << std::endl;
	std::cout << "S:" << p.s << " T:" << p.t << " P:" << p.p << std::endl;
	std::cout << "0:" << p[0] << " 1:" << p[1] << " 2:" << p[2] << std::endl;
}
void Swizzle() {
	std::cout << std::endl;
	glm::vec3 p {1, 2, 3};
	glm::vec3 q = p.xxx;
	glm::vec3 r = p.xyx;
	glm::vec3 s = p.zyz;

	std::cout << "valores originais"<< glm::to_string(p) << std::endl;
	std::cout << "teste 2" << glm::to_string(q) << std::endl;
	std::cout << "teste 3" << glm::to_string(r) << std::endl;
	std::cout << "teste 4" << glm::to_string(s) << std::endl;
}

void op() {
	glm::vec3 value1 {10, 10, 0};
	glm::vec3 value2 {10, 10, 10};
	glm::vec3 result;
	result = value1 - value2;
	std::cout << "Subtracao :" << glm::to_string(result) << std::endl;
	result = value1 * 10.0f;
	std::cout << "escala :" << glm::to_string(result) << std::endl;
	result = value1 + value2;
	std::cout << "Soma :" << glm::to_string(result) << std::endl;
	result = value1 * value2;
	std::cout << "multiplicacao :" << glm::to_string(result) << std::endl;
	result = value1 / value2;
	std::cout << "divisao :" << glm::to_string(result) << std::endl;
	//ñão retorna o tamanho mais sim retorna dessa forma, value[0]*value[0]+value[1]*value[1]+value[2]*value[2] depois é feito a raiz nele
	float l = glm::length(value1);
	std::cout << "length :" << l << std::endl;
	//normnalizando um vetor
	glm::vec3 norm = glm::normalize(value1);

	//função dot(produto escalar) função binaria entro dosi vetores
	float m = glm::dot(value1, value2);
	std::cout << "dot:" << m << std::endl;

	//função cross
	glm::vec3 cross = glm::cross(value1,value2);
	std::cout << "dot:" << m << std::endl;
	//refracao
	glm::vec3 refraccao = glm::refract(value1, norm, 10.0f);
	std::cout << "rafracao:" << m << std::endl;

	//reflecao
	glm::vec3 refleccao = glm::reflect(value1, norm);
	std::cout << "reflecao:" << m << std::endl;
}

int main() {
	/*
	Construtor();
	Componentes();
	Swizzle();
	*/
	op();
	return 0;
}