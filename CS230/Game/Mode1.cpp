
#include <iostream>
#include "../Game/Cat.h"
#include "../Game/Asteroid.h"
#include "../Game/Crates.h"
#include "../Game/Robot.h"
#include "../Engine/Engine.h"
#include "Fonts.h"
#include "States.h"
#include "Mode1.h"
#include <raylib.h>
#include "Gravity.h"
#include "Floor.h"
#include "Portal.h"
#include "../Engine/Score.h"
#include "Particles.h"



Mode1::Mode1() {

}

void Mode1::Load() {
#ifdef _DEBUG
    AddGSComponent(new CS230::ShowCollision());
#endif

    AddGSComponent(new CS230::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, { 0.35 * Engine::GetWindow().GetSize().x, 0 } }));
    AddGSComponent(new Gravity(Mode1::gravity));
    AddGSComponent(new CS230::Timer(timer_max));
    AddGSComponent(new CS230::GameObjectManager());
    AddGSComponent(new Background());
    AddGSComponent(new CS230::Score());
    AddGSComponent(new CS230::ParticleManager<Particles::Smoke>());


    GetGSComponent<Background>()->Add("Assets/Planets.png", 0.25);
    GetGSComponent<Background>()->Add("Assets/Ships.png", 0.5);
    GetGSComponent<Background>()->Add("Assets/Foreground.png", 1.0);

    Floor* starting_floor_ptr = new Floor(Math::irect{ { 0, 0 }, { 930, static_cast<int>(floor) } });
    GetGSComponent<CS230::GameObjectManager>()->Add(starting_floor_ptr);
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 1014, 0 }, { 2700, static_cast<int>(floor) } }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 2884, 0 }, { 4126, static_cast<int>(floor) } }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 4208, 0 }, { 5760, static_cast<int>(floor) } }));

    cat_ptr = new Cat({ 300, floor }, starting_floor_ptr);
    GetGSComponent<CS230::GameObjectManager>()->Add(cat_ptr);

    GetGSComponent<CS230::GameObjectManager>()->Add(new Asteroid({ 600, floor }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Asteroid({ 1800, floor }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Asteroid({ 2400, floor }));

    GetGSComponent<CS230::GameObjectManager>()->Add(new Crates({ 900, floor }, 2));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Crates({ 1400, floor }, 1));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Crates({ 2000, floor }, 5));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Crates({ 4000, floor }, 3));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Crates({ 5450, floor }, 1));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Crates({ 5525, floor }, 3));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Crates({ 5600, floor }, 5));

    GetGSComponent<CS230::GameObjectManager>()->Add(new Robot({ 1025, floor }, cat_ptr, 1025, 1350));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Robot({ 2050, floor }, cat_ptr, 2050, 2325));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Robot({ 3400, floor }, cat_ptr, 3400, 3800));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Robot({ 4225, floor }, cat_ptr, 4225, 4800));


    GetGSComponent<CS230::GameObjectManager>()->Add(new Portal(static_cast<int>(States::MainMenu), Math::irect{ { 5750, 0 }, { 5760, 600 } }));

    GetGSComponent<CS230::Camera>()->SetPosition({ 0,0 });
    GetGSComponent<CS230::Camera>()->SetLimit({ { 0,0 }, { GetGSComponent<Background>()->GetSize() - Engine::GetWindow().GetSize() } });

    last_timer = static_cast<int>(timer_max);
    update_timer_text(last_timer);

    score = GetGSComponent<CS230::Score>()->Value();
    update_score_text(score);

}

void Mode1::Update(double dt) {
    UpdateGSComponents(dt);
    GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);
    if (IsKeyPressed(KEY_ESCAPE)) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }
    GetGSComponent<CS230::Camera>()->Update(cat_ptr->GetPosition());

    if (GetGSComponent<CS230::Timer>()->RemainingInt() < last_timer) {
        last_timer = GetGSComponent<CS230::Timer>()->RemainingInt();
        update_timer_text(last_timer);
    }
    if (last_timer == 0) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }

    if (score != GetGSComponent<CS230::Score>()->Value()) {
        score = GetGSComponent<CS230::Score>()->Value();
        update_score_text(score);
    }

}

void Mode1::Unload() {
    cat_ptr = nullptr;
    ClearGSComponents();

}

void Mode1::Draw() {
    Engine::GetWindow().Clear(0x000000FF);
    Math::TransformationMatrix camera_matrix = GetGSComponent<CS230::Camera>()->GetMatrix();
    GetGSComponent<Background>()->Draw(*GetGSComponent<CS230::Camera>());
    GetGSComponent<CS230::GameObjectManager>()->DrawAll(camera_matrix);

    Math::ivec2 window_size = Engine::GetWindow().GetSize();
    timer_texture->Draw(Math::TranslationMatrix(Math::ivec2{ window_size.x - 10 - timer_texture->GetSize().x, window_size.y - timer_texture->GetSize().y - 5 }));
    score_texture->Draw(Math::TranslationMatrix(Math::ivec2{ window_size.x - 10 - score_texture->GetSize().x, window_size.y - score_texture->GetSize().y - 100 }));


}

void Mode1::update_timer_text(int value) {
    timer_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Timer: " + std::to_string(value), 0xFFFFFFFF);
}

void Mode1::update_score_text(int value) {
    score_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Score: " + std::to_string(value), 0xFFFFFFFF);
}