#include "doctest.h"

#include <zae/Core/Math/Vector2.hpp>
#include <zae/Engine/Uis/Drivers/LinearDriver.hpp>
#include <zae/Engine/Uis/Drivers/ConstantDriver.hpp>

TEST_CASE("Linear driver")
{
	zae::LinearDriver<float> driver(0.0f, 100.0f, zae::Time::Seconds(100));

	CHECK_EQ(doctest::Approx(0.0f), driver.Get());
	driver.Update(zae::Time::Seconds(20));
	CHECK_EQ(doctest::Approx(20.0f), driver.Get());
	driver.Update(zae::Time::Seconds(20));
	CHECK_EQ(doctest::Approx(40.0f), driver.Get());
	driver.Update(zae::Time::Seconds(20));
	CHECK_EQ(doctest::Approx(60.0f), driver.Get());
	driver.Update(zae::Time::Seconds(20));
	CHECK_EQ(doctest::Approx(80.0f), driver.Get());
	driver.Update(zae::Time::Seconds(19));
	CHECK_EQ(doctest::Approx(99.0f), driver.Get());
	driver.Update(zae::Time::Seconds(1));
	CHECK_EQ(doctest::Approx(0.0f), driver.Get());
}

TEST_CASE("Constant driver")
{
	zae::ConstantDriver<float> driver(55.1f);

	driver.Update(zae::Time::Seconds(20));
	CHECK_EQ(doctest::Approx(55.1f), driver.Get());
	driver.Update(zae::Time::Seconds(20));
	CHECK_EQ(doctest::Approx(55.1f), driver.Get());
	driver.Update(zae::Time::Seconds(20));
	CHECK_EQ(doctest::Approx(55.1f), driver.Get());
	driver.Update(zae::Time::Seconds(20));
	CHECK_EQ(doctest::Approx(55.1f), driver.Get());
	driver.Update(zae::Time::Seconds(20));
	CHECK_EQ(doctest::Approx(55.1f), driver.Get());
}