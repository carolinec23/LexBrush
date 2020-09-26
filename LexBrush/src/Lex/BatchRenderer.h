#pragma once
#include <glm/glm.hpp>

namespace LexBrush
{
	class BatchRenderer
	{
	public:
		static void Init();
		static void ShutDown();
		static void Begin(const glm::mat4& viewProjectionMatrix);
		static void Submit(const glm::mat4& transform, const glm::vec4& color = { 1,1,1,1 });
		static void Flush();
	private:
	};
}