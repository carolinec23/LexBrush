#include "lbpch.h"
#include "BatchRenderer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

#include <glad/glad.h>

namespace LexBrush
{
	struct Vertex
	{
		glm::vec4 Color;
		glm::vec2 Position;
		glm::vec2 TexCoord;
	};

	struct RenderData
	{
		VertexArray* Vao = nullptr;
		VertexBuffer* Vbo = nullptr;
		IndexBuffer* Ibo = nullptr;

		Vertex* BufferPtrBase = nullptr;
		Vertex* BufferPtr = nullptr;
		unsigned int IndexCount = 0;
		const size_t MaxVertices = 40000;
		const size_t MaxQuads = MaxVertices / 4;
	};
	static RenderData s_Data;

	void BatchRenderer::Init()
	{
		s_Data.BufferPtrBase = new Vertex[s_Data.MaxVertices];
		s_Data.BufferPtr = s_Data.BufferPtrBase;

		s_Data.Vao = new VertexArray();
		s_Data.Vao->BindVertexArray();

		s_Data.Vbo = new VertexBuffer(s_Data.MaxVertices * sizeof(Vertex), nullptr, DrawType::Dynamic);
		s_Data.Vbo->BindBuffer();

		VertexBufferLayout layout;
		layout.Push<float>(4);
		layout.Push<float>(2);
		layout.Push<float>(2);

		s_Data.Vao->AddBuffer(s_Data.Vbo, layout);

		size_t IndexCount = s_Data.MaxQuads * 6;

		std::vector<unsigned int> indices;
		indices.resize(IndexCount);
		size_t offset = 0;
		for (size_t i = 0; i < IndexCount; i += 6)
		{
			indices[i]	   = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;
			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;
			
			offset += 4;
		}
	
		s_Data.Ibo = new IndexBuffer(IndexCount, indices.data());
		//s_Data.Ibo->BindIndexBuffer();
	}

	void BatchRenderer::ShutDown()
	{
		delete s_Data.Vao;
		delete s_Data.Vbo;
		delete s_Data.Ibo;
		delete[]s_Data.BufferPtrBase;
	}

	void BatchRenderer::Begin(const glm::mat4& viewProjectionMatrix)
	{
	}

	void BatchRenderer::Submit(const glm::mat4& transform,const glm::vec4& color)
	{
		static constexpr size_t numberVertices = 4;
		Vertex vertices [numberVertices] = {
			Vertex{ color , glm::vec2{-0.5f, -0.5f}, glm::vec2{0.0f, 0.0f} },
			Vertex{ color , glm::vec2{ 0.5f, -0.5f}, glm::vec2{1.0f, 0.0f} },
			Vertex{ color , glm::vec2{ 0.5f,  0.5f}, glm::vec2{1.0f, 1.0f} },
			Vertex{ color , glm::vec2{-0.5f,  0.5f}, glm::vec2{0.0f, 1.0f} }
		};

		for (size_t i = 0; i < numberVertices; ++i)
		{
			glm::vec4 pos = transform * glm::vec4(vertices[i].Position, 0, 1);
			s_Data.BufferPtr->Position = pos;
			s_Data.BufferPtr->Color = color;
			s_Data.BufferPtr->TexCoord = vertices[i].TexCoord;
			s_Data.BufferPtr++;
		}
		s_Data.IndexCount += 6;
	}

	void BatchRenderer::Flush()
	{
		size_t sizeInBytes = (s_Data.IndexCount / 6) * 4 * sizeof(Vertex);

		s_Data.Vbo->Update(s_Data.BufferPtrBase, sizeInBytes);
	

		s_Data.Vao->BindVertexArray();
		s_Data.Ibo->BindIndexBuffer();

		glDrawElements(GL_TRIANGLES, s_Data.IndexCount, GL_UNSIGNED_INT, nullptr);

		s_Data.BufferPtr = s_Data.BufferPtrBase;
		s_Data.IndexCount = 0;
	}
}