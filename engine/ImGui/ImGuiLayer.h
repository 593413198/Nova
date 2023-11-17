
// Luhao 2023.11.18

#pragma once

#include "Layer.h"
#include "Log.h"
#include "Window.h"
#include "Application.h"

namespace Nova {
class ImGuiLayer : public Layer {
public:
	ImGuiLayer() : Layer("ImGuiLayer") {}
	~ImGuiLayer() {};

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;

	void Begin();
	void End();
private:
	float m_Time = 0.0f;
};
}

