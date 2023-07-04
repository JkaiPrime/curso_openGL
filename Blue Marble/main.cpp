#include <cassert>// biblioteca para utilizar o assert
#include <array> // biblioteca do array
#include <iostream>
#include <fstream>//biblioteca padrao de funçoes para ler arquivos
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

const int Width = 800;
const int Height = 600;

std::string ReadFile(const char *FilePath){
	std::string FileContents;
	if (std::ifstream FileStream {FilePath, std::ios::in}) {
		//leitura do arquivo
		FileContents.assign(std::istreambuf_iterator<char>(FileStream), std::istreambuf_iterator<char>());
	}
	else {
		std::cout << "Erro ao ler o arquivo" << std::endl;
	}
	return FileContents;
}

void CheckShader(GLuint ShaderId){
	// Verificar se o shader foi compilado
	GLint Result = GL_TRUE;
	glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &Result);

	if (Result == GL_FALSE)
	{
		// Erro ao compilar o shader, imprimir o log para saber o que est� errado
		GLint InfoLogLength = 0;
		glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);

		std::string ShaderInfoLog(InfoLogLength, '\0');
		glGetShaderInfoLog(ShaderId, InfoLogLength, nullptr, &ShaderInfoLog[0]);

		if (InfoLogLength > 0)
		{
			std::cout << "Erro no Vertex Shader: " << std::endl;
			std::cout << ShaderInfoLog << std::endl;

			abort();
		}
	}
}

