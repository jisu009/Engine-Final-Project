/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Seeker.cpp
Project:    CS230 Engine
Author:     Jeonghun Byeon, Jisu Son
Created:    June 15, 2025
*/

#include "Seeker.h"
#include "../Engine/Camera.h"
#include "Gravity.h"

Seeker::Seeker(Math::vec2 start_position/*, CS230::GameObject* starting_floor_ptr*/ )
	: GameObject(start_position)
{
	SetVelocity({ 0,0 });
	AddGOComponent(new CS230::Sprite("Assets/Seeker.spt", this));

    //SetScale({ 1.5, 1.5 });
	current_state = &state_idle;
	current_state->Enter(this);
}

void Seeker::Update(double dt) {
	GameObject::Update(dt);
    SetScale({ 1.5, 1.5 });
    update_x_velocity(dt);
}

void Seeker::update_x_velocity(double dt) {
    Math::vec2 v = GetVelocity();

    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        v.x += x_acceleration * dt;
        if (v.x > max_velocity) {
            v.x = max_velocity;
        }
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
        v.x -= x_acceleration * dt;
        if (v.x < -max_velocity) {
            v.x = -max_velocity;
        }
    }
    else {
        if (v.x > x_drag * dt) {
            v.x -= x_drag * dt;
        }
        else if (v.x < -x_drag * dt) {
            v.x += x_drag * dt;
        }
        else {
            v.x = 0;
        }
    }
    SetVelocity(v);
}

void Seeker::State_Running::Enter(GameObject* object) {
    Seeker* seeker = static_cast<Seeker*>(object);

    seeker->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Running));

    auto& input = Engine::GetInput();

    if (input.KeyDown(CS230::Input::Keys::Left)) {
        seeker->SetScale({ -1, 1 });
    }
    else if (input.KeyDown(CS230::Input::Keys::Right)) {
        seeker->SetScale({ 1,1 });
    }
}
void Seeker::State_Running::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
    Seeker* seeker = static_cast<Seeker*>(object);
    seeker->update_x_velocity(dt);
}
void Seeker::State_Running::CheckExit(GameObject* object) {
    Seeker* seeker = static_cast<Seeker*>(object);
    Math::vec2 v = seeker->GetVelocity();
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Up)) {
        seeker->change_state(&seeker->state_jumping);
    }
    else if (v.x == 0) {
        seeker->change_state(&seeker->state_idle);
    }
}

void Seeker::State_Jumping::Enter(GameObject* object) {
    Seeker* seeker = static_cast<Seeker*>(object);
    seeker->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Jumping));
    Math::vec2 v = seeker->GetVelocity();
    v.y = Seeker::jump_velocity;
    seeker->SetVelocity(v);
}
void Seeker::State_Jumping::Update(GameObject* object, double dt) {
     Seeker* seeker = static_cast<Seeker*>(object);   
     Math::vec2 v = seeker->GetVelocity();
     v.y += Mode3::gravity;
    seeker->SetVelocity({ seeker->GetVelocity().x, seeker->GetVelocity().y - Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() * dt });
    seeker->update_x_velocity(dt);
}
void Seeker::State_Jumping::CheckExit(GameObject* object) {
    Seeker* seeker = static_cast<Seeker*>(object);
    Math::vec2 v = seeker->GetVelocity();
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Up) == false) {
        seeker->change_state(&seeker->state_falling);
        seeker->SetVelocity({ seeker->GetVelocity().x, 0 });
    }
    else if (seeker->GetVelocity().y <= 0) {
        seeker->change_state(&seeker->state_falling);
    }
}

void Seeker::State_Idle::Enter([[maybe_unused]] GameObject* object) {
    Seeker* seeker = static_cast<Seeker*>(object);
    seeker->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
}
void Seeker::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
}
void Seeker::State_Idle::CheckExit(GameObject* object) {
    Seeker* seeker = static_cast<Seeker*>(object);
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
        seeker->change_state(&seeker->state_running);
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        seeker->change_state(&seeker->state_running);
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Up)) {
        seeker->change_state(&seeker->state_jumping);
    }
}

void Seeker::State_Falling::Enter(GameObject* object) {
    Seeker* seeker = static_cast<Seeker*>(object);
    seeker->fall_start_y_position = seeker->GetPosition().y;
    seeker->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Falling));
}
void Seeker::State_Falling::Update(GameObject* object, double dt) {
    Seeker* seeker = static_cast<Seeker*>(object);
    seeker->SetVelocity({ seeker->GetVelocity().x, seeker->GetVelocity().y - Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() * dt });
    seeker->update_x_velocity(dt);
}
void Seeker::State_Falling::CheckExit(GameObject* object)
{
    Seeker* seeker = static_cast<Seeker*>(object);
    if (seeker->GetPosition().y <= Mode3::floor) {  
        seeker->SetPosition({ seeker->GetPosition().x, Mode3::floor });
        Math::vec2 v = seeker->GetVelocity();
        v.y = 0;
        seeker->SetVelocity(v);

        if (std::abs(v.x) < 1.0)
            seeker->change_state(&seeker->state_idle);
        else
            seeker->change_state(&seeker->state_running);
    }
        
}


void Seeker::Draw(Math::TransformationMatrix camer_matrix) {
    CS230::GameObject::Draw(camer_matrix);
}