#include "doctest.h"

#include <zae/Engine/Scene/Entity/Entity.hpp>

class TestComponent1 : public zae::Component
{
public:
	int* val{ nullptr };

	void Start() override { *val += 1; }
	void Update() override { *val += 1; }
};
class TestComponent2 : public zae::Component
{
public:
	int* val{ nullptr };

	void Start() override { *val += 1; }
	void Update() override { *val += 1; }
};
class TestComponent3 : public zae::Component
{
public:
	int* val{ nullptr };

	void Start() override { *val += 1; }
	void Update() override { *val += 1; }
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
		CHECK_EQ(2, e.GetComponents().size());
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

TEST_CASE("Entity with disabled components")
{
	auto e = zae::Entity();

	auto c1 = e.AddComponent<TestComponent1>();
	c1->SetEnabled(false);
	e.AddComponent<TestComponent2>();
	e.AddComponent<TestComponent3>();

	SUBCASE("HasComponent where allow disabled == true")
	{
		CHECK(e.HasComponent<TestComponent1>(true));
		CHECK(e.HasComponent<TestComponent2>(true));
		CHECK(e.HasComponent<TestComponent3>(true));
	}

	SUBCASE("HasComponent where allow disabled == false")
	{
		CHECK_FALSE(e.HasComponent<TestComponent1>(false));
		CHECK(e.HasComponent<TestComponent2>(false));
		CHECK(e.HasComponent<TestComponent3>(false));
	}

	SUBCASE("HasComponent where allow disabled == true")
	{
		CHECK(e.HasComponents<TestComponent1, TestComponent2, TestComponent3>(true));
	}

	SUBCASE("HasComponents where allow disabled == false")
	{
		CHECK_FALSE(e.HasComponents<TestComponent1, TestComponent2, TestComponent3>(false));
	}
}

TEST_CASE("Entity::Update")
{
	auto e = zae::Entity();

	int value = 0;

	auto c1 = e.AddComponent<TestComponent1>();
	auto c2 = e.AddComponent<TestComponent2>();
	auto c3 = e.AddComponent<TestComponent3>();

	c1->val = &value;
	c2->val = &value;
	c3->val = &value;

	SUBCASE("Where component disabled removes it")
	{
		c1->SetEnabled(false);

		e.Update();

		CHECK_FALSE(e.HasComponent<TestComponent1>());
	}

	SUBCASE("Where enabled components starts and updates")
	{
		e.Update();

		CHECK_EQ(6, value);
	}

	SUBCASE("Where components new, sets the entity")
	{
		e.Update();

		CHECK_EQ(&e, c1->GetEntity());
		CHECK_EQ(&e, c2->GetEntity());
		CHECK_EQ(&e, c3->GetEntity());
	}
}