GLuint LoadShaders(const char* VertexShaderFile,const char* FragmentShaderFile) {
	std::string VertexShaderSource = ReadFile(VertexShaderFile);
	std::string FragmentShaderSource = ReadFile(FragmentShaderFile);

	if (VertexShaderSource.empty()){std::cout << "Arquivo Vazio" << std::endl;abort();}//substituição do assert pois estava dando problema
	if (FragmentShaderSource.empty()){std::cout << "Arquivo Vazio" << std::endl;abort();} // substituição do assert pois estava dando problema

	GLuint VertexShaderID  = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	
	

	//Vertex
	std::cout << "compitando o vertex" << VertexShaderFile << std::endl;
	const char* VertexShaderSourcePtr = VertexShaderSource.c_str();// termina a string no caracter nulo
	glShaderSource(VertexShaderID, 1, &VertexShaderSourcePtr,nullptr);
	glCompileShader(VertexShaderID);
	CheckShader(VertexShaderID);

	// Fragment
	std::cout << "compilando o fragment" << FragmentShaderFile << std::endl;
	const char* FragmentShaderSourcePtr = FragmentShaderSource.c_str();// termina a string no caracter nulo
	glShaderSource(FragmentShaderID,1,&FragmentShaderSourcePtr,nullptr);
	glCompileShader(FragmentShaderID);
	CheckShader(FragmentShaderID);


	//linkando com o programa
	std::cout << "Linkando" << std::endl;
	//criando o programa e linkando com o shaders
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID,VertexShaderID);
	glAttachShader(ProgramID,FragmentShaderID);
	glLinkProgram(ProgramID);


	//verificando se deu certo
	GLint Result = GL_TRUE;
	glGetProgramiv(ProgramID, GL_LINK_STATUS,&Result);

	if (Result == GL_FALSE)
	{
		GLint InfoLogLength = 0;
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

		if (InfoLogLength > 0)
		{
			std::string ProgramInfoLog(InfoLogLength, '\0');
			glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramInfoLog[0]);

			std::cout << "Erro ao linkar programa" << std::endl;
			std::cout << ProgramInfoLog << std::endl;

			abort();
		}
	}

	glDetachShader(ProgramID,VertexShaderID);
	glDetachShader(ProgramID,FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Color;
};
int main()
{	
	if (!glfwInit()){std::cout << "Erro ao inicializar o GLFW" << std::endl;abort();}

	GLFWwindow* Window = glfwCreateWindow(Width, Height, "Blue Marble", nullptr, nullptr);

	
	if (!Window){std::cout << "Erro ao criar janela" << std::endl;glfwTerminate();abort();}
	
	glfwMakeContextCurrent(Window);
	glfwSwapInterval(1);


	if (glewInit() != GLEW_OK){std::cout << "Erro ao inicializar o GLEW" << std::endl;glfwTerminate();abort();}

	// verificando a vers~~ao
	GLint GLMajorVersion = 0;
	GLint GLMinorVersion = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &GLMajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &GLMinorVersion);	
	std::cout << "OpenGL Version  : " << GLMajorVersion << "." << GLMinorVersion << std::endl;
	std::cout << "OpenGL Vendor   : " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Renderer : " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version  : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version    : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	/*
	//lendo o shader
	std::string VertexShaderSource = ReadFile("shaders/triangle_vert.glsl");
	std::cout << VertexShaderSource << std::endl;
	*/
	GLuint ProgramID = LoadShaders("shaders/triangle_vert.glsl","shaders/triangle_frag.glsl");

	// Triangulo cordenadas
	std::array<Vertex, 3 > Triangle = {
		Vertex{glm::vec3{-1, -1, 0},glm::vec3{1,0,0}},
		Vertex{glm::vec3{ 1, -1, 0},glm::vec3{0,1,0}},
		Vertex{glm::vec3{0,1,0},glm::vec3{0,0,1}},
	};

	// Model View Projection
	glm::mat4 Model = glm::identity<glm::mat4>();

	// View
	glm::vec3 Eye{ 0.0f, 0.0f, 5.0f }; //distancia e rotação os dois primeiros valores vão mecher na rotação e o terceiro meche na distancia
	glm::vec3 Center{ 0.0f, 0.0f, 0.0 }; // posição, nesse vetor nos alteramos a posição do desenho
	glm::vec3 Up{ 0.0f, 1.0f, 0.0f }; //altera o estado cima ou baixo
	glm::mat4 View = glm::lookAt(Eye, Center, Up);
			
	// Projection
	constexpr float FoV = glm::radians(45.0f); // angulo
	const float AspectRatio = Width / Height;
	const float Near = 0.001f;
	const float Far = 1000.0f;
	glm::mat4 Projection = glm::perspective(FoV, AspectRatio, Near, Far);

	// ModelViewProjection
	glm::mat4 ModelViewProjection = Projection * View * Model;

	// Aplicando o ModelViewProjection
	for (Vertex& Vertex : Triangle){
		glm::vec4 ProjectedVertex = ModelViewProjection * glm::vec4{ Vertex.Position, 1.0f };
		ProjectedVertex /= ProjectedVertex.w;
		Vertex.Position = ProjectedVertex;
	}



	// variavel identificadora do buffer dos vertices
	GLuint VertexBuffer;

	// Pedimos ao OpenGL para gerar um identificador
	glGenBuffers(1, &VertexBuffer);

	// Vamos ativar o buffer de vértices, comandos vão afetar o VertexBuffer
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

	// Passa para o OpenGL o ponteiro para os dados que serão copiados para GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle.data(), GL_STATIC_DRAW);	

	glClearColor(0.3, 0.3, 0.3, 1.0);

	while (!glfwWindowShouldClose(Window)){	
		//limpando o buffer de cor
		glClear(GL_COLOR_BUFFER_BIT);

		//ativar o shader
		glUseProgram(ProgramID);

		//habilitando o atributo na posição 0-> posição e posição 1-> cor
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		//associando o vertexbuffer a 0
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

		//informando onde os vertices estão na posição 0
		glVertexAttribPointer(0, Triangle.size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
		//informando os vertex da posição 1 e utilizando o reinterpret para alterar o tipo do ponteiro para um compativel com o glvertexattrib
		glVertexAttribPointer(1, Triangle.size(), GL_FLOAT, GL_TRUE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Color)));
		//indicando para o opengl que deve ser desenhado o triangulo
		glDrawArrays(GL_TRIANGLES, 0, Triangle.size());

		// desenhando o triangulo
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		//desabilitando o programa
		glUseProgram(0);

		//função para p´rocessar os eventos de uma fila glfw, eventos podem ser teclado, mouse ,etc...
		glfwPollEvents();
		//envia o conteudo do buffer para a janela para ser desenhado
		glfwSwapBuffers(Window);		
	}

	// excluindo o buffer
	glDeleteBuffers(1, &VertexBuffer);
	
	glfwTerminate();

	return 0;
}
