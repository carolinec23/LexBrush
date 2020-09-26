#pragma once
#include <iostream>

namespace LexBrush
{
	enum class DrawType
	{
		Static,
		Dynamic
	};

	class VertexBuffer
	{
	public: 
		VertexBuffer(size_t sizeInBytes, float *positions, DrawType type);
		~VertexBuffer();
		void BindBuffer();
		void UnbindBuffer();
		void Update(const void *vertices, size_t sizeInBytes, size_t offsetInBytes = 0);
		
	private:
		unsigned int m_Buffer;
		size_t m_Size;
		DrawType m_Type;
	};
}