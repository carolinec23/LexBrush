#pragma once
#include <iostream>

namespace LexBrush
{
	class IndexBuffer
	{
	public:
		IndexBuffer(unsigned int count, unsigned int* indices);
		~IndexBuffer();
		void BindIndexBuffer() const;
		void UnbindIndexBuffer() const;
		inline unsigned int GetCount() const { return m_Count; }
	private:
		unsigned int m_ibo;
		unsigned int m_Count;
	};
}