#pragma once

#include <zae/Engine/App.hpp>

namespace test
{
	class EngineApp : public zae::App
	{
	public:
		EngineApp();
		~EngineApp();

		void Start() override;
		void Update() override;
	};
}