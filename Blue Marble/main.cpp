#include <iostream>

#include <cassert>
#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <array>


const int height = 600;
const int width = 500;

int main() {
    //inicializando glfw
    assert(glfwInit());

    //criando a janela
    GLFWwindow* window = glfwCreateWindow(height,width,"Blue Marble",nullptr,nullptr);
    assert(window);

    //ativador de contexto criado na janela window
    glfwMakeContextCurrent(window);

    // iniciando o glew
    assert(glewInit()==GLEW_OK);
    //pegando a versão do open gl
    GLint GLMajorVersion = 0;
    GLint GLMinorVersion = 0;

    glGetIntegerv(GL_MAJOR_VERSION, &GLMajorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &GLMinorVersion);
    std::cout << "Open GL version: " << GLMajorVersion << "." << GLMinorVersion <<std::endl;

    //glGetString() para pegar as informações do driver que estamos usando
    std::cout << "OPENGL Marca da placa de video: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "OPENGL renderizador de video: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OPENGL Versão: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Versão: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    

    //definindo um triangulo
    std::array<glm::vec3, 3 > triangulo = {
        glm::vec3 {-1.0f, -1.0f, 0.0f},
        glm::vec3 { 1.0f, -1.0f, 0.0f},
        glm::vec3 {0.0f, 1.0f, 0.0f},
    };

    //copiando para a memoria
    GLuint VertexBuffer;

    //gerando o identificador do buffer
    glGenBuffers(1, &VertexBuffer);

    //ativando o buffer
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

    //copiando os dados para a memoria de video
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangulo),triangulo.data(),GL_STATIC_DRAW);

    //definindo a cor de fundo
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);


    //loop de interação da janela
    while (!glfwWindowShouldClose(window)) {
        //limpeza do buffer de cor e preenche com a cor que foi informada(em desenhos 3d temos que limpar o dephbuffer)
        glClear(GL_COLOR_BUFFER_BIT);


        glEnableVertexAttribArray(0);
        //ativando esse buffer
        glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

        //indicando onde os vertices estão dentro do vertexbuffer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,nullptr);


        //desenhando na tela
        glDrawArrays(GL_TRIANGLES,0,3);
        //trata os eventos
        glfwPollEvents();

        //envia o conteudo do framebuffer da janela para ser desenhado na tela
        glfwSwapBuffers(window);
    }



    // finalizando o glfw
    glfwTerminate();
    return 0;

}
