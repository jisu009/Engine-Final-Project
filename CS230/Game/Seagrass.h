/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Seagrass.h
Project:    CS230 Engine
Author:     Jeonghun Byeon, Jisu Son
Created:    June 16, 2025
*/

#pragma once
#pragma once
#include "..\Engine\Matrix.h"
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Seagrass : public CS230::GameObject {
public:
    Seagrass(Math::vec2 start_position);
    GameObjectTypes Type() override { return GameObjectTypes::Seagrass; }
    std::string TypeName() override { return "Seagrass"; }
    /* bool CanCollideWith(GameObjectTypes type) override;
     void ResolveCollision(GameObject* other_object) override;*/

    enum class Animations {
        Move
    };

    class State_Moving : public CS230::GameObject::State {
    public:
        void Enter(GameObject* object) override;
        void Update(GameObject* object, double dt) override;
        void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Moving"; }
    };

    State_Moving state_moving;
};
