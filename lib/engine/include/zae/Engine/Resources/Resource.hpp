#pragma once

#include <typeindex>

#include <zae/Core/Utils/NonCopyable.hpp>

namespace zae
{
	class Resource : NonCopyable
	{
	public:
		Resource() = default;
		virtual ~Resource() = default;

		virtual std::type_index GetTypeIndex() const = 0;

	};
}