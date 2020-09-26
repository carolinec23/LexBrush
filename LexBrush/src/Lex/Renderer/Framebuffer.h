#pragma once
#include <cstdint>

namespace LexBrush
{
	struct FramebufferSpecification
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;	// "are we rendering to screen or are we not"
	};

	class Framebuffer
	{
	public:
		Framebuffer(const FramebufferSpecification& spec);
		~Framebuffer();
		void Invalidate();
		void Bind();
		void Unbind();
		const FramebufferSpecification& GetSpecification() const { return m_Specification; };
		uint32_t GetColorAttachment() const { return m_ColorAttachment; };
	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment;
		uint32_t m_DepthAttachment;
		FramebufferSpecification m_Specification;
	};
}