#include "lbpch.h"
#include "Window.h"
#include "glad/glad.h"

#include <iostream>
#include <GLFW/glfw3.h>

namespace LexBrush
{
	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		std::cout << "GLFW Error " << error << " " << description << std::endl;
	}

	Window::Window(const WindowProps& props)
	{
		Init(props);
	}

	Window::~Window()
	{
		Shutdown();
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool Window::IsVSync() const
	{
		return m_Data.VSync;
	}

	bool Window::IsClosed()
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Window::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		std::cout << "Creating window " << props.Title << " " << props.Width << " " << props.Height << std::endl;

		if (s_GLFWWindowCount == 0)
		{
			int success = glfwInit();
			if (!success)
				std::cout << "Could not initialize GLFW!" << std::endl;
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		++s_GLFWWindowCount;

		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!status)
		{
			std::cout << "Glad not working" << std::endl;
		}

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(false);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			if (data.WindowResizeCallback)
				data.WindowResizeCallback(width, height);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			if (data.WindowCloseCallback)
				data.WindowCloseCallback();

		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					if (data.KeyPressedCallback)
						data.KeyPressedCallback(key);
					break;
				}
				case GLFW_RELEASE:
				{
					if (data.KeyReleasedCallback)
						data.KeyReleasedCallback(key);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			if (data.KeyTypedCallback)
				data.KeyTypedCallback(keycode);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					if (data.MouseButtonPressedCallback)
						data.MouseButtonPressedCallback(button);
					break;
				}
				case GLFW_RELEASE:
				{
					if (data.MouseButtonReleasedCallback)
						data.MouseButtonReleasedCallback(button);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			if (data.MouseScrolledCallback)
				data.MouseScrolledCallback((float)xOffset, (float)yOffset);

		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			if (data.MouseMovedCallback)
				data.MouseMovedCallback((float)xPos, (float)yPos);
		});

	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

}