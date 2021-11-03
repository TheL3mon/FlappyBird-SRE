//
// Created by Morten Nobel-Jørgensen on 19/10/2017.
//

#include <SDL_events.h>
#include <iostream>
#include <memory>
#include "BirdController.hpp"
#include "GameObject.hpp"
#include "SpriteComponent.hpp"
#include "PhysicsComponent.hpp"
#include "BirdGame.hpp"
#include "SpriteComponent.hpp"

BirdController::BirdController(GameObject *gameObject) : Component(gameObject) {
    gameObject->getComponent<PhysicsComponent>().get()->setLinearVelocity(glm::vec2(1,0));
}

bool BirdController::onKey(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN){
        std::cout << "some key pressed" << std::endl;
    } else if (event.type == SDL_KEYUP){
        std::cout << "some key released" << std::endl;
    }

    if (event.key.keysym.sym == SDLK_SPACE)
    {
        gameObject->getComponent<PhysicsComponent>().get()->addImpulse(glm::vec2(0, 0.05f));
    }

    return false;
}

void BirdController::onCollisionStart(PhysicsComponent *comp) {
    if (comp->getGameObject()->name.find("Wall") != std::string::npos)
    {
        BirdGame::instance->setGameState(GameState::GameOver);
    }

    if (comp->getGameObject()->name.find("Coin") != std::string::npos)
    {
        comp->getGameObject()->removeComponent(comp->getGameObject()->getComponent<PhysicsComponent>());
        comp->getGameObject()->readyToDelete = true;
    }
}

void BirdController::onCollisionEnd(PhysicsComponent *comp) {

}


