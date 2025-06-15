/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Robot.h
Project:    CS230 Engine
Author:     jeonghun Byeon
Updated:    Aprill 30, 2023
Updated:    Aprill 30, 2023
*/

#pragma once
#include "..\Engine\Matrix.h"
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"
#include "..\Game\Cat.h"

class Robot : public CS230::GameObject {
public:
    Robot(Math::vec2 position, Cat* cat, double left_boundary, double right_boundary);
    GameObjectTypes Type() override { return GameObjectTypes::Robot; }
    std::string TypeName() override { return "Robot"; }
    void ResolveCollision(GameObject* other_object) override;

    //Robot(Math::vec2 position);

private:
    double left;
    double right;
    Cat* cat_ptr;

    double start_y_position = 80;
    static constexpr double walking_speed = 75.0;
    static constexpr double angry_speed = 105.0;

    enum class Animations {
        None,
        Broken,
        Walking,
        Angry
    };

    class State_Broken : public CS230::GameObject::State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Broken"; }
    };

    State_Broken state_broken;

    class State_Walking : public CS230::GameObject::State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Walking"; }
    };

    State_Walking state_walking;

    class State_Angry : public CS230::GameObject::State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Angry"; }
    };

    State_Angry state_angry;
};