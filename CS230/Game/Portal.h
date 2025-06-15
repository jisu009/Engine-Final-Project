#pragma once
#include "..\Engine\Matrix.h"
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Portal : public CS230::GameObject {
public:
    Portal(int to_state, Math::irect boundary);
    virtual GameObjectTypes Type() override { return GameObjectTypes::Portal; }
    std::string TypeName() override { return "Portal"; }

    void GoToState();

private:
    int to_state;
};
