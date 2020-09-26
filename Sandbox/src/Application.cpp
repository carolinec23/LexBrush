#include "Lex.h"
#include <iostream>

#include <GLFW/include/GLFW/glfw3.h>

#include "Lex/Renderer.h"
#include "Lex/VertexBuffer.h"
#include "Lex/VertexBufferLayout.h"
#include "Lex/IndexBuffer.h"
#include "Lex/VertexArray.h"
#include "Lex/Shader.h"
#include "Lex/Texture.h"
#include "Lex/Blender.h"

#include "Lex/BatchRenderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


enum Color
{
    Red,
    Green,
    Blue,
    Alpha
};


int main(void)
{
  
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "LexBrush", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    LexBrush::InitGlad();

    float positions[] = {
        -50.0f, -50.0f, 0.0f, 0.0f,   //0
         50.0f, -50.0f, 1.0f, 0.0f,   //1
         50.0f,  50.0f, 1.0f, 1.0f,   //2
        -50.0f,  50.0f, 0.0f, 1.0f    //3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    LexBrush::Blender::Enable();
    LexBrush::Blender::BlendFunc();

   // LexBrush::VertexArray vertexAr;
   // vertexAr.BindVertexArray();
   //
   // size_t sizeInBytes = 4 * 4 * sizeof(float);
   // LexBrush::VertexBuffer buffer(sizeInBytes, positions);
   // buffer.BindBuffer();
   //
   // LexBrush::VertexBufferLayout layout;
   // layout.Push<float>(2);
   // layout.Push<float>(2);
   // vertexAr.AddBuffer(buffer, layout);
   //
   // int indexCount = 6;
   // LexBrush::IndexBuffer ibo(indexCount, indices);
   // ibo.BindIndexBuffer();

    glm::mat4 proj = glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));     // the position of our camera   //example: if I want to move the "camera" to the right, i would move the object to the left
    //glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
    //glm::mat4 mvp = proj * view *model;

    LexBrush::ShaderProgramSource source = LexBrush::Shader::ParseShader("res/shaders/Basic.glsl");
    LexBrush::Shader shader(source.VertexSource, source.FragmentSource);
    //setuniform4f (????)
    //shader.BindShader();
    //shader.SetUniformMat4f("u_MVP", mvp);

    LexBrush::Texture texture("res/textures/boxer.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    LexBrush::Renderer renderer;

    glm::vec3 translationA(200, 200, 0);
    glm::vec3 translationB(400, 200, 0);

    LexBrush::BatchRenderer::Init();

    float uniformFloats[4] = { 0.0f, 0.3f, 0.8f, 1.0f }; //COPIED TO RENDERER.CPP
    float increment = 0.05f;

    glm::mat4 testTransform = glm::translate(glm::mat4(1.0f), glm::vec3(5, 5, 0));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();
        

        LexBrush::BatchRenderer::Submit(testTransform);
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(translationA));
            glm::mat4 mvp = proj * view * model;
            shader.BindShader();
            shader.SetUniformMat4f("u_MVP", mvp);
            LexBrush::BatchRenderer::Flush();
        }
        
        shader.SetUniform4f("u_Color", uniformFloats);
        
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(translationB));
            glm::mat4 mvp = proj * view * model;
            shader.BindShader();
            shader.SetUniformMat4f("u_MVP", mvp);

            //renderer.Draw(vertexAr, ibo, shader);
        }

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        if (uniformFloats[Red] > 1.0f)
            increment = -0.05f;
        else if (uniformFloats[Red] < 0.0f)
            increment = 0.05f;
        uniformFloats[Red] += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
