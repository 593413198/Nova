
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

		// 定义三角形的三个点，包含颜色
		float vertices[3 * 7] = {
			-0.5f, -0.5, 0.0, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		// 定义索引
		unsigned int indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));

		{
			// 优雅，实在是优雅
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"},
			};
			m_VertexBuffer->SetLayout(layout);
		}

		{
			uint32_t index = 0;
			const auto& layout = m_VertexBuffer->GetLayout();
			for (const auto& element : layout) {
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					element.Normallized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.Offset);
				index++;
			}
		}

		std::string vertexSrc = R"(
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
out vec3 v_Position;
out vec4 v_Color; //新增
void main()
{
	v_Position = a_Position;
	v_Color = a_Color;
	gl_Position = vec4(a_Position, 1.0);
}
)";

		std::string fragmentSrc = R"(
#version 330 core
layout(location = 0) out vec4 color;
in vec3 v_Position;
in vec4 v_Color; //新增

void main()
{
   // color = vec4(v_Position * 0.5 + 0.5, 1.0);
	color = v_Color;
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
