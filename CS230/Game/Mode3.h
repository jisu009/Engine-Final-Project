/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode3.h
Project:    CS230 Engine
Author:     Jeonghun Byeon, Jisu Son
Created:    June 15, 2025
*/
#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "../Engine/Sprite.h"
#include "../Engine/GameObjectManager.h"
#include "../Game/Particles.h"
#include "Gravity.h"
#include <raylib.h>


class Seeker;

class Mode3 : public CS230::GameState {
public:
    Mode3();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override {
        return "Mode3";
    }

    static constexpr double gravity = 180;
    static constexpr double floor = 200;
private:
    CS230::Texture texture;
    Seeker* seeker_ptr;

};