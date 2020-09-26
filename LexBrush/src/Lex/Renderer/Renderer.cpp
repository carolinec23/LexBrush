#include "lbpch.h"
#include "Renderer.h"
#include "glad/glad.h"
#include <iostream>

namespace LexBrush
{
	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::ClearColor(const glm::vec4& color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void Renderer::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	{
		glViewport(x, y, width, height);
	}

	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
	{
		//float uniformFloats[4] = { 0.0f, 0.3f, 0.8f, 1.0f };

		shader.BindShader();
		//shader.SetUniform4f("u_Color", uniformFloats);
		va.BindVertexArray();
		ib.BindIndexBuffer();

		GLsizei count;
		count = (GLsizei) ib.GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		
		
	}
}