/*
** EPITECH PROJECT, 2018
** tech2
** File description:
** Engine
*/

#pragma once

#include <unordered_map>
#include <type_traits>
#include <typeindex>
#include <iostream>
#include <memory>
#include <vector>
#include <any>

#include "IComponent.hpp"
#include "ISystem.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

namespace Engine {
	template<typename T>
	using Storage = std::unordered_map<size_t, T>;

	using Event = rtype::server::Utils::KeyEvent;
	using Info = int;

	template <typename... Args>
	struct Updater;

	template <typename First, typename... Args>
	struct Updater<First, Args...>
	{
		static std::vector<std::string> update(std::vector<std::shared_ptr<std::any>> &systems, Event &event)
		{
			static_assert(is_system<First>::value, "Only systems can be updated");
			for (auto &sys : systems) {
				if (std::type_index((*sys).type()) == std::type_index(typeid(First))) {
					std::vector<std::string> upd = std::any_cast<First &>(*sys).update(event );
					Updater<Args...>::update(systems, event);
					
					return upd;
				}
			}
		}
	};

	template <>
	struct Updater<>
	{
		static std::vector<std::string> update(std::vector<std::shared_ptr<std::any>> &, Event &)
		{
		}
	};

	class Engine {
	public:
		Engine() : _idCounter(0) {};
		Engine(Engine &&) = delete;
		Engine(const Engine &) = default;
		Engine &operator=(Engine &&) = delete;
		Engine &operator=(const Engine &) = delete;

	public:
		Entity createEntity() noexcept {
			Entity entitySetter(++_idCounter);
			return (entitySetter);
		};

	public:
		template<typename T>
		void registerComponent() {
			static_assert(is_component<T>::value, "Only components can be registered");
			components.push_back(std::make_shared<std::any>(std::any(Storage<T>())));
		}

		template<typename T>
		void registerSystem() {
			static_assert(is_system<T>::value, "Only systems can be registered");
			systems.push_back(std::make_shared<std::any>(std::any(T())));
		}

		template<typename T>
		void registerSystemWithCoreRef() {
			static_assert(is_system<T>::value, "Only systems can be registered");
			systems.push_back(std::make_shared<std::any>(std::any(T(this))));
		}

	public:
		template<typename T>
		std::shared_ptr<std::any> &getSystem() {
			static_assert(is_system<T>::value, "You can only get System");
			for (auto &sys : systems) {
				if (std::type_index((*sys).type()) == std::type_index(typeid(T))) {
					return (sys);
				}
			}
			throw std::logic_error("No such system");
		};

		template<typename T>
		std::shared_ptr<std::any> &getStorage() {
			static_assert(is_component<T>::value, "You can only get components");
			for (auto &storage : components) {
				if (std::type_index((*storage).type()) == std::type_index(typeid(Storage<T>))) {
					return (storage);
				}
			}
			throw std::logic_error("No Component of this type");
		};

		template<typename T, typename ... Args>
		void attachComponent(const Entity &entity, Args ... args) {
 			std::any_cast<Storage<T>&>(*this->getStorage<T>()).emplace(entity.getId(), T(args ...));
 		};

		template<typename T>
		void dettachComponent(size_t id) {
			std::any_cast<Storage<T>&>(*this->getStorage<T>()).erase(id);
		};

		template<typename Sys, typename Comp>
		void setSystemStorage() {
			static_assert(is_system<Sys>::value, "You can only set a system storage");
			static_assert(is_component<Comp>::value, "Only component storage can be set");
			for (auto &sys : systems) {
				if (std::type_index((*sys).type()) == std::type_index(typeid(Sys))) {
					std::any_cast<Sys&>(*sys).setStorage(getStorage<Comp>());
					return ;
				}
			}
			throw std::logic_error("No such system");
		};

		template <typename... Args>
		std::vector<std::string> update(Event event) noexcept
		{
			Updater<Args...>::update(systems, event);
		}

		void setMap(std::vector<std::vector<Info>> &m) {
			map = m;
		};
	public:
		~Engine() = default;

	public:
		std::vector<std::vector<Info>> map;
		std::vector<std::shared_ptr<std::any>> components;
		std::vector<std::shared_ptr<std::any>> systems;

	private:
		size_t _idCounter;
	};
}
