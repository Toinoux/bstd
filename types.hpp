/*
** EPITECH PROJECT, 2018
** tech2
** File description:
** types
*/

#pragma once

#include <typeindex>
#include <string>

namespace bstd {
	template<typename T, typename U>
	constexpr bool isSameType() {
		return (std::type_index(typeid(T)) == std::type_index(typeid(U)));
	}

	template<typename Base, typename Derived>
	constexpr void derivedTest() {
		using is_derived = std::is_base_of<Base, Derived>;
		static_assert(is_derived::value, "Derived is not a child of Base");
	}
}