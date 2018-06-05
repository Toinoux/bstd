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
		int value = bstd::randomise<size_t>(1, nbThread);
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
		int value = bstd::randomise<size_t>(nbThread, 200);
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
}