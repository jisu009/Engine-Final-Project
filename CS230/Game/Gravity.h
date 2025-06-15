#pragma once
#include "../Engine/Component.h"

class Gravity : public CS230::Component {
public:
    Gravity(double value) : gravity(value) {}
    double GetValue() { return gravity; }
private:
    double gravity;
};
