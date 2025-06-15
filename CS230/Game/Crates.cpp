/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Asteroid.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    Aprill 30, 2023
*/



#include"Crates.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/Collision.h"

Crates::Crates(Math::vec2 position, int size) : CS230::GameObject(position) {
    switch (size) {
    case 1:
        AddGOComponent(new CS230::Sprite("Assets/Crates1.spt", this));
        break;
    case 2:
        AddGOComponent(new CS230::Sprite("Assets/Crates2.spt", this));
        break;
    case 3:
        AddGOComponent(new CS230::Sprite("Assets/Crates3.spt", this));
        break;
    case 5:
        AddGOComponent(new CS230::Sprite("Assets/Crates5.spt", this));
        break;
    }
}

void Crates::Draw(Math::TransformationMatrix camera_matrix)
{
    CS230::Sprite* sprite = GetGOComponent<CS230::Sprite>();
    if (sprite != nullptr) {
        sprite->Draw(camera_matrix * GetMatrix());
    }

    CS230::ShowCollision* show_collision = Engine::GetGameStateManager().GetGSComponent<CS230::ShowCollision>();
    if (show_collision != nullptr) {
        CS230::Collision* collision = GetGOComponent<CS230::Collision>();
        if (collision != nullptr && show_collision->Enabled()) {
            collision->Draw(camera_matrix);
        }
    }
}