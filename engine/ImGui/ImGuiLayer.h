
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

	void Begin();
	void End();

	void ShowDemoWindow();
private:
	float m_Time = 0.0f;
};
}

