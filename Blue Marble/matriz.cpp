#include <iostream>
#include <iomanip>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>


void PrintMatrix(const glm::mat4& M) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout
				<< std::setw(10)
				<< std::setprecision(4)
				<< std::fixed
				<< M[j][i] << " ";
		}
		std::cout << std::endl;
	}
}
/*
para fazer a translação é somado os valores da posição atual com a qual ele vai ser movido
*/

void MatrizDeTranslation() {
	std::cout << std::endl;
	std::cout << "++++++++++++++++++++++" << std::endl;
	std::cout << "+Matris de translacao+" << std::endl;
	std::cout << "++++++++++++++++++++++" << std::endl;
	glm::mat4 I = glm::identity<glm::mat4>();
	glm::vec3 T {10, 10, 10};
	glm::mat4 translacao = glm::translate(I,T);

	//std::cout << glm::to_string(M) << std::endl;	
	PrintMatrix(translacao);

	std::cout << std::endl;
	glm::vec4 posicao {10, 10, 10, 1};
	glm::vec4 direcao {10, 10, 10, 0};

	posicao = translacao * posicao;
	direcao = translacao * direcao;

	std::cout << "posicao->" << glm::to_string(posicao) << std::endl;
	std::cout << "direcao->" << glm::to_string(direcao) << std::endl;

}
void MatrizEscala() {
	std::cout << std::endl;
	std::cout << "++++++++++++++++++++++" << std::endl;
	std::cout << "+Matris de Escala+" << std::endl;
	std::cout << "++++++++++++++++++++++" << std::endl;

	glm::mat4 I = glm::identity<glm::mat4>();
	glm::vec3 escalaQuantidade {2, 2, 2};
	glm::mat4 escala = glm::scale(I, escalaQuantidade);

	PrintMatrix(escala);

	glm::vec4 posicao {100, 100, 0, 1};
	glm::vec4 direcao {100, 100, 0, 0};

	posicao = escala * posicao;
	direcao = escala * direcao;
	std::cout << "posicao->" << glm::to_string(posicao) << std::endl;
	std::cout << "direcao->" << glm::to_string(direcao) << std::endl;

	std::cout << std::endl;
}
void MatrizRotacao() {
	std::cout << std::endl;
	std::cout << "++++++++++++++++++++++" << std::endl;
	std::cout << "+Matris de Escala+" << std::endl;
	std::cout << "++++++++++++++++++++++" << std::endl;

	glm::mat4 I = glm::identity<glm::mat4>();
	constexpr float angulo = glm::radians(90.0f);
	glm::vec3 eixo {0, 0, 1};
	glm::mat4 rotacao = glm::rotate(I,angulo, eixo);

	PrintMatrix(rotacao);
	glm::vec4 posicao {100, 0, 0, 1};
	glm::vec4 direcao {100, 0, 0, 0};

	posicao = rotacao * posicao;
	direcao = rotacao * direcao;

	std::cout << "posicao->" << glm::to_string(posicao) << std::endl;
	std::cout << "direcao->" << glm::to_string(direcao) << std::endl;
}
//composicao de matriz, representa as tres transformações anteriores
void MatrizComposicao() {
	std::cout << std::endl;
	std::cout << "++++++++++++++++++++++" << std::endl;
	std::cout << "+Matris de Composicao+" << std::endl;
	std::cout << "++++++++++++++++++++++" << std::endl;


	glm::mat4 I = glm::identity<glm::mat4>();
	glm::vec3 T {0, 10, 0};
	glm::mat4 translacao = glm::translate(I, T);

	constexpr float angulo = glm::radians(45.0f);
	glm::vec3 eixo {0, 0, 1};
	glm::mat4 rotacao = glm::rotate(I, angulo, eixo);

	glm::vec3 escalaQuantidade {2, 2, 0};
	glm::mat4 escala = glm::scale(I, escalaQuantidade);

	std::cout << "translacao:" << std::endl;
	PrintMatrix(translacao);

	std::cout << "rotacao:" << std::endl;
	PrintMatrix(rotacao);

	std::cout << "escala:" << std::endl;
	PrintMatrix(escala);

	glm::vec4 Posicao {1, 1, 0, 1};
	glm::vec4 Direcao {1, 1, 0, 0};

	glm::mat4 MatrixBase = translacao * rotacao * escala;
	std::cout << "Matriz base:" << std::endl;
	PrintMatrix(MatrixBase);
	std::cout << std::endl;

	Posicao = MatrixBase * Posicao;
	Direcao = MatrixBase * Direcao;

	std::cout << glm::to_string(Posicao) << std::endl;
	std::cout << glm::to_string(Direcao) << std::endl;
}

void ModelViewProjection() {
	std::cout << std::endl;
	std::cout << "++++++++++++++++++++++" << std::endl;
	std::cout << "+  modelo de visão   +" << std::endl;
	std::cout << "++++++++++++++++++++++" << std::endl;

	//matriz que vai ser formada de tranlation,rotação e escala, é uma matriz composta
	glm::mat4 model = glm::identity<glm::mat4>();

	//olhar o matriz view
	glm::vec3 eye {0, 0, 10};//z
	glm::vec3 center {0, 0, 0};//centro da tela
	glm::vec3 up {0, 1, 0};//y
	
	glm::mat4 viewMatriz = glm::lookAt(eye,center,up);

	std::cout << "view:" << std::endl;
	PrintMatrix(viewMatriz);

	constexpr float FOV = glm::radians(45.0f);
	const float aspectRatio = 800.0f / 600.0f;
	const float near = 1.0f;
	const float far = 100000.0f;
	glm::mat4 perspectiva = glm::perspective(FOV, aspectRatio, near, far);

	std::cout << "Projeção de Perspectiva:" << std::endl;
	PrintMatrix(perspectiva);

	std::cout << "ModelViewProjection:" << std::endl;
	glm::mat4 ModelViewProjection = perspectiva * viewMatriz * model;
	PrintMatrix(ModelViewProjection);

	std::cout << "josias" << std::endl;
	glm::vec4 Position {0, 0, 0, 1};

	Position = ModelViewProjection * Position;

	Position = Position / Position.w;

	std::cout << glm::to_string(Position) << std::endl;

}
int main() {
	
	MatrizDeTranslation();
	MatrizEscala();
	MatrizRotacao();
	MatrizComposicao();
	ModelViewProjection();
}