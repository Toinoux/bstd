/*
** EPITECH PROJECT, 2018
** tech2
** File description:
** main
*/

#include <iostream>

// #define CATCH_CONFIG_MAIN
// #include "catch.hpp"
#include "Engine.hpp"
#include "Component.hpp"
#include "System.hpp"

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
	void update() override {
		for (auto &component : std::any_cast<Engine::Storage<testComponent>&>(*storage)) {
			component.second.posX += component.second.speedX;
			component.second.posY += component.second.speedY;
		}
		printStorage();
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

// TEST_CASE ("ECS TEST") {
int main() {
	Engine::Engine tester;
	Engine::Entity entityTest(tester.createEntity());

	tester.registerComponent<Engine::Component>();
	auto storageTest = std::any_cast<Engine::Storage<Engine::Component>&>(*tester.getStorage<Engine::Component>());

	tester.registerComponent<testComponent>();
	auto storageTest2 = std::any_cast<Engine::Storage<testComponent>&>(*tester.getStorage<testComponent>());

	tester.attachComponent<Engine::Component>(entityTest);
	tester.attachComponent<testComponent>(entityTest);

	tester.registerSystem<testSystem>();
	auto systemTest = tester.getSystem<testSystem>();

	tester.setSystemStorage<testSystem, testComponent>();
	std::any_cast<testSystem&>(*systemTest).update();

	tester.update<testSystem, testSystem, testSystem>();

	for (size_t i = 0 ; i <  10 ; ++i) {
		Engine::Entity entityTest(tester.createEntity());
		std::cout << "Entity created with id: " << entityTest.getId() << std::endl;
	}

	tester.dettachComponent<Engine::Component>(entityTest);
	tester.dettachComponent<testComponent>(entityTest);
};
