#pragma once
#include <iostream>
#include "Renderer.h"

namespace LexBrush
{
	class Texture
	{
	public:
		Texture(const std::string& path);
		~Texture();
		void Bind(unsigned int slot = 0) const;
		void Unbind();
		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }
		static void Bind(unsigned int rendererID, unsigned int slot);
	private:
		unsigned int m_RendererID;
		std::string m_Filepath;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_BPP;	// BPP = bits per pixel
	};
}