/*
** EPITECH PROJECT, 2018
** tech2
** File description:
** IComponent
*/

#pragma once

#include <string>
#include <ctime>

namespace Engine {
	struct Component {};

	template <typename T>
	using is_component = std::is_base_of<Component, T>;
}
