#pragma once

#include <zae/Core/Utils/NonCopyable.hpp>

namespace zae
{

	class System : NonCopyable
	{
	public:
		virtual ~System() = default;

		virtual void Update() = 0;

		bool IsEnabled() const { return enabled; }
		void SetEnabled(bool enable) { this->enabled = enable; }

	private:
		bool enabled = true;

	};

}