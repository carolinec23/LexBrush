#include "lbpch.h"
#include "Blender.h"
#include "glad/glad.h"



namespace LexBrush
{
	void Blender::Enable()
	{
		glEnable(GL_BLEND);
	}

	void Blender::BlendFunc()
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}