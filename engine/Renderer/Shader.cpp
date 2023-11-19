
// Luhao 2023.11.28

#include "Platform/OpenGL/OpenGLShader.h"
#include "RendererAPI.h"

namespace Nova {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (RendererAPI::GetAPI())
		{
		case RendererDeviceType::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		};
		return nullptr;
	}
}
