#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <iostream>

namespace LexBrush
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		void BindVertexArray() const;
		void UnbindVertexArray() const;

		void AddBuffer(VertexBuffer* vb, const VertexBufferLayout& layout);

	private:
		unsigned int m_RendererID;
	};
}