
// Luhao 2023.11.28

#pragma once

#include <string>
#include "RendererAPI.h"
#include "Log.h"

namespace Nova {

	class Shader {
	public:
		~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

}
