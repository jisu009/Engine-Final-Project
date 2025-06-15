#pragma once
#include "Portal.h"
#include "../Engine/Engine.h"
#include "Mode1.h"

Portal::Portal(int to_state, Math::irect boundary) :
    GameObject(static_cast<Math::vec2>(boundary.point_1)),
    to_state(to_state) {
    AddGOComponent(new CS230::RectCollision({ Math::ivec2{ 0, 0 }, boundary.Size() }, this));
}

void Portal::GoToState() {
    Engine::GetGameStateManager().SetNextGameState(to_state);
}