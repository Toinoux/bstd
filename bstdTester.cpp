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

#include "random.hpp"
#include "types.hpp"

TEST_CASE("isSameType") {
	REQUIRE(bstd::isSameType<A, A>());
	REQUIRE_FALSE(bstd::isSameType<A, B>());
	REQUIRE_FALSE(bstd::isSameType<A, C>());
}

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