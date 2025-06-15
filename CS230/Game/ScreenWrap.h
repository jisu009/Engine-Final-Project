#pragma once
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  ScreenManager.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    May 17, 2025
*/
#include "../Engine/GameObject.h"

class ScreenWrap : public CS230::Component {
public:
    ScreenWrap(CS230::GameObject& object) : object(object) {}
    void Update(double dt) override;
private:
    CS230::GameObject& object;
};
