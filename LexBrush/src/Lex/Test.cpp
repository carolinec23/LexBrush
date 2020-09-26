#include "lbpch.h"
#include "Test.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>



namespace LexBrush
{
	void InitGlad()
	{ 
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		if (!status)
		{
			std::cout << "Glad not working" << std::endl;
		}
	}
}