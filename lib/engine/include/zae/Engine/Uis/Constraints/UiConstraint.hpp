#pragma once

#include <cstdint>

namespace zae
{
	class UiConstraints;

	enum class UiConstraintType
	{
		X, Y, Width, Height
	};

	template<UiConstraintType Type>
	class UiConstraint
	{
	public:
		virtual ~UiConstraint() = default;

		bool Update(const UiConstraints* object, const UiConstraints* parent)
		{
			auto last = current;
			current = Calculate(object, parent) + offset;
			return current != last;
		}

		virtual int32_t Calculate(const UiConstraints* object, const UiConstraints* parent) const = 0;

		virtual int32_t Get() const { return current; }

		int32_t GetOffset() const { return offset; }
		void SetOffset(int32_t offset) { this->offset = offset; }

	protected:
		int32_t current = 0;
		int32_t offset = 0;
	};
}

