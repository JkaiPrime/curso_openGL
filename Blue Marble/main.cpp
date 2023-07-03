#include <cassert>
#include <array>
#include <iostream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

const int Width = 800;
const int Height = 600;

int main()
{	
	if (!glfwInit())
	{
		std::cout << "Erro ao inicializar o GLFW" << std::endl;
		return 1;
	}

	GLFWwindow* Window = glfwCreateWindow(Width, Height, "Blue Marble", nullptr, nullptr);

	if (!Window)
	{
		std::cout << "Erro ao criar janela" << std::endl;
		glfwTerminate();
		return 1;
	}
	
	glfwMakeContextCurrent(Window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Erro ao inicializar o GLEW" << std::endl;
		glfwTerminate();
		return 1;
	}

	GLint GLMajorVersion = 0;
	GLint GLMinorVersion = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &GLMajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &GLMinorVersion);	
	std::cout << "OpenGL Version  : " << GLMajorVersion << "." << GLMinorVersion << std::endl;
	std::cout << "OpenGL Vendor   : " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Renderer : " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version  : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version    : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Definir um triângulo em coordenadas de tela
	std::array<glm::vec3, 3> Triangle = {
		glm::vec3{-1.0f, -1.0f, 0.0f},		
		glm::vec3{ 1.0f, -1.0f, 0.0f},
		glm::vec3{ 0.0f,  1.0f, 0.0f},
	};

	// Model View Projection
	glm::mat4 Model = glm::identity<glm::mat4>();

	// View (Câmera)
	glm::vec3 Eye{ 10.0f, 10.0f, 10.0f };
	glm::vec3 Center{ 0.0f, 0.0f, 0.0 };
	glm::vec3 Up{ 0.0f, 1.0f, 0.0f };
	glm::mat4 View = glm::lookAt(Eye, Center, Up);
			
	// Projection
	constexpr float FoV = glm::radians(45.0f);
	const float AspectRatio = Width / Height;
	const float Near = 0.001f;
	const float Far = 1000.0f;
	glm::mat4 Projection = glm::perspective(FoV, AspectRatio, Near, Far);

	// ModelViewProjection
	glm::mat4 ModelViewProjection = Projection * View * Model;

	// Aplicar a ModelViewProjection nos vértices do triângulo
	for (glm::vec3& Vertex : Triangle)
	{
		glm::vec4 ProjectedVertex = ModelViewProjection * glm::vec4{ Vertex, 1.0f };
		ProjectedVertex /= ProjectedVertex.w;
		Vertex = ProjectedVertex;
	}

	// Agora temos que copiar os vértices do triângulo para a memória da GPU

	// Variável que vai conter o identificador do buffer de vértices
	GLuint VertexBuffer;

	// Pedimos ao OpenGL para gerar um identificador
	glGenBuffers(1, &VertexBuffer);

	// Vamos ativar o buffer de vértices, comandos vão afetar o VertexBuffer
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

	// Passa para o OpenGL o ponteiro para os dados que serão copiados para GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle.data(), GL_STATIC_DRAW);	

	glClearColor(1.0f, 0.0f, 0.0f, 1.0);

	while (!glfwWindowShouldClose(Window))
	{		
		glClear(GL_COLOR_BUFFER_BIT);

		// Habilita o atributo na posição 0, normalmente é o atributo de vértices
		// Esse vai ser o identificador que vamos usar no shader para ler a posição
		// de cada vértice, mas não se preocupe com isso agora. Vai ficar tudo mais
		// claro quando formos falar de shaders
		glEnableVertexAttribArray(0);

		// Diz para o OpenGL que o VertexBuffer vai ficar associado ao atributo 0
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

		// Informa ao OpenGL onde, dentro do VertexBuffer, os vértices estão. No
		// nosso caso o array Triangles é tudo o que a gente precisa
		glVertexAttribPointer(0, Triangle.size(), GL_FLOAT, GL_FALSE, 0, nullptr);

		// Finalmente, diz para o OpenGL desenhar o triângulo que criamos anteriormente
		glDrawArrays(GL_TRIANGLES, 0, Triangle.size());

		// Agora que desenhamos o triângulo, podemos desabilitar o atributo da posição
		glDisableVertexAttribArray(0);

		glfwPollEvents();
		glfwSwapBuffers(Window);		
	}

	glDeleteBuffers(1, &VertexBuffer);

	glfwTerminate();

	return 0;
}
