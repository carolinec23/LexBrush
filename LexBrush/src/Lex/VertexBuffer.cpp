#include "lbpch.h"
#include "VertexBuffer.h"
#include "glad/glad.h"
#include <assert.h>


namespace LexBrush 
{
	VertexBuffer::VertexBuffer(size_t sizeInBytes, float* positions, DrawType type)
		:
		m_Size(sizeInBytes),
		m_Type(type)
	{
		glGenBuffers(1, &m_Buffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
		switch (type)
		{
		case LexBrush::DrawType::Static:
			glBufferData(GL_ARRAY_BUFFER, sizeInBytes, positions, GL_STATIC_DRAW);
			break;
		case LexBrush::DrawType::Dynamic:
			glBufferData(GL_ARRAY_BUFFER, sizeInBytes, positions, GL_DYNAMIC_DRAW);
			break;
		}
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_Buffer);
	}

	void VertexBuffer::BindBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
	}

	void VertexBuffer::UnbindBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void VertexBuffer::Update(const void* vertices, size_t sizeInBytes, size_t offsetInBytes)
	{
		assert(m_Type == DrawType::Dynamic);
		assert(sizeInBytes + offsetInBytes <= m_Size);

		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
		glBufferSubData(GL_ARRAY_BUFFER, offsetInBytes, sizeInBytes, vertices);
	}
}