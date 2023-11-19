
// Luhao 2023.11.18

#include <glad/glad.h>
#include "Application.h"

namespace Nova {

	// * test code begin
	class ExampleLayer : public Layer {
	public:
		ExampleLayer() : Layer("Example") {

		}

		~ExampleLayer() {}

		void OnUpdate() override {
			LOG_INFO("ExampleLayer::Update");
		}

		void OnEvent(Nova::Event& event) override {
			LOG_INFO("ExampleLayer::OnEvent {0}", event.ToString());
		}
	};
	// * test code end

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());

		Window::EventCallbackFn fn = std::bind(&Application::OnEvent, this, std::placeholders::_1);
		m_Window->SetEventCallback(fn);

		// 设置 ImGui 图层
		m_ImGuiLayer = new ImGuiLayer();
		PushLayer(m_ImGuiLayer);

		// 生成顶点数组
		glGenVertexArrays(1, &m_VertexArray);
		// 绑定顶点数组
		glBindVertexArray(m_VertexArray);

		// 定义三角形的三个点
		float vertices[3 * 3] = {
				-0.5f, -0.5, 0.0,
				0.5f, -0.5f, 0.0f,
				0.0f, 0.5f, 0.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		// enable 第一个顶点数组，对应 shader 中的顶点数据
		glEnableVertexAttribArray(0);
		// 定义顶点属性为：从零开始，三组数据，浮点型，不进行归一化，每组数据为3*float(即步幅)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		// 定义索引
		unsigned int indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));

		std::string vertexSrc = R"(
#version 330 core
layout(location = 0) in vec3 a_Position;
out vec3 v_Position;
void main()
{
	v_Position = a_Position;
	gl_Position = vec4(a_Position, 1.0);
}
)";

		std::string fragmentSrc = R"(
#version 330 core
layout(location = 0) out vec4 color;
in vec3 v_Position;
void main()
{
	color = vec4(v_Position * 0.5 + 0.5, 1.0);
}
)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
		m_Shader->Bind();

		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	Application::~Application() {
	}

	void Application::Run() {
		while (m_Running) {
			glClearColor((GLfloat)0.3, (GLfloat)0.3, (GLfloat)0.3, (GLfloat)1.0);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_ImGuiLayer->OnUpdate();
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e) {
		LOG_INFO("Application::{}", e.ToString());
		EventDispatcher dispatcher(e);
		// 先用 OnWindowClose 测试，后续支持各种事件
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		for (const auto& layer : m_LayerStack)
		{
			layer->OnEvent(e);
			// 只穿透一层 layer
			if (e.Handled) break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		LOG_INFO("Application::OnWindowClose");
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	Application* CreateApplication() {
		return new Application();
	}
}
