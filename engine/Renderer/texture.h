
// Luhao 2023.11.20

#pragma once

#include <memory>
#include <string>
#include "Log.h"
#include "RendererAPI.h"

namespace Nova
{
	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual void GetSize(int& width, int& height) const = 0;
		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static std::shared_ptr<Texture2D> Create(const std::string& path);
	};
}
