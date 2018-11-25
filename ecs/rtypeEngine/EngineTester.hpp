/*
** EPITECH PROJECT, 2018
** tech2
** File description:
** main
*/

#include <iostream>

#include "Engine.hpp"
#include "IComponent.hpp"
#include "ISystem.hpp"

struct testComponent : Engine::Component {
	testComponent(int pX = 61, int pY = 61, int sX = 61, int sY = 61) :
		posX(pX), posY(pY), speedX(sX), speedY(sY) {};
	int posX;
	int posY;
	int speedX;
	int speedY;
};

class testSystem : Engine::System {
public:
	testSystem() {};
	~testSystem() {};

public:
	void update(Engine::Event &) override {
		for (auto &component : std::any_cast<Engine::Storage<testComponent>&>(*storage)) {
			component.second.posX += component.second.speedX;
			component.second.posY += component.second.speedY;
		}
		// printStorage();
	};

	void setStorage(std::shared_ptr<std::any> &ptr) override {
		storage = ptr;
	};

	void printStorage() const noexcept {
		for (auto &component : std::any_cast<Engine::Storage<testComponent>&>(*storage)) {
			std::cout << "X" << component.second.posX << " - " << component.second.speedX
			<< std::endl << "Y" << component.second.posY << " - " << component.second.speedY << std::endl;
		}
	};
public:
	std::shared_ptr<std::any> storage;
};