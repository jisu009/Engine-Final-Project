/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Meteor.h
Project:    CS230 Engine
Updated:    Aprill 30, 2023
Updated:    Aprill 30, 2023
*/

#pragma once
#include "..\Engine\Matrix.h"
#include "..\Engine\GameObject.h"
#include "..\Game\GameObjectTypes.h"
#include "..\Engine\Particle.h"
#include "..\Game\Particles.h"

class Meteor : public CS230::GameObject {
public:
    Meteor();
    Meteor(Meteor* parent);
    GameObjectTypes Type() override { return GameObjectTypes::Meteor; }
    std::string TypeName() override { return "Meteor"; }
    void Update(double dt) override;
    void ResolveCollision(GameObject* other_object) override;

private:
    double health;
    int size;
    static constexpr double default_velocity = 100;
    static constexpr double default_size = 2;
    static constexpr double default_healths[] = { 3, 5, 8 };
    static constexpr double default_scales[] = { 0.5, 0.75, 1.0 };

    enum class Animations {
        None,
        Fade
    };
};
