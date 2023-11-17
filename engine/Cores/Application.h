
// Luhao 2023.11.18

#include <memory>
#include "Window.h"
#include "Log.h"
#include "Event.h"
#include "ApplicationEvent.h"

namespace Nova {
class Application {
public:
	Application();
	virtual ~Application();
	void Run();

	void OnEvent(Event& e);
	bool OnWindowClose(WindowCloseEvent& e);

private:
	std::unique_ptr<Window> m_Window;
	bool m_Running = true;
};

Application* CreateApplication();
}

