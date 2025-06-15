
#pragma once
#include "..\Engine\Matrix.h"
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Floor : public CS230::GameObject {
public:
    Floor(Math::irect boundary);
    virtual GameObjectTypes Type() override { return GameObjectTypes::Floor; }
    std::string TypeName() override { return "Floor"; }
};

