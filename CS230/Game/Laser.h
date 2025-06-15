
#pragma once
#include "..\Engine\Matrix.h"
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Laser : public CS230::GameObject {
public:
    Laser(Math::vec2 pos, double rot, Math::vec2 scale, Math::vec2 vel);
    GameObjectTypes Type() override { return GameObjectTypes::Laser; }
    std::string TypeName() override { return "Laser"; }
    void Update(double dt) override;
    bool CanCollideWith(GameObjectTypes other_object_type) override;
    void ResolveCollision(GameObject* other_object) override;

    static constexpr double DefaultVelocity = 600;
};

