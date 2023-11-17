
// Luhao 2023.11.18

#include <memory>
#include "Window.h"

namespace Nova {
class Application {
public:
	Application();
	virtual ~Application();
	void Run();

private:
	std::unique_ptr<Window> m_Window;

};
Application* CreateApplication();
}

