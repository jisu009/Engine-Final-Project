/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Cat.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include "..\Engine\Input.h"
#include "..\Engine\Matrix.h"
#include "..\Engine\GameObject.h"
#include "..\Engine\Collision.h"
#include "GameObjectTypes.h"
#include "..\Engine\GameObjectManager.h"


class Ship : public CS230::GameObject {
public:
    Ship(Math::vec2 position, double rotation, Math::vec2 ship_scale);
    virtual void Update(double dt) override;
    virtual void Draw(Math::TransformationMatrix camera_matrix) override;
    GameObjectTypes Type() override { return GameObjectTypes::Ship; }
    std::string TypeName() override { return "Ship"; }
    bool CanCollideWith(GameObjectTypes) override;
    void ResolveCollision(GameObject* other_object) override;
    bool Exploded();

    enum class Animations {
        None,
        Explosion
    };

    enum class Flame_Animations {
        None,
        Flame
    };


private:
    static constexpr double speed = 700;
    static constexpr double drag = 1;
    static constexpr double rotation_speed = 5;
    CS230::Sprite flame_left;
    CS230::Sprite flame_right;
    bool leftflame;
    bool rightflame;

    bool exploded = false;


};
