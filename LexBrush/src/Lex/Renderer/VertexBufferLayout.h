#pragma once
#include <vector>
#include <assert.h>

namespace LexBrush
{
	#define LB_FLOAT 0x1406
	#define LB_UNSIGNED_INT 0x1405
	#define LB_UNSIGNED_BYTE 0x1401
	#define LB_FALSE 0
	#define LB_TRUE 1

	struct VertexBufferElement
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int GetSizeOfType(unsigned int type)
		{
			switch (type)
			{
				case LB_FLOAT:			return 4;
				case LB_UNSIGNED_INT:	return 4;
				case LB_UNSIGNED_BYTE:	return 1;
			}
			assert(false);
			return 0;
		}
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout();

		template<typename T>
		void Push(unsigned int count)
		{
			static_assert(false);
		}

		template<>
		void Push<float>(unsigned int count)
		{
			m_Elements.push_back({ LB_FLOAT, count, LB_FALSE });
			m_Stride += count * VertexBufferElement::GetSizeOfType(LB_FLOAT);
		}

		template<>
		void Push<unsigned int>(unsigned int count)
		{
			m_Elements.push_back({ LB_UNSIGNED_INT, count, LB_FALSE });
			m_Stride += count * VertexBufferElement::GetSizeOfType(LB_UNSIGNED_INT);
		}

		template<>
		void Push<unsigned char>(unsigned int count)
		{
			m_Elements.push_back({ LB_UNSIGNED_BYTE, count, LB_TRUE });
			m_Stride += count * VertexBufferElement::GetSizeOfType(LB_UNSIGNED_BYTE);
		}

		inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }
		inline unsigned int GetStride() const { return m_Stride; }

	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
	};
}