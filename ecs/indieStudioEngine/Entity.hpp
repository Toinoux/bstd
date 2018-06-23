/*
** EPITECH PROJECT, 2018
** tech2
** File description:
** Entity
*/

#pragma once

#include <cstddef>
#include <memory>

namespace Engine {
	class Entity {
	public:
		Entity() = default;
		Entity(size_t id) : _id(id) {};
		Entity(Entity &&) = default;
		Entity(const Entity &) = default;
		Entity &operator=(Entity &&) = delete;
		Entity &operator=(const Entity &) = delete;

	public:
		size_t getId() const noexcept {
			return (_id);
		};

	public:
		~Entity() = default;

	private:
		size_t _id;
	};
}