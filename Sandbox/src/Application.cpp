#include "Lex.h"
#include <iostream>
#include <functional>
#include <GLFW/include/GLFW/glfw3.h>

#include "Lex/Renderer/Renderer.h"
#include "Lex/Renderer/VertexBuffer.h"
#include "Lex/Renderer/VertexBufferLayout.h"
#include "Lex/Renderer/IndexBuffer.h"
#include "Lex/Renderer/VertexArray.h"
#include "Lex/Renderer/Shader.h"
#include "Lex/Renderer/Texture.h"
#include "Lex/Renderer/Blender.h"
#include "Lex/Renderer/Framebuffer.h"
#include "Lex/Renderer/BatchRenderer.h"

#include "Lex/Core/Window.h"

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
    LexBrush::Window window({});

    window.SetWindowResizeCallback([&](int width, int height) {
        LexBrush::Renderer::SetViewport(0, 0, width, height);
        std::cout << "Resized" << std::endl;
     });

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

    glm::vec3 translationA(200, 200, 0);
    glm::vec3 translationB(400, 200, 0);

    LexBrush::BatchRenderer::Init();

    float uniformFloats[4] = { 0.0f, 0.3f, 0.8f, 1.0f }; //COPIED TO RENDERER.CPP
    float increment = 0.05f;

    glm::mat4 testTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(15,11,1)); 
    glm::mat4 testTransform2 = glm::translate(glm::mat4(1.0f), glm::vec3(-10, 4, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(4, 4, 1));

    LexBrush::FramebufferSpecification fbSpec;
    fbSpec.Width = 960;
    fbSpec.Height = 540;
    LexBrush::Framebuffer m_Framebuffer(fbSpec);

    /* Loop until the user closes the window */
    while (!window.IsClosed())
    {
        /* Render here */
        LexBrush::Renderer::ClearColor({ 0,1,1,1 });
        LexBrush::Renderer::Clear();
        m_Framebuffer.Bind();
        LexBrush::Renderer::ClearColor({ 1,1,1,1 });
        LexBrush::Renderer::Clear();

        texture.Bind();
        LexBrush::BatchRenderer::Submit(testTransform);
        LexBrush::BatchRenderer::Submit(testTransform2);
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(translationA));
            glm::mat4 mvp = proj * view;
            shader.BindShader();
            shader.SetUniformMat4f("u_MVP", mvp);
            LexBrush::BatchRenderer::Flush();

            m_Framebuffer.Unbind();
        }
        LexBrush::Texture::Bind(m_Framebuffer.GetColorAttachment(), 0);
        LexBrush::BatchRenderer::Submit(testTransform);
        
        LexBrush::BatchRenderer::Flush();

        window.OnUpdate();
    }

    return 0;
}
