/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Seagrass.cpp
Project:    CS230 Engine
Author:     Jeonghun Byeon, Jisu Son
Created:    June 16, 2025
*/

#pragma once
#include "Seagrass.h"
#include "../Engine/Engine.h"
#include "Mode3.h"

Seagrass::Seagrass(Math::vec2 start_position) :
    GameObject(start_position)
{
    AddGOComponent(new CS230::Sprite("Assets/Seagrass.spt", this));

    current_state = &state_moving;
    current_state->Enter(this);

}

void Seagrass::State_Moving::Enter(GameObject* object)
{
    auto* grass = static_cast<Seagrass*>(object);
    grass->GetGOComponent<CS230::Sprite>()
        ->PlayAnimation(static_cast<int>(Animations::Move));
}
void Seagrass::State_Moving::Update(GameObject* /*object*/, double /*dt*/)
{
}

void Seagrass::State_Moving::CheckExit(GameObject* /*object*/)
{
}