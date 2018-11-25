/*
** EPITECH PROJECT, 2018
** tech2
** File description:
** ISystem
*/

#pragma once

#include <memory>
#include <any>

namespace Engine {
	using Event = rtype::server::Utils::KeyEvent;

	class System {
	public:
		virtual void update(rtype::server::Utils::KeyEvent event) = 0;
		virtual void setStorage(std::shared_ptr<std::any> &ptr) = 0;
	public:
		virtual ~System() = default;
	};

	template <typename T>
	using is_system = std::is_base_of<System, T>;
}
