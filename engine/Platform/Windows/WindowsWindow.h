
// Luhao 2023.11.13

#pragma once

#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer/GraphicsContext.h"

namespace Nova {
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props);

		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned  int GetHeight() const override { return m_Data.Height; }

		void* GetNativeWindow() override {
			return m_Window;
		}

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override {
			m_Data.EventCallback = callback;
		}

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();


	private:
		GLFWwindow* m_Window;
		// Windows 目前只支持 OpenGL
		GraphicsContext* m_Context;

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};

		WindowData  m_Data;
	};
}

