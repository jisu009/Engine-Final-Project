/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Asteroid.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 24, 2023
Updated:    04/30/2024
*/

#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Crates : public CS230::GameObject {
public:
    Crates(Math::vec2 position, int size);
    void Draw(Math::TransformationMatrix camera_matrix);
    GameObjectTypes Type() override { return GameObjectTypes::Crates; }
    std::string TypeName() override { return "Crates"; }
private:
};
