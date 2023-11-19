
// Luhao 2023.11.19

#pragma once

namespace Nova {
class GraphicsContext {
public:
	virtual void Init() = 0;
	virtual void SwapBuffers() = 0;
};
}
