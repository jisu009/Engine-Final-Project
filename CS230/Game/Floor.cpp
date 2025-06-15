#include "Floor.h"
#include "../Engine/Engine.h"
#include "Mode1.h"

Floor::Floor(Math::irect boundary) : GameObject(static_cast<Math::vec2>(boundary.point_1)) {
    AddGOComponent(new CS230::RectCollision({ Math::ivec2{ 0, 0 }, boundary.Size() }, this));
}
