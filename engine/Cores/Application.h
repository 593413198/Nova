
// Luhao 2023.11.18

#include <memory>
#include "Window.h"
#include "Log.h"
#include "Event.h"
#include "ApplicationEvent.h"
#include "Layer.h"
#include "LayerStack.h"

namespace Nova {
class Application {
public:
	Application();
	virtual ~Application();
	void Run();

	void OnEvent(Event& e);
	bool OnWindowClose(WindowCloseEvent& e);

	void PushLayer(Layer* layer);

private:
	std::unique_ptr<Window> m_Window;
	bool m_Running = true;
	LayerStack m_LayerStack;
};

Application* CreateApplication();
}

