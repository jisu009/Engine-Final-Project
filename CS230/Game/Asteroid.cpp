/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Asteroid.cpp
Project:    CS230 Engine
Author:     Jeonghun Byeon
Created:    March 29, 2025
*/

#pragma once
#include "Asteroid.h"
#include "../Engine/Engine.h"
#include "Mode1.h"



Asteroid::Asteroid(Math::vec2 start_position) :
    GameObject(start_position)
{
    AddGOComponent(new CS230::Sprite("Assets/Asteroid.spt", this));
    change_state(&state_landing);
}

bool Asteroid::CanCollideWith(GameObjectTypes type) {
    return type == GameObjectTypes::Floor;
}

void Asteroid::ResolveCollision(GameObject* other_object) {
    if (other_object->Type() == GameObjectTypes::Floor) {
        SetPosition({ GetPosition().x, other_object->GetGOComponent<CS230::RectCollision>()->WorldBoundary().Top() });
        SetVelocity({ 0, 0 });
        change_state(&state_landing);
    }
}


void Asteroid::State_Bouncing::Enter(GameObject* object) {
    Asteroid* asteroid = static_cast<Asteroid*>(object);

    asteroid->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
    asteroid->SetVelocity({ 0, bounce_velocity });
}
void Asteroid::State_Bouncing::Update(GameObject* object, double dt) {
    Asteroid* asteroid = static_cast<Asteroid*>(object);

    asteroid->SetVelocity({ asteroid->GetVelocity().x, asteroid->GetVelocity().y - Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() * dt });
}
void Asteroid::State_Bouncing::CheckExit([[maybe_unused]] GameObject* object) {

}

void Asteroid::State_Landing::Enter(GameObject* object) {
    Asteroid* asteroid = static_cast<Asteroid*>(object);

    asteroid->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Land));
}
void Asteroid::State_Landing::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {

}
void Asteroid::State_Landing::CheckExit(GameObject* object) {
    Asteroid* asteroid = static_cast<Asteroid*>(object);

    if (asteroid->GetGOComponent<CS230::Sprite>()->AnimationEnded() == true) {
        asteroid->change_state(&asteroid->state_bouncing);
    }
}
