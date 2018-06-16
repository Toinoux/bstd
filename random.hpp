/*
** EPITECH PROJECT, 2018
** tech2
** File description:
** random
*/

#pragma once

#include <type_traits>
#include <random>
#include <limits>

namespace bstd {
	template<typename T>
	T randomise(T start = std::numeric_limits<T>::lowest(), T end = std::numeric_limits<T>::max()) {
		static_assert(std::is_arithmetic<T>::value, "Only arithmetic types can be randomised");
		if constexpr (std::is_floating_point<T>::value) {
			static std::random_device device;
			static std::mt19937_64 engine(device());
			std::uniform_real_distribution<T> distrib(start, end);
			return (distrib(engine));
		} else {
			static std::random_device device;
			static std::mt19937_64 engine(device());
			std::uniform_int_distribution<T> distrib(start, end);
			return (distrib(engine));
		}
	}
}