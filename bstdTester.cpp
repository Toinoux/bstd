/*
** EPITECH PROJECT, 2018
** tech2
** File description:
** bstdTester
*/

struct A {};

struct B : A {};

struct C {};

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "types.hpp"

TEST_CASE("isSameType") {
	REQUIRE(bstd::isSameType<A, A>());
	REQUIRE_FALSE(bstd::isSameType<A, B>());
	REQUIRE_FALSE(bstd::isSameType<A, C>());
}

#include "random.hpp"

TEST_CASE("RandGen") {
	REQUIRE(bstd::randomise<int64_t>(1,372684));
	REQUIRE(bstd::randomise<int64_t>(-372684, -1));
	REQUIRE(bstd::randomise<int64_t>(1, 1) == 1);
	REQUIRE(bstd::randomise<int64_t>(1));
	REQUIRE(bstd::randomise<float>(1,372684));
	REQUIRE(bstd::randomise<float>(-372684, -1));
	REQUIRE(bstd::randomise<float>(1.23, 1.23) == 1.23f);
	REQUIRE(bstd::randomise<float>(1));
	REQUIRE(bstd::randomise<float>());
	REQUIRE(bstd::randomise<double>(1,372684));
	REQUIRE(bstd::randomise<double>(-372684, -1));
	REQUIRE(bstd::randomise<double>(1.23, 1.23) == 1.23);
	REQUIRE(bstd::randomise<double>(1));
	REQUIRE(bstd::randomise<double>());
}

#include "threadPool.hpp"

static const int nbThread = bstd::randomise<size_t>(1, 40);

TEST_CASE("ThreadPool") {
	bstd::ThreadPool pool(nbThread);
	std::atomic<int> res = 0;

	REQUIRE(pool.isRunning() == true);
	SECTION("One task") {
		std::future<void> action = pool.addTask([&res] {
			++res;
		});
		action.get();
		REQUIRE(res == 1);
	}

	SECTION("Less than nbThread") {
		std::vector<std::future<void>> actions;
		size_t value = bstd::randomise<size_t>(1, nbThread);
		for (size_t i = 0; i < value; ++i) {
			actions.emplace_back(pool.addTask([&res] {
				++res;
			}));
		}
		for (auto &action : actions) {
			action.get();
		}
		REQUIRE(res == value);
	}

	SECTION("More than nbThread") {
		std::vector<std::future<void>> actions;
		size_t value = bstd::randomise<size_t>(nbThread, 200);
		for (size_t i = 0; i < value; ++i) {
			actions.emplace_back(pool.addTask([&res] {
				++res;
			}));
		}
		for (auto &action : actions) {
			action.get();
		}
		REQUIRE(res == value);
	}

	SECTION("Non void future") {
		std::vector<std::future<int>> actions;
		size_t value = bstd::randomise<size_t>(1, 200);
		for (size_t i = 0; i < value; ++i) {
			actions.emplace_back(pool.addTask([&res] {
				int foo;
				foo = res;
				++res;
				return (foo);
			}));
		}
		for (auto &action : actions) {
			REQUIRE_NOTHROW(action.get());
		}
		REQUIRE(res == value);
	}
}

#include "indieStudioEngine/Engine.hpp"
#include "indieStudioEngine/EngineTester.hpp"

TEST_CASE ("ECS TEST") {
	Engine::Engine tester;
	Engine::Entity entityTest(tester.createEntity());
	Engine::Event ev = 8;

	tester.registerComponent<Engine::Component>();
	auto storageTest = std::any_cast<Engine::Storage<Engine::Component>&>(*tester.getStorage<Engine::Component>());
	REQUIRE(tester.components.size() == 1);

	tester.registerComponent<testComponent>();
	auto storageTest2 = std::any_cast<Engine::Storage<testComponent>&>(*tester.getStorage<testComponent>());
	REQUIRE(tester.components.size() == 2);

	tester.attachComponent<Engine::Component>(entityTest);
	tester.attachComponent<testComponent>(entityTest);
	REQUIRE(std::any_cast<Engine::Storage<Engine::Component>&>(*tester.getStorage<Engine::Component>()).size() == 1);
	REQUIRE(std::any_cast<Engine::Storage<testComponent>&>(*tester.getStorage<testComponent>()).size() == 1);


	tester.registerSystem<testSystem>();
	auto systemTest = tester.getSystem<testSystem>();
	REQUIRE(tester.systems.size() == 1);

	tester.setSystemStorage<testSystem, testComponent>();
	std::any_cast<testSystem&>(*systemTest).update(ev);
	REQUIRE(std::any_cast<Engine::Storage<testComponent>&>(*tester.getStorage<testComponent>())[entityTest.getId()].posX == 122);
	REQUIRE(std::any_cast<Engine::Storage<testComponent>&>(*tester.getStorage<testComponent>())[entityTest.getId()].posY == 122);

	tester.update<testSystem, testSystem, testSystem>(ev);
	REQUIRE(std::any_cast<Engine::Storage<testComponent>&>(*tester.getStorage<testComponent>())[entityTest.getId()].posX == 305);
	REQUIRE(std::any_cast<Engine::Storage<testComponent>&>(*tester.getStorage<testComponent>())[entityTest.getId()].posY == 305);

	for (size_t i = 0 ; i <  10 ; ++i) {
		Engine::Entity entityTest2(tester.createEntity());
		REQUIRE(entityTest2.getId() == (i + 2));
		// std::cout << "Entity created with id: " << entityTest2.getId() << std::endl;
	}

	tester.dettachComponent<Engine::Component>(entityTest.getId());
	tester.dettachComponent<testComponent>(entityTest.getId());
	REQUIRE(std::any_cast<Engine::Storage<Engine::Component>&>(*tester.getStorage<Engine::Component>()).size() == 0);
	REQUIRE(std::any_cast<Engine::Storage<testComponent>&>(*tester.getStorage<testComponent>()).size() == 0);
};


#include "UnixLibrary.hpp"

TEST_CASE("DynamicLoader") {
	// bstd::UnixLibrary linkedList("dll/liblinked.so");
}