#pragma once

#include <zae/Engine/Graphics/Renderer.hpp>

namespace test
{

	class EngineRenderer : public zae::Renderer
	{
	public:
		EngineRenderer();

		void Start() override;
		void Update() override;
	};

}