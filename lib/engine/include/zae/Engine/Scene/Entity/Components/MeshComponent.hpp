#pragma once

#include <zae/Engine/Scene/Entity/Component.hpp>
#include <zae/Engine/Graphics/Renderer.hpp>
#include <string>

namespace zae
{

	class MeshComponent : public Component
	{
	public:
		void SetMesh(const std::string& mesh) { this->mesh = mesh; }
		std::string GetMesh() const { return mesh; }

	private:
		std::string mesh;

	};

}