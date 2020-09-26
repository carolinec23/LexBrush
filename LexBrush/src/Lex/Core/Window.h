#pragma once

#include <sstream>
#include <cstdint>
#include <functional>

struct GLFWwindow;

namespace LexBrush
{
	
	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "LexBrush",
					uint32_t width = 1280,
					uint32_t height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	//	Interface representing a desktop system based Window
	class Window
	{
	public:
		Window(const WindowProps& props);
		~Window();

		void OnUpdate();

		unsigned int GetWidth() const { return m_Data.Width; }
		unsigned int GetHeight() const { return m_Data.Height; }

		//Window attributes
		void SetWindowResizeCallback(const std::function<void(int, int)>& callback) { m_Data.WindowResizeCallback = callback; }
		void SetWindowCloseCallback(const std::function<void()>& callback) { m_Data.WindowCloseCallback = callback; }
		void SetKeyPressedCallback(const std::function<void(int)>& callback) { m_Data.KeyPressedCallback = callback; }
		void SetKeyReleasedCallback(const std::function<void(int)>& callback) { m_Data.KeyReleasedCallback = callback; }
		void SetKeyTypedCallback(const std::function<void(unsigned int)>& callback) { m_Data.KeyTypedCallback = callback; }
		void SetMouseButtonPressedCallback(const std::function<void(int)>& callback) { m_Data.MouseButtonPressedCallback = callback; }
		void SetMouseButtonReleasedCallback(const std::function<void(int)>& callback) { m_Data.MouseButtonReleasedCallback = callback; }
		void SetMouseScrolledCallback(const std::function<void(double, double)>& callback) { m_Data.MouseScrolledCallback = callback; }
		void SetMouseMovedCallback(const std::function<void(double, double)>& callback) { m_Data.MouseMovedCallback = callback; }
		void SetVSync(bool enabled);
		bool IsVSync() const;
		bool IsClosed();

		void* GetNativeWindow() const { return m_Window; }
	private:
		void Init(const WindowProps& props);
		void Shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			std::function<void(int, int)>WindowResizeCallback;
			std::function<void()>WindowCloseCallback;
			std::function<void(int key)>KeyPressedCallback;
			std::function<void(int key)>KeyReleasedCallback;
			std::function<void(unsigned int keycode)>KeyTypedCallback;
			std::function<void(int button)>MouseButtonPressedCallback;
			std::function<void(int button)>MouseButtonReleasedCallback;
			std::function<void(double xOffset, double yOffset)>MouseScrolledCallback;
			std::function<void(double xPos, double yPos)>MouseMovedCallback;
		};

		WindowData m_Data;
	};
}