#pragma once

#include <cassert>

#include <zae/Engine/Uis/Constraints/UiConstraints.hpp>

namespace zae
{

	template<UiConstraintType Type,
		typename = std::enable_if_t<Type == UiConstraintType::Width || Type == UiConstraintType::Height>>
		class RatioConstraint final : public UiConstraint<Type>
	{
	public:
		explicit RatioConstraint(float ratio = 1.0f) :
			ratio(ratio)
		{
		}

		int32_t Calculate(const UiConstraints* object, const UiConstraints* parent) const override
		{
			if constexpr (Type == UiConstraintType::Width)
			{
				assert(!dynamic_cast<RatioConstraint<UiConstraintType::Height> *>(object->GetHeight()) &&
					"Ratio constraint can only be applied to one side of a object");
				return object->GetHeight()->Get() * ratio;
			}
			else if constexpr (Type == UiConstraintType::Height)
			{
				assert(!dynamic_cast<RatioConstraint<UiConstraintType::Width> *>(object->GetWidth()) &&
					"Ratio constraint can only be applied to one side of a object");
				return object->GetWidth()->Get() * ratio;
			}
		}

		float GetRatio() const { return ratio; }
		void SetRatio(float ratio) { this->ratio = ratio; }

	private:
		float ratio;
	};
}
