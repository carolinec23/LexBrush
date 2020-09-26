#include "lbpch.h"
#include "IndexBuffer.h"
#include "glad/glad.h"
#include <iostream>
#include <assert.h>

namespace LexBrush
{
	IndexBuffer::IndexBuffer(unsigned int count, unsigned int* indices)
		:
		m_Count(count)
	{
		assert(sizeof(unsigned int) == sizeof(GLuint));

		glGenBuffers(1, &m_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_ibo);
	}

	void IndexBuffer::BindIndexBuffer() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	}

	void IndexBuffer::UnbindIndexBuffer() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}