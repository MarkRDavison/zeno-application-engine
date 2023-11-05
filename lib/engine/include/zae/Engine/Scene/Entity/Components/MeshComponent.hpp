#pragma once

#include <zae/Engine/Scene/Entity/Component.hpp>
#include <zae/Engine/Graphics/Renderer.hpp>
#include <zae/Engine/Graphics/Mesh/Mesh.hpp>
#include <zae/Engine/Resources/Resources.hpp>
#include <string>

namespace zae
{

	class MeshComponent : public Component
	{
	public:
		void SetMesh(const std::shared_ptr<Mesh>& mesh) { this->mesh = mesh; }
		std::shared_ptr<Mesh> GetMesh() const { return mesh; }

	private:
		std::shared_ptr<Mesh> mesh;
	};

}