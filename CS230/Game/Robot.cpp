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
#include "Robot.h"
#include "../Engine/Engine.h"
#include "Mode1.h"
#include "../Engine/Score.h"



Robot::Robot(Math::vec2 position, Cat* cat, double left_boundary, double right_boundary)
    : CS230::GameObject(position), left(left_boundary), right(right_boundary), cat_ptr(cat) {
    AddGOComponent(new CS230::Sprite("Assets/Robot.spt", this));
    change_state(&state_walking);

    
}

void Robot::ResolveCollision(GameObject* other_object) {
    if (other_object->Type() == GameObjectTypes::Cat) {
        RemoveGOComponent<CS230::Collision>();
        change_state(&state_broken);
        Engine::GetGameStateManager().GetGSComponent<CS230::Score>()->Add(1);

    }
}


void Robot::State_Broken::Enter(GameObject* object) {
    Robot* robot = static_cast<Robot*>(object);

    robot->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Broken));
    robot->SetVelocity({ 0.0, 0.0 });
}
void Robot::State_Broken::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {

}
void Robot::State_Broken::CheckExit([[maybe_unused]] GameObject* object) {

}


void Robot::State_Walking::Enter(GameObject* object) {
    Robot* robot = static_cast<Robot*>(object);

    robot->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Walking));
}
void Robot::State_Walking::Update(GameObject* object, [[maybe_unused]] double dt) {
    Robot* robot = static_cast<Robot*>(object);

    if (robot->GetVelocity().x == 0.0) {
        robot->SetVelocity({ walking_speed, 0.0 });
    }

    if (robot->GetPosition().x <= robot->left) {
        robot->SetVelocity({ walking_speed, 0.0 });
        robot->SetScale({ 1.0, 1.0 });
    }
    else if (robot->GetPosition().x >= robot->right) {
        robot->SetVelocity({ -walking_speed, 0.0 });
        robot->SetScale({ -1.0, 1.0 });
    }
}
void Robot::State_Walking::CheckExit(GameObject* object) {
    Robot* robot = static_cast<Robot*>(object);

    if (robot->cat_ptr->GetPosition().x >= robot->left && robot->cat_ptr->GetPosition().x <= robot->right) {
        if ((robot->GetScale().x > 0 && robot->cat_ptr->GetPosition().x > robot->GetPosition().x) || (robot->GetScale().x < 0 && robot->cat_ptr->GetPosition().x < robot->GetPosition().x)) {
            robot->change_state(&robot->state_angry);
        }
    }
}


void Robot::State_Angry::Enter(GameObject* object) {
    Robot* robot = static_cast<Robot*>(object);

    robot->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Angry));
}
void Robot::State_Angry::Update(GameObject* object, [[maybe_unused]] double dt) {
    Robot* robot = static_cast<Robot*>(object);

    if ((robot->GetScale().x > 0) && (robot->cat_ptr->GetPosition().x > robot->GetPosition().x)) {
        robot->SetVelocity({ angry_speed, 0.0 });
    }
    else if ((robot->GetScale().x < 0) && (robot->cat_ptr->GetPosition().x < robot->GetPosition().x)) {
        robot->SetVelocity({ -angry_speed, 0.0 });
    }

    if (robot->GetPosition().x <= robot->left) {
        robot->SetVelocity({ angry_speed, 0.0 });
        robot->SetScale({ 1.0, 1.0 });
    }
    else if (robot->GetPosition().x >= robot->right) {
        robot->SetVelocity({ -angry_speed, 0.0 });
        robot->SetScale({ -1.0, 1.0 });
    }

    if ((robot->cat_ptr->GetPosition().x < robot->left) || (robot->cat_ptr->GetPosition().x > robot->right)) {
        robot->change_state(&robot->state_walking);
    }
}
void Robot::State_Angry::CheckExit([[maybe_unused]] GameObject* object) {

}