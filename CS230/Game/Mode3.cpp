/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode3.cpp
Project:    CS230 Engine
Author:     Jeonghun Byeon, Jisu Son
Created:    June 15, 2025
*/

#include "Mode3.h"
#include "Background.h"
#include "States.h"
#include "Floor.h"
#include "Seeker.h"

Mode3::Mode3()
{
}

void Mode3::Load()
{
    AddGSComponent(new CS230::Camera(
        Math::rect(
            Math::vec2(0.15f * Engine::GetWindow().GetSize().x, 0.0f),
            Math::vec2(0.35f * Engine::GetWindow().GetSize().x, 0.0f)
        )
    ));

    AddGSComponent(new Gravity(Mode3::gravity));
    AddGSComponent(new CS230::GameObjectManager());
    AddGSComponent(new Background());
    // --
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor({ {0,0},{800,(int)floor} }));
    seeker_ptr = new Seeker({ 20,floor });
    GetGSComponent<CS230::GameObjectManager>()->Add(seeker_ptr);
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ {800, 0} , { 2700, static_cast<int>(floor)} }));



    GetGSComponent<Background>()->Add("Assets/mode3_background.png", 0.25);
    GetGSComponent<Background>()->Add("Assets/mode3_floor.png", 0.35);
    GetGSComponent<Background>()->Add("Assets/mode3_fore.png", 0.2);


    Floor* starting_floor_ptr = new Floor(Math::irect{ { 0, 0 }, { 800, static_cast<int>(floor) } });
    GetGSComponent<CS230::GameObjectManager>()->Add(starting_floor_ptr);

    GetGSComponent<CS230::Camera>()->SetPosition({ 0, 0 });
    GetGSComponent<CS230::Camera>()->SetLimit({ { 0,0 }, 
{     GetGSComponent<Background>()->GetSize() - Engine::GetWindow().GetSize() } });

}

void Mode3::Update(double dt)
{
    UpdateGSComponents(dt);
    GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);
    if (IsKeyPressed(KEY_ESCAPE)) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }
}

void Mode3::Draw()
{
    Engine::GetWindow().Clear(0x000000FF);
    Math::TransformationMatrix camera_matrix = GetGSComponent<CS230::Camera>()->GetMatrix();
    GetGSComponent<Background>()->Draw(*GetGSComponent<CS230::Camera>());
    GetGSComponent<CS230::GameObjectManager>()->DrawAll(camera_matrix);

    Math::ivec2 window_size = Engine::GetWindow().GetSize();
}

void Mode3::Unload()
{
    GetGSComponent<Background>()->Unload();
    GetGSComponent<CS230::GameObjectManager>()->Unload();

    ClearGSComponents();
}

