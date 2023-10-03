#include "doctest.h"

#include <zae/Engine/Scene/Entity/Entity.hpp>

class TestComponent1 : public zae::Component
{

};
class TestComponent2 : public zae::Component
{

};
class TestComponent3 : public zae::Component
{

};

TEST_CASE("Updating default entity does not throw")
{
	auto e = zae::Entity();

	CHECK_NOTHROW(e.Update());
}

TEST_CASE("Adding component to entity works")
{
	auto e = zae::Entity();

	e.AddComponent<TestComponent1>();

	SUBCASE("Can retrieve added component")
	{
		const auto& c = e.GetComponent<TestComponent1>();

		CHECK_NE(nullptr, c);
		CHECK_EQ(1, e.GetComponentCount());
	}

	SUBCASE("Can remove added component")
	{
		e.RemoveComponent<TestComponent1>();

		const auto& c = e.GetComponent<TestComponent1>();

		CHECK_EQ(nullptr, c);
		CHECK_EQ(0, e.GetComponentCount());
	}
}

TEST_CASE("Adding multiple components")
{
	auto e = zae::Entity();

	e.AddComponent<TestComponent1>();
	e.AddComponent<TestComponent2>();

	SUBCASE("Can retrieve added components")
	{
		const auto& c1 = e.GetComponent<TestComponent1>();
		const auto& c2 = e.GetComponent<TestComponent2>();

		CHECK_NE(nullptr, c1);
		CHECK_NE(nullptr, c2);
		CHECK_EQ(2, e.GetComponentCount());
	}

	SUBCASE("Has components works")
	{
		CHECK(e.HasComponent<TestComponent1>());
		CHECK(e.HasComponent<TestComponent2>());
		CHECK_FALSE(e.HasComponent<TestComponent3>());
		CHECK(e.HasComponents<TestComponent1, TestComponent2>());
		CHECK_FALSE(e.HasComponents<TestComponent1, TestComponent2, TestComponent3>());
	}
}