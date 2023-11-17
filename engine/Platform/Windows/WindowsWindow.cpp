
// Luhao 2023.11.13


#include "../Log.h"
#include "WindowsWindow.h"
#include "ApplicationEvent.h"
#include "KeyEvent.h"
#include "MouseEvent.h"

namespace Nova {
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow() noexcept {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		LOG_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized) {
			int success = glfwInit();
			if (!success) {
				return;
			}

			s_GLFWInitialized = true;
		}
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_INFO("Failed to initialize GLAD");
			return;
		}
		SetVSync(true);

		// 注册 Resize 回调事件
		glfwSetWindowSizeCallback(m_Window,
			[](GLFWwindow* window, int width, int height) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				LOG_INFO(event.ToString());
				// TODO: 实现 Event Dispatcher
				//data.EventCallback(event);
			}
		);

		// 注册 Close 回调事件
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			// TODO: 
			WindowCloseEvent event;
			data.EventCallback(event);
			});

		// 注册 鼠标异动 事件
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			//MouseScrolledEvent event((float)xOffset, (float)yOffset);
			//data.EventCallback(event);
			});

		// 注册 键盘事件
		// https://www.glfw.org/docs/3.3/input_guide.html#events
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key);
				LOG_INFO(event.ToString());
				break;
			}
			case GLFW_RELEASE:
			{
				KeyPressedEvent event(key);
				LOG_INFO(event.ToString());
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				LOG_INFO(event.ToString());
				break;
			}
			default:
				break;
			}

			});

		// 注册 鼠标移动事件
		// https://www.glfw.org/docs/3.3/input_guide.html#cursor_pos
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			//MouseMovedEvent event(xpos, ypos);
			//LOG_INFO(event.ToString());
		});

		// 注册 鼠标scroll事件
		// https://www.glfw.org/docs/3.3/input_guide.html#scrolling
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			//MouseScrolledEvent event(xoffset, yoffset);
			//LOG_INFO(event.ToString());
		});
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapBuffers(0);
		}
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return m_Data.VSync;
	}
}