/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode2.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/


#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "../Engine/Sprite.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/Particle.h"
#include "../Game/Particles.h"
#include <raylib.h>

class Ship;

class Mode2 : public CS230::GameState {
public:
    Mode2();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override {
        return "Mode2";
    }

private:
    CS230::Texture texture;

    Ship* ship;
    CS230::Texture* restart;
    CS230::Texture* gameover;

    unsigned int color = 0xFFFFFFFF;

    static constexpr double meteor_timer = 4.5;
    double last_time = 0.0;

    CS230::Texture* score_texture;
    int score;
    void update_score_text(int value);

};
