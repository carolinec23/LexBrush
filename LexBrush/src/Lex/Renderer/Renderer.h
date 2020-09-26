#pragma once
#include <iostream>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace LexBrush
{
	class Renderer
	{
	public:
		static void Clear();
		static void ClearColor(const glm::vec4& color);
		static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
		static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	private:
	};
}
